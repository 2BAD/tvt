/**
 * Validates an IPv4 address.
 *
 * @param ip - The IP address to validate.
 * @returns - The validated IP address.
 * @throws {Error} - If the IP address is not valid.
 */
export const validateIp = (ip: string): string => {
  const ipRegex = /^((25[0-5]|(2[0-4]|1\d|[1-9]|)\d)\.?\b){4}$/
  if (!ipRegex.test(ip)) {
    throw new Error('Invalid IP address')
  }
  return ip
}

/**
 * Validates a port number.
 *
 * @param port - The port number to validate.
 * @returns - The validated port number.
 * @throws {Error} - If the port number is not valid.
 */
export const validatePort = (port: number): number => {
  if (port < 1 || port > 65535) {
    throw new Error('Invalid port number')
  }
  return port
}
