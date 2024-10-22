import debug from 'debug'
import { randomUUID } from 'node:crypto'
import { existsSync, mkdirSync } from 'node:fs'
import { platform } from 'node:os'
import { dirname } from 'node:path'
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

  /**
   * Creates a new device.
   *
   * @param ip - The IP address of the device.
   * @param port - The port of the device.
   * @param settings - The settings for the device.
   * @throws {Error} If not running on Linux or initialization fails
   */
  constructor(ip: string, port = 9008, settings?: Settings) {
    if (platform() !== 'linux') {
      throw new Error('This SDK is only supported on Linux platforms')
    }

    this.ip = validateIp(ip)
    this.port = validatePort(port)
    this.uuid = settings?.uuid ?? randomUUID()

    if (settings) {
      this.#connectionTimeoutMs = settings.connectionTimeoutMs ?? this.#connectionTimeoutMs
      this.#maxRetries = settings.maxRetries ?? this.#maxRetries
      this.#reconnectIntervalMs = settings.reconnectIntervalMs ?? this.#reconnectIntervalMs
      this.#isReconnectEnabled = settings.isReconnectEnabled ?? this.#isReconnectEnabled
    }

    log(`Initializing device ${this.uuid} with IP: ${this.ip}:${this.port}`)

    // Initialize the SDK
    if (
      !sdk.init() ||
      !sdk.setConnectTimeout(this.#connectionTimeoutMs, this.#maxRetries) ||
      !sdk.setReconnectInterval(this.#reconnectIntervalMs, this.#isReconnectEnabled)
    ) {
      const error = this.getLastError()
      log(`Failed to initialize device ${this.uuid}: ${error}`)
      throw new Error(error)
    }

    // Get SDK version information
    const sdkVersion = sdk.getSDKVersion()
    const buildVersion = sdk.getSDKBuildVersion()
    this.#sdkVersion = `0x${sdkVersion.toString(16)} (${sdkVersion})`
    this.#sdkBuild = `${parseBuildDate(buildVersion.toString())} (${buildVersion})`

    log(`${this.uuid} device initialized successfully!`)
  }

  /**
   * Logout and dispose of the SDK resources.
   *
   * @returns A boolean indicating whether the disposal was successful.
   */
  dispose(): boolean {
    log(`Disposing device ${this.uuid}...`)

    try {
      if (this.userId) {
        this.logout()
      }
      const result = sdk.cleanup()
      log(`Device ${this.uuid} disposed successfully`)
      return result
    } catch (error) {
      log(`Failed to dispose device ${this.uuid}: ${error}`)
      return false
    }
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
   * Getter for device information.
   */
  @auth
  get info(): DeviceInfo {
    sdk.getDeviceInfo(this.userId, this.#deviceInfo)
    return this.#deviceInfo
  }

  /**
   * Logs into the device.
   *
   * @param user - The username.
   * @param pass - The password.
   * @returns A boolean indicating whether the login was successful.
   * @throws An error if the login fails.
   */
  @measure
  login(user: string, pass: string): boolean {
    log(`Logging in to device ${this.uuid} with user: ${user}`)

    try {
      this.userId = sdk.login(this.ip, this.port, user, pass, this.#deviceInfo)
      if (this.userId === -1) {
        throw new Error(this.getLastError())
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
   * @returns A boolean indicating whether the logout was successful.
   */
  @auth
  logout(): boolean {
    log(`Logging out from device ${this.uuid}`)
    try {
      const result = sdk.logout(this.userId)
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
   * @returns A boolean indicating whether the alarm was triggered successfully.
   */
  @auth
  triggerAlarm(value: boolean): boolean {
    log(`Triggering alarm on device ${this.uuid} with value: ${value}`)

    try {
      // @TODO: get alarm channels from device info
      const alarmChannels = [0]
      const alarmValues = [value ? 1 : 0]
      const result = sdk.triggerAlarm(
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
   * @returns - Returns true if the snapshot was successfully saved, false otherwise.
   */
  @auth
  saveSnapshot(channel: number, filePath: string): boolean {
    log(`Saving snapshot from device ${this.uuid} channel ${channel} to ${filePath}`)

    try {
      const dirPath = dirname(filePath)

      // sdk doesn't check if path is valid so we need to do it ourselves
      if (!existsSync(dirPath)) {
        mkdirSync(dirPath, { recursive: true })
      }

      const result = sdk.captureJPEGFile_V2(this.userId, channel, filePath)

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
   * @returns A string describing the last error.
   */
  getLastError(): string {
    return NET_SDK_ERROR[sdk.getLastError()] ?? 'Unknown error'
  }
}
