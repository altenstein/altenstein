main.exe: main.c render.c tiles.c player.c items.c spells.c actions.c messages.c
	gcc -o main.exe main.c render.c tiles.c player.c items.c spells.c actions.c messages.c -lpdcurses -lpthread
