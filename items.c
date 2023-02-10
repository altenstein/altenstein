#include<stdio.h>
#include<stdlib.h>
#include<curses.h>
#include<string.h>
#include"render.h"
#include"items.h"

int inventory_cell[25];

int item_backpack_create(int id, char name[32], int add_cells) // The ID must be from 1000 to 1255
{
	id -= 1000;
	if(id > 255) return 0;
	strcpy(backpack[id].backpack_name, name);
	backpack[id].backpack_add_cells = add_cells;
	
	return 0;
}

int init_default_items(void)
{
	inventory_cell[2] = 1;
	inventory_cell[3] = 2;
	inventory_cell[4] = 1000;
	inventory_cell[5] = 3;
	
	// ID: 1000; BACKPACK IN THE DEFAULT LOCATION
	strcpy(backpack[0].backpack_name, "Old small bag");
	backpack[0].backpack_add_cells = 5;
	
	return 0;
}

/*
ID: 1 - Treatment Potion
ID: 2 - Toxic poison
ID: 1000-1255 - Backpacks
*/

item_tile tile_backpack = {.item = {
"      ",
"  {**}",
"  [__]"
} };


item_tile tile_potion = {.item = {
"      ",
"   )( ",
"  (%%)"
} };

item_tile tile_poison = {.item = {
"      ",
"   )( ",
"  [##]"
} };

item_tile tile_bottle = {.item = {
"      ",
"   )( ",
"  (__)"
} };
