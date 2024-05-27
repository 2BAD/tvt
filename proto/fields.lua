local vs = require("proto.valuestrings")

local fields = {
    -- header and command fields
    head = ProtoField.string("ipc.head", "Head"),
    cmd_length = ProtoField.uint32("ipc.len", "Command Length"),
    cmd = ProtoField.uint32("ipc.cmd", "Command", base.HEX),
    cmdType = ProtoField.uint32("ipc.cmdType", "Type", base.HEX, vs.ipc_cmd, 0x0FFFFFFF),
    direction = ProtoField.uint8("ipc.direction", "Direction", base.DEC, vs.direction, 0x0F000000),
    cmdId = ProtoField.uint8("ipc.cmdId", "Command ID", base.DEC),
    cmdVer = ProtoField.uint8("ipc.cmdVer", "Command Version", base.DEC),
    data_length = ProtoField.uint32("ipc.len", "Data Length"),

    -- generic fields
    error = ProtoField.uint32("ipc.error", "Error", base.HEX, vs.net_error),
  -- init fields
  flag = ProtoField.string("ipc.init.flag", "Flag"),
  devType = ProtoField.uint32("ipc.init.devType", "Device Type", base.DEC),
  initProductType = ProtoField.uint32("ipc.init.productType", "Product Type", base.DEC),
  configVer = ProtoField.uint32("ipc.init.ConfigVer", "Config Version", base.DEC),
  id = ProtoField.uint32("ipc.init.ID", "ID", base.DEC),
  encryptType = ProtoField.uint32("ipc.init.EncryptType", "Encrypt Type", base.DEC),
  encryptParam = ProtoField.bytes("ipc.init.EncryptParam", "Encrypt Param", base.SPACE),
  initSoftwareVer = ProtoField.uint32("ipc.init.SoftwareVer", "Software Version", base.DEC),
  loginEncrypt = ProtoField.uint8("ipc.init.loginEncrypt", "Login Encryption", base.DEC),
  loginNonce = ProtoField.bytes("ipc.init.loginNonce", "Login Nonce", base.SPACE),
  supportSoftEncrypt = ProtoField.uint32("ipc.init.supportSoftEncrypt", "Support Soft Encryption", base.DEC),
  transportEncryptType = ProtoField.uint8("ipc.init.transportEncryptType", "Transport Encryption Type", base.DEC),

    -- login fields
    connectType = ProtoField.uint32("ipc.login.connectType", "Connect Type"),
    username = ProtoField.bytes("ipc.login.username", "Username", base.SPACE),
    password = ProtoField.bytes("ipc.login.password", "Password", base.SPACE),
    computerName = ProtoField.string("ipc.login.computerName", "Computer Name"),
    ip = ProtoField.string("ipc.login.ip", "IP"),
    mac = ProtoField.string("ipc.login.mac", "MAC"),
    productType = ProtoField.uint8("ipc.login.productType", "Product Type"),
    resv = ProtoField.uint8("ipc.login.resv", "Resv"),
    netProtocolVer = ProtoField.uint32("ipc.login.netProtocolVer", "Net Protocol Version"),

    -- config fields
    ConfigDataLen = ProtoField.uint32("ipc.config.ConfigDataLen", "ConfigDataLen", base.DEC),
    PTZPresetNum = ProtoField.uint32("ipc.config.PTZPresetNum", "PTZPresetNum", base.DEC),
    PTZCruiseNum = ProtoField.uint32("ipc.config.PTZCruiseNum", "PTZCruiseNum", base.DEC),
    PTZPresetNumForCruise = ProtoField.uint32("ipc.config.PTZPresetNumForCruise", "PTZPresetNumForCruise", base.DEC),
    PresetNameMaxLen = ProtoField.uint32("ipc.config.PresetNameMaxLen", "PresetNameMaxLen", base.DEC),
    CruiseNameMaxLen = ProtoField.uint32("ipc.config.CruiseNameMaxLen", "CruiseNameMaxLen", base.DEC),
    bSupportPTZ = ProtoField.uint8("ipc.config.bSupportPTZ", "bSupportPTZ", base.DEC),
    videoFormat = ProtoField.uint8("ipc.config.videoFormat", "videoFormat", base.DEC),
    sensorInNum = ProtoField.uint8("ipc.config.sensorInNum", "sensorInNum", base.DEC),
    alarmOutNum = ProtoField.uint8("ipc.config.alarmOutNum", "alarmOutNum", base.DEC),
    ucStreamCount = ProtoField.uint8("ipc.config.ucStreamCount", "ucStreamCount", base.DEC),
    bSupportSnap = ProtoField.uint8("ipc.config.bSupportSnap", "bSupportSnap", base.DEC),
    noused = ProtoField.uint8("ipc.config.noused", "noused", base.DEC),
    ucLiveAudioStream = ProtoField.uint8("ipc.config.ucLiveAudioStream", "ucLiveAudioStream", base.DEC),
    ucTalkAudioStream = ProtoField.uint8("ipc.config.ucTalkAudioStream", "ucTalkAudioStream", base.DEC),
    audioEncodeType = ProtoField.uint8("ipc.config.audioEncodeType", "audioEncodeType", base.DEC),
    audioBitWidth = ProtoField.uint8("ipc.config.audioBitWidth", "audioBitWidth", base.DEC),
    audioChannel = ProtoField.uint8("ipc.config.audioChannel", "audioChannel", base.DEC),
    dwAudioSample = ProtoField.uint32("ipc.config.dwAudioSample", "dwAudioSample", base.DEC),
    UserRight = ProtoField.uint32("ipc.config.UserRight", "UserRight", base.DEC),
    softwareVer = ProtoField.bytes("ipc.config.softwareVer", "softwareVer", base.DOT),
    buildDate = ProtoField.uint32("ipc.config.buildDate", "buildDate", base.DEC),
    MAC = ProtoField.bytes("ipc.config.MAC", "MAC", base.COLON),
    deviceName = ProtoField.string("ipc.config.deviceName", "deviceName"),
    nCustomerID = ProtoField.uint32("ipc.config.nCustomerID", "nCustomerID", base.DEC),
    defBrightness = ProtoField.uint8("ipc.config.defBrightness", "defBrightness", base.DEC),
    defContrast = ProtoField.uint8("ipc.config.defContrast", "defContrast", base.DEC),
    defHue = ProtoField.uint8("ipc.config.defHue", "defHue", base.DEC),
    defSaturation = ProtoField.uint8("ipc.config.defSaturation", "defSaturation", base.DEC),
    nosupportPTZ = ProtoField.uint8("ipc.config.nosupportPTZ", "nosupportPTZ", base.DEC),
    bspeedDomePTZ = ProtoField.uint8("ipc.config.bspeedDomePTZ", "bspeedDomePTZ", base.DEC),
    framerate = ProtoField.uint8("ipc.config.framerate", "framerate", base.DEC),
    bSupportSetSubStream = ProtoField.uint8("ipc.config.bSupportSetSubStream", "bSupportSetSubStream", base.DEC),
    _bf_68 = ProtoField.uint32("ipc.config._bf_68", "_bf_68", base.DEC),
    supportPassThroughApi = ProtoField.uint8("ipc.config.supportPassThroughApi", "supportPassThroughApi", base.DEC),
    bSupportMultiChannel = ProtoField.uint8("ipc.config.bSupportMultiChannel", "bSupportMultiChannel", base.DEC),
    noused2 = ProtoField.bytes("ipc.config.noused2", "noused2"),
    apiVersion = ProtoField.uint32("ipc.config.apiVersion", "apiVersion", base.DEC),
    binaryVersion = ProtoField.uint32("ipc.config.binaryVersion", "binaryVersion", base.DEC),
    _bf_78 = ProtoField.uint32("ipc.config._bf_78", "_bf_78", base.DEC),
    noused1 = ProtoField.bytes("ipc.config.noused1", "noused1"),

    -- alarm fields
    channelId = ProtoField.uint32("ipc.alarm.channelId", "ChannelId"),

    -- http fields
    httpDataLen = ProtoField.uint32("ipc.http.dataLen", "HTTP Data Length"),
    httpSeq = ProtoField.uint32("ipc.http.seq", "Sequence"),
    httpReverse = ProtoField.bytes("ipc.http.reverse", "Reverse"),
    httpContent = ProtoField.string("ipc.http.content", "Content"),
    httpEndByte = ProtoField.uint8("ipc.http.endByte", "End Byte"),

    unk8 = ProtoField.uint8("ipc.unk8", "Unknown"),
    unk32 = ProtoField.uint32("ipc.unk32", "Unknown"),
    unkb = ProtoField.bytes("ipc.unkb", "Unknown", base.SPACE)
}

return fields
