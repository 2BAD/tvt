import { describe, expect, it } from 'vitest'
import { parseBuildDate } from './date.ts'

describe('parseBuildDate', () => {
  it('should return the correct date when a valid date string is provided', () => {
    expect.assertions(2)
    expect(parseBuildDate('30912')).toBe('12/09/2020')
    expect(parseBuildDate('00101')).toBe('01/01/2017')
  })

  it('should throw an error when an invalid date string is provided', () => {
    expect.assertions(2)
    expect(() => parseBuildDate('abcd')).toThrow('Invalid date string format. Expected format is YMMDD.')
    expect(() => parseBuildDate('123456')).toThrow('Invalid date string format. Expected format is YMMDD.')
  })
})
