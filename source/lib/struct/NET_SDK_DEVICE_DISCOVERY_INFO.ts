/* eslint-disable import-x/no-named-as-default-member */
import koffi from 'koffi'

export const NET_SDK_DEVICE_DISCOVERY_INFO = koffi.struct('NET_SDK_DEVICE_DISCOVERY_INFO', {
  deviceType: 'uint',
  productType: koffi.array('char', 32),
  strIP: koffi.array('char', 16),
  strNetMask: koffi.array('char', 16),
  strGateWay: koffi.array('char', 16),
  byMac: koffi.array('uchar', 8),
  netPort: 'ushort',
  httpPort: 'ushort',
  softVer: 'uint',
  softBuildDate: 'uint',
  ucIPMode: 'uchar',
  dwSecondIP: koffi.array('char', 16),
  dwSecondMask: koffi.array('char', 16),
  deviceActivated: 'char',
  pwdLevel: 'char',
  nocName: koffi.array('char', 16)
})
