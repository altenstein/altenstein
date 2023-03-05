#include<stdio.h>
#include<stdlib.h>
#include<curses.h>
#include"render.h"
	
interface_tile tile_inventory = {.tile = {
	 "----------------[TITLE]---------------+",
	 "      ||      ||      ||      ||      |",
	 "      ||      ||      ||      ||      |",
	 "      ||      ||      ||      ||      |",
	 "------++------++------++------++------|",
	 "      ||      ||      ||      ||      |",
	 "      ||      ||      ||      ||      |",
	 "      ||      ||      ||      ||      |",
	 "------++------++------++------++------|",
	 "      ||      ||      ||      ||      |",
	 "      ||      ||      ||      ||      |",
	 "      ||      ||      ||      ||      |",
	 "------++------++------++------++------|",
	 "      ||      ||      ||      ||      |",
	 "      ||      ||      ||      ||      |",
	 "      ||      ||      ||      ||      |",
	 "------++------++------++------++------|",
	 "      ||      ||      ||      ||      |",
	 "      ||      ||      ||      ||      |",
	 "      ||      ||      ||      ||      |",
	 "---------+----------------------------+"
} };

interface_tile tile_spell_book = {.tile = {
	 "----------------[TITLE]---------------+",
	 "                                      |",
	 "--------------------------------------|",
	 "                                      |",
	 "--------------------------------------|",
	 "                                      |",
	 "--------------------------------------|",
	 "                                      |",
	 "--------------------------------------|",
	 "                                      |",
	 "--------------------------------------|",
	 "                                      |",
	 "--------------------------------------|",
	 "                                      |",
	 "--------------------------------------|",
	 "                                      |",
	 "--------------------------------------|",
	 "                                      |",
	 "--------------------------------------|",
	 "                                      |",
	 "---------+----------------------------+"
} };

interface_tile tile_chest = {.tile = {
	 "+----------------[TITLE]---------------+-------[INFO]------+",
	 "|      ||      ||      ||      ||      |                   |",
	 "|      ||      ||      ||      ||      |                   |",
	 "|      ||      ||      ||      ||      |                   |",
	 "|------++------++------++------++------|                   |",
	 "|      ||      ||      ||      ||      |                   |",
	 "|      ||      ||      ||      ||      |                   |",
	 "|      ||      ||      ||      ||      |                   |",
	 "|------++------++------++------++------|                   |",
	 "|      ||      ||      ||      ||      |                   |",
	 "|      ||      ||      ||      ||      |                   |",
	 "|      ||      ||      ||      ||      |                   |",
	 "+--------------------------------------+-------------------+"
} };

interface_tile tile_character_info = {.tile = {
	 "|Live:    n/n    $:n    |",
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
	 "  [3] ACTION-3                   [6] ACTION-6                   |",
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
	 "----------------------------+"
} };

interface_tile tile_map_0001_default = {.tile = {	// tile_map_ID_TAG
	 "+-----------------------------------[TITLE]------------------------------------+",
	 "|                                                                           WWW|",
	 "|            WWW                                                             WW|",
	 "|            WWWW                                                           WWW|",
	 "|           WWW                                                    #        WWW|",
	 "|                                                                 # #      WWW |",
	 "|                     T             T                            #   #    WWW  |",
	 "|   T                          T T                               #   #   WWW   |",
	 "|                             T       T                          ## ##  WWW    |",
	 "|                           +-------------------+                        WWW   |",
	 "|                           |A L T E N S T E I N|                        WWW   |",
	 "|                   T    T  +-------------------+                         WWW  |",
	 "|     T                      T       T                                    WWW  |",
	 "|               T              T T T                                     WWW   |",
	 "|                                  T  T                                 WWW    |",
	 "|                                T     T                                 WWW   |",
	 "|                              T    T T                                  WWW   |",
	 "|      T                     T     T                                   WWWWWW  |",
	 "|                             T                   WWW                 WWWWWWW  |",
	 "|                                               WWWWWWWW               WWWWWWWW|",
	 "+-----------------------+------------------------------------------------------+",
	 "ID: 0001-2-1",	// XXXX-... - location id; ...-X-... - map type (world/location/dungeon/house); ...-X - location difficulty (1-3)
	 "TAG: DEFAULT"
} };

interface_tile tile_map_0002_dev = {.tile = {	// tile_map_ID_TAG
	 "+-----------------------------------[TITLE]------------------------------------+",
	 "|                                                                              |",
	 "|                                                                              |",
	 "|                                                                              |",
	 "|                                                                              |",
	 "|                                                                              |",
	 "|                                                                              |",
	 "|                                                                              |",
	 "|                                                                              |",
	 "|                                   W  T  #                                    |",
	 "|                                   W  T  #                                    |",
	 "|                                   W  T  #                                    |",
	 "|                                                                              |",
	 "|                                                                              |",
	 "|                                                                              |",
	 "|                                                                              |",
	 "|                                                                              |",
	 "|                                                                              |",
	 "+--------+                                                                     |",
	 "|DEV-LCTN|                                                                     |",
	 "+--------+--------------+------------------------------------------------------+",
	 "ID: 0002-2-1",	// XXXX-... - location id; ...-X-... - map type (world/location/dungeon/house); ...-X - location difficulty (1-3)
	 "TAG: DEV"
} };


interface_tile tile_map_0003_chargen = {.tile = {	// tile_map_ID_TAG
	 "+-----------------------------------[TITLE]------------------------------------+",
	 "| T     T        T     T       T   T                                           |",
	 "|   T       T         T                                                        |",
	 "|T         T     T        T                                                    |",
	 "|      T       T      T        T                                               |",
	 "|  T      T       T                                                            |",
	 "|     #      T                                                                 |",
	 "| # T  #              T    T                                                   |",
	 "|   #   T #      T                                                             |",
	 "|T  #   #    T                                                                 |",
	 "|   ## ##            T                                                         |",
	 "|W                                                                             |",
	 "|WW        T                                                                   |",
	 "|WWW                                                                           |",
	 "| WWWWW                                                                        |",
	 "|  WWWWWW                                                                      |",
	 "|    WWWWW                                                                     |",
	 "|      WWWWW                                                                   |",
	 "|       WWWWW                                                                  |",
	 "|      WWWWW                                                                   |",
	 "+-----------------------+------------------------------------------------------+",
	 "ID: 0003-2-1",	// XXXX-... - location id; ...-X-... - map type (world/location/dungeon/house); ...-X - location difficulty (1-3)
	 "TAG: CHARGEN"
} };
