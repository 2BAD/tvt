/* eslint-disable import-x/no-named-as-default-member */
import koffi from 'koffi'

export const NET_SDK_IMAGE_EFFECT_T = koffi.struct('NET_SDK_IMAGE_EFFECT_T', {
  minValue: 'uint',
  maxValue: 'uint',
  curValue: 'uint',
  defaultValue: 'uint'
})
