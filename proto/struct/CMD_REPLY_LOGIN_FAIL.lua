local function struct(table, fields, buffer, offset)
  table:add_le(fields.error, buffer(offset, 4)); offset = offset + 4
  return offset
end

return struct
