import koffi from 'koffi'
import { resolve } from 'path'
import { LPNET_SDK_DEVICEINFO } from './struct/LPNET_SDK_DEVICEINFO.ts'
import { NET_SDK_DEVICE_DISCOVERY_INFO } from './struct/NET_SDK_DEVICE_DISCOVERY_INFO.ts'
import { NET_SDK_IPC_DEVICE_INFO } from './struct/NET_SDK_IPC_DEVICE_INFO.ts'
import { type LOG_LEVEL } from './types.ts'

const path = resolve('bin/linux/libdvrnetsdk.so')
const lib = koffi.load(path)

// koffi.alias('DWORD', 'uint32_t')
// koffi.alias('WORD', 'uint16_t')

type SDK = {
  // DWORD NET_SDK_GetSDKVersion();
  getSDKVersion: () => number
  // DWORD NET_SDK_GetSDKBuildVersion();
  getSDKBuildVersion: () => number
  // int NET_SDK_DiscoverDevice(NET_SDK_DEVICE_DISCOVERY_INFO *pDeviceInfo, int bufNum, int waitSeconds = 3);
  discoverDevice: (deviceInfo: Record<string, unknown>, bufNum: number, waitSeconds: number) => number
  // BOOL NET_SDK_GetDeviceIPCInfo(LONG lUserID, NET_SDK_IPC_DEVICE_INFO* pDeviceIPCInfo, LONG lBuffSize, LONG* pIPCCount);
  getDeviceIPCInfo: (
    userId: number,
    deviceIPCInfo: Record<string, unknown>,
    buffSize: number,
    ipcCount: number
  ) => boolean
  // BOOL NET_SDK_Init();
  init: () => boolean
  // BOOL NET_SDK_Cleanup();
  cleanup: () => boolean
  // BOOL NET_SDK_SetConnectTime(DWORD dwWaitTime = 5000, DWORD dwTryTimes = 3);
  setConnectTimeout: (waitTime: number, retryTimes: number) => boolean
  // BOOL NET_SDK_SetReconnect(DWORD dwInterval = 5000, BOOL bEnableRecon = TRUE);
  setReconnectInterval: (interval: number, enableRecon: boolean) => boolean
  // LONG NET_SDK_Login(char *sDVRIP,WORD wDVRPort,char *sUserName,char *sPassword, LPNET_SDK_DEVICEINFO lpDeviceInfo);
  login: (ip: string, port: number, username: string, password: string, deviceInfo: Record<string, unknown>) => number
  // BOOL NET_SDK_GetDeviceInfo(LONG lUserID, LPNET_SDK_DEVICEINFO pdecviceInfo);
  getDeviceInfo: (userId: number, deviceInfo: Record<string, unknown>) => boolean
  // LONG NET_SDK_SetupAlarmChan(LONG lUserID);
  setupAlarmChanel: (userId: number) => number
  // BOOL NET_SDK_CloseAlarmChan(LONG lAlarmHandle);
  closeAlarmChanel: (alarmHandle: number) => boolean
  // BOOL NET_SDK_SetDeviceManualAlarm(LONG lUserID, LONG *pAramChannel, LONG *pValue, LONG lAramChannelCount, BOOL bAlarmOpen);
  triggerAlarm: (userId: number, channel: number, value: number, channelCount: number, alarmOpen: boolean) => boolean
  // DWORD NET_SDK_GetLastError()
  getLastError: () => number
  // BOOL NET_SDK_SetLogToFile(BOOL bLogEnable = FALSE, char *strLogDir = NULL, BOOL bAutoDel = TRUE, int logLevel = YLOG_DEBUG);
  setLogToFile: (logEnable: boolean, logDir: string, autoDel: boolean, logLevel: LOG_LEVEL) => true
}

export const sdk: SDK = {
  getSDKVersion: lib.func('NET_SDK_GetSDKVersion', 'uint32_t', []),
  getSDKBuildVersion: lib.func('NET_SDK_GetSDKBuildVersion', 'uint32_t', []),
  discoverDevice: lib.func('NET_SDK_DiscoverDevice', 'int', [
    koffi.out(koffi.pointer(NET_SDK_DEVICE_DISCOVERY_INFO)),
    'int',
    'int'
  ]),
  getDeviceIPCInfo: lib.func('NET_SDK_GetDeviceIPCInfo', 'bool', [
    'long',
    koffi.out(koffi.pointer(NET_SDK_IPC_DEVICE_INFO)),
    'long',
    'long'
  ]),
  init: lib.func('NET_SDK_Init', 'bool', []),
  cleanup: lib.func('NET_SDK_Cleanup', 'bool', []),
  setConnectTimeout: lib.func('NET_SDK_SetConnectTime', 'bool', ['uint32_t', 'uint32_t']),
  setReconnectInterval: lib.func('NET_SDK_SetReconnect', 'bool', ['uint32_t', 'bool']),
  login: lib.func('NET_SDK_Login', 'long', [
    'string',
    'uint16_t',
    'string',
    'string',
    koffi.out(koffi.pointer(LPNET_SDK_DEVICEINFO))
  ]),
  getDeviceInfo: lib.func('NET_SDK_GetDeviceInfo', 'bool', ['long', koffi.out(koffi.pointer(LPNET_SDK_DEVICEINFO))]),
  setupAlarmChanel: lib.func('NET_SDK_SetupAlarmChan', 'long', ['long']),
  closeAlarmChanel: lib.func('NET_SDK_CloseAlarmChan', 'bool', ['long']),
  triggerAlarm: lib.func('NET_SDK_SetDeviceManualAlarm', 'bool', ['long', 'long', 'long', 'long', 'bool']),
  getLastError: lib.func('NET_SDK_GetLastError', 'uint32_t', []),
  setLogToFile: lib.func('NET_SDK_SetLogToFile', 'bool', ['bool', 'string', 'bool', 'int'])
}
