local function struct(table, fields, buffer, offset)
  table:add_le(fields.connectType, buffer(offset, 4)); offset = offset + 4
  table:add(fields.username, buffer(offset, 32)); offset = offset + 32
  table:add(fields.password, buffer(offset, 32)); offset = offset + 32
  table:add(fields.computerName, buffer(offset, 28)); offset = offset + 28
  table:add(fields.ip, buffer(offset, 8)); offset = offset + 8
  table:add(fields.mac, buffer(offset, 6)); offset = offset + 6
  table:add(fields.productType, buffer(offset, 1)); offset = offset + 1
  table:add(fields.resv, buffer(offset, 1)); offset = offset + 1
  table:add_le(fields.netProtocolVer, buffer(offset, 4)); offset = offset + 4
  return offset
end

return struct
