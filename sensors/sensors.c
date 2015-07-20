#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sensors/error.h>
#include <sensors/sensors.h>

#include "lua.h"
#include "lauxlib.h"

#define LUA_LIB



static int l_readAll(lua_State *L) {

	sensors_init(NULL);

	const sensors_chip_name *scn;
	const sensors_feature *sf;
	const sensors_subfeature *ss;
	int n, n1, n2, err;
	double r;
	char scns[80];

	lua_newtable(L);
	//Push new table on to stack. Index -1

	for(n = 0; (scn = sensors_get_detected_chips(NULL, &n)) != NULL; ) {
		// Iterate over detected chips

		for(n1 = 0; (sf = sensors_get_features(scn, &n1)) != NULL; )
			// Iterate over features of chip

			for(n2 = 0; (ss = sensors_get_all_subfeatures(scn, sf, &n2)) != NULL; ) {
				// Iterate over subfeatures of features from chip

				sprintf(scns, "%s-%x-%x__%s", scn->prefix, scn->bus.nr, scn->addr, ss->name);
				// Set scns to (chip.prefix - chip.bus.nr - chip.addr __ subfeature.name )

				err = sensors_get_value(scn, ss->number, &r);
				// Get value from chip using subfeature.number, store result in r. If err != 0 then an error occured.

				if (err == 0) {
					// Sensor data. Addres in char* scns, name in ss->name, result in r
					lua_pushnumber(L, r);																								//Push table value on stack. Table is now at -2
					lua_setfield(L, -2, scns);																					//Set 3rd argument as key in table at stack index -2 to stack index -1
				}	else {
					return(luaL_error(L, "Can't read sensors!"));
				}
			}
	}

	sensors_cleanup();
	return(1);
}

LUALIB_API int luaopen_sensors (lua_State *L) {

	static const struct luaL_reg lib_funcs [] = {
      {"readAll", l_readAll},
      {NULL, NULL}
    };

	luaL_openlib(L, "sensors", lib_funcs, 0);

	return(1);
}
