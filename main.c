#include<stdio.h>
#include<stdlib.h>
#include<curses.h>

typedef struct {
	char tile[30][120];
} interface_tile;

typedef struct {
	char item[6][6];
} item_tile;

int map_char_color_num(char char_for_find_color)
{
	if(char_for_find_color == 'W')
		return 201;
	if(char_for_find_color == 'T')
		return 202;
	
	return 200;
}

interface_tile render_default_interface(interface_tile map, interface_tile inventory, interface_tile stats, interface_tile actions, interface_tile world_info) 
{
    interface_tile D;
	int color_for_map_element;
    for(int i = 0; i < 21; i++)
	{
		for(int j = 0; j < 80; j++) //Load current map to interface
		{
			color_for_map_element = map_char_color_num(map.tile[i][j]);
			attron(COLOR_PAIR(color_for_map_element));
			printw("%c", map.tile[i][j]);
			attroff(COLOR_PAIR(color_for_map_element));
		}
		for(int k = 0; k < 39; k++) //Load inventory / spell book to interface
		{
			attron(COLOR_PAIR(2));
			printw("%c", inventory.tile[i][k]);
			attroff(COLOR_PAIR(2));
		}
		printw("\n");
	}
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 25; j++) //Load character stats to interface
		{
			attron(COLOR_PAIR(2));
			printw("%c", stats.tile[i][j]);
			attroff(COLOR_PAIR(2));
		}
		for(int j = 0; j < 65; j++) //Load actions (attack/spells and regular) to interface
		{
			attron(COLOR_PAIR(2));
			printw("%c", actions.tile[i][j]);
			attroff(COLOR_PAIR(2));
		}
		for(int j = 0; j < 29; j++) //Load character stats to interface
		{
			attron(COLOR_PAIR(2));
			printw("%c", world_info.tile[i][j]);
			attroff(COLOR_PAIR(2));
		}
		printw("\n");
	}
    return D;
}

int main(void)
{
	
	interface_tile tile_current_map = {.tile = {
	 "+--------------------------------[LOCATION MAP]--------------------------------+",
	 "|                                                                            WW|",
	 "|            WWW                                                             WW|",
	 "|            WWWW           a                                               WW |",
	 "|           WWW                                                    #        WW |",
	 "|                                                                 # #      WW  |",
	 "|                     T                                          #   #    WW   |",
	 "|   T            f                                               #  B#   WW    |",
	 "|                                                                ## ##  WW     |",
	 "|                                                                        WW    |",
	 "|                                  T                                     WW    |",
	 "|                   T            T                                        WW   |",
	 "|     T                       T       T                                   WW   |",
	 "|               T              T T T                                     WW    |",
	 "|                                  T  T                                 WW     |",
	 "|  p                             T     T                                 WW    |",
	 "|                              T    T T                                  WW    |",
	 "|      T                     T     T                                  WWWWWW   |",
	 "| +                           T                                    WWWWWWWWWWWW|",
	 "|                                                                 WWWWWWWWWWWWW|",
	 "+-----------------------+------------------------------------------------------+"
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
	
	if (has_colors() == FALSE)
	{
		endwin();
		puts("\nYour terminal does not support color");
		return (1);
	}
	
	start_color();
	use_default_colors();
	
	init_pair(1, 13, 11); //USER
	init_pair(2, 8, COLOR_BLACK); // Interface default pair
	init_pair(200, 8, COLOR_BLACK); // Map default pair
	
	init_pair(201, 3, COLOR_BLACK); // Water color
	init_pair(202, 2, COLOR_BLACK); // Tree color
	
	render_default_interface(tile_current_map, tile_inventory, tile_character_info, tile_actions, tile_world_info);
	
	attron(COLOR_PAIR(1));
	mvaddch(3, 3, '@');
	attroff(COLOR_PAIR(1));
	
	getch();

	endwin();
	
	return 0;
}