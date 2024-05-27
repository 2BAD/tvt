local function struct(table, fields, buffer, offset)
  table:add_le(fields.flag, buffer(offset, 4)); offset = offset + 4
  table:add_le(fields.devType, buffer(offset, 4)); offset = offset + 4
  table:add_le(fields.initProductType, buffer(offset, 4)); offset = offset + 4
  table:add_le(fields.protocolVer, buffer(offset, 4)); offset = offset + 4
  table:add_le(fields.configVer, buffer(offset, 4)); offset = offset + 4
  table:add_le(fields.id, buffer(offset, 4)); offset = offset + 4
  table:add_le(fields.encryptType, buffer(offset, 4)); offset = offset + 4
  table:add_le(fields.encryptParam, buffer(offset, 4)); offset = offset + 4
  table:add_le(fields.mac, buffer(offset, 8)); offset = offset + 8
  table:add_le(fields.initSoftwareVer, buffer(offset, 4)); offset = offset + 4
  table:add_le(fields.loginEncrypt, buffer(offset, 1)); offset = offset + 1
  table:add_le(fields.loginNonce, buffer(offset, 3)); offset = offset + 3
  table:add_le(fields.supportSoftEncrypt, buffer(offset, 4)); offset = offset + 4
  table:add_le(fields.transportEncryptType, buffer(offset, 1)); offset = offset + 1
  table:add_le(fields.reservedBytes, buffer(offset, 3)); offset = offset + 3
  table:add_le(fields.reservedBytes, buffer(offset, 8)); offset = offset + 8
  return offset
end

return struct
