# Changelog

All notable changes to this project are documented here. The format is based on
[Keep a Changelog](https://keepachangelog.com/en/1.1.0/), and this project follows
[Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [2.1.0] - 2026-08-30

### Added

- Live streaming via `startLiveStream`: a `LiveStream` with a `frames()` iterator and `recordTo`/`stopRecording` (H.264 video, PCM audio; record and read at once).
- Alarm monitoring via `startAlarmMonitoring`/`stopAlarmMonitoring`, one callback per event (`ALARM_TYPE`/`ALARM_TYPE_NAME`).
- Recorded footage: `searchRecordings`, `downloadRecording` (AVI or native format, main/sub stream, progress), and `startPlayback` for a `PlaybackStream` with `frames()`, `recordTo`, and transport controls.
- In-memory snapshots via `captureSnapshot`, or `saveSnapshot` to disk.
- RTSP URLs via `getRtspUrl`, with optional credential embedding and path omission.
- Image controls `getVideoEffect`/`setVideoEffect` (brightness, contrast, saturation, hue).
- Device clock `getTime`/`setTime`.
- Power control `reboot`/`shutdown`.
- Channel stream count via `getStreamCount`.

## [2.0.0] - 2025

### Changed

- All device methods are async and return Promises, and construction is now the async factory `Device.create` instead of `new Device`. See the migration notes in the README.

[2.1.0]: https://github.com/2BAD/tvt/compare/v2.0.0...v2.1.0
[2.0.0]: https://github.com/2BAD/tvt/releases/tag/v2.0.0
