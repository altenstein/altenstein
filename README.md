<p align="center">
      <img src="https://i.ibb.co/ry5Z04M/Altenstein-2.png" width="1452">
</p>

<p align="center">
   <img src="https://img.shields.io/badge/Build-0.0.3.23-success" alt="Build">
   <img src="https://img.shields.io/badge/Ready-pre--alpha-orange" alt="Developer">
   <img src="https://img.shields.io/badge/License-BSD--3_Clause-red" alt="License">
</p>

## About 
**Altenstein** is a Rouglike medival text RPG, that we write right now.
Based on the Dungeons and Dragons.

Additions coming soon..

## Build 0.0.3.23
<p align="center">
      <img src="https://i.ibb.co/ftgwRjC/image-2023-02-25-03-45-55.png" width="965">
</p>

### Compile GCC (MinGW)
cmd /k cd "C:\Dev\altenstein" && gcc -o main.exe main.c render.c tiles.c player.c items.c spells.c actions.c messages.c -lpdcurses -lpthread && main.exe

-lpdcurses -> -lncurses (for linux build)

### Dependencies 
[Current Libs](https://github.com/altenstein/altenstein/issues/2)

libgcc_s_dw2-1.dll  
libpdcurses.dll  
pthreadGC-3.dll 

## Graphics

To select the visual appearance of the game, use the settings of the console in which the game appears.

(I recommend trying SimSun-ExtB)

## Developers

- [KatCote](https://github.com/KatCote)
