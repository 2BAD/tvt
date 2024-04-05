export const xor = (a: Buffer, b: Buffer): Buffer => {
  if (a.length !== b.length) {
    throw new Error('Buffer sizes are different. Buffer A length: ' + a.length + ', Buffer B length: ' + b.length)
  }
  if (a.length % 4 !== 0) {
    throw new Error('Invalid data size. Data length must be a multiple of 4. Current length: ' + a.length)
  }
  const c = Buffer.allocUnsafe(a.length)
  for (let i = 0; i < a.length; i += 4) {
    c.writeUInt32BE((a.readUInt32BE(i) ^ b.readUInt32BE(i)) >>> 0, i)
  }
  return c
}
