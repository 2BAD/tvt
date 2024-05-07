-- Declare the protocol
local protocol = Proto("IPC", "IPC Protocol")

-- Define lookup table for packet types
local vs_packet_type = {
  [1] = "Login",
  [6] = "Session",
  [11] = "Alarm",
  [5] = "5",
  [7] = "7",
  [21] = "21",
  [22] = "22"
}

local vs_cmd_type = {
  [0x0100] = "CMD_BASE_LOGIN",
  [0x0101] = "CMD_REQUEST_LOGIN_DECODER",
  [0x0102] = "CMD_REQUEST_LOGOUT_DECODER",
  [0x0103] = "CMD_END_NUM_LOGIN",

  [0x0300] = "CMD_BASE_ENCODER",
  [0x0301] = "CMD_STREAM_START",
  [0x0302] = "CMD_STREAM_SWITCH",
  [0x0303] = "CMD_STREAM_STOP",
  [0x0304] = "CMD_KEYFRAME",
  [0x0305] = "CMD_END_NUM_ENCODER",

  [0x010000] = "CMD_BASE_NUM_CFG",
  [0x010001] = "CMD_CONFIG_GET",
  [0x010002] = "CMD_CONFIG_SET",

  [0x020000] = "CMD_BASE_NUM_CMS_CONTROL_ENC",
  [0x020001] = "CMD_SWITCH_ENC",
  [0x020002] = "CMD_STOP_DECODE",
  [0x020003] = "CMD_START_DECODE",

  [0x030000] = "CMD_BASE_NUM_CTRL",
  [0x030001] = "CMD_MSG_LOGIN",
  [0x030002] = "CMD_MSG_LOGOUT",
  [0x030003] = "CMD_MSG_REBOOT",
  [0x030004] = "CMD_MSG_SHUTDOWN",
  [0x030005] = "CMD_MSG_EXFACTORY_SETUP",
  [0x030006] = "CMD_CHANGE_TIME",
  [0x030007] = "CMD_Exception_Set",
  [0x030008] = "CMD_GET_VERSION_INFO",
  [0x030009] = "MSG_GET_DEVICE_INFO",
  [0x030010] = "CMD_NET_DEVICE_SEARCH",
  [0x030011] = "CMD_GET_ALL_USERINFO",
  [0x030012] = "CMD_SET_ALL_USERINFO",
  [0x030013] = "CMD_UPDATE_START",
  [0x030014] = "CMD_UPDATE_DATA"
}

local vs_direction = {
  [0] = "Request",
  [1] = "Response"
}

-- Define the fields
local fields = {
    head = ProtoField.string("ipc.head", "Head"),
    data_length = ProtoField.uint32("ipc.len", "Data Length"),
    cmd = ProtoField.uint32("ipc.cmd", "Command", base.HEX),
    cmdType = ProtoField.uint32("ipc.cmdType", "Type", base.HEX, vs_cmd_type, 0x0000FFFF),
    cmdId = ProtoField.uint8("ipc.cmdId", "Command ID", base.DEC),
    cmdVer = ProtoField.uint8("ipc.cmdVer", "Command Version", base.DEC),
    counter = ProtoField.uint32("ipc.counter", "Counter"),
    sdkVersion = ProtoField.uint32("ipc.sdkVersion", "SDK Version"),
    session = ProtoField.uint32("ipc.session", "Session"),
    direction = ProtoField.uint8("ipc.direction", "Direction", base.DEC, vs_direction),
    login = ProtoField.bytes("ipc.login", "Login", base.SPACE),
    password = ProtoField.bytes("ipc.password", "Passw", base.SPACE),
    manufacturer = ProtoField.string("ipc.manufacturer", "Manufacturer"),

    unk8 = ProtoField.uint8("ipc.unk8", "Unk8"),
    unk32 = ProtoField.uint32("ipc.unk32", "Unk32"),
    unkb = ProtoField.bytes("ipc.unkb", "UnkBs", base.SPACE)
}

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

    -- Add fields to the t_header
    t_header:add(fields.head, buffer(offset, 4))
    local p_head = buffer(offset, 4):string()
    offset = offset + 4

    t_header:add_le(fields.data_length, buffer(offset, 4))
    offset = offset + 4

    if p_head == '1111' and buffer:len() == offset then
      pinfo.cols.info = 'keepalive'
    end

    if buffer:len() > offset then

      -- Create t_command subtree
      local t_command = t_ipc:add(protocol, buffer(offset), "Command")

      t_command:add_le(fields.cmd, buffer(offset, 4))
      local p_cmd = buffer(offset, 4):uint()
      t_command:add_le(fields.cmdType, buffer(offset, 4))
      local p_cmdType = buffer(offset, 4):uint()
      offset = offset + 4

      t_command:add_le(fields.cmdId, buffer(offset, 4))
      local p_cmdId = buffer(offset, 4):uint()
      offset = offset + 4

      t_command:add_le(fields.cmdVer, buffer(offset, 4))
      local p_cmdVer = buffer(offset, 4):uint()
      offset = offset + 4

      t_command:add_le(fields.data_length, buffer(offset, 4))
      offset = offset + 4

      -- pinfo.cols.info = vs_direction[p_direction] .. "(" .. vs_cmd[p_cmd] .. " " .. vs_packet_type[p_type] .. ")"

      -- Init Session
      if p_cmd == 21 and p_type == 6 then
        t_command:add(fields.unk8, buffer(offset, 1))
        offset = offset + 1
        t_command:add(fields.unk8, buffer(offset, 1))
        offset = offset + 1
        t_command:add(fields.unk8, buffer(offset, 1))
        offset = offset + 1
        t_command:add(fields.unk8, buffer(offset, 1))
        offset = offset + 1
        t_command:add_le(fields.unk32, buffer(offset, 4))
        offset = offset + 4
        t_command:add_le(fields.unk32, buffer(offset, 4))
        offset = offset + 4
        t_command:add_le(fields.session, buffer(offset, 4))
        offset = offset + 4
        t_command:add_le(fields.unk32, buffer(offset, 4))
        offset = offset + 4
        t_command:add_le(fields.unk32, buffer(offset, 4))
        offset = offset + 4
        t_command:add_le(fields.unk32, buffer(offset, 4))
        offset = offset + 4

        t_command:add(fields.unk8, buffer(offset, 1))
        offset = offset + 1
        t_command:add(fields.unk8, buffer(offset, 1))
        offset = offset + 1
        t_command:add(fields.unk8, buffer(offset, 1))
        offset = offset + 1
        t_command:add(fields.unk8, buffer(offset, 1))
        offset = offset + 1

        t_command:add_le(fields.unk32, buffer(offset, 4))
        offset = offset + 4
        t_command:add_le(fields.unk32, buffer(offset, 4))
        offset = offset + 4
        t_command:add_le(fields.unk32, buffer(offset, 4))
        offset = offset + 4
        t_command:add_le(fields.unk32, buffer(offset, 4))
        offset = offset + 4
      else
        t_command:add_le(fields.unk32, buffer(offset, 4))
        offset = offset + 4
        t_command:add_le(fields.data_length, buffer(offset, 4))
        offset = offset + 4
        local t_frame = t_command:add(protocol, buffer(offset), "Frame")

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
          elseif p_type == 1 and p_direction == 1 and buffer:len() > 40 then
            offset = offset + 58
            t_ipc:add(fields.manufacturer, buffer(offset, 4))
            offset = offset + 4
          end
        end
      end
    end
end

-- Register the protocol
DissectorTable.get("tcp.port"):add(9008, protocol)
