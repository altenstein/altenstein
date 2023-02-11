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

int action_transfer_from_chest(int chest_id, int chest_selected_cell)
{
	if (chest[chest_id].chest_cell[chest_selected_cell] != 0)
	{
		for (int cell = 1; cell <= player_additional_limit; cell++)
		{
			if (inventory_cell[cell] == 0){
				inventory_cell[cell] = chest[chest_id].chest_cell[chest_selected_cell];
				chest[chest_id].chest_cell[chest_selected_cell] = 0; 
				
				break;
			} 
		} 
	}
}

int action_transfer_to_chest(int chest_id, int player_selected_cell)
{
	if (inventory_cell[player_selected_cell] > 999 && inventory_cell[player_selected_cell] < 1256)
	{
		for (int backpack_cell = 0; backpack_cell < 20; backpack_cell++)
		{
			if (backpack[inventory_cell[player_selected_cell] - 1000].backpack_cell[backpack_cell] != 0) return 0;
		}
	}
	
	if (inventory_cell[player_selected_cell] != 0)
	{
		for (int cell = 1; cell <= 15; cell++)
		{
			
			if (chest[chest_id].chest_cell[cell] == 0)
			{
				chest[chest_id].chest_cell[cell] = inventory_cell[player_selected_cell];
				inventory_cell[player_selected_cell] = 0;
				
				break;
			}
			
		}
	}
	
	return 0;
}

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
			
			if (player_action == 'w') chest_selected_cell -= 5;
			else if (player_action == 's') chest_selected_cell += 5;
			else if (player_action == 'a') chest_selected_cell -= 1;
			else if (player_action == 'd') chest_selected_cell += 1;
			
			if (chest_selected_cell > 15) chest_selected_cell = 1;
			else if (chest_selected_cell < 1) chest_selected_cell = 15;
			
			if(action_6_flag == 1){ // Player cell selection
			
				if((key_buffer) == 2 && player_selected_cell + 5 <= player_additional_limit) player_selected_cell += 5;
				else if((key_buffer) == 3) player_selected_cell -= 5;
				else if((key_buffer) == 4) player_selected_cell -= 1;
				else if((key_buffer) == 5 && player_selected_cell + 1 <= player_additional_limit) player_selected_cell += 1;
			
				if(player_selected_cell > player_additional_limit) player_selected_cell = 1;
				else if(player_selected_cell < 1) player_selected_cell = player_additional_limit;
			}
			
			if (player_action == 32 && action_6_flag == 1) action_transfer_from_chest(structure_id, chest_selected_cell);
			
			if (player_action == '\n' && action_6_flag == 1) action_transfer_to_chest(structure_id, player_selected_cell);
			
			if(action_6_flag == 1) {
				
				clear();
				
				render_default_interface(current_map_tile, current_inventory_tile, tile_character_info, tile_actions, tile_world_info);
				render_map_entities(player_y, player_x, current_map_tile);
				render_inventory();
				render_selected_cell(player_selected_cell, action_6_flag);
			}
			
			action_6_switch_inv(0, current_map_tile);
			
			render_structure_chest(chest_selected_cell, structure_id);
			render_chest_items(structure_id);
			render_chest_selected_cell(chest_selected_cell, structure_id);
			
			attron(COLOR_PAIR(005));
			mvprintw(22, 28, "1");
			attroff(COLOR_PAIR(005));
			attron(COLOR_PAIR(007));
			mvprintw(22, 31, "Close the chest");
			mvprintw(22, 46, "            ");
			attroff(COLOR_PAIR(007));
		}
		while ((player_action = getch()) != 49);
		
		clear();
		
		render_default_interface(current_map_tile, current_inventory_tile, tile_character_info, tile_actions, tile_world_info);
		render_map_entities(player_y, player_x, current_map_tile);
		
		if (action_6_flag == 0) action_6_flag = 1;
		else if (action_6_flag == 1) action_6_flag = 0;
		action_6_switch_inv(1, current_map_tile);
		
		if(action_6_flag == 1) {
			render_inventory();
			render_selected_cell(player_selected_cell, action_6_flag);
		}
		
	}
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
		current_inventory_item = 0;
		
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
		current_inventory_item = item_id;
		
		attron(COLOR_PAIR(005));
		mvprintw(24, 28, "2");
		attroff(COLOR_PAIR(005));
		attron(COLOR_PAIR(007));
		mvprintw(24, 31, "Use %s", item_with_info[item_id].item_name);
		//mvprintw(24, 45, "             ");
		attroff(COLOR_PAIR(007));
	}
	
	else if(mod == 2) // Staff usage passive
	{
		current_inventory_item = item_id;
		
		attron(COLOR_PAIR(006));
		mvprintw(24, 28, "2");
		attroff(COLOR_PAIR(006));
		attron(COLOR_PAIR(010));
		mvprintw(24, 31, "Use %s", item_with_info[item_id].item_name);
		//mvprintw(24, 45, "             ");
		attroff(COLOR_PAIR(010));
	}
	
	else if(mod == 3) // Staff usage action
	{
		current_inventory_item = item_id;
		
		attron(COLOR_PAIR(005));
		mvprintw(24, 28, "2");
		attroff(COLOR_PAIR(005));
		attron(COLOR_PAIR(007));
		mvprintw(24, 31, "Use %s", item_with_info[item_id].item_name);
		//mvprintw(24, 44, "              ");
		attroff(COLOR_PAIR(007));
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
