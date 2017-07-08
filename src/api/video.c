#include <gba_video.h>

#include "lauxlib.h"
#include "enum.h"

static int video_REG_VCOUNT(lua_State *l) {
	lua_pushinteger(l, (int) REG_VCOUNT);
	return 1;
}

const luaL_Reg video[] = {
	{"REG_VCOUNT", video_REG_VCOUNT},
	{NULL, NULL}
};

int luaopen_video(lua_State *l) {
	luaL_newlib(l, video);
	return 1;
}