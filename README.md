lua-sensor
==========


Description
-----------

Simple libsensors binding for Lua




Dependencies
------------

To build this Module you need:
 * Lua 5.1 + headers
 * libsensors4 + headers

Install in Debian/Ubuntu:

    sudo apt-get install libsensors4* lua5.1 liblua5.1-0-dev




Build
-----

The build process is straight-forward, just run:

    sensors/make.sh

The build module is in sensors/sensors.so.
It compiles using a single GCC command:

	gcc -Wall -Wextra -Wpedantic -fPIC -shared -I/usr/include/sensors/ -I/usr/include/lua5.1 -o sensors.so sensors.c -llua5.1 -lsensors




Test
----

Run sensors/test.lua. If you see something comparable to the output of the "sensors" -commmand on your system, & no error is displayed, the compiled module works.

Please keep in mind that the test script searches for a module named sensors, and if your default Lua searchpath already contains such a module, it chooses that over the freshly build one.




Usage
-----

The module exports 3 functions. readAll, init and cleanup.
Example:

	#!/usr/bin/lua5.1
	local sensors = require("sensors")
	for k,v in pairs(sensors.readAll()) do
		print(k,v)
	end

(From `sensors/test.lua`)

The `sens.readAll()` returns a table that has the sensor name as table key, and it's
sensor value as table value. The `sensors.readAll()` has one optional argument,
if truethy the sensor_init and sensor_cleanup functions are not automatically
called. This is useful for longer-running programs. If you specify this argument,
make sure to call the `sensors.init()` and `sensors.cleanup()` functions accordingly.

See `sensors/monitor.lua` as an example.




Installation
------------

Please note that in order to make Lua find the module, you need to copy it to Lua's default search path,
To list the paths Lua looks for Modules, you can use:

    lua -e "print((package.path:gsub(';', '\n')))"

Where `?` is the module's filename.
