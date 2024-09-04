import type { Device } from '../device.ts'

/**
 * A method decorator that checks if the user is logged in (userId is defined) before executing the decorated method.
 *
 * @template This - The type of the class instance, extending Device.
 * @template Args - The argument types of the decorated method.
 * @template Return - The return type of the decorated method.
 *
 * @param target - The original method to be decorated.
 * @param _context - The context in which the method is executed, providing metadata.
 * @returns A replacement method that includes the login check.
 */
export const auth = <This extends Device, Args extends unknown[], Return>(
  target: (this: This, ...args: Args) => Return,
  _context: DecoratorContext
) => {
  /**
   * Replacement method that checks if the user is logged in before executing the original method.
   *
   * @param args - Arguments passed to the original method.
   * @returns The result of the original method execution.
   * @throws Will throw an error if the user is not logged in (userId is undefined).
   */
  function requireAuth(this: This, ...args: Args): Return {
    if (this.userId === undefined) {
      throw new Error('Requested method require authentication. Please login first.')
    }
    return target.call(this, ...args)
  }

  return requireAuth
}
