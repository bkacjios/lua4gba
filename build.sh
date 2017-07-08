#!/bin/bash
rm -f lua52.gba filesystem.gbfs
gbfs filesystem.gbfs filesystem/*.* filesystem/sprites/*.*
make
insgbfs filesystem.gbfs lua52.gba filesystem
gbafix -p lua52.gba -t lua52