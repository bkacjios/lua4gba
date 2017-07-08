local rom = io.open("lua52.gba", "rb")
local out = io.open("lua52_demo.gba", "wb")
local filesystem = assert(io.open("filesystem.gbfs", "rb"))

while true do
	local word = rom:read(4)
	if not word or word == "" then break end
	if word == "PinE" then
		if rom:read(12) == "ightGBFS\r\n\x1a\n" then
			local pos = rom:seek() - 16

			print(("FOUND PinEightGBFS: %08X (%d)"):format(pos, pos))

			local size = -16

			while string.byte(rom:read(1)) == 0 do
				size = size + 1
			end

			local fs_size = filesystem:seek("end")

			print(size, fs_size)

			assert(fs_size == size, "filesystem and allocated gbfs partition mismatch")
			filesystem:seek("set", 0)

			rom:seek("set", 0)
			out:write(rom:read(pos))
			out:write(filesystem:read("*a"))
			rom:seek("set", pos + size)
			out:write(rom:read("*a"))

			--print(rom:write("pINeIGHTgbfs"))

			rom:seek("set", pos)

			print(rom:read(12))

			break
		end
	end
end

out:close()
rom:close()
filesystem:close()

--[[local filesystem = io.open("filesystem.gbfs", "rb")
local header = io.open("filesystem.h", "wb")

local size = filesystem:seek("end")
filesystem:seek("set", 0)

header:write(("#define GBFS_PARTITION() \n const unsigned char gbfs[%d] __attribute__ ((aligned (16))) = {%s};"):format(size, ]]