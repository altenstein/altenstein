#include<stdio.h>
#include<stdlib.h>
#include<curses.h>
#include<string.h>
#include"render.h"
#include"items.h"

int main(void)
{
	initscr();
	
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);
	
	int player_x = 2;
	int player_y = 1;
	player_hp = 23;
	player_hp_max = 100;
	
	if (has_colors() == FALSE)
	{
		endwin();
		puts("\nYour terminal does not support color");
		return (1);
	}
	else start_color();
	
	init_color_location_map();
	init_color_entities();
	init_color_service();
	init_default_items();
	
	render_default_interface(tile_map_0000_deafult, tile_inventory, tile_character_info, tile_actions, tile_world_info);
	render_map_entities(player_y, player_x, tile_map_0000_deafult);
	
	init_actions();
	
	map_player_movement(player_y, player_x, tile_map_0000_deafult);
	
	getch();
	endwin();
	
	return 0;
}
