import { auth, measure } from './decorators/index.ts'
import { parseBuildDate } from './helpers/date.ts'
import { validateIp, validatePort } from './helpers/validators.ts'
import { sdk } from './sdk/index.ts'
import { NET_SDK_ERROR } from './sdk/types.ts'

export type Settings = {
  connectionTimeoutMs?: number
  maxRetries?: number
  reconnectIntervalMs?: number
  isReconnectEnabled?: boolean
}

/**
 * Represents a generic TVT Device.
 */
export class Device {
  ip: string
  port: number
  // @ts-expect-error checking for userId is done inside the @auth decorator so unless the decorator is removed, userId will always be defined
  userId: number
  deviceInfo: Record<string, unknown> = {}
  connectionTimeoutMs = 5 * 1000
  maxRetries = 3
  reconnectIntervalMs = 30 * 1000
  isReconnectEnabled = true
  isAlarmOpen = true

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

    this.init()
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
   * Gets the build and SDK version.
   */
  version(): void {
    const sdkVersion = sdk.getSDKVersion()
    const buildVersion = sdk.getSDKBuildVersion()
    console.log(`SDK version: 0x${sdkVersion.toString(16)} (${sdkVersion})`)
    // that's a build date actually
    console.log(`Build date: ${parseBuildDate(buildVersion.toString())} (${buildVersion})`)
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
   * @param value - A boolean indicating whether to trigger the alarm.
   * @returns A boolean indicating whether the alarm was triggered successfully.
   */
  @auth
  triggerAlarm(value: boolean): boolean {
    const alarmChannels = [0]
    const alarmValues = [value ? 1 : 0]
    return sdk.triggerAlarm(this.userId, alarmChannels, alarmValues, alarmChannels.length, this.isAlarmOpen)
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
