#include <gba_systemcalls.h>

#include "lauxlib.h"

static int bios_checksum(lua_State *l) {
	lua_pushinteger(l, (int) BiosCheckSum());
	return 1;
}

static int bios_div(lua_State *l) {
	lua_pushinteger(l, (int) Div(luaL_checkint(l, 1), luaL_checkint(l, 2)));
	return 1;
}

static int bios_divmod(lua_State *l) {
	lua_pushinteger(l, (int) DivMod(luaL_checkint(l, 1), luaL_checkint(l, 2)));
	return 1;
}

static int bios_divabs(lua_State *l) {
	lua_pushinteger(l, (int) DivAbs(luaL_checkint(l, 1), luaL_checkint(l, 2)));
	return 1;
}

static int bios_divarm(lua_State *l) {
	lua_pushinteger(l, (int) DivArm(luaL_checkint(l, 1), luaL_checkint(l, 2)));
	return 1;
}

static int bios_divarmmod(lua_State *l) {
	lua_pushinteger(l, (int) DivArmMod(luaL_checkint(l, 1), luaL_checkint(l, 2)));
	return 1;
}

static int bios_divarmabs(lua_State *l) {
	lua_pushinteger(l, (int) DivArmAbs(luaL_checkint(l, 1), luaL_checkint(l, 2)));
	return 1;
}

static int bios_sqrt(lua_State *l) {
	lua_pushinteger(l, (int) Sqrt(luaL_checkint(l, 1)));
	return 1;
}

static int bios_arctan(lua_State *l) {
	lua_pushinteger(l, (int) ArcTan(luaL_checkint(l, 1)));
	return 1;
}

static int bios_arctan2(lua_State *l) {
	lua_pushinteger(l, (int) ArcTan2(luaL_checkint(l, 1), luaL_checkint(l, 2)));
	return 1;
}

const luaL_Reg bios[] = {
	{"div", bios_div},
	{"divmod", bios_divmod},
	{"divabs", bios_divabs},
	{"divarm", bios_divarm},
	{"divarmmod", bios_divarmmod},
	{"divarmabs", bios_divarmabs},
	{"sqrt", bios_sqrt},
	{"arctan", bios_arctan},
	{"arctan2", bios_arctan2},
	{"checksum", bios_checksum},
	{NULL, NULL}
};

int luaopen_bios(lua_State *l) {
	luaL_newlib(l, bios);
	return 1;
}