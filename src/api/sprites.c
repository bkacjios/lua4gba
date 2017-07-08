#include <gba_sprites.h>
#include <gba_video.h>
#include <stdio.h>
#include <string.h>

#include "lauxlib.h"
#include "enum.h"

typedef u16 ScreenBlock[1024];
typedef u16 Tile[32];
typedef Tile TileBlock[256];

#define MEM_VRAM				((volatile uint32*)0x6000000)
#define MEM_TILE				((TileBlock*)0x6000000)
#define MEM_SCREENBLOCKS		((ScreenBlock*)0x6000000)

static int sprite_load(lua_State *l) {
	luaL_checktype(l, 1, LUA_TSTRING);
	luaL_checktype(l, 2, LUA_TSTRING);

	size_t tile_len, pal_len;
	const char* tile = lua_tolstring(l, 1, &tile_len);
	const char* pallet = lua_tolstring(l, 2, &pal_len);

	memcpy(&MEM_TILE[4][0], tile, tile_len);
	memcpy(SPRITE_PALETTE, pallet, pal_len);

	OBJATTR *sprite = &OAM[0];
	sprite->attr0 = (ATTR0_SQUARE | ATTR0_COLOR_256);
	sprite->attr1 = ATTR1_SIZE_16;
	sprite->attr2 = 0;
	return 0;
}

const luaL_Reg sprite[] = {
	{"load", sprite_load},
	{NULL, NULL}
};

int luaopen_sprite(lua_State *l) {
	luaL_newlib(l, sprite);
	return 1;
}