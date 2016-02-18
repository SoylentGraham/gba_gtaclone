echo off
h:
cd \
cd ferk
del ferk.gba
del ferk.elf
echo compiling...
PATH=e:\devkitadv\devkitadv\bin;%PATH%;h:\ferk\core
rem media/misc/*.c
gcc -o ferk.elf core/*.c game/*.c media/map/*.c media/gfx/*.c
objcopy -O binary ferk.elf ferk.gba
