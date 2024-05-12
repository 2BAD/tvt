/* eslint-disable jsdoc/require-jsdoc */
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
  userId: number | undefined
  deviceInfo: Record<string, unknown> = {}
  connectionTimeoutMs = 5 * 1000
  maxRetries = 3
  reconnectIntervalMs = 30 * 1000
  isReconnectEnabled = true
  isAlarmOpen = true

  constructor(ip: string, port = 9008, settings?: Settings) {
    this.ip = this.#validateIp(ip)
    this.port = this.#validatePort(port)

    if (settings) {
      this.connectionTimeoutMs = settings.connectionTimeoutMs ?? this.connectionTimeoutMs
      this.maxRetries = settings.maxRetries ?? this.maxRetries
      this.reconnectIntervalMs = settings.reconnectIntervalMs ?? this.reconnectIntervalMs
      this.isReconnectEnabled = settings.isReconnectEnabled ?? this.isReconnectEnabled
    }

    this.init()
  }

  #validateIp(ip: string): string {
    const ipRegex = /^(?:[0-9]{1,3}\.){3}[0-9]{1,3}$/
    if (!ipRegex.test(ip)) {
      throw new Error('Invalid IP address')
    }
    return ip
  }

  #validatePort(port: number): number {
    if (port < 1 || port > 65535) {
      throw new Error('Invalid port number')
    }
    return port
  }

  init(): void {
    if (
      !sdk.init() ||
      !sdk.setConnectTimeout(this.connectionTimeoutMs, this.maxRetries) ||
      !sdk.setReconnectInterval(this.reconnectIntervalMs, this.isReconnectEnabled)
    ) {
      throw new Error(this.getLastError())
    }
  }

  login(user: string, pass: string): number {
    this.userId = sdk.login(this.ip, this.port, user, pass, this.deviceInfo)
    if (this.userId === -1) {
      throw new Error(this.getLastError())
    }
    return this.userId
  }

  triggerAlarm(value: boolean): boolean {
    if (this.userId === undefined) {
      throw new Error('User ID is not set. Please login first.')
    }
    const alarmChannels = [0]
    const alarmValues = [value ? 1 : 0]
    return sdk.triggerAlarm(this.userId, alarmChannels, alarmValues, alarmChannels.length, this.isAlarmOpen)
  }

  getLastError(): string {
    return NET_SDK_ERROR[sdk.getLastError()] ?? 'Unknown error'
  }
}
