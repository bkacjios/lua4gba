#include <gba_input.h>

#include "lauxlib.h"
#include "enum.h"

static int input_scan(lua_State *l) {
	scanKeys();
	return 0;
}

static int input_getPressed(lua_State *l) {
	lua_pushinteger(l, keysDown());
	return 1;
}

static int input_getPressedRepeat(lua_State *l) {
	lua_pushinteger(l, keysDownRepeat());
	return 1;
}

static int input_getReleased(lua_State *l) {
	lua_pushinteger(l, keysUp());
	return 1;
}

static int input_getHeld(lua_State *l) {
	lua_pushinteger(l, keysHeld());
	return 1;
}

static int input_setRepeat(lua_State *l) {
	setRepeat(luaL_checkint(l, 1), luaL_checkint(l, 2));
	return 0;
}

const luaL_Reg input[] = {
	{"scan", input_scan},
	{"getPressed", input_getPressed},
	{"getPressedRepeat", input_getPressedRepeat},
	{"getReleased", input_getReleased},
	{"getHeld", input_getHeld},
	{"setRepeat", input_setRepeat},
	{NULL, NULL}
};

int luaopen_input(lua_State *l) {
	luaL_newlib(l, input);
	{
		LUA_ENUM(l, KEY_A);
		LUA_ENUM(l, KEY_B);
		LUA_ENUM(l, KEY_SELECT);
		LUA_ENUM(l, KEY_START);
		LUA_ENUM(l, KEY_RIGHT);
		LUA_ENUM(l, KEY_LEFT);
		LUA_ENUM(l, KEY_UP);
		LUA_ENUM(l, KEY_DOWN);
		LUA_ENUM(l, KEY_R);
		LUA_ENUM(l, KEY_L);
	}
	return 1;
}