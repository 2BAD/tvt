import { describe, expect, it } from 'vitest'
import { validateIp, validatePort } from './validators.ts'

describe('validateIp', () => {
  it('should return the IP address if it is valid', () => {
    expect.assertions(16)
    const validIps = [
      '0.0.0.0',
      '8.8.8.8',
      '127.0.0.1',
      '100.100.100.100',
      '192.168.0.1',
      '18.101.25.153',
      '123.23.34.2',
      '172.26.168.134',
      '212.58.241.131',
      '128.0.0.0',
      '23.71.254.72',
      '223.255.255.255',
      '192.0.2.235',
      '99.198.122.146',
      '46.51.197.88',
      '173.194.34.134'
    ]

    for (const ip of validIps) {
      expect(validateIp(ip)).toBe(ip)
    }
  })

  it('should throw an error if the IP address is invalid', () => {
    expect.assertions(5)
    const invalidIps = ['999.999.999.999', '256.256.256.256', 'abc.def.ghi.jkl', '123.456.78.90.12', '']
    for (const ip of invalidIps) {
      expect(() => validateIp(ip)).toThrow('Invalid IP address')
    }
  })
})

describe('validatePort', () => {
  it('should return the port number if it is valid', () => {
    expect.assertions(1)
    const port = 8080
    expect(validatePort(port)).toBe(port)
  })

  it('should throw an error if the port number is less than 1', () => {
    expect.assertions(1)
    const invalidPort = 0
    expect(() => validatePort(invalidPort)).toThrow('Invalid port number')
  })

  it('should throw an error if the port number is greater than 65535', () => {
    expect.assertions(1)
    const invalidPort = 65536
    expect(() => validatePort(invalidPort)).toThrow('Invalid port number')
  })

  it('should throw an error if the port number is negative', () => {
    expect.assertions(1)
    const invalidPort = -1
    expect(() => validatePort(invalidPort)).toThrow('Invalid port number')
  })
})
