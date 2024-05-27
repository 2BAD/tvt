local vs = require("proto.valuestrings")
local fields = require("proto.fields")
local struct = require("proto.struct.init")

-- Declare the protocol
local protocol = Proto("IPC", "TVT IPC Protocol")

-- Define the fields
protocol.fields = fields

-- Define the dissector function
function protocol.dissector(buffer, pinfo, root)
  -- Set protocol name
  pinfo.cols.protocol = protocol.name
  local offset = 0
  local p_head = buffer(offset, 4):string()

  -- If head is "1111" and there is no data then it's a keepalive packet
  if p_head == "1111" and buffer:len() == offset + 8 then
    pinfo.cols.info = "keepalive"
  end

  -- Init packet is a special case and should be handled differently
  if p_head == 'head' then
    pinfo.cols.info = "CMD_INIT"

    -- Create top level t_ipc subtree
    local t_ipc = root:add(protocol, buffer(), "IPC")

    local process = struct["CMD_INIT"]
    offset = process(t_ipc, fields, buffer, offset)

    -- If head is not "1111" nor "head" then it's a part of a chunked packet and should be skipped
  elseif p_head ~= "1111" and p_head ~= "head" then
    -- TODO: try to combine chunks in a global function
    -- see https://ask.wireshark.org/question/11650/lua-wireshark-dissector-combine-data-from-2-udp-packets/
    pinfo.cols.info = "^^^ CHUNK ^^^"
    -- otherwise continue parsing
  else
    -- Create top level t_ipc subtree
    local t_ipc = root:add(protocol, buffer(), "IPC")
    -- Create t_header subtree
    local t_header = t_ipc:add(protocol, buffer(offset), "Header")

    -- Add fields to the t_header
    t_header:add(fields.flag, buffer(offset, 4)); offset = offset + 4
    t_header:add_le(fields.cmdLen, buffer(offset, 4)); offset = offset + 4

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
      t_command:add_le(fields.dataLen, buffer(offset, 4)); offset = offset + 4

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
          t_unknown:add_le(fields.unknownBytes, buffer(offset))
        end
      end
    end
  end
end

-- Register the protocol
DissectorTable.get("tcp.port"):add(9008, protocol)
