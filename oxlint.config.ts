import { axiom } from '@2bad/axiom'
import { defineConfig } from 'oxlint'

export default defineConfig({
  extends: [axiom],
  rules: {
    // value + type declarations sharing a name (const X / type X) are valid TS, not a redeclaration
    'no-redeclare': 'off'
  }
})
