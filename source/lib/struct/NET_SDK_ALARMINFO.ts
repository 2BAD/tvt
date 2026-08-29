/* eslint-disable import-x/no-named-as-default-member */
import koffi from 'koffi'

export const NET_SDK_ALARMINFO = koffi.struct('NET_SDK_ALARMINFO', {
  dwAlarmType: 'uint',
  dwSensorIn: 'uint',
  dwChannel: 'uint',
  dwDisk: 'uint'
})

export const NET_MESSAGE_CALLBACK = koffi.proto(
  'bool NET_MESSAGE_CALLBACK(long lCommand, long lUserID, void *pBuf, uint32_t dwBufLen, void *pUser)'
)
