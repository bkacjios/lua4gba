#include "gba.h"
#include <stdio.h>
#include "gbfs.h"
#include "lauxlib.h"
#include "enum.h"

extern GBFS_FILE const* fs;

static int gbfs_getFile(lua_State *l) {
	u32 len;
	char* file = (char*) gbfs_get_obj(fs, luaL_checkstring(l, 1), &len);
	if (file == NULL) return 0; // Return nil
	lua_pushlstring(l, file, len);
	return 1;
}

static int gbfs_getFileNum(lua_State *l) {
	lua_pushinteger(l, gbfs_count_objs(fs));
	return 1;
}

const luaL_Reg gbfs[] = {
	{"getFile", gbfs_getFile},
	{"getFileNum", gbfs_getFileNum},
	{NULL, NULL}
};

int luaopen_gbfs(lua_State *l) {
	luaL_newlib(l, gbfs);
	return 1;
}