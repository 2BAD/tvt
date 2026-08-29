# TVT Device SDK

[![NPM version](https://img.shields.io/npm/v/@2bad/tvt)](https://www.npmjs.com/package/@2bad/tvt)
[![License](https://img.shields.io/npm/l/@2bad/tvt)](https://opensource.org/license/MIT)
[![GitHub Build Status](https://img.shields.io/github/actions/workflow/status/2BAD/tvt/build.yml)](https://github.com/2BAD/tvt/actions/workflows/build.yml)
[![Code coverage](https://img.shields.io/codecov/c/github/2BAD/tvt)](https://codecov.io/gh/2BAD/tvt)
[![Written in TypeScript](https://img.shields.io/github/languages/top/2BAD/tvt)](https://www.typescriptlang.org/)

TypeScript bindings for TVT (Tongwei Video Technology) CCTV devices: IP cameras, NVRs, DVRs. Talks the proprietary NET_SDK protocol through the vendor's `libdvrnetsdk.so` via [koffi](https://koffi.dev/) FFI. There's no usable English documentation, so this was built by disassembling the vendor SDK and reverse engineering the wire protocol from packet captures. The Wireshark dissectors from that work are in `proto/`.

Everything is async. Native calls don't block the event loop, and callbacks from the SDK's own threads get marshalled back into JS properly.

## Requirements

- Linux x86_64
- Node.js >= 26

The required `.so` files ship with the package under `bin/linux` and are loaded automatically. No system-wide installation, no `LD_LIBRARY_PATH` stuff.

## Install

```bash
npm install @2bad/tvt
```

## Quick start

```typescript
import { Device } from '@2bad/tvt'

const device = await Device.create('192.168.1.100', 9008)
await device.login('admin', 'password')

const info = await device.getInfo()
console.log(`${info.deviceName} (${info.deviceProduct}), ${info.videoInputNum} video inputs`)

await device.saveSnapshot(0, '/tmp/ch0.jpg')

await device.dispose()
```

`dispose()` stops any running streams and alarm monitoring, logs out, and releases the SDK. Call it exactly once, at the end.

## Live streaming

`startLiveStream` pulls the raw elementary stream from a channel. Video frames are H.264 Annex B chunks, audio is PCM. You can record to disk, consume frames programmatically, or both at once on a single stream.

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

## Alarm monitoring

Subscribes to the device's alarm channel. The device pushes events; you get a callback per event. Motion, sensor inputs, video loss, tripwire, perimeter, face match, disk errors: the whole `ALARM_TYPE` table.

```typescript
import { ALARM_TYPE, ALARM_TYPE_NAME, Device } from '@2bad/tvt'

const device = await Device.create('192.168.1.100')
await device.login('admin', 'password')

await device.startAlarmMonitoring((event) => {
  console.log(`${ALARM_TYPE_NAME.get(event.type)} on channel ${event.channel}`)
  if (event.type === ALARM_TYPE.SENSOR) {
    console.log(`sensor input ${event.sensorIn}`)
  }
})

// later
await device.stopAlarmMonitoring()
```

One subscription per device. `startAlarmMonitoring` throws if one is already active; `stopAlarmMonitoring` is idempotent. While monitoring is active the process is kept alive even if the event loop has nothing else to do, since alarms arrive from the SDK's thread, not libuv.

## Snapshots

Two ways to do it:

```typescript
// straight to disk (directory is created if missing)
await device.saveSnapshot(0, '/tmp/snapshot.jpg')

// in memory
const jpeg = await device.captureSnapshot(0)

// megapixel sensors can exceed the 4MB default buffer; size it yourself
const big = await device.captureSnapshot(0, 16 * 1024 * 1024)
```

## RTSP

If you'd rather feed ffmpeg or GStreamer than pull frames over the SDK:

```typescript
const url = await device.getRtspUrl(0, STREAM_TYPE.MAIN)
// rtsp://admin:password@192.168.1.100:554/...
```

Credentials from `login` are embedded by default; pass `{ includeCredentials: false }` to keep them out. Some firmware reports a stream path that its own RTSP server answers with 404, while serving the main stream at the root; `{ omitPath: true }` works around that.

## Device control

```typescript
await device.getTime() // device wall clock as a Date, host timezone
await device.setTime() // sync to now; or pass a Date
await device.getVideoEffect(0) // { brightness, contrast, saturation, hue }, each 0-100
await device.setVideoEffect(0, { brightness: 60, contrast: 50, saturation: 50, hue: 50 })
await device.getStreamCount(0) // streams the channel supports
await device.triggerAlarm(true) // drive the alarm output relay
await device.reboot() // session dies; create a new Device when it is back
await device.shutdown() // requires physical power-on afterwards
device.version // SDK + device firmware/kernel/hardware/MCU versions
```

The device stores wall-clock time with no timezone. `getTime`/`setTime` translate through the host timezone; run your host and device in the same one or account for it.

## API

```typescript
class Device {
  static create(ip: string, port?: number, settings?: Settings): Promise<Device>

  login(user: string, pass: string): Promise<boolean>
  logout(): Promise<boolean>
  getInfo(): Promise<DeviceInfo>
  get version(): VersionInfo

  startLiveStream(channel?: number, streamType?: STREAM_TYPE): Promise<LiveStream>
  saveSnapshot(channel: number, filePath: string): Promise<boolean>
  captureSnapshot(channel?: number, bufferSize?: number): Promise<Buffer>
  getRtspUrl(channel?: number, streamType?: STREAM_TYPE, options?: RtspUrlOptions): Promise<string>
  getStreamCount(channel?: number): Promise<number>

  startAlarmMonitoring(onAlarm: AlarmCallback): Promise<boolean>
  stopAlarmMonitoring(): Promise<boolean>
  triggerAlarm(value: boolean): Promise<boolean>

  getTime(): Promise<Date>
  setTime(time?: Date): Promise<boolean>
  getVideoEffect(channel?: number): Promise<VideoEffect>
  setVideoEffect(channel: number, effect: VideoEffect): Promise<boolean>

  reboot(): Promise<boolean>
  shutdown(): Promise<boolean>

  getLastError(): Promise<string>
  dispose(): Promise<boolean>
}

class LiveStream {
  frames(): AsyncGenerator<LiveFrame>
  recordTo(filePath: string): Promise<boolean>
  stopRecording(): Promise<boolean>
  stop(): Promise<boolean>
  get stopped(): boolean
}
```

`Settings` on `Device.create` controls the native connection behavior: `connectionTimeoutMs` (5000), `maxRetries` (3), `reconnectIntervalMs` (30000), `isReconnectEnabled` (true).

Every method except `create`, `login`, and `getLastError` requires a prior successful `login` and throws otherwise.

### Error semantics

Methods that return data (`getInfo`, `captureSnapshot`, `getTime`, `getRtspUrl`, `getVideoEffect`, `startLiveStream`, `login`) throw on failure with the decoded NET_SDK error name. Methods that perform an action (`saveSnapshot`, `triggerAlarm`, `setTime`, `logout`, ...) resolve `false` on failure. `getLastError()` returns the name of the most recent SDK error; the full table is exported as `NET_SDK_ERROR`.

### Debug logging

Namespaced under [debug](https://github.com/debug-js/debug):

```bash
DEBUG=tvt:* node app.js       # everything
DEBUG=tvt:perf node app.js    # native call timings only
```

## Repository layout

```
bin/       vendor .so libraries (libdvrnetsdk.so and dependencies)
docs/      vendor NET_SDK manuals (PDF/CHM), C headers, demo sources
proto/     Wireshark dissectors (Lua) for the wire protocol
source/    the TypeScript implementation
  device.ts       Device class, public entry point
  stream.ts       LiveStream
  lib/sdk.ts      typed FFI layer over libdvrnetsdk.so
  lib/struct/     koffi struct definitions mirroring the C headers
```

`proto/ipc.lua` dissects the device protocol in Wireshark. Useful if you're extending the bindings or poking at firmware behavior.

## Development

```bash
git clone https://github.com/2BAD/tvt.git
cd tvt
pnpm install
pnpm build          # tsdown
pnpm check          # oxlint + oxfmt + tsc
pnpm test:unit      # vitest, no hardware needed
pnpm test:integration   # requires a real device on the network
```

## Migration from v1.x

Construction is now a factory and async: `new Device(ip)` becomes `await Device.create(ip)`. Every SDK call returns a Promise: `device.info` becomes `await device.getInfo()`.

## License

MIT. See [LICENSE](LICENSE).

## Disclaimer

Not affiliated with or endorsed by TVT Digital Technology Co., Ltd. This is an independent implementation built on reverse engineering. The vendor libraries in `bin/` are redistributed as-is. Point it only at devices you own or are authorized to manage.
