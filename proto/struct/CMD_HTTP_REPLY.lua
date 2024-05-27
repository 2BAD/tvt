local function struct(table, fields, buffer, offset)
  local p_httpDataLen = buffer(offset, 4):le_uint()
  table:add_le(fields.httpDataLen, buffer(offset, 4)); offset = offset + 4
  table:add_le(fields.httpSeq, buffer(offset, 4)); offset = offset + 4
  table:add_le(fields.httpReverse, buffer(offset, 64)); offset = offset + 64
  table:add_le(fields.httpContent, buffer(offset, buffer:len() - offset)); offset = offset + (buffer:len() - offset)
  return offset
end

return struct
