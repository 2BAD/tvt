import tsconfigPaths from 'vite-tsconfig-paths'
// eslint-disable-next-line import/no-unresolved
import { defineConfig } from 'vitest/config'

export default defineConfig({
  test: {
    exclude: ['build', 'node_modules'],
    coverage: {
      provider: 'v8'
    },
    testTimeout: 30000
  },
  plugins: [tsconfigPaths()]
})
