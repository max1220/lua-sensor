lua-sensor
==========

Description
-----------
Simple libsensors4 binding for Lua



Dependencies
------------
To build this Module you need:
 * Lua 5.1 + headers
 * libsensors4 + headers

Install in Debian/Ubuntu:

    sudo apt-get install libsensors4* lua5.1 liblua5.1-0-dev



Build
-----
The build process is straight-forward:

    sensors/make.sh

The build module is in sensors/sensors.so.

To see where Lua searches for it's packages:

    lua -e "print(package.path)"



Test
----
Run sensors/test.lua. If you see something comparable to the output of the "sensors" -commmand on your system, & no error is displayed, your module works.

Please keep in mind that the test script searches for a module named sensors, and if your default searchpath already contains such a module, it chooses that over the freshly build one.



Usage
-----
The module exports a single function, called readAll
Example:

    #!/usr/bin/lua
    local sens = require("sensors")
    for k,v in pairs(sens.readAll()) do
      print(string.format("Sensor name: %s\n\tValue:%s\n", k, v))
    end

(From sensors/test.lua)
