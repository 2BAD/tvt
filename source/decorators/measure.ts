import debug from 'debug'
import { performance } from 'node:perf_hooks'

const log = debug('tvt:perf')

/**
 * A method decorator that measures the execution time of the decorated method.
 *
 * @param target - The original method to be decorated.
 * @param context - The context in which the method is executed, providing metadata such as the method name.
 * @returns A replacement method that includes execution time measurement.
 */
export const measure = <This, Args extends unknown[], Return>(
  target: (this: This, ...args: Args) => Return,
  context: DecoratorContext
  // eslint-disable-next-line @typescript-eslint/no-explicit-any
): any => {
  const methodName = String(context.name)

  /**
   * Replacement method that measures the execution time of the original method.
   *
   * @param args - Arguments passed to the original method.
   * @returns The result of the original method execution.
   */
  function trackPerf(this: This, ...args: Args): Return {
    const start = performance.now()
    const result = target.call(this, ...args)
    const finish = performance.now()
    log(`[${methodName}] execution time: ${finish - start} ms`)
    return result
  }
  return trackPerf
}
