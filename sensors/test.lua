#!/usr/bin/lua5.1
local sensors = require("sensors")
for k,v in pairs(sensors.readAll()) do
	print(k,v)
end
