#include <gba_console.h>
#include <gba_interrupt.h>
#include <gba_systemcalls.h>
#include <gba_timers.h>
#include <gba_input.h>
#include <gba_video.h>
#include <gba_sprites.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "gbfs.h"

#include "lauxlib.h"
#include "lualib.h"

GBFS_SPACE(filesystem, 1024); // Allocate 1mb to the filesystem
GBFS_FILE const* fs;

extern int luaopen_input(lua_State *l);
extern int luaopen_system(lua_State *l);
extern int luaopen_bios(lua_State *l);
extern int luaopen_interrupt(lua_State *l);
extern int luaopen_video(lua_State *l);
extern int luaopen_gbfs(lua_State *l);
extern int luaopen_sprite(lua_State *l);

const void *lua_script = 0;

static int report(lua_State *l, int status) {
	const char *msg;
	if (status) {
		msg = lua_tostring(l, -1);
		if (msg == NULL) msg = "(error with no message)";
		printf(msg);
		lua_pop(l, 1);
	}
	return status;
}

static int traceback(lua_State *l)
{
	luaL_traceback(l, l, lua_tostring(l, 1), 1);
	return 1;
}

static int lcall(lua_State *l, int narg, int nresults) {
	int status;
	int base = lua_gettop(l) - narg;
	lua_pushcfunction(l, traceback);
	lua_insert(l, base);
	status = lua_pcall(l, narg, nresults, base);
	lua_remove(l, base);
	return status;
}

static int docall(lua_State *l, int status) {
	if (status == 0) status = lcall(l, 0, 0);
	return report(l, status);
}

static int loadstring(lua_State *l, const char *str, u32 len, const char *name) {
	return luaL_loadbuffer(l, str, len, name);
}

static int dostring(lua_State *l, const char *str, u32 len, const char *name) {
	return docall(l, loadstring(l, str, len, name));
}

int gbfs_loader(lua_State* l) {
	const char* name = lua_tostring(l, 1);
	char* file = (char*) gbfs_get_obj(fs, name, 0);

	if (file == NULL) {
		lua_pushfstring(l, "\n\tno file " LUA_QS, name);
		return 1;
	}

	if (luaL_loadbuffer(l, file, strlen(file), name) == 0) {
		lua_pushstring(l, name);
		return 2;
	} else
		return luaL_error(l, "error loading module " LUA_QS
			" from file " LUA_QS ":\n\t%s",
			lua_tostring(l, 1), name, lua_tostring(l, -1));
}

int main() {
	irqInit();
	irqEnable(IRQ_VBLANK);

	fs = (GBFS_FILE*) filesystem;

	consoleDemoInit();

	SetMode(MODE_0 | BG0_ENABLE | OBJ_ENABLE | OBJ_1D_MAP);

	lua_State *l = luaL_newstate();
	
	if (l == NULL) {
		printf("cannot create lua state: not enough memory");
		return 0;
	}

	luaL_openlibs(l);
	luaL_requiref(l, "input", luaopen_input, 0);
	luaL_requiref(l, "system", luaopen_system, 0);
	luaL_requiref(l, "bios", luaopen_bios, 0);
	luaL_requiref(l, "interrupt", luaopen_interrupt, 0);
	luaL_requiref(l, "video", luaopen_video, 0);
	luaL_requiref(l, "gbfs", luaopen_gbfs, 0);
	luaL_requiref(l, "sprite", luaopen_sprite, 0);
	lua_pop(l, 7);

	lua_getglobal(l, "package");
	{
		lua_getfield(l, -1, "searchers");
		{
			// Replace lua file loader with our own
			lua_pushinteger(l, 2); //luaL_len(l, -1) + 1 // Insert?
			lua_pushcfunction(l, gbfs_loader);
			lua_settable(l, -3);
		}
	}
	lua_pop(l, 2);

	u32 len;
	char* lua_main = (char*) gbfs_get_obj(fs, "main.lua", &len);

	if (lua_main > 0)
		dostring(l, lua_main, len, "=main.lua");

	//u16 frame = 0;

	while(1) {
		//frame = frame + 1;
		//scanKeys();
		VBlankIntrWait();
		//u16 anim = frame / 15;

		//if (anim % 12 == 3)
		//	anim = 3 * 8;
		//else
		//	anim = (anim % 3) * 8;

		//sprite->attr2 = anim;
		//printf("attr2: %u\n", sprite->attr2);
	}

	lua_close(l);

	return 0;
}