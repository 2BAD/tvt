import debug from 'debug'
import { existsSync, mkdirSync } from 'node:fs'
import { dirname } from 'node:path'
import { sdk } from './lib/sdk.ts'
import type { FrameInfo, STREAM_TYPE } from './lib/types.ts'

const log = debug('tvt:stream')

export type LiveFrame = FrameInfo & { data: Buffer }

type Subscriber = {
  queue: LiveFrame[]
  notify: () => void
}

const MAX_QUEUED_FRAMES = 256

/**
 * A live audio/video stream pulled from a device channel. Created by Device.startLiveStream.
 */
export class LiveStream {
  readonly handle: number
  readonly channel: number
  readonly streamType: STREAM_TYPE
  readonly #userId: number
  #stopped = false
  #recording = false
  // frames arrive from the SDK's own thread, not through libuv, so while iterators wait for the
  // next frame the event loop would otherwise be empty and the process would exit
  #keepAlive: NodeJS.Timeout | null = null
  readonly #subscribers = new Set<Subscriber>()
  readonly #onStop: () => void

  /** @internal */
  constructor(handle: number, userId: number, channel: number, streamType: STREAM_TYPE, onStop: () => void) {
    this.handle = handle
    this.channel = channel
    this.streamType = streamType
    this.#userId = userId
    this.#onStop = onStop
  }

  get stopped(): boolean {
    return this.#stopped
  }

  /**
   * Iterates over the frames of the stream as they arrive.
   *
   * Frames are buffered per iterator; when a consumer falls more than 256 frames behind, the
   * oldest buffered frames are dropped. The iterator ends when the stream is stopped.
   *
   * @yields Frames of the stream, in arrival order.
   * @throws {Error} An error if the stream is already stopped.
   */
  async *frames(): AsyncGenerator<LiveFrame, void, undefined> {
    if (this.#stopped) {
      throw new Error('Live stream is stopped')
    }

    const subscriber: Subscriber = { queue: [], notify: () => {} }
    const needAttach = this.#subscribers.size === 0
    this.#subscribers.add(subscriber)

    if (needAttach) {
      try {
        await sdk.setLiveDataCallBack(this.handle, (frame, data) => {
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
          await sdk.setLiveDataCallBack(this.handle, null)
        }
      }
    }
  }

  #dispatch(frame: FrameInfo, data: Buffer): void {
    for (const subscriber of this.#subscribers) {
      subscriber.queue.push({ ...frame, data })
      if (subscriber.queue.length > MAX_QUEUED_FRAMES) {
        subscriber.queue.shift()
        log(`Dropped a frame from live stream ${this.handle}: consumer is too slow`)
      }
      subscriber.notify()
    }
  }

  /**
   * Starts recording the stream to an AVI file.
   *
   * @param filePath - The path where the recording will be saved.
   * @returns A promise that resolves to a boolean indicating whether recording started successfully.
   * @throws {Error} An error if the stream is already stopped.
   */
  async recordTo(filePath: string): Promise<boolean> {
    if (this.#stopped) {
      throw new Error('Live stream is stopped')
    }

    log(`Recording live stream ${this.handle} to ${filePath}`)

    const dirPath = dirname(filePath)

    // sdk doesn't check if path is valid so we need to do it ourselves
    if (!existsSync(dirPath)) {
      mkdirSync(dirPath, { recursive: true })
    }

    const result = await sdk.startSavingLiveStream(this.handle, filePath)
    if (result) {
      // the file is only written from the next keyframe on, which can be seconds away
      await sdk.makeKeyFrame(this.#userId, this.channel, this.streamType)
    }
    this.#recording = result
    return result
  }

  /**
   * Stops recording the stream to file. The stream itself keeps running until stop is called.
   *
   * @returns A promise that resolves to a boolean indicating whether recording was stopped successfully.
   */
  async stopRecording(): Promise<boolean> {
    if (!this.#recording) {
      return true
    }
    this.#recording = false
    return sdk.stopSavingLiveStream(this.handle)
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
      await sdk.stopSavingLiveStream(this.handle)
    }

    const result = await sdk.stopLivePlay(this.handle)

    if (this.#keepAlive) {
      clearInterval(this.#keepAlive)
      this.#keepAlive = null
    }
    for (const subscriber of this.#subscribers) {
      subscriber.notify()
    }
    this.#subscribers.clear()
    this.#onStop()

    log(`Live stream ${this.handle} stopped`)
    return result
  }
}
