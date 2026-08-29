/* eslint-disable import-x/no-named-as-default-member */
import koffi from 'koffi'

export const DD_TIME = koffi.struct('DD_TIME', {
  second: 'uchar',
  minute: 'uchar',
  hour: 'uchar',
  wday: 'uchar',
  mday: 'uchar',
  month: 'uchar',
  year: 'ushort',
  nTotalseconds: 'int',
  nMicrosecond: 'int'
})
