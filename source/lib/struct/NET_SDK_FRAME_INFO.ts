/* eslint-disable import-x/no-named-as-default-member */
import koffi from 'koffi'

export const NET_SDK_FRAME_INFO = koffi.struct('NET_SDK_FRAME_INFO', {
  deviceID: 'uint',
  channel: 'uint',
  frameType: 'uint',
  length: 'uint',
  keyFrame: 'uint',
  width: 'uint',
  height: 'uint',
  frameIndex: 'uint',
  frameAttrib: 'uint',
  streamID: 'uint',
  time: 'int64',
  relativeTime: 'int64'
})

export const LIVE_DATA_CALLBACK = koffi.proto(
  'void LIVE_DATA_CALLBACK(long lLiveHandle, NET_SDK_FRAME_INFO frameInfo, void *pBuffer, void *pUser)'
)
