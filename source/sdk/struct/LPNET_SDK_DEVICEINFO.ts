import koffi from 'koffi'

export const LPNET_SDK_DEVICEINFO = koffi.struct('LPNET_SDK_DEVICEINFO', {
  localVideoInputNum: 'uchar',
  audioInputNum: 'uchar',
  sensorInputNum: 'uchar',
  sensorOutputNum: 'uchar',
  displayResolutionMask: 'uint',

  // preserve typo to match original code
  // spell-checker: disable-next-line
  videoOuputNum: 'uchar',
  netVideoOutputNum: 'uchar',
  netVideoInputNum: 'uchar',
  IVSNum: 'uchar',

  presetNumOneCH: 'uchar',
  cruiseNumOneCH: 'uchar',
  presetNumOneCruise: 'uchar',
  trackNumOneCH: 'uchar',

  userNum: 'uchar',
  netClientNum: 'uchar',
  netFirstStreamNum: 'uchar',
  deviceType: 'uchar',

  // preserve typo to match original code
  // spell-checker: disable-next-line
  doblueStream: 'uchar',
  audioStream: 'uchar',
  talkAudio: 'uchar',
  bPasswordCheck: 'uchar',

  defBrightness: 'uchar',
  defContrast: 'uchar',
  defSaturation: 'uchar',
  defHue: 'uchar',

  videoInputNum: 'ushort',
  deviceID: 'ushort',
  videoFormat: 'uint',

  function: koffi.array('uint', 8),

  deviceIP: 'uint',
  deviceMAC: koffi.array('uchar', 6),
  devicePort: 'ushort',

  buildDate: 'uint',
  buildTime: 'uint',

  deviceName: koffi.array('char', 36),

  firmwareVersion: koffi.array('char', 36),
  kernelVersion: koffi.array('char', 64),
  hardwareVersion: koffi.array('char', 36),
  MCUVersion: koffi.array('char', 36),
  firmwareVersionEx: koffi.array('char', 64),
  softwareVer: 'uint',
  szSN: koffi.array('char', 32),
  deviceProduct: koffi.array('char', 28)
})
