import koffi from 'koffi'
import { resolve } from 'path'
import { LPNET_SDK_DEVICEINFO } from './struct/LPNET_SDK_DEVICEINFO.ts'

const path = resolve('bin/linux/libdvrnetsdk.so')
const dvr = koffi.load(path)

// koffi.alias('DWORD', 'uint32_t')
// koffi.alias('WORD', 'uint16_t')

type SDK = {
  // DWORD CALL_METHOD NET_SDK_GetSDKVersion();
  getSDKVersion: () => number
  // DWORD CALL_METHOD NET_SDK_GetSDKBuildVersion();
  getSDKBuildVersion: () => number
  // BOOL CALL_METHOD NET_SDK_Init();
  init: () => boolean
  // BOOL CALL_METHOD NET_SDK_Cleanup();
  cleanup: () => boolean
  // BOOL CALL_METHOD NET_SDK_SetConnectTime(DWORD dwWaitTime = 5000, DWORD dwTryTimes = 3);
  connect: (waitTime: number, retryTimes: number) => boolean
  // BOOL CALL_METHOD NET_SDK_SetReconnect(DWORD dwInterval = 5000, BOOL bEnableRecon = TRUE);
  reconnect: (interval: number, enableRecon: boolean) => boolean
  // LONG CALL_METHOD NET_SDK_Login(char *sDVRIP,WORD wDVRPort,char *sUserName,char *sPassword,LPNET_SDK_DEVICEINFO lpDeviceInfo);
  login: (ip: string, port: number, username: string, password: string, deviceInfo: Record<string, unknown>) => number
  // BOOL CALL_METHOD NET_SDK_GetDeviceInfo(LONG lUserID, LPNET_SDK_DEVICEINFO pdecviceInfo);
  getDeviceInfo: (userId: number) => Record<string, unknown>
  // LONG CALL_METHOD NET_SDK_SetupAlarmChan(LONG lUserID);
  setupAlarmChanel: (userId: number) => number
  // BOOL CALL_METHOD NET_SDK_CloseAlarmChan(LONG lAlarmHandle);
  closeAlarmChanel: (alarmHandle: number) => boolean
  // BOOL CALL_METHOD NET_SDK_SetDeviceManualAlarm(LONG lUserID, LONG *pAramChannel, LONG *pValue, LONG lAramChannelCount, BOOL bAlarmOpen);
  triggerAlarm: (userId: number, channel: number, value: number, channelCount: number, alarmOpen: boolean) => boolean
  // DWORD CALL_METHOD NET_SDK_GetLastError()
  getLastError: () => number
}

export const sdk: SDK = {
  getSDKVersion: dvr.func('NET_SDK_GetSDKVersion', 'uint32_t', []),
  getSDKBuildVersion: dvr.func('NET_SDK_GetSDKBuildVersion', 'uint32_t', []),
  init: dvr.func('NET_SDK_Init', 'bool', []),
  cleanup: dvr.func('NET_SDK_Cleanup', 'bool', []),
  connect: dvr.func('NET_SDK_SetConnectTime', 'bool', ['uint32_t', 'uint32_t']),
  reconnect: dvr.func('NET_SDK_SetReconnect', 'bool', ['uint32_t', 'bool']),
  login: dvr.func('NET_SDK_Login', 'long', [
    'string',
    'uint16_t',
    'string',
    'string',
    koffi.out(koffi.pointer(LPNET_SDK_DEVICEINFO))
  ]),
  getDeviceInfo: dvr.func('NET_SDK_GetDeviceInfo', 'bool', ['long', koffi.out(koffi.pointer(LPNET_SDK_DEVICEINFO))]),
  setupAlarmChanel: dvr.func('NET_SDK_SetupAlarmChan', 'long', ['long']),
  closeAlarmChanel: dvr.func('NET_SDK_CloseAlarmChan', 'bool', ['long']),
  triggerAlarm: dvr.func('NET_SDK_SetDeviceManualAlarm', 'bool', ['long', 'long', 'long', 'long', 'bool']),
  getLastError: dvr.func('NET_SDK_GetLastError', 'uint32_t', [])
}