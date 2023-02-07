#include<stdio.h>
#include<stdlib.h>
#include<curses.h>
#include"render.h"

int main(void)
{
	initscr();
	
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);
	
	int player_x = 2;
	int player_y = 1;
	player_hp = 23; // MUST BE REWRITED WITH RASES, CLASSES AND PLAYER CHAR GENERATION
	player_hp_max = 100; // MUST BE REWRITED WITH RASES, CLASSES AND PLAYER CHAR GENERATION
	
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
	
	render_default_interface(tile_map_0000_deafult, tile_inventory, tile_character_info, tile_actions, tile_world_info);
	render_map_entities(player_y, player_x, tile_map_0000_deafult);
	
	//mvprintw(10, 10, "%d", player_hp); //Use for check variables
	
	init_actions();
	
	map_player_movement(player_y, player_x, tile_map_0000_deafult);
	
	getch();
	endwin();
	
	return 0;
}
