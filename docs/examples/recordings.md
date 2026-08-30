# Recordings

Search the recorder's disk, then download a clip or play it back frame by frame.

```typescript
import { Device, RECORD_TYPE_NAME } from '@2bad/tvt'

const device = await Device.create('192.168.1.100')
await device.login('admin', 'password')

const start = new Date('2026-08-29T08:00:00')
const stop = new Date('2026-08-29T09:00:00')

// what recordings exist on channel 0 in that window
const files = await device.searchRecordings(0, start, stop)
for (const file of files) {
  console.log(
    `${file.startTime.toISOString()} - ${file.stopTime.toISOString()} ${RECORD_TYPE_NAME.get(file.recType) ?? file.recType}${file.locked ? ' (locked)' : ''}`
  )
}

// download the whole window to an AVI, with progress
await device.downloadRecording(0, start, stop, '/tmp/clip.avi', {
  onProgress: (percent) => console.log(`${percent}%`)
})
```

`searchRecordings` returns the segments the device reports for the channel, each with `startTime`/`stopTime` (Date), a `recType` bitmask (decode via `RECORD_TYPE_NAME`), the `locked` flag, and the device-internal `partition`/`fileIndex`. `downloadRecording` resolves once the file is fully written; it polls the device for progress and calls `onProgress` as it advances.

The download defaults to a standard AVI container and the main stream. Pass `format: RECORDING_FORMAT.PRIVATE` for the device's native format (an H.264 elementary stream in a proprietary header, playable in TVT's SDPlayer), or `streamType: STREAM_TYPE.SUB` for the sub stream:

```typescript
import { RECORDING_FORMAT, STREAM_TYPE } from '@2bad/tvt'

await device.downloadRecording(0, start, stop, '/tmp/clip.dav', {
  format: RECORDING_FORMAT.PRIVATE,
  streamType: STREAM_TYPE.SUB
})
```

Times are wall-clock, interpreted in the host timezone, same as `getTime`/`setTime`. Run host and device in the same zone or account for the offset.

See also [playback](playback.md) for streaming a recording with transport controls instead of downloading it.
