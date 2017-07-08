#define LUA_ENUM(L, value) \
	lua_pushlstring(L, #value, sizeof(#value)-1); \
	lua_pushnumber(L, value); \
	lua_settable(L, -3);
