#!/usr/bin/lua
local sens = require("sensors")
for k,v in pairs(sens.readAll()) do
	print(string.format("Sensor name: %s\n\tValue:%s\n", k, v))
end
