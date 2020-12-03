#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sensors/error.h>
#include <sensors/sensors.h>

#include "lua.h"
#include "lauxlib.h"



static int lua_sensor_init(lua_State *L) {
	if (sensors_init(NULL)) {
		lua_pushnil(L);
		lua_pushstring(L, "Can't initialize sensors!");
		return 2;
	}
	lua_pushboolean(L, 1);
	return 1;
}

static int lua_sensor_cleanup(lua_State *L) {
	sensors_cleanup();
	lua_pushboolean(L, 1);
	return 1;
}

static int lua_sensor_readAll(lua_State *L) {
	int skip_init_cleanup = 0;
	if (lua_toboolean(L, 1)) {
		skip_init_cleanup = 1;
	} else if (sensors_init(NULL)) {
		lua_pushnil(L);
		lua_pushstring(L, "Can't initialize sensors!");
		return 2;
	}


	const sensors_chip_name *scn;
	const sensors_feature *sf;
	const sensors_subfeature *ss;
	int n, n1, n2, err;
	double r;
	char scns[80];

	//Push new table on to stack. Index -1
	lua_newtable(L);

	// Iterate over detected chips
	for(n = 0; (scn = sensors_get_detected_chips(NULL, &n)) != NULL; ) {
		// Iterate over features of chip
		for(n1 = 0; (sf = sensors_get_features(scn, &n1)) != NULL; )
			// Iterate over subfeatures of features from chip
			for(n2 = 0; (ss = sensors_get_all_subfeatures(scn, sf, &n2)) != NULL; ) {
				// Set scns to (chip.prefix - chip.bus.nr - chip.addr __ subfeature.name )
				char* label = sensors_get_label(scn, sf); // get the lable
				sprintf(scns, "%s-%x-%x__%s(%s)", scn->prefix, scn->bus.nr, scn->addr, ss->name, label);
				free(label);

				// Get value from chip using subfeature.number, store result in r. If err != 0 then an error occured.
				err = sensors_get_value(scn, ss->number, &r);

				if (err == 0) {
					// No error, got Sensor data. Addres in char* scns, name in ss->name, result in r
					lua_pushnumber(L, r); // Push table value on stack. Table is now at -2
					lua_setfield(L, -2, scns); // Set 3rd argument as key in table at stack index -2 to stack index -1
				}	else {
					return luaL_error(L, "Can't read sensors!");
				}
			}
	}

	if (skip_init_cleanup==0) {
		sensors_cleanup();
	}

	return 1;
}


LUALIB_API int luaopen_sensors (lua_State *L) {
	static const struct luaL_reg lib_funcs [] = {
		{"readAll", lua_sensor_readAll},
		{"init", lua_sensor_init},
		{"cleanup", lua_sensor_cleanup},
		{NULL, NULL}
	};

	luaL_openlib(L, "sensors", lib_funcs, 0);

	return 1;
}
