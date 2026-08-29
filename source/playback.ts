import debug from 'debug'
import { existsSync, mkdirSync } from 'node:fs'
import { dirname } from 'node:path'
import { sdk } from './lib/sdk.ts'
import { PLAYBACK_CONTROL, type FrameInfo } from './lib/types.ts'

const log = debug('tvt:playback')

export type PlaybackFrame = FrameInfo & { data: Buffer }

type Subscriber = {
  queue: PlaybackFrame[]
  notify: () => void
}

const MAX_QUEUED_FRAMES = 256

/**
 * A playback stream of recorded footage from one or more device channels. Created by
 * Device.startPlayback.
 */
export class PlaybackStream {
  readonly handle: number
  readonly channels: number[]
  #stopped = false
  #recording = false
  // frames arrive from the SDK's own thread, not through libuv, so while iterators wait for the
  // next frame the event loop would otherwise be empty and the process would exit
  #keepAlive: NodeJS.Timeout | null = null
  readonly #subscribers = new Set<Subscriber>()
  readonly #onStop: () => void

  /** @internal */
  constructor(handle: number, channels: number[], onStop: () => void) {
    this.handle = handle
    this.channels = channels
    this.#onStop = onStop
  }

  get stopped(): boolean {
    return this.#stopped
  }

  /**
   * Iterates over the frames of the playback stream as they arrive.
   *
   * Frames are buffered per iterator; when a consumer falls more than 256 frames behind, the
   * oldest buffered frames are dropped. The iterator ends when the stream is stopped.
   *
   * @yields Frames of the stream, in arrival order.
   * @throws {Error} An error if the stream is already stopped.
   */
  async *frames(): AsyncGenerator<PlaybackFrame, void, undefined> {
    if (this.#stopped) {
      throw new Error('Playback stream is stopped')
    }

    const subscriber: Subscriber = { queue: [], notify: () => {} }
    const needAttach = this.#subscribers.size === 0
    this.#subscribers.add(subscriber)

    if (needAttach) {
      try {
        await sdk.setPlayDataCallBack(this.handle, (frame, data) => {
          this.#dispatch(frame, data)
        })
      } catch (error) {
        this.#subscribers.delete(subscriber)
        throw error
      }
      this.#keepAlive = setInterval(() => {}, 60_000)
    }

    try {
      while (!this.#stopped) {
        const frame = subscriber.queue.shift()
        if (frame === undefined) {
          await new Promise<void>((resolve) => {
            subscriber.notify = resolve
          })
          continue
        }
        yield frame
      }
    } finally {
      this.#subscribers.delete(subscriber)
      if (this.#subscribers.size === 0) {
        if (this.#keepAlive) {
          clearInterval(this.#keepAlive)
          this.#keepAlive = null
        }
        if (!this.#stopped) {
          await sdk.setPlayDataCallBack(this.handle, null)
        }
      }
    }
  }

  #dispatch(frame: FrameInfo, data: Buffer): void {
    for (const subscriber of this.#subscribers) {
      subscriber.queue.push({ ...frame, data })
      if (subscriber.queue.length > MAX_QUEUED_FRAMES) {
        subscriber.queue.shift()
        log(`Dropped a frame from playback stream ${this.handle}: consumer is too slow`)
      }
      subscriber.notify()
    }
  }

  /**
   * Starts recording the playback stream to an AVI file.
   *
   * @param filePath - The path where the recording will be saved.
   * @returns A promise that resolves to a boolean indicating whether recording started successfully.
   * @throws {Error} An error if the stream is already stopped.
   */
  async recordTo(filePath: string): Promise<boolean> {
    if (this.#stopped) {
      throw new Error('Playback stream is stopped')
    }

    log(`Recording playback stream ${this.handle} to ${filePath}`)

    const dirPath = dirname(filePath)

    // sdk doesn't check if path is valid so we need to do it ourselves
    if (!existsSync(dirPath)) {
      mkdirSync(dirPath, { recursive: true })
    }

    const result = await sdk.startSavingPlayback(this.handle, this.channels[0] ?? 0, filePath)
    this.#recording = result
    return result
  }

  /**
   * Stops recording the playback stream to file. The stream itself keeps running until stop is called.
   *
   * @returns A promise that resolves to a boolean indicating whether recording was stopped successfully.
   */
  async stopRecording(): Promise<boolean> {
    if (!this.#recording) {
      return true
    }
    this.#recording = false
    return sdk.stopSavingPlayback(this.handle, this.channels[0] ?? 0)
  }

  async pause(): Promise<boolean> {
    return sdk.playBackControl(this.handle, PLAYBACK_CONTROL.PAUSE, 0)
  }

  async resume(): Promise<boolean> {
    return sdk.playBackControl(this.handle, PLAYBACK_CONTROL.RESUME, 0)
  }

  /** Steps the playback speed up one notch. */
  async fastForward(): Promise<boolean> {
    return sdk.playBackControl(this.handle, PLAYBACK_CONTROL.FAST_FORWARD, 0)
  }

  /** Steps the playback speed down one notch. */
  async rewind(): Promise<boolean> {
    return sdk.playBackControl(this.handle, PLAYBACK_CONTROL.REWIND, 0)
  }

  /** Advances a single frame while paused. */
  async frameStep(): Promise<boolean> {
    return sdk.playBackControl(this.handle, PLAYBACK_CONTROL.FRAME_STEP, 0)
  }

  /** Resets the playback speed back to normal after fastForward or rewind. */
  async normalSpeed(): Promise<boolean> {
    return sdk.playBackControl(this.handle, PLAYBACK_CONTROL.NORMAL, 0)
  }

  /**
   * Stops the stream, ends all frame iterators, and releases the native handle. Idempotent.
   *
   * @returns A promise that resolves to a boolean indicating whether the stream was stopped successfully.
   */
  async stop(): Promise<boolean> {
    if (this.#stopped) {
      return true
    }
    this.#stopped = true

    if (this.#recording) {
      this.#recording = false
      await sdk.stopSavingPlayback(this.handle, this.channels[0] ?? 0)
    }

    const result = await sdk.stopPlayBack(this.handle)

    if (this.#keepAlive) {
      clearInterval(this.#keepAlive)
      this.#keepAlive = null
    }
    for (const subscriber of this.#subscribers) {
      subscriber.notify()
    }
    this.#subscribers.clear()
    this.#onStop()

    log(`Playback stream ${this.handle} stopped`)
    return result
  }
}
