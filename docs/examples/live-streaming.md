# Live streaming

`startLiveStream` pulls the raw elementary stream from a channel. Video frames are H.264 Annex B chunks, audio is PCM. Record to disk, read frames in code, or both at once on one stream.

```typescript
import { Device, FRAME_TYPE, STREAM_TYPE } from '@2bad/tvt'

const device = await Device.create('192.168.1.100')
await device.login('admin', 'password')

const stream = await device.startLiveStream(0, STREAM_TYPE.MAIN)

// record to an AVI container (H.264 + PCM)
await stream.recordTo('/tmp/capture.avi')
await new Promise((resolve) => setTimeout(resolve, 10_000))
await stream.stopRecording()

// or consume frames directly
for await (const frame of stream.frames()) {
  if (frame.frameType === FRAME_TYPE.VIDEO) {
    console.log(
      `${frame.width}x${frame.height} keyframe=${frame.keyFrame} ${frame.data.length} bytes t=${frame.time}us`
    )
  }
  if (frame.keyFrame) break
}

await stream.stop()
await device.dispose()
```

Things to know:

- Each `frames()` iterator gets its own queue. A consumer that falls more than 256 frames behind loses the oldest frames; nobody blocks the SDK callback thread.
- `recordTo` forces a keyframe request so the file starts within a GOP, not seconds later.
- `frame.time` is absolute microseconds since the Unix epoch, `frame.relativeTime` is stream-relative microseconds.
- A stream that's still running when `dispose()` is called gets stopped for you, but don't rely on that.
