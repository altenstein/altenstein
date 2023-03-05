#include<stdio.h>
#include<curses.h>
#include<windows.h>
#include"render.h"

bool quit_cbc_flag;

int render_text_cbc(int cbc_y, int cbc_x, char cbc_text[])
{
	for (int i_cbc = 0; i_cbc < strlen(cbc_text); i_cbc++)
	{
		mvprintw(cbc_y, cbc_x + i_cbc, "%c", cbc_text[i_cbc]);
		
		refresh();
		
		if (quit_cbc_flag == 0) Sleep(50);
	}
	
	return 0;
}
int render_text_frame(int frame_y, int frame_x, int frame_height, int frame_width)
{
	for (int frame_i = 0; frame_i < frame_height; frame_i++)
	{
		for (int frame_j = 0; frame_j < frame_width; frame_j++)
		{
			if (frame_i == 0) mvaddch(frame_y, frame_x + frame_j, '-');
			else if (frame_i == frame_height - 1) mvaddch(frame_y + frame_i, frame_x + frame_j, '-');
			else if (frame_j == 0) mvaddch(frame_y + frame_i, frame_x + frame_j, '|');
			else if (frame_j == frame_width - 1) mvaddch(frame_y + frame_i, frame_x + frame_j, '|');
			else mvaddch(frame_y + frame_i, frame_x + frame_j, ' ');
		}
	}
	
	mvaddch(frame_y, frame_x, '+');
	mvaddch(frame_y, frame_x + frame_width - 1, '+');
	mvaddch(frame_y + frame_height - 1, frame_x + frame_width - 1, '+');
	mvaddch(frame_y + frame_height - 1, frame_x, '+');
	
	refresh();
	
	return 0;
}

int render_message(int mod, int msg_id)
{
	/*
	mod: 10000-100000; mod - 10000 = item_id; mod/10000 = button_mod;
	
	button_mod: 1 - [Enter] only message
	button_mod: 2 - [No] [Yes] dialogue
	button_mod: 3 - [Create a character] only message
	
	return: 0 - No; 1 - Yes / Enter
	*/
	
	int button_y;
	int button_x_1;
	int button_x_2;
	int button_mod;
	
	int msg_y;
	int msg_x;
	
	int item_id;
	
	char player_selected_answer;
	
	button_mod = mod/10000;
	item_id = mod - 10000;
	
	// M E S S A G E S
	
	if (msg_id == 1) // Boat deafult location story
	{
		stop_render_flag = 1;
		
		clear();
		
		msg_y = 11;
		msg_x = 43;
		
		render_text_frame(msg_y, msg_x, 6, 33);
		
		render_text_cbc(msg_y + 1, msg_x + 2, "You went by boat on the river");
		render_text_cbc(msg_y + 2, msg_x + 2, "in search of people.");
		
		button_y = msg_y + 4;
		button_x_1 = msg_x + 24;
	}
	
	else if (msg_id == 2) // Boat deafult location crash
	{
		stop_render_flag = 1;
		
		clear();
		
		msg_y = 11;
		msg_x = 49;
		
		render_text_frame(msg_y, msg_x, 6, 21);
		
		render_text_cbc(msg_y + 1, msg_x + 2, "Your boat crashed");
		render_text_cbc(msg_y + 2, msg_x + 2, "into a tree.");
		
		button_y = msg_y + 4;
		button_x_1 = msg_x + 12;
	}
	
	else if (msg_id == 3) // Quit the game
	{
		msg_y = 8;
		msg_x = 30;
		
		quit_cbc_flag = 1;
		
		render_text_frame(msg_y, msg_x, 5, 18);
		render_text_cbc(msg_y + 1, msg_x + 2, "Quit the game?");
		
		quit_cbc_flag = 0;
		
		button_y = msg_y + 3;
		button_x_1 = msg_x + 3;
	}
	
	else if (msg_id == 4) // Create a character																<---------[TODO]---------<<<
	{
		msg_y = 11;
		msg_x = 49;
		
		render_text_cbc(msg_y + 1, msg_x + 2, "Stand. Who are you?");
		
		button_y = msg_y + 4;
		button_x_1 = msg_x + 12;
	}
	
	// B U T T O N S
	
	if (button_mod == 1)
	{
		attron(COLOR_PAIR(002));
		
		do
		{
			mvprintw(button_y, button_x_1, "[Enter]");
		}
		while((player_selected_answer = getch()) != '\n');
		
		attroff(COLOR_PAIR(002));
		
		stop_render_flag = 0;
		
		return 1;
	}
	
	if (button_mod == 2)
	{
		bool quit_choise_flag = 0;
		
		attron(COLOR_PAIR(001));
		mvprintw(button_y, button_x_1 + 7, "[Yes]");
		attroff(COLOR_PAIR(001));
		
		attron(COLOR_PAIR(002));
		mvprintw(button_y, button_x_1, "[No]");
		attroff(COLOR_PAIR(002));
		
		while((player_selected_answer = getch()) != '\n')
		{
			if (player_selected_answer == 27) { quit_choise_flag = 0; break; }
			
			if ((player_selected_answer == 5 || player_selected_answer == 4) && quit_choise_flag == 0)
			{
				quit_choise_flag = 1;
				
				attron(COLOR_PAIR(002));
				mvprintw(button_y, button_x_1 + 7, "[Yes]");
				attroff(COLOR_PAIR(002));
		
				attron(COLOR_PAIR(001));
				mvprintw(button_y, button_x_1, "[No]");
				attroff(COLOR_PAIR(001));
			}
			
			else if ((player_selected_answer == 5 || player_selected_answer == 4) && quit_choise_flag == 1)
			{
				quit_choise_flag = 0;
				
				attron(COLOR_PAIR(001));
				mvprintw(button_y, button_x_1 + 7, "[Yes]");
				attroff(COLOR_PAIR(001));
		
				attron(COLOR_PAIR(002));
				mvprintw(button_y, button_x_1, "[No]");
				attroff(COLOR_PAIR(002));
			}
		}
		
		refresh();
		
		stop_render_flag = 0;
		
		if (quit_choise_flag == 1) return 1;
		if (quit_choise_flag == 0) return 0;
	}
	
	return 0;
}
