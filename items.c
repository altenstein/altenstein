#include<stdio.h>
#include<stdlib.h>
#include<curses.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>
#include<windows.h> // Comment for linux build
#include"render.h"
#include"items.h"

item_backpack backpack[255];
item_info item_with_info[8192];
structure_chest chest[1024];
int inventory_cell[25];

int item_backpack_create(int id, char name[32], char description[32], int add_cells) // The ID must be from 1000 to 1255
{
	id -= 1000;
	if(id > 255) return 0;
	strcpy(backpack[id].backpack_name, name);
	strcpy(backpack[id].backpack_description, description);
	backpack[id].backpack_add_cells = add_cells;
	
	return 0;
}

int init_default_items(void)
{
	inventory_cell[1] = 1;
	
	// ID: 1000; BACKPACK IN THE DEFAULT LOCATION
	strcpy(backpack[0].backpack_name, "Old small bag");
	backpack[0].backpack_add_cells = 5;
	strcpy(backpack[0].backpack_description, "Add slots: 5");
	
	// ID: 1001; TEST BACKPACK
	strcpy(backpack[1].backpack_name, "TEST BACKPACK");
	backpack[1].backpack_add_cells = 20;
	strcpy(backpack[1].backpack_description, "Add slots: 20");
	
	for (int i = 1; i <= 25; i++){
		if (inventory_cell[i] > 999 && inventory_cell[i] < 1256 && (player_additional_limit + backpack[inventory_cell[i] - 1000].backpack_add_cells) >= i){
			player_additional_limit = player_inventory_limit + backpack[inventory_cell[i] - 1000].backpack_add_cells;
			if (player_inventory_limit + backpack[inventory_cell[i] - 1000].backpack_add_cells >= 25) player_additional_limit = 25;
	}   }
	
	chest[0].chest_cell[7] = 3;
	chest[0].chest_cell[1] = 1;
	chest[0].chest_cell[14] = 2;
	chest[0].chest_cell[15] = 1000;
	chest[0].chest_cell[8] = 6;
	
	chest[1].chest_cell[1] = 5;
	chest[1].chest_cell[2] = 6;
	chest[1].chest_cell[3] = 7;
	chest[1].chest_cell[4] = 8;
	chest[1].chest_cell[5] = 1001;
	chest[1].chest_cell[6] = 1;
	chest[1].chest_cell[7] = 2;
	chest[1].chest_cell[8] = 3;
	chest[1].chest_cell[9] = 4;
	
	return 0;
}

/*
!!! ITEM NAME NOT MORE THAN 17 (of course this also applies to the description) (CHEST INFO WINDOW IS 19) !!!
-------|-----------------| - Critical point
ID: 1 - Treatment Potion
ID: 2 - Toxic Poison
ID: 3 - Empty bottle
ID: 4 - Mug of Ale
ID: 5 - Money (1 GC)
ID: 6 - Money (10 GC)
ID: 7 - Money (100 GC)
ID: 8 - Money (1000 GC)
ID: 9 - Empty mug
ID: 1000-1255 - Backpacks
*/

int init_items_with_info(void)
{
	strcpy(item_with_info[1].item_name, "Treatment Potion");
	strcpy(item_with_info[1].item_description, "2 HP/Sec; 60 Sec;"); // YOU CAN USE DESCR-2 FOR SECOND DESCRIPTION LINE
	item_with_info[1].item_usable = 1;
	item_with_info[1].item_cost = 50;
	
	strcpy(item_with_info[2].item_name, "Toxic Poison");
	strcpy(item_with_info[2].item_description, "[Description 2]");
	item_with_info[2].item_usable = 1;
	item_with_info[2].item_cost = 25;
	
	strcpy(item_with_info[3].item_name, "Empty bottle");
	strcpy(item_with_info[3].item_description, "");
	item_with_info[3].item_usable = 0;
	item_with_info[3].item_cost = 1;
	
	strcpy(item_with_info[4].item_name, "Mug of Ale");
	strcpy(item_with_info[4].item_description, "1 HP/Sec; 30 Sec;");
	item_with_info[4].item_usable = 1;
	item_with_info[4].item_cost = 2;
	
	strcpy(item_with_info[5].item_name, "1 GC");
	strcpy(item_with_info[5].item_description, "Gold Coin");
	item_with_info[5].item_usable = 0;
	
	strcpy(item_with_info[6].item_name, "10 GC");
	strcpy(item_with_info[6].item_description, "Some Gold Coins");
	item_with_info[6].item_usable = 0;
	
	strcpy(item_with_info[7].item_name, "100 GC");
	strcpy(item_with_info[7].item_description, "Many Gold Coins");
	item_with_info[7].item_usable = 0;
	
	strcpy(item_with_info[8].item_name, "1000 GC");
	strcpy(item_with_info[8].item_description, "A lot of Gold");
	item_with_info[8].item_usable = 0;
	
	strcpy(item_with_info[9].item_name, "Empty mug");
	strcpy(item_with_info[9].item_description, "");
	item_with_info[9].item_usable = 0;
	item_with_info[9].item_cost = 1;
}

item_tile tile_empty = {.item = {
"      ",
"      ",
"      "
} };

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

int usage_item_potion_heal(int potion_id)
{
	int res;
	
	if (player_hp >= player_hp_max - 2) return -1; // Do not replace potion to empty bottle
	
	void *thread_func_heal(void *arg) // Heal function by ID
	{
		int arg_potion_id = * (int *) arg;
		int potion_hps;
		int potion_timer;
		
		//---------------------------------------------------------------------------------------
		
		if (arg_potion_id == 1) // Treatment Potion
		{
			potion_hps = 2;
			potion_timer = 60;
		} 
		else if (arg_potion_id == 4) // Mug of Ale
		{
			potion_hps = 1;
			potion_timer = 30;
		}
		else { pthread_exit(NULL); }
		
		//---------------------------------------------------------------------------------------
		
		player_potion_cooldown = -1; 
		if (arg_potion_id == 4) inventory_cell[buffer_inventory_selected_cell] = 9;// Replace potion to empty mug
		else inventory_cell[buffer_inventory_selected_cell] = 3; // Replace potion to empty bottle
		
		if (action_6_flag == 1) render_inventory();
		render_selected_cell(player_selected_cell, action_6_flag);
		
		refresh();
		
		for (int p_i = 0; p_i < potion_timer; p_i++)
		{
			if ((player_hp + potion_hps) >= player_hp_max) { player_hp = player_hp_max; break; }
			
			player_hp += potion_hps;
			_srf_ { render_player_info(); refresh(); }
			
			refresh();
			
			Sleep(1000); // usleep(x1000) for linux build
		}
		
		for (int cooldown = 180; cooldown >= 0; cooldown--)
		{
			player_potion_cooldown = cooldown; 
			_srf_ { render_player_info(); refresh(); }
			
			Sleep(1000); // usleep(x1000) for linux build
		}
		
		pthread_exit(NULL);
	}
	
	pthread_t item_thread_potion_heal;
	
	res = pthread_create (&item_thread_potion_heal, NULL, thread_func_heal, &potion_id);
	
	if (res != 0) {
        mvprintw(29, 0, "main error: can't create thread, status = %d\n", res);
        exit(-10);
    }

	res = pthread_detach(item_thread_potion_heal);
	
	if (res != 0) {
        mvprintw(29, 0, "main error: can't detach thread, status = %d\n", res);
        exit(-11);
    }
	
	Sleep(10);
	
	return 0;
}

item_tile tile_poison = {.item = {
"      ",
"   )( ",
"  [XX]"
} };

item_tile tile_bottle = {.item = {
"      ",
"   )( ",
"  (__)"
} };

item_tile tile_ale = {.item = {
"   .  ",
" |:.|+",
" |##|+"
} };

item_tile tile_mug = {.item = {
"      ",
" |  |+",
" |__|+"
} };

item_tile tile_money_1 = {.item = {
"      ",
"      ",
"     $"
} };

item_tile tile_money_2 = {.item = {
"      ",
"      ",
"    $$"
} };

item_tile tile_money_3 = {.item = {
"      ",
"    .$",
":. .$$"
} };

item_tile tile_money_4 = {.item = {
"  .::$",
".:::$$",
"::$$$$"
} };
