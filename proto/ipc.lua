local vs = require("proto.valuestrings")
local fields = require("proto.fields")
local struct = require("proto.struct.init")

-- Declare the protocol
local protocol = Proto("IPC", "TVT IPC Protocol")

-- Define the fields
protocol.fields = fields

-- Define the dissector function
function protocol.dissector(buffer, pinfo, tree)
  -- Set protocol name
  pinfo.cols.protocol = protocol.name

  -- Create t_ipc subtree
  local t_ipc = tree:add(protocol, buffer(), "IPC")
  local offset = 0

  -- Create t_header subtree
  local t_header = t_ipc:add(protocol, buffer(offset), "Header")
  local p_head = buffer(offset, 4):string()

  -- If head is "1111" and there is no data then it's a keepalive packet
  if p_head == "1111" and buffer:len() == offset + 8 then
    pinfo.cols.info = "keepalive"
  end

  -- If head is not "1111" nor "head" then it's a part of  chunked packet and should be skipped
  if p_head ~= "1111" and p_head ~= "head" then
    pinfo.cols.info = "^^^ CHUNK ^^^"
  -- otherwise continue parsing
  else
    -- Add fields to the t_header
    t_header:add(fields.head, buffer(offset, 4)); offset = offset + 4
    t_header:add_le(fields.cmd_length, buffer(offset, 4)); offset = offset + 4

    -- continue parsing if there is more data
    if buffer:len() > offset then

      -- Create t_command subtree
      local t_command = t_ipc:add(protocol, buffer(offset), "Command")

      local p_cmdType = buffer(offset, 4):le_uint()
      t_command:add_le(fields.cmd, buffer(offset, 4))
      t_command:add_le(fields.cmdType, buffer(offset, 4))
      t_command:add_le(fields.direction, buffer(offset, 4)); offset = offset + 4

      if vs.ipc_cmd[p_cmdType] and pinfo.cols.info ~= "keepalive" then
        pinfo.cols.info = vs.ipc_cmd[p_cmdType]
      else
        pinfo.cols.info = string.format("0x%X", p_cmdType)
      end

      t_command:add_le(fields.cmdId, buffer(offset, 4)); offset = offset + 4
      t_command:add_le(fields.cmdVer, buffer(offset, 4)); offset = offset + 4
      t_command:add_le(fields.data_length, buffer(offset, 4)); offset = offset + 4

      if buffer:len() > offset then
        -- Create t_data subtree
        local t_data = t_command:add(protocol, buffer(offset), "Data")

        local process = struct[vs.ipc_cmd[p_cmdType]]
        if process then
            offset = process(t_data, fields, buffer, offset)
        end

        -- handle the rest of the data if any
        if buffer:len() > offset then
          local t_unknown = t_command:add(protocol, buffer(offset), "Unknown")
          t_unknown:add_le(fields.unkb, buffer(offset))
        end
      end
    end
  end
end

-- Register the protocol
DissectorTable.get("tcp.port"):add(9008, protocol)
