/* eslint-disable import-x/no-named-as-default-member */
import koffi from 'koffi'
import { DD_TIME } from './DD_TIME.ts'

export const NET_SDK_REC_FILE = koffi.struct('NET_SDK_REC_FILE', {
  dwChannel: 'uint32',
  bFileLocked: 'uint32',
  startTime: DD_TIME,
  stopTime: DD_TIME,
  dwRecType: 'uint32',
  dwPartition: 'uint32',
  dwFileIndex: 'uint32'
})
