local function struct(table, fields, buffer, offset)
  local p_httpContentLen = buffer(offset, 4):le_uint()
  table:add_le(fields.httpContentLen, buffer(offset, 4)); offset = offset + 4
  table:add_le(fields.httpSeq, buffer(offset, 4)); offset = offset + 4
  table:add_le(fields.httpReverse, buffer(offset, 64)); offset = offset + 64
  table:add_le(fields.httpContent, buffer(offset, p_httpContentLen)); offset = offset + p_httpContentLen
  -- Unless we reverse engineer the firmware, we can't know what the last byte is for, but it's always 0
  -- ...
  -- len = std::string::length(&strReq);
  -- RealDataLen = len + 73
  -- ...
  -- m_pTmpBuffer[RealDataLen - 1] = 0;
  -- if ( (unsigned int)CIPCNetDevice_V3::SendCmd(this, 0x1010D00, m_pTmpBuffer, RealDataLen) )
  table:add_le(fields.httpEndByte, buffer(offset, 1)); offset = offset + 1
  return offset
end

return struct
