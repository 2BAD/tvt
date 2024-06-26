local M = {}

local files = {
  "CMD_INIT",
  "CMD_REQUEST_LOGIN",
  "CMD_REPLY_LOGIN_SUCC",
  "CMD_REPLY_LOGIN_FAIL",
  "CMD_REQUEST_ALARM_OUT_START",
  "CMD_REQUEST_ALARM_OUT_STOP",
  "CMD_HTTP_REQUEST",
  "CMD_HTTP_REPLY"
}

for _, file in ipairs(files) do
  M[file] = require(file)
end

return M
