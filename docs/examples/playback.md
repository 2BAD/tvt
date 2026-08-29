# Playback

Streaming playback works like the live path: a `PlaybackStream` with the same `frames()` iterator and `recordTo`, plus transport controls.

```typescript
import { Device, FRAME_TYPE } from '@2bad/tvt'

const device = await Device.create('192.168.1.100')
await device.login('admin', 'password')

const stream = await device.startPlayback(0, new Date('2026-08-29T08:00:00'), new Date('2026-08-29T09:00:00'))

for await (const frame of stream.frames()) {
  if (frame.frameType === FRAME_TYPE.VIDEO) {
    console.log(`${frame.width}x${frame.height} keyframe=${frame.keyFrame} ${frame.data.length} bytes`)
  }
}

// transport controls, any time while playing
await stream.pause()
await stream.resume()
await stream.fastForward() // one speed step up; rewind() steps down; normalSpeed() resets
await stream.frameStep() // advance one frame while paused

await stream.stop()
await device.dispose()
```

Same mechanics as a live stream: per-iterator queues with the 256-frame drop policy, `recordTo`/`stopRecording` to save the playback to an AVI, and automatic cleanup of any playback stream still running at `device.dispose()`.
