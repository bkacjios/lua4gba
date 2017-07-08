print("table", table)
print("string", string)
print("math", math)
print("debug", debug)

print("_VERSION", _VERSION)
print("math.pi", math.pi)
print("math.huge", math.huge)

local input = require("input")
local system = require("system")
local bios = require("bios")
local interrupt = require("interrupt")
local bit = require("bit32")
local video = require("video")

print("input", input)
print("system", system)
print("bios", bios)
print("interrupt", interrupt)
print("bit", bit)
print("video", video)

print(math.sqrt(1337))

print("io.stdin", io.stdin)
print("io.stdout", io.stdout)
print("io.stderr", io.stderr)

local band = bit.band
local bor = bit.bor
local seeded = false
local frame = 0

local HRZ = 59.73

require("script.lua")

while true do
	input.scan()

	local held = input.getHeld()
	local pressed = input.getPressed()

	if band(pressed, input.KEY_A) ~= 0 then
		local time = frame / 59.73
		local seconds = math.floor(time % 60)
		local minutes = math.floor(time/60)

		print(("%02d:%02d"):format(minutes, seconds))
	end

	if band(pressed, input.KEY_B) ~= 0 then
		if not seeded then
			math.randomseed(frame)
		end
		print(math.random())
	end

	if bor(input.KEY_L, input.KEY_R, input.KEY_START, input.KEY_SELECT) == held then
		system.softReset(system.ROM_RESTART)
	end

	frame = frame + 1
	interrupt.waitVBlank()
end