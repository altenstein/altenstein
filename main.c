#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

typedef struct {
	char tile[29][120];
} interface_tile;

typedef struct {
	char item[6][6];
} item_tile;

interface_tile render_default_interface(interface_tile map, interface_tile inventory, interface_tile stats, interface_tile actions, interface_tile world_info) 
{
    interface_tile D;
    for(int i = 0; i < 21; i++)
	{
		for(int j = 0; j < 80; j++)
		{
			printf("%c", map.tile[i][j]);
		}
		for(int k = 0; k < 39; k++)
		{
			printf("%c", inventory.tile[i][k]);
		}
		printf("\n");
	}
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 25; j++)
		{
			printf("%c", stats.tile[i][j]);
		}
		for(int j = 0; j < 65; j++)
		{
			printf("%c", actions.tile[i][j]);
		}
		for(int j = 0; j < 29; j++)
		{
			printf("%c", world_info.tile[i][j]);
		}
		printf("\n");
	}
	printf("[ACTION] > ");
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
	 "-----------[INVENTORY NN/NN]----------+",
	 "                                      |",
	 "                                      |",
	 "                                      |",
	 "                                      |",
	 "                                      |",
	 "                                      |",
	 "                                      |",
	 "                                      |",
	 "                                      |",
	 "                                      |",
	 "                                      |",
	 "                                      |",
	 "                                      |",
	 "                                      |",
	 "                                      |",
	 "                                      |",
	 "                                      |",
	 "                                      |",
	 "                                      |",
	 "---------+----------------------------+"
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
	 "---------[Settings]---------+"
	} };
	

    render_default_interface(tile_current_map, tile_inventory, tile_character_info, tile_actions, tile_world_info);
	
	getchar();
	
	return 0;
}