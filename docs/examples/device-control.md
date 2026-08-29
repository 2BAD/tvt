# Device control

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
