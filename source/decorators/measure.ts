import { performance } from 'perf_hooks'
import { Roarr as log } from 'roarr'

/**
 * A method decorator that measures the execution time of the decorated method.
 *
 * @param target - The original method to be decorated.
 * @param context - The context in which the method is executed, providing metadata such as the method name.
 * @returns A replacement method that includes execution time measurement.
 */
export const measure = <This, Args extends any[], Return>(
  target: (this: This, ...args: Args) => Return,
  context: DecoratorContext
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
    log(`[${methodName}] Execution time: ${finish - start} milliseconds`)
    return result
  }
  return trackPerf
}
