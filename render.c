#include<stdio.h>
#include<stdlib.h>
#include<curses.h>
#include<string.h>
#include<pthread.h>
#include<windows.h>
#include"render.h"
#include"items.h"

interface_tile current_map_tile;
interface_tile preload_map_tile;
interface_tile current_inventory_tile;

bool stop_render_flag = 0;

int map_color_num(char char_for_find_color, int map_type)
{
	if(map_type == 50) // 50 is 1 in ASCII; Colors for location map
	{if(char_for_find_color == 'W')
		return 201;
	else if(char_for_find_color == 'T')
		return 202;
	else if(char_for_find_color == '#')
		return 203;
	else if(char_for_find_color == '*')
		return 200;  // or 206
	else if(char_for_find_color == '<')
		return 200;
	else if(char_for_find_color == '>')
		return 200;
	else if(char_for_find_color == '_')
		return 012;
	else if(char_for_find_color == '^')
		return 012;
	}
	
	return 200;
}

int init_color_location_map(void)
{
	init_pair(200, 8, 0); // Map default pair
	
	init_pair(201, 9, 0); // Water color
	init_pair(202, 2, 0); // Tree color
	init_pair(203, 6, 0); // Wall/Wood color
	init_pair(204, 4, 0); // Full fire
	init_pair(205, 6, 0); // Little fire
	init_pair(206, 12, 0); // Hot coal / Rock
	
	return 0;
}

int init_color_service(void)
{
	init_pair(001, 8, 0); // Interface default pair
	init_pair(011, 0, 0); // Full black
	init_pair(012, 7, 0); // Default b/w
	init_pair(017, 8, 0); // Chest
	
	init_pair(002, 10, 0); // Low difficulty
	init_pair(003, 6, 0); // Middle difficulty
	init_pair(004, 4, 0); // High difficulty
	
	init_pair(005, 9, 0); // Action active (BUTTON)
	init_pair(006, 1, 0); // Action passive (BUTTON)
	init_pair(007, 10, 0); // Action active (ACTION)
	init_pair(010, 8, 0); // Action passive (ACTION)
	
	init_pair(013, 11, 0); // Blue for potion
	init_pair(014, 12, 0); // Blink Red for potion
	init_pair(015, 10, 0); // Green for potion
	init_pair(016, 6, 0); // Yellow for potion
	
	// FOR WHITE USE DEFAULT B/W (012)
	
	return 0;
}

int init_color_entities(void)
{
	init_pair(100, 14, 0); //USER (Default)
	init_pair(101, 4, 0); //Entity (Default)
	
	return 0;
}

int init_actions(void)
{	
	action_6_switch_inv(action_6_mod, current_map_tile);
	action_1_special(action_1_mod, current_map_tile);
	action_2_inventory_usage(action_2_mod, 0);
	
	return 0;
}

int render_selected_cell(int selected_cell, int action_6_flag)
{	
	int current_backpack_id = 0;
	player_additional_limit = player_inventory_limit;

	for (int i = 1; i <= 25; i++)
	{
		if (inventory_cell[i] > 999 && inventory_cell[i] < 1256 && (player_additional_limit + backpack[inventory_cell[i] - 1000].backpack_add_cells) >= i){
			player_additional_limit = player_inventory_limit + backpack[inventory_cell[i] - 1000].backpack_add_cells;
			if (player_inventory_limit + backpack[inventory_cell[i] - 1000].backpack_add_cells >= 25) player_additional_limit = 25;
			
			current_backpack_id = inventory_cell[i];
	}	}	
	
	//mvprintw(29, 0, "%d", current_backpack_id);

	int cell_x;
	int cell_y;
	int cell_x_clear;
	int cell_y_clear;
	
	if(action_6_flag == 1){ // Inventory cell selection
	
		action_2_inventory_usage(-1, inventory_cell[selected_cell]);
	
		attron(COLOR_PAIR(100));
	
		mvprintw(23, 90, "                            ");
		mvprintw(25, 90, "                            ");
	
		if (inventory_cell[selected_cell] != 0){ // Item information by ID
			mvprintw(23, 91, "%s", item_with_info[inventory_cell[selected_cell]].item_name);
			mvprintw(25, 91, "%s", item_with_info[inventory_cell[selected_cell]].item_description);
			if (item_with_info[inventory_cell[selected_cell]].item_usable == 1) {
				action_2_inventory_usage(1, inventory_cell[selected_cell]);
			}
		}
		
		if (inventory_cell[selected_cell] > 999 && inventory_cell[selected_cell] < 1256){ // Backpack information by ID
			mvprintw(23, 91, "%s", backpack[inventory_cell[selected_cell] - 1000].backpack_name);
			mvprintw(25, 91, "%s", backpack[inventory_cell[selected_cell] - 1000].backpack_description);
		}
		
		attroff(COLOR_PAIR(100));
	
		if (selected_cell > player_additional_limit) selected_cell = 1;
		
		if(selected_cell >= 21){
			cell_y = 5;
			cell_x = selected_cell - 20;
		} else if (selected_cell >= 16) {
			cell_y = 4;
			cell_x = selected_cell - 15;
		} else if (selected_cell >= 11) {
			cell_y = 3;
			cell_x = selected_cell - 10;
		} else if (selected_cell >= 6) {
			cell_y = 2;
			cell_x = selected_cell - 5;
		} else if (selected_cell >= 1) {
			cell_y = 1;
			cell_x = selected_cell;
		}
		
		attron(COLOR_PAIR(002));
		mvprintw((cell_y * 4) - 3, 72 + (cell_x * 8), "%d", selected_cell);
		attroff(COLOR_PAIR(002));
		attron(COLOR_PAIR(001));
		
		int count = 1;
		int i_limit;
		
		if (player_inventory_limit%10 == 0) i_limit = (player_additional_limit/10) * 2;
		else i_limit = ((player_additional_limit/10) * 2) + 1;
		
		for (int i = 1; i <= i_limit; i++){
			for (int j = 1; j <= 5; j++){
				if(count == player_additional_limit + 1) break;
				if (count != selected_cell) mvprintw((i * 4) - 3, 72 + (j * 8), "%d", count);
				count++;
			}
		}
		
		attroff(COLOR_PAIR(001));
		
		if (current_backpack_id != 0) backpack[current_backpack_id - 1000].backpack_used = 0;
		
		for (int k = player_inventory_limit + 1; k <= player_additional_limit; k++)
		{
			if (current_backpack_id != 0){
				if (inventory_cell[k] < 1000 || inventory_cell[k] > 1255){
				backpack[current_backpack_id - 1000].backpack_cell[k - player_inventory_limit - 1] = inventory_cell[k];
				if (inventory_cell[k] != 0) backpack[current_backpack_id - 1000].backpack_used++;
		}	}	}
		
		buffer_inventory_selected_cell = selected_cell;
		
	} else if (action_6_flag == 0){ // Spell book cell selection
	
		if (inventory_cell[buffer_inventory_selected_cell] != 0){
		action_2_inventory_usage(1, inventory_cell[buffer_inventory_selected_cell]);
		} else {action_2_inventory_usage(-1, 0);}
	
		if (selected_cell > player_spell_book_limit) selected_cell = 1;
		if (selected_cell > 10) selected_cell = 1;
		
		cell_x = 1;
		cell_y = selected_cell;
		
		attron(COLOR_PAIR(002));
		
		mvprintw((cell_y * 2) - 1, 80, "%d", selected_cell);
		
		attroff(COLOR_PAIR(002));
		attron(COLOR_PAIR(001));
		
		int count = 1;
		
		for (int i = 1; i <= player_spell_book_limit; i++){
			if (count != selected_cell) mvprintw((i * 2) - 1, 80, "%d", count);
			count++;
		}
		
		attroff(COLOR_PAIR(001));
		
		buffer_spell_book_selected_cell = selected_cell;
	}
	
	return 0;
}

int render_player_info(void)
{
	attron(COLOR_PAIR(001));
	mvprintw(28, 93, "[Lvl: %d]", player_level);
	mvprintw(28, 104, "[Exp: %d]", player_exp);
	attroff(COLOR_PAIR(001));
	
	attron(COLOR_PAIR(002));
	mvprintw(21, 1, "Live:");
	attroff(COLOR_PAIR(002));
	
	attron(COLOR_PAIR(003));
	mvprintw(21, 17, "$:%d", player_balance);
	attroff(COLOR_PAIR(003));
	
	if(player_hp <= (player_hp_max*0,33)) attron(COLOR_PAIR(004));
	else if(player_hp <= (player_hp_max*0,67)) attron(COLOR_PAIR(003));
	else if(player_hp <= player_hp_max) attron(COLOR_PAIR(002));
	
	if(player_hp/100 < 1) mvprintw(21, 9, "%d/%d", player_hp, player_hp_max);
	else if(10 > player_hp/100 >= 1) mvprintw(21, 8, "%d/%d", player_hp, player_hp_max);
	else if(player_hp/100 >= 10) mvprintw(21, 7, "%d/%d", player_hp, player_hp_max);
	
	attron(COLOR_PAIR(001));
	if(player_potion_cooldown > 0){ mvprintw(28, 27, "[PCD: %d]--", player_potion_cooldown); } else { mvprintw(28, 27, "----------"); }
	attroff(COLOR_PAIR(001));
	
	attroff(COLOR_PAIR(002));
	attroff(COLOR_PAIR(003));
	attroff(COLOR_PAIR(004));
	
	/* PLAYER STATS WILL BE HERE*/
}

int render_default_interface(interface_tile map, interface_tile inventory, interface_tile stats, interface_tile actions, interface_tile world_info) 
{
	current_map_tile = map;
	current_inventory_tile = inventory;
	
	int color_for_map_element;
	int map_type = map.tile[21][9];
	
    for(int i = 0; i < 21; i++)
	{
		for(int j = 0; j < 80; j++) //Load current map to interface
		{
			color_for_map_element = map_color_num(map.tile[i][j], map_type);
			attron(COLOR_PAIR(color_for_map_element));
			printw("%c", map.tile[i][j]);
			attroff(COLOR_PAIR(color_for_map_element));
		}
		for(int k = 0; k < 39; k++) //Load inventory / spell book to interface
		{
			attron(COLOR_PAIR(001));
			printw("%c", inventory.tile[i][k]);
			attroff(COLOR_PAIR(001));
		}
		printw("\n");
	}
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 25; j++) //Load character stats to interface
		{
			attron(COLOR_PAIR(001));
			printw("%c", stats.tile[i][j]);
			attroff(COLOR_PAIR(001));
		}
		for(int j = 0; j < 65; j++) //Load actions (attack/spells and regular) to interface
		{
			attron(COLOR_PAIR(001));
			printw("%c", actions.tile[i][j]);
			attroff(COLOR_PAIR(001));
		}
		for(int j = 0; j < 29; j++) //Load character stats to interface
		{
			attron(COLOR_PAIR(001));
			printw("%c", world_info.tile[i][j]);
			attroff(COLOR_PAIR(001));
		}
		printw("\n");
	}
	
	if(map.tile[21][11] == 49) attron(COLOR_PAIR(002)); // Set low difficulty
	else if(map.tile[21][11] == 50) attron(COLOR_PAIR(003)); // Set medium difficulty
	else if(map.tile[21][11] == 51) attron(COLOR_PAIR(004)); // Set high difficulty

	if(map.tile[21][9] == 49) mvprintw(0, 34, "[WORLD MAP]");
	else if(map.tile[21][9] == 50) mvprintw(0, 33, "[LOCATION MAP]");
	else if(map.tile[21][9] == 51) mvprintw(0, 35, "[DUNGEON]");
	else if(map.tile[21][9] == 52) mvprintw(0, 36, "[HOUSE]");
	
	attron(COLOR_PAIR(002));
	
	player_inventory_used = 0;
	
	for(int i2 = 0; i2 < 25; i2++) if (inventory_cell[i2] != 0) player_inventory_used++;
	
	if(action_6_flag == 1) mvprintw(0, 91, "[INVENTORY %d/%d]", player_inventory_used, player_additional_limit);
	else if(action_6_flag == 0) mvprintw(0, 91, "[SPELL BOOK %d/%d]", player_spell_book_used, player_spell_book_limit);
	
	attroff(COLOR_PAIR(002));
	attroff(COLOR_PAIR(003));
	attroff(COLOR_PAIR(004));

    return 0;
}

int render_chargen_interface(void)
{
	// CHARGEN REALIZATION 																										<---------[TODO]---------<<<
	
	return 0;
}

int render_item(int selected_cell, item_tile selected_item, int color_map_id, int mod_y, int mod_x)
{
	int base_y;
	int base_x;
	
	if (selected_cell == 1) {base_y = 1 + mod_y; base_x = 80 + mod_x;}
	else if (selected_cell == 2) {base_y = 1 + mod_y; base_x = 88 + mod_x;}
	else if (selected_cell == 3) {base_y = 1 + mod_y; base_x = 96 + mod_x;}
	else if (selected_cell == 4) {base_y = 1 + mod_y; base_x = 104 + mod_x;}
	else if (selected_cell == 5) {base_y = 1 + mod_y; base_x = 112 + mod_x;}
	else if (selected_cell == 6) {base_y = 5 + mod_y; base_x = 80 + mod_x;}
	else if (selected_cell == 7) {base_y = 5 + mod_y; base_x = 88 + mod_x;}
	else if (selected_cell == 8) {base_y = 5 + mod_y; base_x = 96 + mod_x;}
	else if (selected_cell == 9) {base_y = 5 + mod_y; base_x = 104 + mod_x;}
	else if (selected_cell == 10) {base_y = 5 + mod_y; base_x = 112 + mod_x;}
	else if (selected_cell == 11) {base_y = 9 + mod_y; base_x = 80 + mod_x;}
	else if (selected_cell == 12) {base_y = 9 + mod_y; base_x = 88 + mod_x;}
	else if (selected_cell == 13) {base_y = 9 + mod_y; base_x = 96 + mod_x;}
	else if (selected_cell == 14) {base_y = 9 + mod_y; base_x = 104 + mod_x;}
	else if (selected_cell == 15) {base_y = 9 + mod_y; base_x = 112 + mod_x;}
	else if (selected_cell == 16) {base_y = 13 + mod_y; base_x = 80 + mod_x;}
	else if (selected_cell == 17) {base_y = 13 + mod_y; base_x = 88 + mod_x;}
	else if (selected_cell == 18) {base_y = 13 + mod_y; base_x = 96 + mod_x;}
	else if (selected_cell == 19) {base_y = 13 + mod_y; base_x = 104 + mod_x;}
	else if (selected_cell == 20) {base_y = 13 + mod_y; base_x = 112 + mod_x;}
	else if (selected_cell == 21) {base_y = 17 + mod_y; base_x = 80 + mod_x;}
	else if (selected_cell == 22) {base_y = 17 + mod_y; base_x = 88 + mod_x;}
	else if (selected_cell == 23) {base_y = 17 + mod_y; base_x = 96 + mod_x;}
	else if (selected_cell == 24) {base_y = 17 + mod_y; base_x = 104 + mod_x;}
	else if (selected_cell == 25) {base_y = 17 + mod_y; base_x = 112 + mod_x;}
	
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 6; j++){
			
			if (color_map_id == 1){
				if(selected_item.item[i][j] == ')') attron(COLOR_PAIR(013));
				else if(selected_item.item[i][j] == '(') attron(COLOR_PAIR(013));
				else if(selected_item.item[i][j] == '%') attron(COLOR_PAIR(014));
				else if(selected_item.item[i][j] == 'X') attron(COLOR_PAIR(015));
				else if(selected_item.item[i][j] == ']') attron(COLOR_PAIR(013));
				else if(selected_item.item[i][j] == '[') attron(COLOR_PAIR(013));
				else if(selected_item.item[i][j] == '_') attron(COLOR_PAIR(013));
				else if(selected_item.item[i][j] == '|') attron(COLOR_PAIR(013));
				else if(selected_item.item[i][j] == '+') attron(COLOR_PAIR(013));
				else if(selected_item.item[i][j] == '#') attron(COLOR_PAIR(016));
				else if(selected_item.item[i][j] == '.') attron(COLOR_PAIR(012));
				else if(selected_item.item[i][j] == ':') attron(COLOR_PAIR(012));
			} else if((color_map_id > 999) && (color_map_id < 1256)) {
				if(selected_item.item[i][j] == '{') attron(COLOR_PAIR(016));
				else if(selected_item.item[i][j] == '}') attron(COLOR_PAIR(016));
				else if(selected_item.item[i][j] == '[') attron(COLOR_PAIR(016));
				else if(selected_item.item[i][j] == ']') attron(COLOR_PAIR(016));
				else if(selected_item.item[i][j] == '*') attron(COLOR_PAIR(016));
				else if(selected_item.item[i][j] == '_') attron(COLOR_PAIR(016));
			} else if (color_map_id == 2) {
				if(selected_item.item[i][j] == '$') attron(COLOR_PAIR(003));
				if(selected_item.item[i][j] == ':') attron(COLOR_PAIR(003));
				if(selected_item.item[i][j] == '.') attron(COLOR_PAIR(003));
			}
			
			mvaddch(base_y + i, base_x + j, selected_item.item[i][j]);
			
			attroff(COLOR_PAIR(001));
			attroff(COLOR_PAIR(013));
			attroff(COLOR_PAIR(014));
			attroff(COLOR_PAIR(015));
			attroff(COLOR_PAIR(016));
		} }
	
	return 0;
}

int render_inventory(void)
{
	int color_map_id;
	
	for (int cell = 1; cell <= player_additional_limit; cell++)
	{
		item_tile current_item_tile;
		
		if (inventory_cell[cell] == 0){current_item_tile = tile_empty;}
		else if (inventory_cell[cell] == 1) {current_item_tile = tile_potion; color_map_id = 1;} 
		else if (inventory_cell[cell] == 2) {current_item_tile = tile_poison; color_map_id = 1;} 
		else if (inventory_cell[cell] == 3) {current_item_tile = tile_bottle; color_map_id = 1;} 
		else if (inventory_cell[cell] == 4) {current_item_tile = tile_ale; color_map_id = 1;} 
		else if (inventory_cell[cell] == 5) {current_item_tile = tile_money_1; color_map_id = 2;} 
		else if (inventory_cell[cell] == 9) {current_item_tile = tile_mug; color_map_id = 1;} 
		else if ((1256 > inventory_cell[cell]) && (inventory_cell[cell] > 999)) {current_item_tile = tile_backpack; color_map_id = 1000;}
		
		render_item(cell, current_item_tile, color_map_id, 0, 0);
	}
	
	return 0;
}

int render_map_fire_3x2(int in_fire_y, int in_fire_x, int in_fire_map_id_1, int in_fire_map_id_2, int in_fire_map_id_3, int in_fire_map_id_4)
{
	// THREAD DYNAMIC FIRE RENDER  			<---------[TODO]---------<<<
	
	int res;
	//int work_fire = 1;
	
	
	typedef struct fireArgs_tag {
		int fire_y;
		int fire_x;
		int fire_map_id_1;
		int fire_map_id_2;
		int fire_map_id_3;
		int fire_map_id_4;
	} fireArgs_t;
	
	fireArgs_t fire_arg_struct;
	
	fire_arg_struct.fire_y = in_fire_y;
	fire_arg_struct.fire_x = in_fire_x;
	fire_arg_struct.fire_map_id_1 = in_fire_map_id_1;
	fire_arg_struct.fire_map_id_2 = in_fire_map_id_2;
	fire_arg_struct.fire_map_id_3 = in_fire_map_id_3;
	fire_arg_struct.fire_map_id_4 = in_fire_map_id_4;
	
	//---------------------------------------------------------------------------------------
	
	pthread_t thread_fire_engine;
	
	void *thread_func_fire_engine(void *arg) 
	{
		fireArgs_t *fire_arg = (fireArgs_t*) arg;
		
		int fire_y = fire_arg->fire_y;
		int fire_x = fire_arg->fire_x;
		
		int fire_map_id_1 = fire_arg->fire_map_id_1;
		int fire_map_id_2 = fire_arg->fire_map_id_2;
		int fire_map_id_3 = fire_arg->fire_map_id_3;
		int fire_map_id_4 = fire_arg->fire_map_id_4;
		
		do
		{
			attron(COLOR_PAIR(204));
			_srf_ mvaddch(fire_y, fire_x, 'f');
			_srf_ mvaddch(fire_y, fire_x + 1, 'F');
			_srf_ mvaddch(fire_y, fire_x + 2, 'F');
			attroff(COLOR_PAIR(204));
	
			attron(COLOR_PAIR(205));
			_srf_ mvaddch(fire_y - 1, fire_x, '.');
			attroff(COLOR_PAIR(205));
	
			attron(COLOR_PAIR(206));
			_srf_ mvaddch(fire_y - 1, fire_x + 1, 'f');
			_srf_ mvaddch(fire_y - 1, fire_x + 2, 'f');
			attroff(COLOR_PAIR(206));
			
			_srf_ refresh();
			Sleep(300);
			
			attron(COLOR_PAIR(204));
			_srf_ mvaddch(fire_y, fire_x, 'F');
			_srf_ mvaddch(fire_y, fire_x + 1, 'F');
			_srf_ mvaddch(fire_y, fire_x + 2, 'f');
			attroff(COLOR_PAIR(204));
	
			attron(COLOR_PAIR(205));
			_srf_ mvaddch(fire_y - 1, fire_x + 1, '"');
			attroff(COLOR_PAIR(205));
	
			attron(COLOR_PAIR(206));
			_srf_ mvaddch(fire_y - 1, fire_x, 'f');
			_srf_ mvaddch(fire_y - 1, fire_x + 2, 'f');
			attroff(COLOR_PAIR(206));
			
			_srf_ refresh();
			Sleep(300);
			
			attron(COLOR_PAIR(204));
			_srf_ mvaddch(fire_y, fire_x, 'F');
			_srf_ mvaddch(fire_y, fire_x + 1, 'f');
			_srf_ mvaddch(fire_y, fire_x + 2, 'F');
			attroff(COLOR_PAIR(204));
	
			attron(COLOR_PAIR(205));
			_srf_ mvaddch(fire_y - 1, fire_x + 2, '.');
			attroff(COLOR_PAIR(205));
	
			attron(COLOR_PAIR(206));
			_srf_ mvaddch(fire_y - 1, fire_x + 1, 'f');
			_srf_ mvaddch(fire_y - 1, fire_x, 'f');
			attroff(COLOR_PAIR(206));
			
			_srf_ refresh();
			Sleep(300);
		}
		while(current_map_tile.tile[21][4] - 48 == fire_map_id_1 && current_map_tile.tile[21][5] - 48 == fire_map_id_2
		   && current_map_tile.tile[21][6] - 48 == fire_map_id_3 && current_map_tile.tile[21][7] - 48 == fire_map_id_4);
		
		//mvprintw(29,0,"NOT OK %d %d %d %d", fire_y, fire_x, current_map_tile.tile[21][7], fire_map_id_4);
		
		pthread_exit(NULL);
	}
	
	res = pthread_create (&thread_fire_engine, NULL, thread_func_fire_engine, &fire_arg_struct);
	
	if (res != 0) {
		mvprintw(29, 0, "main error: can't create thread, status = %d\n", res);
		exit(-10);
	}

	res = pthread_detach(thread_fire_engine);
	
	if (res != 0) {
		mvprintw(29, 0, "main error: can't detach thread, status = %d\n", res);
		exit(-11);
	}
	
	return 0;
}

int render_map_entities(interface_tile map)
{
	int map_id_1 = map.tile[21][4] - 48;
	int map_id_2 = map.tile[21][5] - 48;
	int map_id_3 = map.tile[21][6] - 48;
	int map_id_4 = map.tile[21][7] - 48;
	
	// ID: 0000 | DEFAULT
	
	if((map_id_1 == 0) && (map_id_2 == 0) && (map_id_3 == 0) && (map_id_4 == 1))
	{
		// Render entities
		
		attron(COLOR_PAIR(101));
		mvaddch(7, 68, 'B'); // Boat
		mvaddch(18, 10, 'T'); // Tree with chest
		attroff(COLOR_PAIR(101));
		
		attron(COLOR_PAIR(011));
		mvaddch(15, 38, '*'); // Dev location teleport
		attroff(COLOR_PAIR(011));
		
		// Player check
		
		attron(COLOR_PAIR(101));
		
		if((player_y == 18) && (player_x == 10))
		{ 
			// CHEST ID: 0000
			
			strcpy(chest[0].chest_name, "Default location tree stash");
			strcpy(chest[0].chest_type, "STASH IN A TREE");
			chest[0].chest_map_id_1 = map_id_1;
			chest[0].chest_map_id_2 = map_id_2;
			chest[0].chest_map_id_3 = map_id_3;
			chest[0].chest_map_id_4 = map_id_4;
			chest[0].chest_x = player_x;
			chest[0].chest_y = player_y;
			
			mvprintw(21, 91, "Tree with a stash");
			
			if (transfer_inside_inventory_flag == 1) {
				action_1_mod = 10;
				action_1_special(action_1_mod, map);
			} else {
				action_1_mod = 1;
				action_1_special(action_1_mod, map);
			}
			
			
			
			attroff(COLOR_PAIR(101));
			
			return 1;
		}
		
		if((player_y == 7) && (player_x == 68))
		{
			mvprintw(21, 91, "Boat to another place");
			preload_map_tile = tile_map_0003_chargen;
			
			action_1_mod = 2;
			action_1_special(action_1_mod, map);
			
			attroff(COLOR_PAIR(101));
			
			return 2;
		}
		
		if((player_y == 15) && (player_x == 38))
		{
			mvprintw(21, 91, "Teleport to Develop map");
			preload_map_tile = tile_map_0002_dev;
			
			action_1_mod = 3;
			action_1_special(action_1_mod, map);
			
			attroff(COLOR_PAIR(101));
			
			return 2;
		}
		
		// No player check
		
		mvprintw(21, 90, "                            ");
	}
	
	else if((map_id_1 == 0) && (map_id_2 == 0) && (map_id_3 == 0) && (map_id_4 == 2))
	{
		// Render entities
		
		attron(COLOR_PAIR(101));
		mvaddch(11, 3, 'B'); // Test boat (need to add a teleportation function to any location)
		mvaddch(9, 3, 'C'); // Test chest 1 (CURRENT ITEMS)
		
		// Player check
		
		if((player_y == 9) && (player_x == 3))
		{ 
			// CHEST ID: 0001
			
			strcpy(chest[1].chest_name, "TEST CHEST");
			strcpy(chest[1].chest_type, "TEST CHEST");
			chest[1].chest_map_id_1 = map_id_1;
			chest[1].chest_map_id_2 = map_id_2;
			chest[1].chest_map_id_3 = map_id_3;
			chest[1].chest_map_id_4 = map_id_4;
			chest[1].chest_x = player_x;
			chest[1].chest_y = player_y;
			
			mvprintw(21, 91, "TEST CHEST");
			
			action_1_mod = 1;
			action_1_special(action_1_mod, map);
			
			return 1;
		}
		
		if((player_y == 11) && (player_x == 3))
		{
			mvprintw(21, 91, "TELEPORT TO DEFAULT MAP");
			preload_map_tile = tile_map_0001_default;
			
			action_1_mod = 3;
			action_1_special(action_1_mod, map);
			
			return 2;
		}
		
		// No player check
		
		attroff(COLOR_PAIR(101));
		mvprintw(21, 90, "                            ");
	}
	
	else if((map_id_1 == 0) && (map_id_2 == 0) && (map_id_3 == 0) && (map_id_4 == 3))
	{
		// Render entities
		
		attron(COLOR_PAIR(101));
		mvaddch(13, 18, 'P'); // Plate (Eastern exit from Borovia)
		attroff(COLOR_PAIR(101));
		
		// Player check
		
		if((player_y == 13) && (player_x == 18))
		{ 
			action_1_mod = 4;
			action_1_special(action_1_mod, map);
			
			return 1;
		}
		
		// No player check
		
		mvprintw(21, 90, "                            ");
	}
	
	action_1_mod = -1;
	action_1_special(action_1_mod, map);
	
	return 0;
}

int render_structure_chest(int chest_selected_cell, int chest_id)
{
	int base_y = 4;
	int base_x = 10;
	int title_x_pos = 10 + (40 - strlen(chest[chest_id].chest_type))/2;
	
	attron(COLOR_PAIR(017));
	
	for(int i = 0; i < 21; i++)
	{
		for(int j = 0; j < 80; j++) mvprintw(i + base_y, j + base_x, "%c", tile_chest.tile[i][j]);
	}
	
	mvprintw(4, title_x_pos, "[%s]", chest[chest_id].chest_type);
	
	attroff(COLOR_PAIR(017));
	
	return 0;
}

int render_chest_selected_cell(int chest_selected_cell, int chest_id)
{
	int cell_y;
	int cell_x;
	
	if (chest_selected_cell > 15) chest_selected_cell = 1;
	
	if (chest_selected_cell >= 11) {
		cell_y = 3;
		cell_x = chest_selected_cell - 10;
	} else if (chest_selected_cell >= 6) {
		cell_y = 2;
		cell_x = chest_selected_cell - 5;
	} else if (chest_selected_cell >= 1) {
		cell_y = 1;
		cell_x = chest_selected_cell;
	}
	
	attron(COLOR_PAIR(001));
	mvprintw((cell_y * 4) + 1, (cell_x * 8) + 3, "%d", chest_selected_cell);
	attroff(COLOR_PAIR(001));
	
	mvprintw(6, 50, "                   ");
	mvprintw(8, 50, "                   ");
	
	attron(COLOR_PAIR(100));
	
	if (chest[chest_id].chest_cell[chest_selected_cell] != 0){ // Item information by ID
			mvprintw(6, 51, "%s", item_with_info[chest[chest_id].chest_cell[chest_selected_cell]].item_name);
			mvprintw(8, 51, "%s", item_with_info[chest[chest_id].chest_cell[chest_selected_cell]].item_description);
		}
		
	if (chest[chest_id].chest_cell[chest_selected_cell] > 999 && chest[chest_id].chest_cell[chest_selected_cell] < 1256){ // Backpack information by ID
		mvprintw(6, 51, "%s", backpack[chest[chest_id].chest_cell[chest_selected_cell] - 1000].backpack_name);
		mvprintw(8, 51, "%s", backpack[chest[chest_id].chest_cell[chest_selected_cell] - 1000].backpack_description);
	}
	
	attroff(COLOR_PAIR(100));
	
	return 0;	
}

int render_chest_items(int chest_id)
{
	int color_map_id;
	
	for (int cell = 1; cell <= 15; cell++)
	{
		item_tile current_item_tile;
		
		if (chest[chest_id].chest_cell[cell] == 0){continue;}
		else if (chest[chest_id].chest_cell[cell] == 1) {current_item_tile = tile_potion; color_map_id = 1;} 
		else if (chest[chest_id].chest_cell[cell] == 2) {current_item_tile = tile_poison; color_map_id = 1;} 
		else if (chest[chest_id].chest_cell[cell] == 3) {current_item_tile = tile_bottle; color_map_id = 1;} 
		else if (chest[chest_id].chest_cell[cell] == 4) {current_item_tile = tile_ale; color_map_id = 1;} 
		else if (chest[chest_id].chest_cell[cell] == 5) {current_item_tile = tile_money_1; color_map_id = 2;} 
		else if (chest[chest_id].chest_cell[cell] == 6) {current_item_tile = tile_money_2; color_map_id = 2;} 
		else if (chest[chest_id].chest_cell[cell] == 7) {current_item_tile = tile_money_3; color_map_id = 2;} 
		else if (chest[chest_id].chest_cell[cell] == 8) {current_item_tile = tile_money_4; color_map_id = 2;} 
		else if (chest[chest_id].chest_cell[cell] == 9) {current_item_tile = tile_mug; color_map_id = 1;} 
		else if ((1256 > chest[chest_id].chest_cell[cell]) && (chest[chest_id].chest_cell[cell] > 999)) {current_item_tile = tile_backpack; color_map_id = 1000;}
		
		render_item(cell, current_item_tile, color_map_id, 4, -69);
	}
	
	return 0;	
}

int render_static_entities(void)
{
	if (current_map_tile.tile[21][4] == 48 && current_map_tile.tile[21][5] == 48 && current_map_tile.tile[21][6] == 48 && current_map_tile.tile[21][7] == 51)
	{ // 0003
		render_map_fire_3x2(9, 52, 0, 0, 0, 3);
	}
	
	return 0;
}

int render_loaded_location(void)
{	
	int moving_msg_flag = -1;

	clear();
	
	if (current_map_tile.tile[21][4] == 48 && current_map_tile.tile[21][5] == 48 && current_map_tile.tile[21][6] == 48 && current_map_tile.tile[21][7] == 49
	 && preload_map_tile.tile[21][4] == 48 && preload_map_tile.tile[21][5] == 48 && preload_map_tile.tile[21][6] == 48 && preload_map_tile.tile[21][7] == 50)
	{ // 0001 - > 0002
		current_map_tile = preload_map_tile;
		
		player_y = 11;
		player_x = 3;
	} else if (current_map_tile.tile[21][4] == 48 && current_map_tile.tile[21][5] == 48 && current_map_tile.tile[21][6] == 48 && current_map_tile.tile[21][7] == 49
			&& preload_map_tile.tile[21][4] == 48 && preload_map_tile.tile[21][5] == 48 && preload_map_tile.tile[21][6] == 48 && preload_map_tile.tile[21][7] == 51)
	{ // 0001 -> 0003
		current_map_tile = preload_map_tile;
		
		render_message(10000, 1);
		render_message(10000, 2);
		
		player_y = 9;
		player_x = 6;
	} else if (current_map_tile.tile[21][4] == 48 && current_map_tile.tile[21][5] == 48 && current_map_tile.tile[21][6] == 48 && current_map_tile.tile[21][7] == 50)
	{ // 0002 -> 0001
		current_map_tile = preload_map_tile;
		
		player_y = 15;
		player_x = 38;
	}
	
	//Sleep(2000);
	
	render_default_interface(current_map_tile, tile_inventory, tile_character_info, tile_actions, tile_world_info);
	render_map_entities(current_map_tile);
	render_selected_cell(player_selected_cell, action_6_flag);
	render_player_info();
	
	if (action_6_flag == 1) render_inventory();
	
	action_6_switch_inv(1, current_map_tile);
	action_6_switch_inv(1, current_map_tile);
	
	render_static_entities();
	
	map_player_movement(current_map_tile);
	
	return 0;
}
