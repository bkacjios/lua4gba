local gbfs = require("gbfs")
local sprite = require("sprite")

print("gbfs", gbfs)
print("sprite", sprite)

local hero_img = gbfs.getFile("hero.img.bin")
local hero_pal = gbfs.getFile("hero.pal.bin")

print(#hero_img)
print(#hero_pal)

local s = sprite.load(hero_img, hero_pal)

io.stdout:write("this is a test\n")
io.stdout:flush()