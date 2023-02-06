#include<stdio.h>
#include<stdlib.h>
#include<curses.h>
#include"render.h"

typedef struct {
	char item[6][6];
} item_tile;

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
	
	interface_tile tile_current_map = {.tile = {
	 "+-----------------------------------[TITLE]------------------------------------+",
	 "|                                                                            WW|",
	 "|            WWW                                                             WW|",
	 "|            WWWW                                                           WW |",
	 "|           WWW                                                    #        WW |",
	 "|                                                                 # #      WW  |",
	 "|                     T             T                            #   #    WW   |",
	 "|   T                          T T                               #   #   WW    |",
	 "|                             T       T                          ## ##  WW     |",
	 "|                           +-------------------+                        WW    |",
	 "|                           |A L T E N S T E I N|                        WW    |",
	 "|                   T    T  +-------------------+                         WW   |",
	 "|     T                      T       T                                    WW   |",
	 "|               T              T T T                                     WW    |",
	 "|                                  T  T                                 WW     |",
	 "|                                T     T                                 WW    |",
	 "|                              T    T T                                  WW    |",
	 "|      T                     T     T                                  WWWWWW   |",
	 "|                             T                                    WWWWWWWWWWWW|",
	 "|                                                                 WWWWWWWWWWWWW|",
	 "+-----------------------+------------------------------------------------------+",
	 "ID: 0000-2-1"	// XXXX-... - location id; ...-X-... - location type (world/location/dungeon/house); ...-X - location difficulty (1-3)
    } };
	
	interface_tile tile_inventory = {.tile = {
	 "------++---[INVENTORY NN/NN]--++------+", // NN/NN - Weight/Weight_limit
	 "1     ||2     ||3     ||4     ||5     |",
	 "      ||      ||      ||      ||      |",
	 "      ||      ||      ||      ||      |",
	 "------++------++------++------++------+",
	 "6     ||7     ||7     ||9     ||10    |",
	 "      ||      ||      ||      ||      |",
	 "      ||      ||      ||      ||      |",
	 "------++------++------++------++------+",
	 "11    ||12    ||13    ||14    ||15    |",
	 "      ||      ||      ||      ||      |",
	 "      ||      ||      ||      ||      |",
	 "------++------++------++------++------+",
	 "16    ||17    ||18    ||19    ||20    |",
	 "      ||      ||      ||      ||      |",
	 "      ||      ||      ||      ||      |",
	 "------++------++------++------++------+",
	 "21    ||22    ||23    ||24    ||25    |",
	 "      ||      ||      ||      ||      |",
	 "      ||      ||      ||      ||      |",
	 "------++-+----++------++------++------+",
	} };

	interface_tile tile_character_info = {.tile = {
	 "|Live:  nnn/nnn  $:n    |",
	 "|1.Strength      +n   nn|",
	 "|2.Dexterity     +n   nn|",
	 "|3.Constitution  +n   nn|",
	 "|4.Intelligence  +n   nn|",
	 "|5.Wisdom        +n   nn|",
	 "|6.Charisma      +n   nn|",
	 "+-----------------------+"
	} };	
	
	interface_tile tile_actions = {.tile = {
	 "                                                                |",
	 "  [1] ACTION-1                   [4] ACTION-4                   |",
	 "                                                                |",
	 "  [2] ACTION-2                   [5] ACTION-5                   |",
	 "                                                                |",
	 "  [3] ACTION-3                   [6] ACTION-6                   |", // Action 6 must switch invetory to spell book & switch attack actions to spells || And back
	 "                                                                |",
	 "----------------------------------------------------------------+"
	} };
	
	interface_tile tile_world_info = {.tile = {
	 "                            |",
	 "                            |",
	 "                            |",
	 "                            |",
	 "                            |",
	 "                            |",
	 "                            |",
	 "---------[Settings]---------+"
	} };
	
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
	
	init_color_location_map();
	init_color_entities();
	init_color_service();
	
	render_default_interface(tile_current_map, tile_inventory, tile_character_info, tile_actions, tile_world_info);
	render_map_entities(player_y, player_x, tile_current_map);
	
	map_player_movement(player_y, player_x, tile_current_map);
	
	getch();

	endwin();
	
	return 0;
}