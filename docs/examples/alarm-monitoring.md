# Alarm monitoring

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
