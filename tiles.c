#include<stdio.h>
#include<stdlib.h>
#include<curses.h>
#include"render.h"

int x = 12;

interface_tile tile_map_0000_deafult = {.tile = {
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
	 "ID: 0000-2-1",	// XXXX-... - location id; ...-X-... - map type (world/location/dungeon/house); ...-X - location difficulty (1-3)
	 "TAG: DEFAULT"
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