import debug from 'debug'
import { randomUUID } from 'node:crypto'
import { existsSync, mkdirSync } from 'node:fs'
import { platform } from 'node:os'
import { dirname } from 'node:path'
import { performance } from 'node:perf_hooks'
import pSeries from 'p-series'
import { fromDeviceTime, parseBuildDate, toDeviceTime } from './helpers/date.ts'
import { validateIp, validatePort } from './helpers/validators.ts'
import { sdk } from './lib/sdk.ts'
import {
  NET_SDK_ERROR_NAME,
  RECORDING_FORMAT,
  STREAM_TYPE,
  type AlarmCallback,
  type DeviceInfo,
  type DeviceTime,
  type RecFile,
  type VideoEffect
} from './lib/types.ts'
import { PlaybackStream } from './playback.ts'
import { LiveStream } from './stream.ts'
import type { Settings, VersionInfo } from './types.ts'
export {
  ALARM_TYPE,
  ALARM_TYPE_NAME,
  FRAME_TYPE,
  PLAYBACK_CONTROL,
  RECORD_TYPE,
  RECORD_TYPE_NAME,
  RECORDING_FORMAT,
  STREAM_TYPE
} from './lib/types.ts'
export { PlaybackStream } from './playback.ts'
export type { PlaybackFrame } from './playback.ts'
export { LiveStream } from './stream.ts'
export type { LiveFrame } from './stream.ts'
export type * from './types.ts'

const log = debug('tvt:device')
const perf = debug('tvt:perf')

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

  // @ts-expect-error assigned by login, every method that reads it calls #requireAuth first
  userId: number
  #user = ''
  #pass = ''
  // @ts-expect-error deviceInfo is passed as a pointer to login function and should be initialized as an empty object
  #deviceInfo: DeviceInfo = {}

  readonly #sdkVersion: string
  readonly #sdkBuild: string
  readonly #liveStreams = new Set<LiveStream>()
  readonly #playbackStreams = new Set<PlaybackStream>()
  #alarmHandle: number | null = null
  // alarms arrive from the SDK's own thread, not through libuv, so a program that only waits
  // for them would otherwise run out of event loop work and exit
  #alarmKeepAlive: NodeJS.Timeout | null = null

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

  #requireAuth(): void {
    if (this.userId === undefined) {
      throw new Error('Requested method require authentication. Please login first.')
    }
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
      const error = NET_SDK_ERROR_NAME.get(errorCode) ?? 'Unknown error'
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
  get version(): VersionInfo {
    this.#requireAuth()

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
  async getInfo(): Promise<DeviceInfo> {
    this.#requireAuth()

    await sdk.getDeviceInfo(this.userId, this.#deviceInfo)
    return this.#deviceInfo
  }

  /**
   * Logs into the device.
   *
   * @param user - The username.
   * @param pass - The password.
   * @returns A promise that resolves to a boolean indicating whether the login was successful.
   * @throws {Error} An error if the login fails.
   */
  async login(user: string, pass: string): Promise<boolean> {
    log(`Logging in to device ${this.uuid} with user: ${user}`)
    const start = performance.now()

    try {
      this.userId = await sdk.login(this.ip, this.port, user, pass, this.#deviceInfo)
      if (this.userId === -1) {
        throw new Error(await this.getLastError())
      }
      this.#user = user
      this.#pass = pass
      log(`Successfully logged in to device ${this.uuid}`)
      perf(`[login] execution time: ${performance.now() - start} ms`)
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
  async logout(): Promise<boolean> {
    this.#requireAuth()

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
  async triggerAlarm(value: boolean): Promise<boolean> {
    this.#requireAuth()

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
  async saveSnapshot(channel: number, filePath: string): Promise<boolean> {
    this.#requireAuth()

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
   * Starts alarm monitoring: subscribes to the device's alarm channel and invokes the callback
   * with every alarm event it reports.
   *
   * @param onAlarm - Called once per alarm event.
   * @returns A promise that resolves to a boolean indicating whether monitoring started.
   * @throws {Error} An error if monitoring is already active or the subscription fails.
   */
  async startAlarmMonitoring(onAlarm: AlarmCallback): Promise<boolean> {
    this.#requireAuth()

    if (this.#alarmHandle !== null) {
      throw new Error('Alarm monitoring is already active. Call stopAlarmMonitoring first.')
    }

    log(`Starting alarm monitoring on device ${this.uuid}`)

    await sdk.addAlarmListener(this.userId, (events) => {
      for (const event of events) {
        onAlarm(event)
      }
    })

    const handle = await sdk.setupAlarmChannel(this.userId)
    if (handle === -1) {
      await sdk.removeAlarmListener(this.userId)
      throw new Error(await this.getLastError())
    }

    this.#alarmHandle = handle
    this.#alarmKeepAlive = setInterval(() => {}, 60_000)
    log(`Successfully started alarm monitoring on device ${this.uuid} with handle ${handle}`)
    return true
  }

  /**
   * Stops alarm monitoring. Idempotent.
   *
   * @returns A promise that resolves to a boolean indicating whether monitoring was stopped successfully.
   */
  async stopAlarmMonitoring(): Promise<boolean> {
    if (this.#alarmHandle === null) {
      return true
    }

    log(`Stopping alarm monitoring on device ${this.uuid}`)

    const result = await sdk.closeAlarmChannel(this.#alarmHandle)
    this.#alarmHandle = null
    await sdk.removeAlarmListener(this.userId)

    if (this.#alarmKeepAlive) {
      clearInterval(this.#alarmKeepAlive)
      this.#alarmKeepAlive = null
    }
    return result
  }

  /**
   * Captures a jpeg snapshot of a specific video channel into memory.
   *
   * @param channel - The channel number to capture.
   * @param bufferSize - Size of the receiving buffer in bytes, for images larger than the 4MB default.
   * @returns A promise that resolves to the JPEG data.
   * @throws {Error} An error if the capture fails.
   */
  async captureSnapshot(channel = 0, bufferSize?: number): Promise<Buffer> {
    this.#requireAuth()

    log(`Capturing snapshot from device ${this.uuid} channel ${channel}`)

    const data = await sdk.captureJPEGData_V2(this.userId, channel, bufferSize)
    if (data === null) {
      throw new Error(await this.getLastError())
    }
    return data
  }

  /**
   * Gets the current system time of the device, interpreted in the host timezone.
   *
   * @returns A promise that resolves to the device time.
   * @throws {Error} An error if reading the time fails.
   */
  async getTime(): Promise<Date> {
    this.#requireAuth()

    // @ts-expect-error passed as a pointer and filled by the sdk
    const time: DeviceTime = {}
    if (!(await sdk.getDeviceTime(this.userId, time))) {
      throw new Error(await this.getLastError())
    }
    return fromDeviceTime(time)
  }

  /**
   * Sets the system time of the device.
   *
   * @param time - The time to set, defaults to now.
   * @returns A promise that resolves to a boolean indicating whether the time was set successfully.
   */
  async setTime(time: Date = new Date()): Promise<boolean> {
    this.#requireAuth()

    log(`Setting time on device ${this.uuid} to ${time.toISOString()}`)
    // the device stores wall-clock time, so shift the unix timestamp by the host timezone offset
    return sdk.changeTime(this.userId, Math.floor(time.getTime() / 1000) - time.getTimezoneOffset() * 60)
  }

  /**
   * Gets the RTSP URL of a video channel, with the login credentials embedded by default.
   *
   * Some firmware rejects the path its own SDK reports with 404 while serving the main stream
   * at the root path; use omitPath on such devices.
   *
   * @param channel - The channel number.
   * @param streamType - The stream the URL points to (main or sub).
   * @param options - includeCredentials embeds the login credentials (default true), omitPath
   * drops the device-reported path and returns the root URL (default false).
   * @returns A promise that resolves to the RTSP URL.
   * @throws {Error} An error if the device does not return a URL.
   */
  async getRtspUrl(
    channel = 0,
    streamType: STREAM_TYPE = STREAM_TYPE.MAIN,
    options?: { includeCredentials?: boolean; omitPath?: boolean }
  ): Promise<string> {
    this.#requireAuth()

    const raw = await sdk.getRtspUrl(this.userId, channel, streamType)
    if (raw === null) {
      throw new Error(await this.getLastError())
    }

    const url = new URL(raw)
    if (options?.includeCredentials ?? true) {
      url.username = this.#user
      url.password = this.#pass
    }
    if (options?.omitPath) {
      url.pathname = '/'
      url.search = ''
    }
    return url.href
  }

  /**
   * Gets the video effect settings (brightness, contrast, saturation, hue) of a channel.
   *
   * @param channel - The channel number.
   * @returns A promise that resolves to the video effect settings.
   * @throws {Error} An error if reading the settings fails.
   */
  async getVideoEffect(channel = 0): Promise<VideoEffect> {
    this.#requireAuth()

    const effect = await sdk.getVideoEffect(this.userId, channel)
    if (effect === null) {
      throw new Error(await this.getLastError())
    }
    return effect
  }

  /**
   * Sets the video effect settings (brightness, contrast, saturation, hue) of a channel.
   *
   * @param channel - The channel number.
   * @param effect - The settings to apply.
   * @returns A promise that resolves to a boolean indicating whether the settings were applied successfully.
   */
  async setVideoEffect(channel: number, effect: VideoEffect): Promise<boolean> {
    this.#requireAuth()

    log(`Setting video effect on device ${this.uuid} channel ${channel}`)
    return sdk.setVideoEffect(this.userId, channel, effect)
  }

  /**
   * Gets the number of streams a video channel supports.
   *
   * @param channel - The channel number.
   * @returns A promise that resolves to the stream count.
   */
  async getStreamCount(channel = 0): Promise<number> {
    this.#requireAuth()

    return sdk.supportStreamNum(this.userId, channel)
  }

  /**
   * Reboots the device. The session becomes invalid; create and login a new Device once it is back up.
   *
   * @returns A promise that resolves to a boolean indicating whether the reboot was accepted.
   */
  async reboot(): Promise<boolean> {
    this.#requireAuth()

    log(`Rebooting device ${this.uuid}`)
    return sdk.reboot(this.userId)
  }

  /**
   * Shuts the device down. It has to be powered back on physically.
   *
   * @returns A promise that resolves to a boolean indicating whether the shutdown was accepted.
   */
  async shutdown(): Promise<boolean> {
    this.#requireAuth()

    log(`Shutting down device ${this.uuid}`)
    return sdk.shutdown(this.userId)
  }

  /**
   * Starts pulling a live stream from a video channel.
   *
   * @param channel - The channel number to stream from.
   * @param streamType - The stream to pull (main or sub).
   * @returns A promise that resolves to a LiveStream.
   * @throws {Error} An error if starting the stream fails.
   */
  async startLiveStream(channel = 0, streamType: STREAM_TYPE = STREAM_TYPE.MAIN): Promise<LiveStream> {
    this.#requireAuth()

    log(`Starting live stream from device ${this.uuid} channel ${channel} (stream type ${streamType})`)

    const liveHandle = await sdk.livePlay(this.userId, channel, streamType)
    if (liveHandle === -1) {
      throw new Error(await this.getLastError())
    }

    const stream: LiveStream = new LiveStream(liveHandle, this.userId, channel, streamType, () =>
      this.#liveStreams.delete(stream)
    )
    this.#liveStreams.add(stream)

    log(`Successfully started live stream from device ${this.uuid} with handle ${liveHandle}`)
    return stream
  }

  /**
   * Searches for recorded files on a channel within a time range.
   *
   * Times are interpreted in the host timezone; run host and device in the same one or account
   * for the offset.
   *
   * @param channel - The channel number.
   * @param start - Range start.
   * @param stop - Range end.
   * @returns A promise that resolves to the recordings found, ordered as the device returns them.
   * @throws {Error} An error if the search fails.
   */
  async searchRecordings(channel: number, start: Date, stop: Date): Promise<RecFile[]> {
    this.#requireAuth()

    log(
      `Searching recordings on device ${this.uuid} channel ${channel} from ${start.toISOString()} to ${stop.toISOString()}`
    )

    const files = await sdk.searchRecordings(this.userId, channel, toDeviceTime(start), toDeviceTime(stop))
    if (files === null) {
      throw new Error(await this.getLastError())
    }
    return files
  }

  /**
   * Downloads a recording of a channel to a file, resolving once the download completes.
   *
   * Times are interpreted in the host timezone; run host and device in the same one or account
   * for the offset.
   *
   * @param channel - The channel number.
   * @param start - Range start.
   * @param stop - Range end.
   * @param filePath - The path where the recording will be saved.
   * @param options - format selects the container (RECORDING_FORMAT.AVI by default, or the device's
   * private format), streamType picks main or sub stream (main by default), onProgress is called
   * with the download percentage (0-100) as it advances.
   * @returns A promise that resolves to true once the download completes.
   * @throws {Error} An error if the download fails to start or fails midway.
   */
  async downloadRecording(
    channel: number,
    start: Date,
    stop: Date,
    filePath: string,
    options?: { format?: RECORDING_FORMAT; streamType?: STREAM_TYPE; onProgress?: (percent: number) => void }
  ): Promise<boolean> {
    this.#requireAuth()

    log(`Downloading recording from device ${this.uuid} channel ${channel} to ${filePath}`)

    const dirPath = dirname(filePath)
    if (!existsSync(dirPath)) {
      mkdirSync(dirPath, { recursive: true })
    }

    const format = options?.format ?? RECORDING_FORMAT.AVI
    const firstStream = (options?.streamType ?? STREAM_TYPE.MAIN) === STREAM_TYPE.MAIN
    const handle = await sdk.getFileByTime(
      this.userId,
      channel,
      toDeviceTime(start),
      toDeviceTime(stop),
      filePath,
      format,
      firstStream
    )
    if (handle === -1) {
      throw new Error(await this.getLastError())
    }

    try {
      for (;;) {
        const pos = await sdk.getDownloadPos(handle)
        if (pos < 0) {
          throw new Error(await this.getLastError())
        }
        options?.onProgress?.(pos)
        if (pos >= 100) {
          break
        }
        await new Promise((resolve) => setTimeout(resolve, 500))
      }
    } finally {
      await sdk.stopGetFile(handle)
    }

    log(`Successfully downloaded recording from device ${this.uuid}`)
    return true
  }

  /**
   * Starts playback of a channel's recordings over a time range.
   *
   * Times are interpreted in the host timezone; run host and device in the same one or account
   * for the offset.
   *
   * @param channel - The channel number.
   * @param start - Range start.
   * @param stop - Range end.
   * @returns A promise that resolves to a PlaybackStream.
   * @throws {Error} An error if starting playback fails.
   */
  async startPlayback(channel: number, start: Date, stop: Date): Promise<PlaybackStream> {
    this.#requireAuth()

    log(
      `Starting playback from device ${this.uuid} channel ${channel} from ${start.toISOString()} to ${stop.toISOString()}`
    )

    const handle = await sdk.playBackByTime(this.userId, [channel], 1, toDeviceTime(start), toDeviceTime(stop))
    if (handle === -1) {
      throw new Error(await this.getLastError())
    }

    const stream: PlaybackStream = new PlaybackStream(handle, [channel], () => this.#playbackStreams.delete(stream))
    this.#playbackStreams.add(stream)

    log(`Successfully started playback from device ${this.uuid} with handle ${handle}`)
    return stream
  }

  /**
   * Gets the last error that occurred.
   *
   * @returns A promise that resolves to a string describing the last error.
   */
  async getLastError(): Promise<string> {
    const errorCode = await sdk.getLastError()
    return NET_SDK_ERROR_NAME.get(errorCode) ?? 'Unknown error'
  }

  /**
   * Logout and dispose of the SDK resources.
   *
   * @returns A promise that resolves to a boolean indicating whether the disposal was successful.
   */
  async dispose(): Promise<boolean> {
    log(`Disposing device ${this.uuid}...`)

    try {
      for (const stream of this.#liveStreams) {
        await stream.stop()
      }
      for (const stream of this.#playbackStreams) {
        await stream.stop()
      }
      await this.stopAlarmMonitoring()
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
