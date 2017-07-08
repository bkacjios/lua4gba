#include <gba_systemcalls.h>

#include "lauxlib.h"
#include "enum.h"

static int system_softReset(lua_State *l) {
	SoftReset((RESTART_FLAG) luaL_checkint(l, 1));
	return 0;
}

static int system_registerRamReset(lua_State *l) {
	RegisterRamReset((RESET_FLAGS) luaL_checkint(l, 1));
	return 0;
}

static int system_halt(lua_State *l) {
	Halt();
	return 0;
}

static int system_stop(lua_State *l) {
	Stop();
	return 0;
}

const luaL_Reg system[] = {
	{"softReset", system_softReset},
	{"registerRamReset", system_registerRamReset},
	{"halt", system_halt},
	{"stop", system_stop},
	{NULL, NULL}
};

int luaopen_system(lua_State *l) {
	luaL_newlib(l, system);
	{
		LUA_ENUM(l, ROM_RESTART);
		LUA_ENUM(l, RAM_RESTART);
		LUA_ENUM(l, RESET_EWRAM);
		LUA_ENUM(l, RESET_IWRAM);
		LUA_ENUM(l, RESET_PALETTE);
		LUA_ENUM(l, RESET_VRAM);
		LUA_ENUM(l, RESET_OAM);
		LUA_ENUM(l, RESET_SIO);
		LUA_ENUM(l, RESET_SOUND);
		LUA_ENUM(l, RESET_OTHER);
	}
	return 1;
}