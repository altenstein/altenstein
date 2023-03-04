#include<stdio.h>
#include<curses.h>
#include"render.h"

int render_message(int mod, int msg_id)
{
	int button_y;
	int button_x_1;
	int button_x_2;
	int button_mod;
	
	int msg_y;
	int msg_x;
	
	int item_id;
	
	char player_selected_answer;
	
	/*
	mod: 10000-100000; mod - 10000 = item_id; mod/10000 = button_mod;
	
	button_mod: 1 - [Enter] only message
	button_mod: 2 - [No] [Yes] dialogue
	
	return: 0 - No; 1 - Yes / Enter
	*/
	
	button_mod = mod/10000;
	item_id = mod - 10000;
	
	if (msg_id == 1)
	{
		stop_render_flag = 1;
		
		msg_y = 11;
		msg_x = 49;
		
		mvprintw(msg_y, msg_x,     "+-------------------+");
		mvprintw(msg_y + 1, msg_x, "| Your boat crashed |");
		mvprintw(msg_y + 2, msg_x, "| into a tree.      |");
		mvprintw(msg_y + 3, msg_x, "|                   |");
		mvprintw(msg_y + 4, msg_x, "|                   |");
		mvprintw(msg_y + 5, msg_x, "+-------------------+");
		
		button_y = msg_y + 4;
		button_x_1 = msg_x + 12;
	}
	
	if (button_mod == 1)
	{
		attron(COLOR_PAIR(002));
		
		do
		{
			mvprintw(button_y, button_x_1, "[Enter]");
		}
		while((player_selected_answer = getch()) != '\n');
		
		attroff(COLOR_PAIR(002));
	}
	
	stop_render_flag = 0;
	refresh();
	
	return 0;
}
