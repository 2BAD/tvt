import debug from 'debug'
import { randomUUID } from 'node:crypto'
import { existsSync, mkdirSync } from 'node:fs'
import { platform } from 'node:os'
import { dirname } from 'node:path'
import pSeries from 'p-series'
import { auth, measure } from './decorators/index.ts'
import { parseBuildDate } from './helpers/date.ts'
import { validateIp, validatePort } from './helpers/validators.ts'
import { sdk } from './lib/sdk.ts'
import { NET_SDK_ERROR, type DeviceInfo } from './lib/types.ts'
import type { Settings, VersionInfo } from './types.ts'
export type * from './types.ts'

const log = debug('tvt:device')

/**
 * Represents a generic TVT Device.
 */
export class Device {
  readonly uuid: `${string}-${string}-${string}-${string}-${string}`
  readonly ip: string
  readonly port: number

  readonly #connectionTimeoutMs: number = 5 * 1000
  readonly #maxRetries: number = 3
  readonly #reconnectIntervalMs: number = 30 * 1000
  readonly #isReconnectEnabled: boolean = true
  readonly #isAlarmOpen: boolean = true

  // this could have been a private but it's used in the @auth decorator and decorators can't access private properties atm
  // @ts-expect-error checking for userId is done inside the @auth decorator so unless the decorator is removed, userId will always be defined
  userId: number
  // @ts-expect-error deviceInfo is passed as a pointer to login function and should be initialized as an empty object
  #deviceInfo: DeviceInfo = {}

  readonly #sdkVersion: string
  readonly #sdkBuild: string

  private constructor(ip: string, port: number, settings: Settings | undefined, sdkVersion: string, sdkBuild: string) {
    this.ip = ip
    this.port = port
    this.uuid = settings?.uuid ?? randomUUID()

    if (settings) {
      this.#connectionTimeoutMs = settings.connectionTimeoutMs ?? this.#connectionTimeoutMs
      this.#maxRetries = settings.maxRetries ?? this.#maxRetries
      this.#reconnectIntervalMs = settings.reconnectIntervalMs ?? this.#reconnectIntervalMs
      this.#isReconnectEnabled = settings.isReconnectEnabled ?? this.#isReconnectEnabled
    }

    this.#sdkVersion = sdkVersion
    this.#sdkBuild = sdkBuild

    log(`Device ${this.uuid} created with IP: ${this.ip}:${this.port}`)
  }

  /**
   * Creates and initializes a new Device instance.
   *
   * @param ip - The IP address of the device.
   * @param port - The port of the device.
   * @param settings - Optional settings for the device.
   * @returns A promise that resolves to an initialized Device instance
   * @throws {Error} If not running on Linux or initialization fails
   */
  public static async create(ip: string, port = 9008, settings?: Settings): Promise<Device> {
    if (platform() !== 'linux') {
      throw new Error('This SDK is only supported on Linux platforms')
    }

    const validatedIp = validateIp(ip)
    const validatedPort = validatePort(port)

    log(`Initializing device with IP: ${validatedIp}:${validatedPort}`)

    // Initialize the SDK
    const [initResult, timeoutResult, reconnectResult] = await pSeries([
      () => sdk.init(),
      () => sdk.setConnectTimeout(settings?.connectionTimeoutMs ?? 5000, settings?.maxRetries ?? 3),
      () => sdk.setReconnectInterval(settings?.reconnectIntervalMs ?? 30000, settings?.isReconnectEnabled ?? true)
    ])

    if (!initResult || !timeoutResult || !reconnectResult) {
      const errorCode = await sdk.getLastError()
      const error = NET_SDK_ERROR[errorCode] ?? 'Unknown error'
      log(`Failed to initialize device: ${error}`)
      throw new Error(error)
    }

    // Get SDK version information
    const [sdkVersion, buildVersion] = await Promise.all([sdk.getSDKVersion(), sdk.getSDKBuildVersion()])

    const formattedSdkVersion = `0x${sdkVersion.toString(16)} (${sdkVersion})`
    const formattedSdkBuild = `${parseBuildDate(buildVersion.toString())} (${buildVersion})`

    return new Device(validatedIp, validatedPort, settings, formattedSdkVersion, formattedSdkBuild)
  }

  /**
   * This getter method returns the versions information of the device and sdk.
   * If the information is not available, it throws an error.
   */
  @auth
  get version(): VersionInfo {
    if (this.#deviceInfo === undefined) {
      throw new Error('Device info is not available!')
    }

    return {
      sdk: {
        version: this.#sdkVersion,
        build: this.#sdkBuild
      },
      device: {
        name: this.#deviceInfo.deviceName,
        model: this.#deviceInfo.deviceProduct,
        SN: this.#deviceInfo.szSN,
        firmware: this.#deviceInfo.firmwareVersion,
        kernel: this.#deviceInfo.kernelVersion,
        hardware: this.#deviceInfo.hardwareVersion,
        MCU: this.#deviceInfo.MCUVersion,
        software: this.#deviceInfo.softwareVer
      }
    }
  }

  /**
   * Gets the device information.
   *
   * @returns A promise that resolves to the device information
   */
  @auth
  async getInfo(): Promise<DeviceInfo> {
    await sdk.getDeviceInfo(this.userId, this.#deviceInfo)
    return this.#deviceInfo
  }

  /**
   * Logs into the device.
   *
   * @param user - The username.
   * @param pass - The password.
   * @returns A promise that resolves to a boolean indicating whether the login was successful.
   * @throws An error if the login fails.
   */
  @measure
  async login(user: string, pass: string): Promise<boolean> {
    log(`Logging in to device ${this.uuid} with user: ${user}`)

    try {
      this.userId = await sdk.login(this.ip, this.port, user, pass, this.#deviceInfo)
      if (this.userId === -1) {
        throw new Error(await this.getLastError())
      }
      log(`Successfully logged in to device ${this.uuid}`)
      return Boolean(this.userId)
    } catch (error) {
      log(`Failed to log in to device ${this.uuid}: ${error}`)
      throw error
    }
  }

  /**
   * Logs out of the device.
   *
   * @returns A promise that resolves to a boolean indicating whether the logout was successful.
   */
  @auth
  async logout(): Promise<boolean> {
    log(`Logging out from device ${this.uuid}`)
    try {
      const result = await sdk.logout(this.userId)
      if (result) {
        log(`Successfully logged out from device ${this.uuid}`)
      } else {
        log(`Failed to log out from device ${this.uuid}`)
      }
      return result
    } catch (error) {
      log(`Error logging out from device ${this.uuid}: ${error}`)
      return false
    }
  }

  /**
   * Triggers an alarm on the device.
   *
   * @param value - A boolean indicating what state to set the alarm to.
   * @returns A promise that resolves to a boolean indicating whether the alarm was triggered successfully.
   */
  @auth
  async triggerAlarm(value: boolean): Promise<boolean> {
    log(`Triggering alarm on device ${this.uuid} with value: ${value}`)

    try {
      // @TODO: get alarm channels from device info
      const alarmChannels = [0]
      const alarmValues = [value ? 1 : 0]
      const result = await sdk.triggerAlarm(
        this.userId,
        alarmChannels,
        alarmValues,
        alarmChannels.length,
        this.#isAlarmOpen
      )

      if (result) {
        log(`Successfully triggered alarm on device ${this.uuid}`)
      } else {
        log(`Failed to trigger alarm on device ${this.uuid}`)
      }

      return result
    } catch (error) {
      log(`Error triggering alarm on device ${this.uuid}: ${error}`)
      return false
    }
  }

  /**
   * Saves a jpeg snapshot of a specific video channel to a file.
   *
   * @param channel - The channel number to save a snapshot of.
   * @param filePath - The path where the snapshot will be saved.
   * @returns A promise that resolves to a boolean indicating if the snapshot was successfully saved.
   */
  @auth
  async saveSnapshot(channel: number, filePath: string): Promise<boolean> {
    log(`Saving snapshot from device ${this.uuid} channel ${channel} to ${filePath}`)

    try {
      const dirPath = dirname(filePath)

      // sdk doesn't check if path is valid so we need to do it ourselves
      if (!existsSync(dirPath)) {
        mkdirSync(dirPath, { recursive: true })
      }

      const result = await sdk.captureJPEGFile_V2(this.userId, channel, filePath)

      if (result) {
        log(`Successfully saved snapshot from device ${this.uuid}`)
      } else {
        log(`Failed to save snapshot from device ${this.uuid}`)
      }

      return result
    } catch (error) {
      log(`Error saving snapshot from device ${this.uuid}: ${error}`)
      return false
    }
  }

  /**
   * Gets the last error that occurred.
   *
   * @returns A promise that resolves to a string describing the last error.
   */
  async getLastError(): Promise<string> {
    const errorCode = await sdk.getLastError()
    return NET_SDK_ERROR[errorCode] ?? 'Unknown error'
  }

  /**
   * Logout and dispose of the SDK resources.
   *
   * @returns A promise that resolves to a boolean indicating whether the disposal was successful.
   */
  async dispose(): Promise<boolean> {
    log(`Disposing device ${this.uuid}...`)

    try {
      if (this.userId) {
        await this.logout()
      }
      const result = await sdk.cleanup()
      log(`Device ${this.uuid} disposed successfully`)
      return result
    } catch (error) {
      log(`Failed to dispose device ${this.uuid}: ${error}`)
      return false
    }
  }
}
