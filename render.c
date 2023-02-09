#include<stdio.h>
#include<stdlib.h>
#include<curses.h>
#include<string.h>
#include"render.h"
#include"items.h"

int map_color_num(char char_for_find_color, int map_type)
{
	if(map_type == 50) // 50 is 1 in ASCII; Colors for location map
	{if(char_for_find_color == 'W')
		return 201;
	else if(char_for_find_color == 'T')
		return 202;
	else if(char_for_find_color == '#')
		return 203;
	}
	
	return 200;
}

int init_color_location_map(void)
{
	init_pair(200, 8, 0); // Map default pair
	
	init_pair(201, 9, 0); // Water color
	init_pair(202, 2, 0); // Tree color
	init_pair(203, 6, 0); // Wall/Wood color
	
	return 0;
}

int init_color_service(void)
{
	init_pair(001, 8, 0); // Interface default pair
	init_pair(011, 0, 0); // Full black
	init_pair(012, 7, 0); // Default b/w
	
	init_pair(002, 10, 0); // Low difficulty
	init_pair(003, 6, 0); // Middle difficulty
	init_pair(004, 4, 0); // High difficulty
	
	init_pair(005, 9, 0); // Action active (BUTTON)
	init_pair(006, 1, 0); // Action passive (BUTTON)
	init_pair(007, 10, 0); // Action active (ACTION)
	init_pair(010, 2, 0); // Action passive (ACTION)
	
	init_pair(013, 11, 0); // Blue for potion
	init_pair(014, 12, 0); // Red for potion
	
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
	action_6_switch_inv(action_6_mod, tile_map_0000_deafult);
	action_1_special(action_1_mod, 0, 0, tile_map_0000_deafult);
	
	return 0;
}

int render_selected_cell(int selected_cell, int action_6_flag)
{
	int cell_x;
	int cell_y;
	int cell_x_clear;
	int cell_y_clear;
	
	if(action_6_flag == 1){ // Inventory cell selection
	
		if (selected_cell > player_inventory_limit) selected_cell = 1;
		
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
		
		if (player_inventory_limit%10 == 0) i_limit = (player_inventory_limit/10) * 2;
		else i_limit = ((player_inventory_limit/10) * 2) + 1;
		
		for (int i = 1; i <= i_limit; i++){
			for (int j = 1; j <= 5; j++){
				if(count == player_inventory_limit + 1) break;
				if (count != selected_cell) mvprintw((i * 4) - 3, 72 + (j * 8), "%d", count);
				count++;
			}
		}
		
		attroff(COLOR_PAIR(001));
		
	} else if (action_6_flag == 0){ // Spell book cell selection
	
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
	}
	
	return 0;
}

int render_default_interface(interface_tile map, interface_tile inventory, interface_tile stats, interface_tile actions, interface_tile world_info) 
{
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
	
	attron(COLOR_PAIR(002));
	mvprintw(21, 1, "Live:");
	mvprintw(21, 17, "$:%d", player_balance);
	attroff(COLOR_PAIR(002));
	
	if(player_hp <= (player_hp_max*0,33)) attron(COLOR_PAIR(004));
	else if(player_hp <= (player_hp_max*0,67)) attron(COLOR_PAIR(003));
	else if(player_hp <= player_hp_max) attron(COLOR_PAIR(002));
	
	if(player_hp/100 < 1) mvprintw(21, 9, "%d/%d", player_hp, player_hp_max);
	else if(10 > player_hp/100 >= 1) mvprintw(21, 8, "%d/%d", player_hp, player_hp_max);
	else if(player_hp/100 >= 10) mvprintw(21, 7, "%d/%d", player_hp, player_hp_max);
	
	attroff(COLOR_PAIR(002));
	attroff(COLOR_PAIR(003));
	attroff(COLOR_PAIR(004));
	
	if(map.tile[21][11] == 49) attron(COLOR_PAIR(002)); // Set low difficulty
	else if(map.tile[21][11] == 50) attron(COLOR_PAIR(003)); // Set medium difficulty
	else if(map.tile[21][11] == 51) attron(COLOR_PAIR(004)); // Set high difficulty

	if(map.tile[21][9] == 49) mvprintw(0, 34, "[WORLD MAP]");
	else if(map.tile[21][9] == 50) mvprintw(0, 33, "[LOCATION MAP]");
	else if(map.tile[21][9] == 51) mvprintw(0, 35, "[DUNGEON]");
	else if(map.tile[21][9] == 52) mvprintw(0, 36, "[HOUSE]");
	
	attron(COLOR_PAIR(002));
	
	if(action_6_flag == 1) mvprintw(0, 91, "[INVENTORY %d/%d]", player_inventory_used, player_inventory_limit);
	else if(action_6_flag == 0) mvprintw(0, 91, "[SPELL BOOK %d/%d]", player_spell_book_used, player_spell_book_limit);
	
	attroff(COLOR_PAIR(002));
	attroff(COLOR_PAIR(003));
	attroff(COLOR_PAIR(004));
	
	attron(COLOR_PAIR(001));
	mvprintw(28, 93, "[Lvl: %d]", player_level);
	mvprintw(28, 104, "[Exp: %d]", player_exp);
	attroff(COLOR_PAIR(001));

    return 0;
}

int render_item(int selected_cell, item_tile selected_item)
{
	if (selected_cell == 1)
	{
		for (int i = 0; i < 3; i++){
			for (int j = 0; j < 6; j++){
				
				if(selected_item.item[i][j] == ')') attron(COLOR_PAIR(013));
				else if(selected_item.item[i][j] == '(') attron(COLOR_PAIR(013));
				else if(selected_item.item[i][j] == '%') attron(COLOR_PAIR(014));
				
				mvaddch(i+1, j+80, selected_item.item[i][j]);
				
				attroff(COLOR_PAIR(013));
				attroff(COLOR_PAIR(014));
		} }
	}
	
	return 0;
}

int render_map_entities(int player_x, int player_y, interface_tile map)
{
	if(map.tile[21][9] == 0) return 0;
	
	// ID: 0000 | DEFAULT
	
	if((map.tile[21][4] == '0') && (map.tile[21][5] == '0') && (map.tile[21][6] == '0') && (map.tile[21][7] == '0'))
	{
		
		// Render entities
		
		attron(COLOR_PAIR(101));
		mvaddch(7, 68, 'B'); // Boat
		mvaddch(18, 10, 'T'); // Tree with chest
		
		// Player check
		
		if((player_x == 18) && (player_y == 10))
		{
			mvprintw(21, 91, "Tree with a stash");
			
			action_1_mod = 1;
			action_1_special(action_1_mod, player_x, player_y, map);
			
			return 1;
		}
		
		if((player_x == 7) && (player_y == 68))
		{
			mvprintw(21, 91, "Boat to another place");
			
			action_1_mod = 2;
			action_1_special(action_1_mod, player_x, player_y, map);
			
			return 2;
		}
		
		// No player check
		
		attroff(COLOR_PAIR(101));
		mvprintw(21, 90, "                            ");
	}
	
	action_1_mod = -1;
	action_1_special(action_1_mod, player_x, player_y, map);
	
	return 0;
}
