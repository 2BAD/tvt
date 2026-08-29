/* eslint-disable import-x/no-named-as-default-member */
import koffi from 'koffi'

export const NET_SDK_CLIENTINFO = koffi.struct('NET_SDK_CLIENTINFO', {
  lChannel: 'long',
  streamType: 'long',
  hPlayWnd: 'void *',
  bNoDecode: 'int'
})
