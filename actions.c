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

int action_1_special(int mod, int player_x, int player_y, interface_tile map)
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
		mvprintw(22, 31, "Open the stash");
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
