# RTSP

If you'd rather feed ffmpeg or GStreamer than pull frames over the SDK:

```typescript
import { STREAM_TYPE } from '@2bad/tvt'

const url = await device.getRtspUrl(0, STREAM_TYPE.MAIN)
// rtsp://admin:password@192.168.1.100:554/...
```

Credentials from `login` are embedded by default; pass `{ includeCredentials: false }` to keep them out. Some firmware reports a stream path that its own RTSP server answers with 404, while serving the main stream at the root; `{ omitPath: true }` works around that.
