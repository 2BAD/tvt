import tsconfigPaths from 'vite-tsconfig-paths'
import { coverageConfigDefaults, defineConfig } from 'vitest/config'

// eslint-disable-next-line import-x/no-default-export
export default defineConfig({
  test: {
    exclude: ['build', 'node_modules'],
    coverage: {
      exclude: ['build', ...coverageConfigDefaults.exclude],
      provider: 'v8'
    },
    testTimeout: 30000
  },
  plugins: [tsconfigPaths()]
})
