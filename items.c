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
	inventory_cell[5] = 2;
	inventory_cell[7] = 1000;
	inventory_cell[3] = 3;
	inventory_cell[6] = 3;
	
	// ID: 1000; BACKPACK IN THE DEFAULT LOCATION
	strcpy(backpack[0].backpack_name, "Old small bag");
	strcpy(backpack[0].backpack_description, "[Description 1000]");
	backpack[0].backpack_add_cells = 5;
	
	for (int i = 1; i <= 25; i++){
		if (inventory_cell[i] > 999 && inventory_cell[i] < 1256 && (player_additional_limit + backpack[inventory_cell[i] - 1000].backpack_add_cells) >= i){
			player_additional_limit = player_inventory_limit + backpack[inventory_cell[i] - 1000].backpack_add_cells;
	}   }
	
	return 0;
}

/*
ID: 1 - Treatment Potion
ID: 2 - Toxic Poison
ID: 3 - Empty bottle
ID: 1000-1255 - Backpacks
*/

int init_items_with_info(void)
{
	strcpy(item_with_info[1].item_name, "Treatment Potion");
	strcpy(item_with_info[1].item_description, "[Description 1]");
	item_with_info[1].item_usable = 1;
	
	strcpy(item_with_info[2].item_name, "Toxic Poison");
	strcpy(item_with_info[2].item_description, "[Description 2]");
	item_with_info[2].item_usable = 1;
	
	strcpy(item_with_info[3].item_name, "Empty bottle");
	strcpy(item_with_info[3].item_description, "[Description 3]");
	item_with_info[3].item_usable = 0;
}

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
