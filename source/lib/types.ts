export const LOG_LEVEL = {
  LOG_FATAL: 0,
  LOG_ERROR: 1,
  LOG_WARN: 2,
  LOG_INFO: 3,
  LOG_DEBUG: 4,
  LOG_BUFF: 5
} as const

export type LOG_LEVEL = (typeof LOG_LEVEL)[keyof typeof LOG_LEVEL]

export const STREAM_TYPE = {
  MAIN: 0,
  SUB: 1
} as const

export type STREAM_TYPE = (typeof STREAM_TYPE)[keyof typeof STREAM_TYPE]

export const FRAME_TYPE = {
  NONE: 0,
  VIDEO: 1,
  AUDIO: 2,
  TALK_AUDIO: 3,
  JPEG: 4,
  VIDEO_FORMAT: 5,
  AUDIO_FORMAT: 6,
  TALK_AUDIO_FORMAT: 7
} as const

export type FRAME_TYPE = (typeof FRAME_TYPE)[keyof typeof FRAME_TYPE]

export type FrameInfo = {
  deviceID: number
  channel: number
  frameType: number
  length: number
  keyFrame: number
  width: number
  height: number
  frameIndex: number
  frameAttrib: number
  streamID: number
  /** absolute time in microseconds since 1970-01-01 00:00:00 UTC */
  time: number
  /** relative time in microseconds */
  relativeTime: number
}

export type LiveFrameCallback = (frame: FrameInfo, data: Buffer) => void

// spell-checker: disable
export const ALARM_TYPE = {
  MOTION: 0x01,
  SENSOR: 0x02,
  VIDEO_LOSS: 0x03,
  FRONT_OFFLINE: 0x04,
  OSC: 0x05,
  AVD: 0x06,
  AVD_SCENE: 0x07,
  AVD_CLARITY: 0x08,
  AVD_COLOR: 0x09,
  PEA_TRIPWIRE: 0x0a,
  PEA_PERIMETER: 0x0b,
  VFD: 0x0c,
  CDD: 0x0d,
  IPD: 0x0e,
  CPC: 0x0f,
  FACE_MATCH: 0x10,
  FACE_MATCH_FOR_IPC: 0x11,
  PEA_FOR_IPC: 0x12,
  TRAJECT: 0x13,
  VEHICLE: 0x14,
  AOI_ENTRY: 0x15,
  AOI_LEAVE: 0x16,
  PASS_LINE: 0x17,
  TRAFFIC: 0x18,
  DOOR_BELL: 0x19,
  EXCEPTION: 0x41,
  IP_CONFLICT: 0x42,
  DISK_IO_ERROR: 0x43,
  DISK_FULL: 0x44
} as const
// spell-checker: enable

export type ALARM_TYPE = (typeof ALARM_TYPE)[keyof typeof ALARM_TYPE]

export const ALARM_TYPE_NAME: ReadonlyMap<number, string> = new Map(
  Object.entries(ALARM_TYPE).map(([name, code]) => [code, name])
)

export type AlarmEvent = {
  /** ALARM_TYPE code */
  type: number
  /** sensor input port for sensor alarms */
  sensorIn: number
  /** channel the alarm relates to */
  channel: number
  /** disk number for disk alarms */
  disk: number
}

export type AlarmCallback = (event: AlarmEvent) => void

export type DeviceTime = {
  second: number
  minute: number
  hour: number
  /** day of week, 0-6, Sunday = 0 */
  wday: number
  /** day of month, 1-31 */
  mday: number
  /** month, 0-11, January = 0 */
  month: number
  /** years since 1900 */
  year: number
  nTotalseconds: number
  nMicrosecond: number
}

export type VideoEffect = {
  /** 0-100 */
  brightness: number
  /** 0-100 */
  contrast: number
  /** 0-100 */
  saturation: number
  /** 0-100 */
  hue: number
}

// spell-checker: disable
export const NET_SDK_ERROR = {
  NET_SDK_SUCCESS: 0,
  NET_SDK_PASSWORD_ERROR: 1,
  NET_SDK_NOENOUGH_AUTH: 2,
  NET_SDK_NOINIT: 3,
  NET_SDK_CHANNEL_ERROR: 4,
  NET_SDK_OVER_MAXLINK: 5,
  NET_SDK_LOGIN_REFUSED: 6,
  NET_SDK_VERSION_NOMATCH: 7,
  NET_SDK_NETWORK_FAIL_CONNECT: 8,
  NET_SDK_NETWORK_NOT_CONNECT: 9,
  NET_SDK_NETWORK_SEND_ERROR: 10,
  NET_SDK_NETWORK_RECV_ERROR: 11,
  NET_SDK_NETWORK_RECV_TIMEOUT: 12,
  NET_SDK_NETWORK_ERRORDATA: 13,
  NET_SDK_ORDER_ERROR: 14,
  NET_SDK_OPER_BY_OTHER: 15,
  NET_SDK_OPER_NOPERMIT: 16,
  NET_SDK_COMMAND_TIMEOUT: 17,
  NET_SDK_ERROR_SERIALPORT: 18,
  NET_SDK_ERROR_ALARMPORT: 19,
  NET_SDK_PARAMETER_ERROR: 20,
  NET_SDK_CHAN_EXCEPTION: 21,
  NET_SDK_NODISK: 22,
  NET_SDK_ERROR_DISKNUM: 23,
  NET_SDK_DISK_FULL: 24,
  NET_SDK_DISK_ERROR: 25,
  NET_SDK_NOSUPPORT: 26,
  NET_SDK_BUSY: 27,
  NET_SDK_MODIFY_FAIL: 28,
  NET_SDK_PASSWORD_FORMAT_ERROR: 29,
  NET_SDK_DISK_FORMATING: 30,
  NET_SDK_DVR_NORESOURCE: 31,
  NET_SDK_DVR_OPRATE_FAILED: 32,
  NET_SDK_OPEN_HOSTSOUND_FAIL: 33,
  NET_SDK_DVR_VOICEOPENED: 34,
  NET_SDK_TIME_INPUTERROR: 35,
  NET_SDK_NOSPECFILE: 36,
  NET_SDK_CREATEFILE_ERROR: 37,
  NET_SDK_FILEOPENFAIL: 38,
  NET_SDK_OPERNOTFINISH: 39,
  NET_SDK_GETPLAYTIMEFAIL: 40,
  NET_SDK_PLAYFAIL: 41,
  NET_SDK_FILEFORMAT_ERROR: 42,
  NET_SDK_DIR_ERROR: 43,
  NET_SDK_ALLOC_RESOURCE_ERROR: 44,
  NET_SDK_AUDIO_MODE_ERROR: 45,
  NET_SDK_NOENOUGH_BUF: 46,
  NET_SDK_CREATESOCKET_ERROR: 47,
  NET_SDK_SETSOCKET_ERROR: 48,
  NET_SDK_MAX_NUM: 49,
  NET_SDK_USERNOTEXIST: 50,
  NET_SDK_WRITEFLASHERROR: 51,
  NET_SDK_UPGRADEFAIL: 52,
  NET_SDK_CARDHAVEINIT: 53,
  NET_SDK_PLAYERFAILED: 54,
  NET_SDK_MAX_USERNUM: 55,
  NET_SDK_GETLOCALIPANDMACFAIL: 56,
  NET_SDK_NOENCODEING: 57,
  NET_SDK_IPMISMATCH: 58,
  NET_SDK_MACMISMATCH: 59,
  NET_SDK_UPGRADELANGMISMATCH: 60,
  NET_SDK_MAX_PLAYERPORT: 61,
  NET_SDK_NOSPACEBACKUP: 62,
  NET_SDK_NODEVICEBACKUP: 63,
  NET_SDK_PICTURE_BITS_ERROR: 64,
  NET_SDK_PICTURE_DIMENSION_ERROR: 65,
  NET_SDK_PICTURE_SIZ_ERROR: 66,
  NET_SDK_LOADPLAYERSDKFAILED: 67,
  NET_SDK_LOADPLAYERSDKPROC_ERROR: 68,
  NET_SDK_LOADDSSDKFAILED: 69,
  NET_SDK_LOADDSSDKPROC_ERROR: 70,
  NET_SDK_DSSDK_ERROR: 71,
  NET_SDK_VOICEMONOPOLIZE: 72,
  NET_SDK_JOINMULTICASTFAILED: 73,
  NET_SDK_CREATEDIR_ERROR: 74,
  NET_SDK_BINDSOCKET_ERROR: 75,
  NET_SDK_SOCKETCLOSE_ERROR: 76,
  NET_SDK_USERID_ISUSING: 77,
  NET_SDK_PROGRAM_EXCEPTION: 78,
  NET_SDK_WRITEFILE_FAILED: 79,
  NET_SDK_FORMAT_READONLY: 80,
  NET_SDK_WITHSAMEUSERNAME: 81,
  NET_SDK_DEVICETYPE_ERROR: 82,
  NET_SDK_LANGUAGE_ERROR: 83,
  NET_SDK_PARAVERSION_ERROR: 84,
  NET_SDK_FILE_SUCCESS: 85,
  NET_SDK_FILE_NOFIND: 86,
  NET_SDK_NOMOREFILE: 87,
  NET_SDK_FILE_EXCEPTION: 88,
  NET_SDK_TRY_LATER: 89,
  NET_SDK_DEVICE_OFFLINE: 90,
  NET_SDK_CREATEJPEGSTREAM_FAIL: 91,
  NET_SDK_USER_ERROR_NO_USER: 92,
  NET_SDK_USER_ERROR_USER_OR_PASSWORD_IS_NULL: 93,
  NET_SDK_USER_ERROR_ALREDAY_LOGIN: 94,
  NET_SDK_USER_ERROR_SYSTEM_BUSY: 95,
  NET_SDK_DEVICE_NOT_SUPPROT: 96,
  NET_SDK_USER_ERROR_SYSTEM_NO_READY: 97,
  NET_SDK_CHANNEL_OFFLINE: 98,
  NET_SDK_GETREADYINFO_FAIL: 99,
  NET_SDK_NORESOURCE: 100,
  NET_SDK_DEVICE_QUERYSYSTEMCAPS_FAIL: 101,
  NET_SDK_INBUFFER_TOSMALL: 102,
  NET_SDK_NO_PASSWORD_STRENGTH: 103,
  NET_SDK_FILE_NOT_MATCH_PRODUCT: 104
} as const
// spell-checker: enable

export const NET_SDK_ERROR_NAME: ReadonlyMap<number, string> = new Map(
  Object.entries(NET_SDK_ERROR).map(([name, code]) => [code, name])
)

export type DeviceInfo = {
  localVideoInputNum: number
  audioInputNum: number
  sensorInputNum: number
  sensorOutputNum: number
  displayResolutionMask: number
  // spell-checker: disable-next-line
  videoOuputNum: number
  netVideoOutputNum: number
  netVideoInputNum: number
  IVSNum: number
  presetNumOneCH: number
  cruiseNumOneCH: number
  presetNumOneCruise: number
  trackNumOneCH: number
  userNum: number
  netClientNum: number
  netFirstStreamNum: number
  deviceType: number
  // spell-checker: disable-next-line
  doblueStream: number
  audioStream: number
  talkAudio: number
  bPasswordCheck: number
  defBrightness: number
  defContrast: number
  defSaturation: number
  defHue: number
  videoInputNum: number
  deviceID: number
  videoFormat: number
  function: Uint32Array
  deviceIP: number
  deviceMAC: Uint8Array
  devicePort: number
  buildDate: number
  buildTime: number
  deviceName: string
  firmwareVersion: string
  kernelVersion: string
  hardwareVersion: string
  MCUVersion: string
  firmwareVersionEx: string
  softwareVer: number
  szSN: string
  deviceProduct: string
}
