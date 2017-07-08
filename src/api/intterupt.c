#include <gba_systemcalls.h>

#include "lauxlib.h"

static int interrupt_wait(lua_State *l) {
	IntrWait(luaL_checkint(l, 1), luaL_checkint(l, 2));
	return 0;
}

static int input_waitVBlank(lua_State *l) {
	VBlankIntrWait();
	return 0;
}

const luaL_Reg inturrupt[] = {
	{"wait", interrupt_wait},
	{"waitVBlank", input_waitVBlank},
	{NULL, NULL}
};

int luaopen_interrupt(lua_State *l) {
	luaL_newlib(l, inturrupt);
	return 1;
}