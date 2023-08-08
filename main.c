#include<stdio.h>
#include<stdlib.h>
#include<curses.h>
#include<string.h>
#include"render.h"
#include"items.h"

/*

D E V E L O P M E N T  B Y
██╗  ██╗ █████╗ ████████╗ ██████╗ ██████╗ ████████╗███████╗
██║ ██╔╝██╔══██╗╚══██╔══╝██╔════╝██╔═══██╗╚══██╔══╝██╔════╝
█████╔╝ ███████║   ██║   ██║     ██║   ██║   ██║   █████╗  
██╔═██╗ ██╔══██║   ██║   ██║     ██║   ██║   ██║   ██╔══╝  
██║  ██╗██║  ██║   ██║   ╚██████╗╚██████╔╝   ██║   ███████╗
╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝    ╚═════╝ ╚═════╝    ╚═╝   ╚══════╝

*/

int main(void)
{
	initscr();
	
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);
	
	if (has_colors() == FALSE)
	{
		endwin();
		puts("\nYour terminal does not support color");
		return 1;
	}
	else start_color();
	
	init_color_location_map();
	init_color_entities();
	init_color_service();
	init_default_items();
	init_items_with_info();
	
	//current_map_tile = tile_map_0001_default;
	current_map_tile = tile_map_0004_central;
	
	player_y = 10; // 10 for chargen // 1 // 10 for central
	player_x = 69; // 57 for chargen // 2 // 69 for central
	
	render_default_interface(current_map_tile, tile_inventory, tile_character_info, tile_actions, tile_world_info);
	render_map_entities(current_map_tile);
	
	init_actions();
	
	launch();
	
	getch();
	
	endwin();
	
	return 0;
}
