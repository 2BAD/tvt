import koffi from 'koffi'

export const NET_SDK_IPC_DEVICE_INFO = koffi.struct('NET_SDK_IPC_DEVICE_INFO', {
  deviceID: 'uint',
  channel: 'ushort',
  guid: koffi.array('uchar', 48),
  status: 'ushort',
  szEtherName: koffi.array('char', 16),
  szServer: koffi.array('char', 64),
  nPort: 'ushort',
  nHttpPort: 'ushort',
  nCtrlPort: 'ushort',
  szID: koffi.array('char', 64),
  username: koffi.array('char', 36),
  manufacturerId: 'uint',
  manufacturerName: koffi.array('char', 36),
  productModel: koffi.array('char', 36),
  bUseDefaultCfg: 'uchar',
  bPOEDevice: 'uchar',
  resv: koffi.array('uchar', 2),
  szChlname: koffi.array('char', 36)
})
