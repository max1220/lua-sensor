#!/usr/bin/lua5.1
local sensors = require("sensors")
sensors.init()
while true do
	io.write("\027[0m\027[2J\027[1;1H") -- clear screen, reset cursor
	for k,v in pairs(sensors.readAll(true)) do
		print(("%40s - %12s"):format(k,v))
	end
	io.popen("sleep 1"):read("*a")
end
sensors.cleanup()
