# Snapshots

Two ways to do it:

```typescript
// straight to disk (directory is created if missing)
await device.saveSnapshot(0, '/tmp/snapshot.jpg')

// in memory
const jpeg = await device.captureSnapshot(0)

// megapixel sensors can exceed the 4MB default buffer; size it yourself
const big = await device.captureSnapshot(0, 16 * 1024 * 1024)
```
