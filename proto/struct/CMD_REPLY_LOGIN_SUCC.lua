local function struct(table, fields, buffer, offset)
  table:add_le(fields.ConfigDataLen, buffer(offset, 4)); offset = offset + 4
  table:add_le(fields.PTZPresetNum, buffer(offset, 4)); offset = offset + 4
  table:add_le(fields.PTZCruiseNum, buffer(offset, 4)); offset = offset + 4
  table:add_le(fields.PTZPresetNumForCruise, buffer(offset, 4)); offset = offset + 4
  table:add_le(fields.PresetNameMaxLen, buffer(offset, 4)); offset = offset + 4
  table:add_le(fields.CruiseNameMaxLen, buffer(offset, 4)); offset = offset + 4
  table:add_le(fields.bSupportPTZ, buffer(offset, 1)); offset = offset + 1
  table:add_le(fields.videoFormat, buffer(offset, 1)); offset = offset + 1
  table:add_le(fields.sensorInNum, buffer(offset, 1)); offset = offset + 1
  table:add_le(fields.alarmOutNum, buffer(offset, 1)); offset = offset + 1
  table:add_le(fields.ucStreamCount, buffer(offset, 1)); offset = offset + 1
  table:add_le(fields.bSupportSnap, buffer(offset, 1)); offset = offset + 1
  table:add_le(fields.noused, buffer(offset, 1)); offset = offset + 1
  table:add_le(fields.ucLiveAudioStream, buffer(offset, 1)); offset = offset + 1
  table:add_le(fields.ucTalkAudioStream, buffer(offset, 1)); offset = offset + 1
  table:add_le(fields.audioEncodeType, buffer(offset, 1)); offset = offset + 1
  table:add_le(fields.audioBitWidth, buffer(offset, 1)); offset = offset + 1
  table:add_le(fields.audioChannel, buffer(offset, 1)); offset = offset + 1
  table:add_le(fields.dwAudioSample, buffer(offset, 4)); offset = offset + 4
  table:add_le(fields.UserRight, buffer(offset, 4)); offset = offset + 4
  table:add(fields.softwareVer, buffer(offset, 4)); offset = offset + 4
  table:add_le(fields.buildDate, buffer(offset, 4)); offset = offset + 4
  table:add_le(fields.MAC, buffer(offset, 6)); offset = offset + 6
  table:add_le(fields.deviceName, buffer(offset, 34)); offset = offset + 34
  table:add_le(fields.nCustomerID, buffer(offset, 4)); offset = offset + 4
  table:add_le(fields.defBrightness, buffer(offset, 1)); offset = offset + 1
  table:add_le(fields.defContrast, buffer(offset, 1)); offset = offset + 1
  table:add_le(fields.defHue, buffer(offset, 1)); offset = offset + 1
  table:add_le(fields.defSaturation, buffer(offset, 1)); offset = offset + 1
  table:add_le(fields.nosupportPTZ, buffer(offset, 1)); offset = offset + 1
  table:add_le(fields.bspeedDomePTZ, buffer(offset, 1)); offset = offset + 1
  table:add_le(fields.framerate, buffer(offset, 1)); offset = offset + 1
  table:add_le(fields.bSupportSetSubStream, buffer(offset, 1)); offset = offset + 1
  table:add_le(fields._bf_68, buffer(offset, 4)); offset = offset + 4
  table:add_le(fields.supportPassThroughApi, buffer(offset, 1)); offset = offset + 1
  table:add_le(fields.bSupportMultiChannel, buffer(offset, 1)); offset = offset + 1
  table:add_le(fields.noused2, buffer(offset, 2)); offset = offset + 2
  table:add_le(fields.apiVersion, buffer(offset, 4)); offset = offset + 4
  table:add_le(fields.binaryVersion, buffer(offset, 4)); offset = offset + 4
  table:add_le(fields._bf_78, buffer(offset, 4)); offset = offset + 4
  table:add_le(fields.noused1, buffer(offset, 74)); offset = offset + 74
  table:add_le(fields.unk8, buffer(offset, 1)); offset = offset + 1
  table:add_le(fields.unk8, buffer(offset, 1)); offset = offset + 1
  return offset
end

return struct
