export type Settings = {
  uuid?: `${string}-${string}-${string}-${string}-${string}`
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
