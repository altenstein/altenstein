#include<stdio.h>
#include<stdlib.h>
#include<curses.h>
#include<string.h>
#include"render.h"
#include"items.h"

int action_6_mod = 1;
int action_6_flag = 0;
int action_1_mod = -1;
int action_2_mod = -1;

int action_structure_usage(int player_y, int player_x, int structure_type, int structure_id)
{
	/*
	ID: 1 - Chest
	*/
	
	int chest_selected_cell = 1;
	
	if (structure_type == 1)
	{
		char player_action;
		
		attron(COLOR_PAIR(005));
		mvprintw(22, 28, "1");
		attroff(COLOR_PAIR(005));
		attron(COLOR_PAIR(007));
		mvprintw(22, 31, "Close the chest");
		mvprintw(22, 46, "            ");
		attroff(COLOR_PAIR(007));
		
		do
		{
			char key_buffer = player_action;
			
			if (player_action == 'w');
			else if (player_action == 's');
			else if (player_action == 'a');
			else if (player_action == 'd');
			
			if(action_6_flag == 1){ // Player cell selection
			
				if((key_buffer) == 2 && player_selected_cell + 5 <= player_additional_limit) player_selected_cell += 5;
				else if((key_buffer) == 3) player_selected_cell -= 5;
				else if((key_buffer) == 4) player_selected_cell -= 1;
				else if((key_buffer) == 5 && player_selected_cell + 1 <= player_additional_limit) player_selected_cell += 1;
			
				if(player_selected_cell > player_additional_limit) player_selected_cell = 1;
				else if(player_selected_cell < 1) player_selected_cell = player_additional_limit;
			}
			
			if(action_6_flag == 1) {
				render_inventory();
				render_selected_cell(player_selected_cell, action_6_flag);
			}
			
			render_structure_chest(chest_selected_cell, structure_id);
		}
		while ((player_action = getch()) != 49);
		
		clear();
		
		render_default_interface(current_map_tile, current_inventory_tile, tile_character_info, tile_actions, tile_world_info);
		render_map_entities(player_y, player_x, current_map_tile);
		render_inventory();
		
	}
}

int action_6_switch_inv(int mod, interface_tile map)
{
	if(mod == 0) // Button passive
	{
		attron(COLOR_PAIR(006));
		mvprintw(26, 59, "6");
		attroff(COLOR_PAIR(006));
		attron(COLOR_PAIR(010));
		if(action_6_flag == 0) mvprintw(26, 62, "Switch to Inventory");
		else if(action_6_flag == 1) mvprintw(26, 62, "Switch to Spell book");
		attroff(COLOR_PAIR(010));
	}
	
	else if(mod == 1) // Button active
	{
		clear();
		
		if(action_6_flag == 0) // Set Inventory
		{
			player_selected_cell = buffer_inventory_selected_cell;
			action_6_flag = 1;
			render_default_interface(map, tile_inventory, tile_character_info, tile_actions, tile_world_info);
		}
		else if(action_6_flag == 1) // Set Spell book
		{
			player_selected_cell = buffer_spell_book_selected_cell;
			action_6_flag = 0;
			render_default_interface(map, tile_spell_book, tile_character_info, tile_actions, tile_world_info);
		}
		
		attron(COLOR_PAIR(005));
		mvprintw(26, 59, "6");
		attroff(COLOR_PAIR(005));
		attron(COLOR_PAIR(007));
		if(action_6_flag == 0) mvprintw(26, 62, "Switch to Inventory");
		else if(action_6_flag == 1) mvprintw(26, 62, "Switch to Spell book");
		attroff(COLOR_PAIR(007));
	}
	
	return 0;
}

int action_1_special(int mod, int player_y, int player_x, interface_tile map)
{
	
	// Button initializations
	
	if(mod == -1) // Button init
	{
		attron(COLOR_PAIR(006));
		mvprintw(22, 28, "1");
		attroff(COLOR_PAIR(006));
		attron(COLOR_PAIR(010));
		mvprintw(22, 31, "[NO ACTION]"); // Need to replace with Look around
		mvprintw(22, 42, "                ");
		attroff(COLOR_PAIR(010));
	}
	
	else if(mod == 1) // Chest action init
	{
		attron(COLOR_PAIR(005));
		mvprintw(22, 28, "1");
		attroff(COLOR_PAIR(005));
		attron(COLOR_PAIR(007));
		mvprintw(22, 31, "Open the chest");
		mvprintw(22, 45, "             ");
		attroff(COLOR_PAIR(007));
	}
	
	else if(mod == 2) // Boat init
	{
		attron(COLOR_PAIR(005));
		mvprintw(22, 28, "1");
		attroff(COLOR_PAIR(005));
		attron(COLOR_PAIR(007));
		mvprintw(22, 31, "Take the boat");
		mvprintw(22, 44, "              ");
		attroff(COLOR_PAIR(007));
	}
	
	// Button actions
	
	else if(mod == 11) // Chest action
	{
		int current_chest_id = -1;
		
		for (int i = 0; i < 1024; i++)
		{
			int map_id_1_buffer;
			int map_id_2_buffer;
			int map_id_3_buffer;
			int map_id_4_buffer;

			if (map.tile[21][4] > 47 && map.tile[21][4] < 58) map_id_1_buffer = map.tile[21][4] - 48;
			if (map.tile[21][5] > 47 && map.tile[21][5] < 58) map_id_2_buffer = map.tile[21][5] - 48;
			if (map.tile[21][6] > 47 && map.tile[21][6] < 58) map_id_3_buffer = map.tile[21][6] - 48;
			if (map.tile[21][7] > 47 && map.tile[21][7] < 58) map_id_4_buffer = map.tile[21][7] - 48;
			
			if (chest[i].chest_map_id_1 != map_id_1_buffer) continue;
			if (chest[i].chest_map_id_2 != map_id_2_buffer) continue;
			if (chest[i].chest_map_id_3 != map_id_3_buffer) continue;
			if (chest[i].chest_map_id_4 != map_id_4_buffer) continue;
			
			current_chest_id = i;
		}
		
		if (current_chest_id != -1)
		{
			action_structure_usage(player_y, player_x, 1, current_chest_id);
		}
		
		attron(COLOR_PAIR(005));
		mvprintw(22, 28, "1");
		attroff(COLOR_PAIR(005));
		attron(COLOR_PAIR(007));
		mvprintw(22, 31, "Open the chest");
		mvprintw(22, 45, "             ");
		attroff(COLOR_PAIR(007));
	}
	
	return 0;
}

int action_2_inventory_usage(int mod, int item_id)
{
	if(mod == -1) // Staff usage passive
	{
		attron(COLOR_PAIR(006));
		mvprintw(24, 28, "2");
		attroff(COLOR_PAIR(006));
		attron(COLOR_PAIR(010));
		mvprintw(24, 31, "[NO ACTION]"); // Need to replace
		mvprintw(24, 42, "                ");
		attroff(COLOR_PAIR(010));
	}
	
	else if(mod == 1) // Staff usage active
	{
		attron(COLOR_PAIR(005));
		mvprintw(24, 28, "2");
		attroff(COLOR_PAIR(005));
		attron(COLOR_PAIR(007));
		mvprintw(24, 31, "Use %s", item_with_info[item_id].item_name);
		//mvprintw(24, 45, "             ");
		attroff(COLOR_PAIR(007));
	}
	
	else if(mod == 2) // Staff usage action
	{
		attron(COLOR_PAIR(005));
		mvprintw(24, 28, "2");
		attroff(COLOR_PAIR(005));
		attron(COLOR_PAIR(007));
		mvprintw(24, 31, "Use %s", item_with_info[item_id].item_name);
		//mvprintw(24, 44, "              ");
		attroff(COLOR_PAIR(007));
	}
}
