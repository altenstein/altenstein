#include<stdio.h>
#include<stdlib.h>

int main(void)
{
	char current_map[21][100] = 
	{
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
	};
	
	for(int i = 0; i < 21; i++)
	{
		for(int j = 0; j < 100; j++)
		{
			printf("%c", current_map[i][j]);
		}
		printf("\n");
		system("Color 0C");
	}
	printf("\n\n\n\n\n\n\n\n");
	
	getchar();
	return 0;
}