#include<stdio.h>
#include<stdlib.h>
#include<curses.h>
#include"render.h"

typedef struct {
	char tile[30][120];
} interface_tile;

typedef struct {
	char item[6][6];
} item_tile;

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
	
	init_pair(002, 10, 0); // Low difficulty
	init_pair(003, 6, 0); // Middle difficulty
	init_pair(004, 4, 0); // High difficulty
	
	return 0;
}

int init_color_entities(void)
{
	init_pair(100, 14, 0); //USER (Default)
	init_pair(101, 4, 0); //Entity (Default)
	
	return 0;
}

int render_map_entities(int player_x, int player_y, interface_tile map)
{
	if(map.tile[21][9] == 0) return 0;
	
	if((map.tile[21][4] == '0') && (map.tile[21][5] == '0') && (map.tile[21][6] == '0') && (map.tile[21][7] == '0'))
	{
		attron(COLOR_PAIR(101));
		mvaddch(7, 68, 'B'); // Boat
		mvaddch(18, 10, 'T'); // Tree with chest
	}
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
	
	if(map.tile[21][11] == 49) attron(COLOR_PAIR(002));
	else if(map.tile[21][11] == 50) attron(COLOR_PAIR(003));
	else if(map.tile[21][11] == 51) attron(COLOR_PAIR(004));

	if(map.tile[21][9] == 49) mvprintw(0, 34, "[WORLD MAP]");
	else if(map.tile[21][9] == 50) mvprintw(0, 33, "[LOCATION MAP]");
	else if(map.tile[21][9] == 51) mvprintw(0, 35, "[DUNGEON]");
	else if(map.tile[21][9] == 52) mvprintw(0, 36, "[HOUSE]");
	
	attroff(COLOR_PAIR(002));
	attroff(COLOR_PAIR(003));
	attroff(COLOR_PAIR(004));

    return 0;
}

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