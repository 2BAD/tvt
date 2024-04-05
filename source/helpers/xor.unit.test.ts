import { Buffer } from 'node:buffer'
import { describe, expect, it } from 'vitest'
import { xor } from './xor.ts'

describe('xor function', () => {
  it('throws error if buffer sizes are different', () => {
    expect.assertions(1)

    const a = Buffer.from([1, 2, 3, 4])
    const b = Buffer.from([5, 6, 7])

    expect(() => xor(a, b)).toThrow('Buffer sizes are different. Buffer A length: 4, Buffer B length: 3')
  })

  it('throws error if data length is not multiple of 4', () => {
    expect.assertions(1)

    const a = Buffer.from([1, 2, 3])
    const b = Buffer.from([4, 5, 6])

    expect(() => xor(a, b)).toThrow('Invalid data size. Data length must be a multiple of 4. Current length: 3')
  })

  it('returns 4b buffer XORed correctly', () => {
    expect.assertions(1)

    const a = Buffer.from([1, 2, 3, 4])
    const b = Buffer.from([5, 6, 7, 8])
    const expected = Buffer.from([4, 4, 4, 12])

    expect(xor(a, b)).toStrictEqual(expected)
  })

  it('returns zero filled buffer XORed correctly', () => {
    expect.assertions(1)

    const a = Buffer.alloc(32)
    const b = Buffer.alloc(32, 'b0561d7e', 'hex')
    const expected = b

    expect(xor(a, b)).toStrictEqual(expected)
  })

  it('returns partially filled buffer XORed correctly', () => {
    expect.assertions(1)

    const a = Buffer.alloc(32)
    Buffer.from('123456').copy(a)
    const b = Buffer.alloc(32, '2aadc207', 'hex')
    const expected = Buffer.from('1b9ff1331f9bc2072aadc2072aadc2072aadc2072aadc2072aadc2072aadc207', 'hex')

    expect(xor(a, b)).toStrictEqual(expected)
  })
})
