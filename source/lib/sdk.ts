import koffi from 'koffi'
import { platform } from 'node:os'
import { resolve } from 'node:path'
import { LPNET_SDK_DEVICEINFO, NET_SDK_DEVICE_DISCOVERY_INFO, NET_SDK_IPC_DEVICE_INFO } from './struct/index.ts'
import type { DeviceInfo, LOG_LEVEL } from './types.ts'

type SDK = {
  // ✅︎ DWORD NET_SDK_GetSDKVersion();
  getSDKVersion: () => number
  // ✅︎ DWORD NET_SDK_GetSDKBuildVersion();
  getSDKBuildVersion: () => number
  // int NET_SDK_DiscoverDevice(NET_SDK_DEVICE_DISCOVERY_INFO *pDeviceInfo, int bufNum, int waitSeconds = 3);
  discoverDevice: (deviceInfo: DeviceInfo, bufNum: number, waitSeconds: number) => number
  // spell-checker: disable-next-line
  // ✅︎ BOOL NET_SDK_GetDeviceInfo(LONG lUserID, LPNET_SDK_DEVICEINFO pdecviceInfo);
  getDeviceInfo: (userId: number, deviceInfo: DeviceInfo) => boolean
  // BOOL NET_SDK_GetDeviceIPCInfo(LONG lUserID, NET_SDK_IPC_DEVICE_INFO *pDeviceIPCInfo, LONG lBuffSize, LONG *pIPCCount);
  getDeviceIPCInfo: (userId: number, deviceIPCInfo: DeviceInfo, buffSize: number, ipcCount: number[]) => boolean
  // ✅︎ BOOL NET_SDK_Init();
  init: () => boolean
  // ✅︎ BOOL NET_SDK_Cleanup();
  cleanup: () => boolean
  // ✅︎ BOOL NET_SDK_SetConnectTime(DWORD dwWaitTime = 5000, DWORD dwTryTimes = 3);
  setConnectTimeout: (waitTime: number, retryTimes: number) => boolean
  // ✅︎ BOOL NET_SDK_SetReconnect(DWORD dwInterval = 5000, BOOL bEnableRecon = TRUE);
  setReconnectInterval: (interval: number, enableRecon: boolean) => boolean
  // ✅︎ LONG NET_SDK_Login(char *sDVRIP, WORD wDVRPort, char *sUserName, char *sPassword, LPNET_SDK_DEVICEINFO lpDeviceInfo);
  login: (ip: string, port: number, username: string, password: string, deviceInfo: DeviceInfo) => number
  // ✅︎ BOOL NET_SDK_Logout(LONG lUserID)
  logout: (userId: number) => boolean
  // LONG NET_SDK_SetupAlarmChan(LONG lUserID);
  setupAlarmChanel: (userId: number) => number
  // BOOL NET_SDK_CloseAlarmChan(LONG lAlarmHandle);
  closeAlarmChanel: (alarmHandle: number) => boolean
  // ✅︎ BOOL NET_SDK_SetDeviceManualAlarm(LONG lUserID, LONG *pAramChannel, LONG *pValue, LONG lAramChannelCount, BOOL bAlarmOpen);
  triggerAlarm: (
    userId: number,
    channel: number[],
    value: number[],
    channelCount: number,
    alarmOpen: boolean
  ) => boolean
  // BOOL NET_SDK_GetConfigFile(LONG lUserID, char *sFileName);
  getConfigFile: (userId: number, fileName: string) => boolean
  // BOOL NET_SDK_SetConfigFile(LONG lUserID, char *sFileName);
  setConfigFile: (userId: number, fileName: string) => boolean
  // ✅︎ DWORD NET_SDK_GetLastError()
  getLastError: () => number
  /**
   * Probably windows only. Based on de compiled code from the SDK:
   * ...
   * void __fastcall YLog4C::SetLogDir(const char *lpszDir)
   * ...
   * strcpy(g_strLogDir, lpszDir);
   * nLen = strlen(g_strLogDir);
   * v5 = g_strLogDir[nLen - 1];
   * if ( nLen > 2 && g_strLogDir[1] == ':' && (v5 == '\\' || v5 == '/') )
   * ...
   */
  // BOOL NET_SDK_SetLogToFile(BOOL bLogEnable = FALSE, char *strLogDir = NULL, BOOL bAutoDel = TRUE, int logLevel = YLOG_DEBUG);
  setLogToFile: (logEnable: boolean, logDir: string, autoDel: boolean, logLevel: LOG_LEVEL) => true
  // BOOL NET_SDK_SaveLiveData(POINTERHANDLE lLiveHandle, char *sFileName);
  startSavingLiveStream: (liveHandle: number, fileName: string) => boolean
  // BOOL NET_SDK_StopSaveLiveData(POINTERHANDLE lLiveHandle);
  stopSavingLiveStream: (liveHandle: number) => boolean
  // ✅︎ BOOL NET_SDK_CaptureJPEGFile_V2(LONG lUserID, LONG lChannel, char *sPicFileName);
  captureJPEGFile_V2: (userId: number, channel: number, fileName: string) => boolean
}

const isLinux = platform() === 'linux'

if (!isLinux) {
  throw new Error('This SDK is only supported on Linux platforms')
}

/**
 * Creates a lazy-loaded SDK instance for interfacing with TVT devices.
 * The SDK is only loaded when first accessed and subsequent calls use the cached instance.
 * This SDK is specifically designed for Linux systems and provides methods for device control and monitoring.
 *
 * @returns An object containing all available SDK methods
 * @throws {Error} If the library cannot be loaded or if running on non-Linux systems
 */
const createSDK = (): SDK => {
  let lib: ReturnType<typeof koffi.load> | null = null

  /**
   * Gets or initializes the library instance.
   *
   * @returns The loaded shared library instance
   */
  const getLib = () => {
    if (!lib) {
      const path = resolve(import.meta.dirname, '../../', 'bin/linux/libdvrnetsdk.so')
      lib = koffi.load(path)
    }
    return lib
  }

  return {
    /**
     * Gets the SDK version number.
     *
     * @returns {number} The SDK version in hex format
     */
    getSDKVersion: getLib().func('NET_SDK_GetSDKVersion', 'uint32_t', []),

    /**
     * Gets the SDK build version (typically represents build date).
     *
     * @returns {number} The SDK build version
     */
    getSDKBuildVersion: getLib().func('NET_SDK_GetSDKBuildVersion', 'uint32_t', []),

    /**
     * Discovers TVT devices on the network.
     *
     * @param {DeviceInfo} deviceInfo - Buffer to store discovered device information
     * @param {number} bufNum - Size of the buffer
     * @param {number} waitSeconds - Time to wait for device responses
     * @returns {number} Number of devices discovered
     */
    discoverDevice: getLib().func('NET_SDK_DiscoverDevice', 'int', [
      koffi.out(koffi.pointer(NET_SDK_DEVICE_DISCOVERY_INFO)),
      'int',
      'int'
    ]),

    /**
     * Gets detailed information about a connected device.
     *
     * @param {number} userId - User ID from successful login
     * @param {DeviceInfo} deviceInfo - Buffer to store device information
     * @returns {boolean} Success status
     */
    getDeviceInfo: getLib().func('NET_SDK_GetDeviceInfo', 'bool', [
      'long',
      koffi.out(koffi.pointer(LPNET_SDK_DEVICEINFO))
    ]),

    /**
     * Gets information about IPC devices connected to an NVR/DVR.
     *
     * @param {number} userId - User ID from successful login
     * @param {DeviceInfo} deviceIPCInfo - Buffer to store IPC information
     * @param {number} buffSize - Size of the buffer
     * @param {number[]} ipcCount - Array to store the count of IPCs
     * @returns {boolean} Success status
     */
    getDeviceIPCInfo: getLib().func('NET_SDK_GetDeviceIPCInfo', 'bool', [
      'long',
      koffi.out(koffi.pointer(NET_SDK_IPC_DEVICE_INFO)),
      'long',
      'long *'
    ]),

    /**
     * Initializes the SDK. Must be called before using any other functions.
     *
     * @returns {boolean} Success status
     */
    init: getLib().func('NET_SDK_Init', 'bool', []),

    /**
     * Cleans up and releases SDK resources.
     *
     * @returns {boolean} Success status
     */
    cleanup: getLib().func('NET_SDK_Cleanup', 'bool', []),

    /**
     * Sets connection timeout parameters.
     *
     * @param {number} waitTime - Wait time in milliseconds
     * @param {number} retryTimes - Number of retry attempts
     * @returns {boolean} Success status
     */
    setConnectTimeout: getLib().func('NET_SDK_SetConnectTime', 'bool', ['uint32_t', 'uint32_t']),

    /**
     * Sets reconnection parameters.
     *
     * @param {number} interval - Reconnection interval in milliseconds
     * @param {boolean} enableRecon - Enable/disable reconnection
     * @returns {boolean} Success status
     */
    setReconnectInterval: getLib().func('NET_SDK_SetReconnect', 'bool', ['uint32_t', 'bool']),

    /**
     * Logs into a device.
     *
     * @param {string} ip - Device IP address
     * @param {number} port - Device port
     * @param {string} username - Login username
     * @param {string} password - Login password
     * @param {DeviceInfo} deviceInfo - Buffer to store device information
     * @returns {number} User ID if successful, -1 if failed
     */
    login: getLib().func('NET_SDK_Login', 'long', [
      'string',
      'uint16_t',
      'string',
      'string',
      koffi.out(koffi.pointer(LPNET_SDK_DEVICEINFO))
    ]),

    /**
     * Logs out from a device.
     *
     * @param {number} userId - User ID from successful login
     * @returns {boolean} Success status
     */
    logout: getLib().func('NET_SDK_Logout', 'bool', ['long']),

    /**
     * Sets up an alarm channel.
     *
     * @param {number} userId - User ID from successful login
     * @returns {number} Alarm handle if successful
     */
    setupAlarmChanel: getLib().func('NET_SDK_SetupAlarmChan', 'long', ['long']),

    /**
     * Closes an alarm channel.
     *
     * @param {number} alarmHandle - Handle from setupAlarmChanel
     * @returns {boolean} Success status
     */
    closeAlarmChanel: getLib().func('NET_SDK_CloseAlarmChan', 'bool', ['long']),

    /**
     * Triggers manual alarms on specified channels.
     *
     * @param {number} userId - User ID from successful login
     * @param {number[]} channel - Array of channel numbers
     * @param {number[]} value - Array of alarm values
     * @param {number} channelCount - Number of channels
     * @param {boolean} alarmOpen - Alarm open/close state
     * @returns {boolean} Success status
     */
    triggerAlarm: getLib().func('NET_SDK_SetDeviceManualAlarm', 'bool', ['long', 'long *', 'long *', 'long', 'bool']),

    /**
     * Gets device configuration file.
     *
     * @param {number} userId - User ID from successful login
     * @param {string} fileName - Path to save configuration file
     * @returns {boolean} Success status
     */
    getConfigFile: getLib().func('NET_SDK_GetConfigFile', 'bool', ['long', 'string']),

    /**
     * Sets device configuration from file.
     *
     * @param {number} userId - User ID from successful login
     * @param {string} fileName - Path to configuration file
     * @returns {boolean} Success status
     */
    setConfigFile: getLib().func('NET_SDK_SetConfigFile', 'bool', ['long', 'string']),

    /**
     * Gets the last error code from the SDK.
     *
     * @returns {number} Error code
     */
    getLastError: getLib().func('NET_SDK_GetLastError', 'uint32_t', []),

    /**
     * Configures SDK logging to file.
     *
     * @param {boolean} logEnable - Enable/disable logging
     * @param {string} logDir - Directory for log files
     * @param {boolean} autoDel - Enable auto-deletion of old logs
     * @param {number} logLevel - Logging level
     * @returns {boolean} Success status
     */
    setLogToFile: getLib().func('NET_SDK_SetLogToFile', 'bool', ['bool', 'string', 'bool', 'int']),

    /**
     * Starts saving live stream to file.
     *
     * @param {number} liveHandle - Live stream handle
     * @param {string} fileName - Path to save stream file
     * @returns {boolean} Success status
     */
    startSavingLiveStream: getLib().func('NET_SDK_SaveLiveData', 'bool', ['long', 'string']),

    /**
     * Stops saving live stream to file.
     *
     * @param {number} liveHandle - Live stream handle
     * @returns {boolean} Success status
     */
    stopSavingLiveStream: getLib().func('NET_SDK_StopSaveLiveData', 'bool', ['long']),

    /**
     * Captures a JPEG snapshot from a channel.
     *
     * @param {number} userId - User ID from successful login
     * @param {number} channel - Video channel number
     * @param {string} fileName - Path to save JPEG file
     * @returns {boolean} Success status
     */
    captureJPEGFile_V2: getLib().func('NET_SDK_CaptureJPEGFile_V2', 'bool', ['long', 'long', 'string'])
  }
}

export const sdk = createSDK()
