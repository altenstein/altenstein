#include<stdio.h>
#include<stdlib.h>


typedef struct {
    char arr[21][100];
} map;

map map_render(map m) {
    map D;
    for(int i = 0; i < 21; i++)
	{
		for(int j = 0; j < 100; j++)
		{
			printf("%c", m.arr[i][j]);
		}
		printf("\n");
		system("Color 0C");
	}
	printf("\n\n\n\n\n\n\n\n");
    return D;
}

int main(void)
{
	map current_map = {.arr = {
	 "###############################################",
	 "#@                                          WW#",
	 "#            WWW                            WW#",
	 "#            WWWW           a              WW #",
	 "#           WWW                   #        WW #",
	 "#                                # #      WW  #",
	 "#                     T         #   #    WW   #",
	 "#   T            f              #  B#   WW    #",
	 "#                               ## ##  WW     #",
	 "#                                       WW    #",
	 "#                                  T    WW    #",
	 "#                   T            T       WW   #",
	 "#     T                       T       T  WW   #",
	 "#               T              T T T    WW    #",
	 "#                                  T  TWW T   #",
	 "#  p                             T     TWW    #",
	 "#                              T    T T WWT   #",
	 "#      T                     T     T WWWWWW   #",
	 "# +                           T   WWWWWWWWWWWW#",
	 "#                                WWWWWWWWWWWWW#",
	 "###############################################"
    } };

    map_render(current_map);
	
	getchar();
	return 0;
}