import type { IKoffiLib } from 'koffi'
import { platform } from 'node:os'
import { resolve } from 'node:path'
import { LPNET_SDK_DEVICEINFO, NET_SDK_DEVICE_DISCOVERY_INFO, NET_SDK_IPC_DEVICE_INFO } from './struct/index.ts'
import type { DeviceInfo, LOG_LEVEL } from './types.ts'

interface TVTSDK {
  // ✅︎ DWORD NET_SDK_GetSDKVersion();
  getSDKVersion: () => Promise<number>
  // ✅︎ DWORD NET_SDK_GetSDKBuildVersion();
  getSDKBuildVersion: () => Promise<number>
  // int NET_SDK_DiscoverDevice(NET_SDK_DEVICE_DISCOVERY_INFO *pDeviceInfo, int bufNum, int waitSeconds = 3);
  discoverDevice: (deviceInfo: DeviceInfo, bufNum: number, waitSeconds: number) => Promise<number>
  // spell-checker: disable-next-line
  // ✅︎ BOOL NET_SDK_GetDeviceInfo(LONG lUserID, LPNET_SDK_DEVICEINFO pdecviceInfo);
  getDeviceInfo: (userId: number, deviceInfo: DeviceInfo) => Promise<boolean>
  // BOOL NET_SDK_GetDeviceIPCInfo(LONG lUserID, NET_SDK_IPC_DEVICE_INFO *pDeviceIPCInfo, LONG lBuffSize, LONG *pIPCCount);
  getDeviceIPCInfo: (
    userId: number,
    deviceIPCInfo: DeviceInfo,
    buffSize: number,
    ipcCount: number[]
  ) => Promise<boolean>
  // ✅︎ BOOL NET_SDK_Init();
  init: () => Promise<boolean>
  // ✅︎ BOOL NET_SDK_Cleanup();
  cleanup: () => Promise<boolean>
  // ✅︎ BOOL NET_SDK_SetConnectTime(DWORD dwWaitTime = 5000, DWORD dwTryTimes = 3);
  setConnectTimeout: (waitTime: number, retryTimes: number) => Promise<boolean>
  // ✅︎ BOOL NET_SDK_SetReconnect(DWORD dwInterval = 5000, BOOL bEnableRecon = TRUE);
  setReconnectInterval: (interval: number, enableRecon: boolean) => Promise<boolean>
  // ✅︎ LONG NET_SDK_Login(char *sDVRIP, WORD wDVRPort, char *sUserName, char *sPassword, LPNET_SDK_DEVICEINFO lpDeviceInfo);
  login: (ip: string, port: number, username: string, password: string, deviceInfo: DeviceInfo) => Promise<number>
  // ✅︎ BOOL NET_SDK_Logout(LONG lUserID)
  logout: (userId: number) => Promise<boolean>
  // LONG NET_SDK_SetupAlarmChan(LONG lUserID);
  setupAlarmChannel: (userId: number) => Promise<number>
  // BOOL NET_SDK_CloseAlarmChan(LONG lAlarmHandle);
  closeAlarmChannel: (alarmHandle: number) => Promise<boolean>
  // ✅︎ BOOL NET_SDK_SetDeviceManualAlarm(LONG lUserID, LONG *pAramChannel, LONG *pValue, LONG lAramChannelCount, BOOL bAlarmOpen);
  triggerAlarm: (
    userId: number,
    channel: number[],
    value: number[],
    channelCount: number,
    alarmOpen: boolean
  ) => Promise<boolean>
  // BOOL NET_SDK_GetConfigFile(LONG lUserID, char *sFileName);
  getConfigFile: (userId: number, fileName: string) => Promise<boolean>
  // BOOL NET_SDK_SetConfigFile(LONG lUserID, char *sFileName);
  setConfigFile: (userId: number, fileName: string) => Promise<boolean>
  // ✅︎ DWORD NET_SDK_GetLastError()
  getLastError: () => Promise<number>
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
  setLogToFile: (logEnable: boolean, logDir: string, autoDel: boolean, logLevel: LOG_LEVEL) => Promise<true>
  // BOOL NET_SDK_SaveLiveData(POINTERHANDLE lLiveHandle, char *sFileName);
  startSavingLiveStream: (liveHandle: number, fileName: string) => Promise<boolean>
  // BOOL NET_SDK_StopSaveLiveData(POINTERHANDLE lLiveHandle);
  stopSavingLiveStream: (liveHandle: number) => Promise<boolean>
  // ✅︎ BOOL NET_SDK_CaptureJPEGFile_V2(LONG lUserID, LONG lChannel, char *sPicFileName);
  captureJPEGFile_V2: (userId: number, channel: number, fileName: string) => Promise<boolean>
}

export class SDK implements TVTSDK {
  static #instance: SDK
  #_koffi: typeof import('koffi') | null = null
  #_lib: IKoffiLib | null = null

  private constructor() {
    if (!this.isLinux) {
      throw new Error('This SDK is only supported on Linux platforms')
    }
  }

  public static getInstance(): SDK {
    if (!SDK.#instance) {
      SDK.#instance = new SDK()
    }
    return SDK.#instance
  }

  private get isLinux(): boolean {
    return platform() === 'linux'
  }

  private get koffi() {
    return (async () => {
      try {
        if (!this.#_koffi) {
          this.#_koffi = (await import('koffi')).default
        }
        return this.#_koffi
      } catch (e) {
        console.error('Failed to load koffi:', e)
        throw new Error('Failed to initialize koffi')
      }
    })()
  }

  private get lib() {
    return (async () => {
      try {
        if (!this.#_lib) {
          const koffi = await this.koffi
          const path = resolve(import.meta.dirname, '../../', 'bin/linux/libdvrnetsdk.so')
          this.#_lib = koffi.load(path)
        }
        return this.#_lib
      } catch (e) {
        console.error('Failed to load library:', e)
        throw new Error('Failed to initialize TVT SDK library')
      }
    })()
  }

  /**
   * Gets the SDK version number.
   *
   * @returns The SDK version in hex format
   */
  public async getSDKVersion(): Promise<number> {
    return (await this.lib).func('NET_SDK_GetSDKVersion', 'uint32_t', [])()
  }

  /**
   * Gets the SDK build version (typically represents build date).
   *
   * @returns The SDK build version
   */
  public async getSDKBuildVersion(): Promise<number> {
    return (await this.lib).func('NET_SDK_GetSDKBuildVersion', 'uint32_t', [])()
  }

  /**
   * Discovers TVT devices on the network.
   *
   * @param deviceInfo - Buffer to store discovered device information
   * @param bufNum - Size of the buffer
   * @param waitSeconds - Time to wait for device responses
   * @returns Number of devices discovered
   */
  public async discoverDevice(deviceInfo: DeviceInfo, bufNum: number, waitSeconds: number): Promise<number> {
    const koffi = await this.koffi
    const lib = await this.lib
    return lib.func('NET_SDK_DiscoverDevice', 'int', [
      koffi.out(koffi.pointer(NET_SDK_DEVICE_DISCOVERY_INFO)),
      'int',
      'int'
    ])(deviceInfo, bufNum, waitSeconds)
  }

  /**
   * Gets detailed information about a connected device.
   *
   * @param userId - User ID from successful login
   * @param deviceInfo - Buffer to store device information
   * @returns Success status
   */
  public async getDeviceInfo(userId: number, deviceInfo: DeviceInfo): Promise<boolean> {
    const koffi = await this.koffi
    const lib = await this.lib
    return lib.func('NET_SDK_GetDeviceInfo', 'bool', ['long', koffi.out(koffi.pointer(LPNET_SDK_DEVICEINFO))])(
      userId,
      deviceInfo
    )
  }

  /**
   * Gets information about IPC devices connected to an NVR/DVR.
   *
   * @param userId - User ID from successful login
   * @param deviceIPCInfo - Buffer to store IPC information
   * @param buffSize - Size of the buffer
   * @param ipcCount - Array to store the count of IPCs
   * @returns Success status
   */
  public async getDeviceIPCInfo(
    userId: number,
    deviceIPCInfo: DeviceInfo,
    buffSize: number,
    ipcCount: number[]
  ): Promise<boolean> {
    const koffi = await this.koffi
    const lib = await this.lib
    return lib.func('NET_SDK_GetDeviceIPCInfo', 'bool', [
      'long',
      koffi.out(koffi.pointer(NET_SDK_IPC_DEVICE_INFO)),
      'long',
      'long *'
    ])(userId, deviceIPCInfo, buffSize, ipcCount)
  }

  /**
   * Initializes the SDK. Must be called before using any other functions.
   *
   * @returns Success status
   */
  public async init(): Promise<boolean> {
    return (await this.lib).func('NET_SDK_Init', 'bool', [])()
  }

  /**
   * Cleans up and releases SDK resources.
   *
   * @returns Success status
   */
  public async cleanup(): Promise<boolean> {
    return (await this.lib).func('NET_SDK_Cleanup', 'bool', [])()
  }

  /**
   * Sets connection timeout parameters.
   *
   * @param waitTime - Wait time in milliseconds
   * @param retryTimes - Number of retry attempts
   * @returns Success status
   */
  public async setConnectTimeout(waitTime: number, retryTimes: number): Promise<boolean> {
    return (await this.lib).func('NET_SDK_SetConnectTime', 'bool', ['uint32_t', 'uint32_t'])(waitTime, retryTimes)
  }

  /**
   * Sets reconnection parameters.
   *
   * @param interval - Reconnection interval in milliseconds
   * @param enableRecon - Enable/disable reconnection
   * @returns Success status
   */
  public async setReconnectInterval(interval: number, enableRecon: boolean): Promise<boolean> {
    return (await this.lib).func('NET_SDK_SetReconnect', 'bool', ['uint32_t', 'bool'])(interval, enableRecon)
  }

  /**
   * Logs into a device.
   *
   * @param ip - Device IP address
   * @param port - Device port
   * @param username - Login username
   * @param password - Login password
   * @param deviceInfo - Buffer to store device information
   * @returns User ID if successful, -1 if failed
   */
  public async login(
    ip: string,
    port: number,
    username: string,
    password: string,
    deviceInfo: DeviceInfo
  ): Promise<number> {
    const koffi = await this.koffi
    const lib = await this.lib
    return lib.func('NET_SDK_Login', 'long', [
      'string',
      'uint16_t',
      'string',
      'string',
      koffi.out(koffi.pointer(LPNET_SDK_DEVICEINFO))
    ])(ip, port, username, password, deviceInfo)
  }

  /**
   * Logs out from a device.
   *
   * @param userId - User ID from successful login
   * @returns Success status
   */
  public async logout(userId: number): Promise<boolean> {
    return (await this.lib).func('NET_SDK_Logout', 'bool', ['long'])(userId)
  }

  /**
   * Sets up an alarm channel.
   *
   * @param userId - User ID from successful login
   * @returns Alarm handle if successful
   */
  public async setupAlarmChannel(userId: number): Promise<number> {
    return (await this.lib).func('NET_SDK_SetupAlarmChan', 'long', ['long'])(userId)
  }

  /**
   * Closes an alarm channel.
   *
   * @param alarmHandle - Handle from setupAlarmChannel
   * @returns Success status
   */
  public async closeAlarmChannel(alarmHandle: number): Promise<boolean> {
    return (await this.lib).func('NET_SDK_CloseAlarmChan', 'bool', ['long'])(alarmHandle)
  }

  /**
   * Triggers manual alarms on specified channels.
   *
   * @param userId - User ID from successful login
   * @param channel - Array of channel numbers
   * @param value - Array of alarm values
   * @param channelCount - Number of channels
   * @param alarmOpen - Alarm open/close state
   * @returns Success status
   */
  public async triggerAlarm(
    userId: number,
    channel: number[],
    value: number[],
    channelCount: number,
    alarmOpen: boolean
  ): Promise<boolean> {
    return (await this.lib).func('NET_SDK_SetDeviceManualAlarm', 'bool', ['long', 'long *', 'long *', 'long', 'bool'])(
      userId,
      channel,
      value,
      channelCount,
      alarmOpen
    )
  }

  /**
   * Gets device configuration file.
   *
   * @param userId - User ID from successful login
   * @param fileName - Path to save configuration file
   * @returns Success status
   */
  public async getConfigFile(userId: number, fileName: string): Promise<boolean> {
    return (await this.lib).func('NET_SDK_GetConfigFile', 'bool', ['long', 'string'])(userId, fileName)
  }

  /**
   * Sets device configuration from file.
   *
   * @param userId - User ID from successful login
   * @param fileName - Path to configuration file
   * @returns Success status
   */
  public async setConfigFile(userId: number, fileName: string): Promise<boolean> {
    return (await this.lib).func('NET_SDK_SetConfigFile', 'bool', ['long', 'string'])(userId, fileName)
  }

  /**
   * Gets the last error code from the SDK.
   *
   * @returns Error code
   */
  public async getLastError(): Promise<number> {
    return (await this.lib).func('NET_SDK_GetLastError', 'uint32_t', [])()
  }

  /**
   * Configures SDK logging to file.
   *
   * @param logEnable - Enable/disable logging
   * @param logDir - Directory for log files
   * @param autoDel - Enable auto-deletion of old logs
   * @param logLevel - Logging level
   * @returns Success status
   */
  public async setLogToFile(logEnable: boolean, logDir: string, autoDel: boolean, logLevel: LOG_LEVEL): Promise<true> {
    return (await this.lib).func('NET_SDK_SetLogToFile', 'bool', ['bool', 'string', 'bool', 'int'])(
      logEnable,
      logDir,
      autoDel,
      logLevel
    )
  }

  /**
   * Starts saving live stream to file.
   *
   * @param liveHandle - Live stream handle
   * @param fileName - Path to save stream file
   * @returns Success status
   */
  public async startSavingLiveStream(liveHandle: number, fileName: string): Promise<boolean> {
    return (await this.lib).func('NET_SDK_SaveLiveData', 'bool', ['long', 'string'])(liveHandle, fileName)
  }

  /**
   * Stops saving live stream to file.
   *
   * @param liveHandle - Live stream handle
   * @returns Success status
   */
  public async stopSavingLiveStream(liveHandle: number): Promise<boolean> {
    return (await this.lib).func('NET_SDK_StopSaveLiveData', 'bool', ['long'])(liveHandle)
  }

  /**
   * Captures a JPEG snapshot from a channel.
   *
   * @param userId - User ID from successful login
   * @param channel - Video channel number
   * @param fileName - Path to save JPEG file
   * @returns Success status
   */
  public async captureJPEGFile_V2(userId: number, channel: number, fileName: string): Promise<boolean> {
    return (await this.lib).func('NET_SDK_CaptureJPEGFile_V2', 'bool', ['long', 'long', 'string'])(
      userId,
      channel,
      fileName
    )
  }
}

// Export a singleton instance
export const sdk = SDK.getInstance()
