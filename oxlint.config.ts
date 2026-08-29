import { axiom } from '@2bad/axiom'
import { defineConfig } from 'oxlint'

export default defineConfig({
  extends: [axiom],
  overrides: [
    {
      // enum-style const X + type X pairs are valid TS, not a redeclaration; tsc catches real ones
      files: ['**/lib/types.ts'],
      rules: { 'no-redeclare': 'off' }
    }
  ]
})
