import { auth, measure } from './decorators/index.ts'
import { parseBuildDate } from './helpers/date.ts'
import { validateIp, validatePort } from './helpers/validators.ts'
import { sdk } from './sdk/index.ts'
import { NET_SDK_ERROR, type DeviceInfo } from './sdk/types.ts'

export type Settings = {
  connectionTimeoutMs?: number
  maxRetries?: number
  reconnectIntervalMs?: number
  isReconnectEnabled?: boolean
}

export type VersionInfo = {
  sdk: {
    version: string
    build: string
  }
  device: {
    name: string
    model: string
    SN: string
    firmware: string
    kernel: string
    hardware: string
    MCU: string
    software: number
  }
}

/**
 * Represents a generic TVT Device.
 */
export class Device {
  ip: string
  port: number
  // @ts-expect-error checking for userId is done inside the @auth decorator so unless the decorator is removed, userId will always be defined
  userId: number
  // @ts-expect-error deviceInfo is passed as a pointer to login function and should be initialized as an empty object
  deviceInfo: DeviceInfo = {}
  connectionTimeoutMs = 5 * 1000
  maxRetries = 3
  reconnectIntervalMs = 30 * 1000
  isReconnectEnabled = true
  isAlarmOpen = true

  sdkVersion: string | undefined
  sdkBuild: string | undefined

  /**
   * Creates a new device.
   *
   * @param ip - The IP address of the device.
   * @param port - The port of the device.
   * @param settings - The settings for the device.
   */
  constructor(ip: string, port = 9008, settings?: Settings) {
    this.ip = validateIp(ip)
    this.port = validatePort(port)

    if (settings) {
      this.connectionTimeoutMs = settings.connectionTimeoutMs ?? this.connectionTimeoutMs
      this.maxRetries = settings.maxRetries ?? this.maxRetries
      this.reconnectIntervalMs = settings.reconnectIntervalMs ?? this.reconnectIntervalMs
      this.isReconnectEnabled = settings.isReconnectEnabled ?? this.isReconnectEnabled
    }

    if (this.init()) {
      console.log('Device initialized successfully!')

      const sdkVersion = sdk.getSDKVersion()
      const buildVersion = sdk.getSDKBuildVersion()
      this.sdkVersion = `0x${sdkVersion.toString(16)} (${sdkVersion})`
      // that's a build date actually
      this.sdkBuild = `${parseBuildDate(buildVersion.toString())} (${buildVersion})`
    }
  }

  /**
   * Initializes the SDK.
   *
   * @returns A boolean indicating whether the initialization was successful.
   * @throws An error if the initialization fails.
   */
  init(): boolean {
    if (
      !sdk.init() ||
      !sdk.setConnectTimeout(this.connectionTimeoutMs, this.maxRetries) ||
      !sdk.setReconnectInterval(this.reconnectIntervalMs, this.isReconnectEnabled)
    ) {
      throw new Error(this.getLastError())
    }
    return true
  }

  /**
   * Logout and dispose of the SDK resources.
   *
   * @returns A boolean indicating whether the disposal was successful.
   */
  dispose(): boolean {
    if (this.userId) {
      this.logout()
    }
    return this.cleanup()
  }

  /**
   * Dispose of the SDK resources.
   *
   * @returns A boolean indicating whether the cleanup was successful.
   */
  cleanup(): boolean {
    return sdk.cleanup()
  }

  /**
   * This getter method returns the versions information of the device and sdk.
   * If the the information is not available, it throws an error.
   */
  @auth
  get version(): VersionInfo {
    if (this.deviceInfo === undefined) {
      throw new Error('Device info is not available!')
    }

    return {
      sdk: {
        version: this.sdkVersion ?? 'Unknown',
        build: this.sdkBuild ?? 'Unknown'
      },
      device: {
        name: this.deviceInfo.deviceName,
        model: this.deviceInfo.deviceProduct,
        SN: this.deviceInfo.szSN,
        firmware: this.deviceInfo.firmwareVersion,
        kernel: this.deviceInfo.kernelVersion,
        hardware: this.deviceInfo.hardwareVersion,
        MCU: this.deviceInfo.MCUVersion,
        software: this.deviceInfo.softwareVer
      }
    }
  }

  /**
   * Getter for device information.
   */
  @auth
  get info(): DeviceInfo {
    return this.deviceInfo
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
    this.userId = sdk.login(this.ip, this.port, user, pass, this.deviceInfo)
    if (this.userId === -1) {
      throw new Error(this.getLastError())
    }
    return Boolean(this.userId)
  }

  /**
   * Logs out of the device.
   *
   * @returns A boolean indicating whether the logout was successful.
   */
  @auth
  logout(): boolean {
    return sdk.logout(this.userId)
  }

  /**
   * Triggers an alarm on the device.
   *
   * @param value - A boolean indicating what state to set the alarm to.
   * @returns A boolean indicating whether the alarm was triggered successfully.
   */
  @auth
  triggerAlarm(value: boolean): boolean {
    const alarmChannels = [0]
    const alarmValues = [value ? 1 : 0]
    return sdk.triggerAlarm(this.userId, alarmChannels, alarmValues, alarmChannels.length, this.isAlarmOpen)
  }

  @auth
  saveSnapshot(channel: number, fileName: string): boolean {
    return sdk.captureJPEGFile_V2(this.userId, channel, fileName)
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
