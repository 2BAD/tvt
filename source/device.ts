/* eslint-disable jsdoc/require-jsdoc */
import { auth, measure } from './decorators/index.ts'
import { validateIp, validatePort } from './helpers/validators.ts'
import { sdk } from './sdk/index.ts'
import { NET_SDK_ERROR } from './sdk/types.ts'

export type Settings = {
  connectionTimeoutMs?: number
  maxRetries?: number
  reconnectIntervalMs?: number
  isReconnectEnabled?: boolean
}

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

  dispose(): boolean {
    // do not call logout if the user is not logged in a first place
    if (this.userId) {
      this.logout()
    }
    return this.cleanup()
  }

  cleanup(): boolean {
    return sdk.cleanup()
  }

  @measure
  login(user: string, pass: string): boolean {
    this.userId = sdk.login(this.ip, this.port, user, pass, this.deviceInfo)
    if (this.userId === -1) {
      throw new Error(this.getLastError())
    }
    return Boolean(this.userId)
  }

  @auth
  logout(): boolean {
    return sdk.logout(this.userId)
  }

  @auth
  triggerAlarm(value: boolean): boolean {
    const alarmChannels = [0]
    const alarmValues = [value ? 1 : 0]
    return sdk.triggerAlarm(this.userId, alarmChannels, alarmValues, alarmChannels.length, this.isAlarmOpen)
  }

  getLastError(): string {
    return NET_SDK_ERROR[sdk.getLastError()] ?? 'Unknown error'
  }
}
