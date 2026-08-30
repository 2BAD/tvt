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

## Compatibility

TVT is mostly a white-label manufacturer, so their hardware gets sold under a lot of other names. If a device answers on port 9008 or works with TVT's SuperLive/SuperCam apps, it's almost certainly a rebadged TVT and this SDK should talk to it.

Brands known to sell rebadged TVT devices:

- Digital Watchdog (some product lines)
- Q-See
- CP Plus
- Provision-ISR
- Avycon
- TeleEye
- NoVus
- Meriva Security
- InVid Tech
- Alibi (Observint)
- TecVoz
- JFL Alarmes
- Gazer
- Questek
- Technomate

The long tail is much bigger: pulling the OEM logo files out of TVT firmware turned up 79 brands ([IPVM has the list](https://ipvm.com/discussions/a-list-of-tvt-s-79-dvr-oems)). Most of these brands source from several manufacturers though, so not every product they sell is TVT. And GE's TruVision "TVT-xxxx" model numbers have nothing to do with TVT, that's just a product-line prefix.

## Install

```bash
npm install @2bad/tvt
```

## Quick start

```typescript
import { Device } from '@2bad/tvt'

// 9008 port for cameras, 6036 for NVRs
const device = await Device.create('192.168.1.100', 9008)
await device.login('admin', 'password')

const info = await device.getInfo()
console.log(`${info.deviceName} (${info.deviceProduct}), ${info.videoInputNum} video inputs`)

await device.saveSnapshot(0, '/tmp/ch0.jpg')

await device.dispose()
```

`dispose()` stops any running streams and alarm monitoring, logs out, and releases the SDK. Call it exactly once, at the end.

## Examples

Runnable examples live in [`docs/examples`](docs/examples):

- [Live streaming](docs/examples/live-streaming.md) - pull frames or record to an AVI
- [Alarm monitoring](docs/examples/alarm-monitoring.md) - subscribe to the device's alarm events
- [Recordings](docs/examples/recordings.md) - search and download recorded footage
- [Playback](docs/examples/playback.md) - stream a recording with transport controls
- [Snapshots](docs/examples/snapshots.md) - capture a JPEG to disk or memory
- [RTSP](docs/examples/rtsp.md) - get an RTSP URL for ffmpeg or GStreamer
- [Device control](docs/examples/device-control.md) - time, image, power, and version

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

  searchRecordings(channel: number, start: Date, stop: Date): Promise<RecFile[]>
  downloadRecording(
    channel: number,
    start: Date,
    stop: Date,
    filePath: string,
    options?: { format?: RECORDING_FORMAT; streamType?: STREAM_TYPE; onProgress?: (percent: number) => void }
  ): Promise<boolean>
  startPlayback(channel: number, start: Date, stop: Date): Promise<PlaybackStream>

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

class PlaybackStream {
  frames(): AsyncGenerator<PlaybackFrame>
  recordTo(filePath: string): Promise<boolean>
  stopRecording(): Promise<boolean>
  pause(): Promise<boolean>
  resume(): Promise<boolean>
  fastForward(): Promise<boolean>
  rewind(): Promise<boolean>
  frameStep(): Promise<boolean>
  normalSpeed(): Promise<boolean>
  stop(): Promise<boolean>
  get stopped(): boolean
}
```

`Settings` on `Device.create` controls the native connection behavior: `connectionTimeoutMs` (5000), `maxRetries` (3), `reconnectIntervalMs` (30000), `isReconnectEnabled` (true).

Every method except `create`, `login`, and `getLastError` requires a prior successful `login` and throws otherwise.

### Error semantics

Methods that return data (`getInfo`, `captureSnapshot`, `getTime`, `getRtspUrl`, `getVideoEffect`, `startLiveStream`, `searchRecordings`, `startPlayback`, `downloadRecording`, `login`) throw on failure with the decoded NET_SDK error name. Methods that perform an action (`saveSnapshot`, `triggerAlarm`, `setTime`, `logout`, ...) resolve `false` on failure. `getLastError()` returns the name of the most recent SDK error; the full table is exported as `NET_SDK_ERROR`.

### Debug logging

Namespaced under [debug](https://github.com/debug-js/debug):

```bash
DEBUG=tvt:* node app.js       # everything
DEBUG=tvt:perf node app.js    # native call timings only
```

## Repository layout

```
bin/       vendor .so libraries (libdvrnetsdk.so and dependencies)
docs/
  examples/       usage examples
  vendor/         vendor SDK reference: NET_SDK manuals (PDF/CHM), C headers, demo sources
proto/     Wireshark dissectors (Lua) for the wire protocol
source/    the TypeScript implementation
  device.ts       Device class, public entry point
  stream.ts       LiveStream
  playback.ts     PlaybackStream
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
