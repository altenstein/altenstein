#include<stdio.h>
#include<stdlib.h>
#include<curses.h>
#include<string.h>
#include"render.h"
#include"items.h"

int inventory_cell_1 = 0;
int inventory_cell_2 = 0;
int inventory_cell_3 = 0;
int inventory_cell_4 = 0;
int inventory_cell_5 = 0;
int inventory_cell_6 = 0;
int inventory_cell_7 = 0;
int inventory_cell_8 = 0;
int inventory_cell_9 = 0;
int inventory_cell_10 = 0;
int inventory_cell_11 = 0;
int inventory_cell_12 = 0;
int inventory_cell_13 = 0;
int inventory_cell_14 = 0;
int inventory_cell_15 = 0;
int inventory_cell_16 = 0;
int inventory_cell_17 = 0;
int inventory_cell_18 = 0;
int inventory_cell_19 = 0;
int inventory_cell_20 = 0;
int inventory_cell_21 = 0;
int inventory_cell_22 = 0;
int inventory_cell_23 = 0;
int inventory_cell_24 = 0;
int inventory_cell_25 = 0;

int item_backpack_create(int id, char name[32], int add_cells) // The ID must be from 1000 to 1255
{
	id -= 1000;
	if(id > 255) return 0;
	strcpy(backpack[id].backpack_name, "Small bag");
	backpack[id].backpack_add_cells = add_cells;
	
	return 0;
}

int init_default_items(void)
{
	// ID: 0; BACKPACK IN THE DEFAULT LOCATION
	strcpy(backpack[0].backpack_name, "Old small bag");
	backpack[0].backpack_add_cells = 5;
	
	return 0;
}

item_tile tile_backpack = {.item = {
"      ",
"  (**)",
"  [__]"
} };


item_tile tile_potion = {.item = {
"      ",
"   )( ",
"  (%%)"
} };

item_tile tile_bottle = {.item = {
"      ",
"   )( ",
"  (__)"
} };
