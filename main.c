#include<stdio.h>
#include<stdlib.h>
#include<curses.h>
#include"render.h"

int map_player_movement(int player_y, int player_x, interface_tile map)
{
	attron(COLOR_PAIR(100));
	mvaddch(player_y, player_x, '@');
	attroff(COLOR_PAIR(100));
	char player_move = getch();
	do
	{
		int buffer_player_y = player_y;
		int buffer_player_x = player_x;
		
		if ((player_move == 'w') && ((player_y - 1) != 0) && (map.tile[player_y - 1][player_x] == ' ')) player_y--;
		else if ((player_move == 's') && ((player_y + 1) != 20) && (map.tile[player_y + 1][player_x] == ' ')) player_y++;
		else if ((player_move == 'a') && ((player_x - 1) != 0) && (map.tile[player_y][player_x - 1] == ' ')) player_x--;
		else if ((player_move == 'd') && ((player_x - 1) != 77) && (map.tile[player_y][player_x + 1] == ' ')) player_x++;
		
		attron(COLOR_PAIR(200));
		mvaddch(buffer_player_y, buffer_player_x, ' ');
		attroff(COLOR_PAIR(200));
		attron(COLOR_PAIR(100));
		mvaddch(player_y, player_x, '@');
		attroff(COLOR_PAIR(100));
		
		render_map_entities(player_y, player_x, map);
	}
	while ((player_move = getch()) != 27);
	
	return 0;
}

int main(void)
{
	initscr();
	
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);
	
	int player_x = 2;
	int player_y = 1;
	
	if (has_colors() == FALSE)
	{
		endwin();
		puts("\nYour terminal does not support color");
		return (1);
	}
	else start_color();
	
	printf("%d", x);
	
	init_color_location_map();
	init_color_entities();
	init_color_service();
	
	render_default_interface(tile_map_0000_deafult, tile_inventory, tile_character_info, tile_actions, tile_world_info);
	render_map_entities(player_y, player_x, tile_map_0000_deafult);
	
	map_player_movement(player_y, player_x, tile_map_0000_deafult);
	
	getch();
	endwin();
	
	return 0;
}