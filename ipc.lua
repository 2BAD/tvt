-- Declare the protocol
local ipc_protocol = Proto("IPC", "IPC Protocol")

-- Define lookup table for packet types
local vs_packet_type = {
  [1] = "login",
  [2] = "stop?",
  [9] = "info",
  [21] = "hello",
  [22] = "heartbeat"
}

local vs_direction = {
  [0] = "Request",
  [1] = "Response"
}


-- Define the fields
local fields = {
    header = ProtoField.string("ipc.header", "Header"),
    frame_length = ProtoField.uint32("ipc.frame_length", "Frame Length"),
    type = ProtoField.uint8("ipc.type", "Type", base.DEC, vs_packet_type),
    counter = ProtoField.uint32("ipc.counter", "Counter"),
    session = ProtoField.uint32("ipc.session", "Session"),
    direction = ProtoField.uint8("ipc.direction", "Direction", base.DEC, vs_direction),
    unk8 = ProtoField.uint8("ipc.unk8", "Unk8"),
    unk32 = ProtoField.uint32("ipc.unk32", "Unk32"),
    unkb = ProtoField.bytes("ipc.unkb", "UnkBs", base.SPACE),
    manufacturer = ProtoField.string("ipc.manufacturer", "Manufacturer"),
    login = ProtoField.bytes("ipc.login", "Login", base.SPACE),
    password = ProtoField.bytes("ipc.password", "Passw", base.SPACE)
}

ipc_protocol.fields = fields

-- Define the dissector function
function ipc_protocol.dissector(buffer, pinfo, tree)
    -- Set protocol name
    pinfo.cols.protocol = ipc_protocol.name

    -- Create t_ipc subtree
    local t_ipc = tree:add(ipc_protocol, buffer(), "IPC Data")
    local offset = 0

    -- Add fields to the t_ipc
    t_ipc:add(fields.header, buffer(offset, 4))
    offset = offset + 4

    t_ipc:add_le(fields.frame_length, buffer(offset, 4))
    offset = offset + 4

    if buffer:len() > offset then

      local t_header = t_ipc:add(ipc_protocol, buffer(offset), "Header")
      t_header:add(fields.type, buffer(offset, 1))
      local p_type = buffer(offset, 1):uint()
      offset = offset + 1

      pinfo.cols.info = vs_packet_type[p_type]

      t_header:add(fields.unk8, buffer(offset, 1))
      offset = offset + 1
      t_header:add(fields.unk8, buffer(offset, 1))
      offset = offset + 1

      t_header:add(fields.direction, buffer(offset, 1))
      local p_direction = buffer(offset, 1):uint()
      offset = offset + 1

      pinfo.cols.info = vs_direction[p_direction] .. "(" .. vs_packet_type[p_type] .. ")"

      t_header:add_le(fields.counter, buffer(offset, 4))
      offset = offset + 4

      if p_type == 21 then
        t_header:add(fields.unk8, buffer(offset, 1))
        offset = offset + 1
        t_header:add(fields.unk8, buffer(offset, 1))
        offset = offset + 1
        t_header:add(fields.unk8, buffer(offset, 1))
        offset = offset + 1
        t_header:add(fields.unk8, buffer(offset, 1))
        offset = offset + 1
        t_header:add_le(fields.unk32, buffer(offset, 4))
        offset = offset + 4
        t_header:add_le(fields.unk32, buffer(offset, 4))
        offset = offset + 4
        t_header:add_le(fields.session, buffer(offset, 4))
        offset = offset + 4
        t_header:add_le(fields.unk32, buffer(offset, 4))
        offset = offset + 4
        t_header:add_le(fields.unk32, buffer(offset, 4))
        offset = offset + 4
        t_header:add_le(fields.unk32, buffer(offset, 4))
        offset = offset + 4
        t_header:add_le(fields.unk32, buffer(offset, 4))
        offset = offset + 4
        t_header:add_le(fields.unk32, buffer(offset, 4))
        offset = offset + 4
        t_header:add_le(fields.unk32, buffer(offset, 4))
        offset = offset + 4
        t_header:add_le(fields.unk32, buffer(offset, 4))
        offset = offset + 4
        t_header:add_le(fields.unk32, buffer(offset, 4))
        offset = offset + 4
      else
        t_header:add_le(fields.unk32, buffer(offset, 4))
        offset = offset + 4
        t_header:add_le(fields.frame_length, buffer(offset, 4))
        offset = offset + 4
        local t_frame = t_header:add(ipc_protocol, buffer(offset), "Frame")

        if buffer:len() > offset then
          if p_type == 1 and p_direction == 0 then
            t_frame:add_le(fields.unk32, buffer(offset, 4))
            offset = offset + 4
            t_frame:add_le(fields.login, buffer(offset, 32))
            offset = offset + 32
            t_frame:add_le(fields.password, buffer(offset, 32))
            offset = offset + 32
            t_frame:add_le(fields.unkb, buffer(offset, 32))
            offset = offset + 32
            t_frame:add_le(fields.unk32, buffer(offset, 4))
            offset = offset + 4
            t_frame:add_le(fields.unk32, buffer(offset, 4))
            offset = offset + 4
            t_frame:add_le(fields.unk32, buffer(offset, 4))
            offset = offset + 4
          elseif p_type == 1 and p_direction == 1 then
            offset = offset + 58
            t_ipc:add(fields.manufacturer, buffer(offset, 4))
            offset = offset + 4
          end
        end
      end
    end
end

-- Register the protocol
DissectorTable.get("tcp.port"):add(9008, ipc_protocol)
