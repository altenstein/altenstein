#include<stdio.h>
#include<curses.h>
#include<windows.h>
#include"render.h"
#include"items.h"

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
	
	char player_answer_selection;
	
	button_mod = mod/10000;
	item_id = mod - 10000;
	
	// M E S S A G E S
	
	if (action_1_mod == 1) action_1_special(10, current_map_tile);
	else if (action_1_mod == 2) action_1_special(20, current_map_tile);
	else if (action_1_mod == 3) action_1_special(30, current_map_tile);
	else if (action_1_mod == 4) action_1_special(40, current_map_tile);
	else if (action_1_mod == 5) action_1_special(50, current_map_tile);
	
	if (action_2_mod == 1) action_2_inventory_usage(2, inventory_cell[buffer_inventory_selected_cell]);
	
	action_6_switch_inv(0, current_map_tile);
	
	stop_render_flag = 1;
	
	if (msg_id == 1) // Boat deafult location story
	{
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
	
	else if (msg_id == 4) // Create a character	(Enter town try)
	{
		msg_y = 7;
		msg_x = 26;
		
		render_text_frame(msg_y, msg_x, 6, 24);
		render_text_cbc(msg_y + 1, msg_x + 7, "Guardians:");
		render_text_cbc(msg_y + 2, msg_x + 2, "Stand! Who are you?!");
		
		button_y = msg_y + 4;
		button_x_1 = msg_x + 2;
	}
	
	else if (msg_id == 5) // Plate
	{
		if (global_plate_id == 1) // 0003
		{
			msg_y = 8;
			msg_x = 24;
			
			render_text_frame(msg_y, msg_x, 5, 30);
			render_text_cbc(msg_y + 1, msg_x + 2, "Eastern exit from Borovia.");
			
			button_y = msg_y + 3;
			button_x_1 = msg_x + 21;
		}
	}
	
	else if (msg_id == 6) // Create a character	(Talk with Guardian)
	{
		msg_y = 8;
		msg_x = 26;
		
		render_text_frame(msg_y, msg_x, 5, 25);
		render_text_cbc(msg_y + 1, msg_x + 2, "- Hello. Who are you?");
		
		button_y = msg_y + 3;
		button_x_1 = msg_x + 3;
	}
	
	
	
	// B U T T O N S
	
	if (button_mod == 1)
	{
		do
		{
			attron(COLOR_PAIR(002));
			mvprintw(button_y, button_x_1, "[Enter]");
			attroff(COLOR_PAIR(002));
		}
		while((player_answer_selection = getch()) != '\n');
		
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
		
		while((player_answer_selection = getch()) != '\n')
		{
			if (player_answer_selection == 27) { quit_choise_flag = 0; break; }
			
			if ((player_answer_selection == 5 || player_answer_selection == 4) && quit_choise_flag == 0)
			{
				quit_choise_flag = 1;
				
				attron(COLOR_PAIR(002));
				mvprintw(button_y, button_x_1 + 7, "[Yes]");
				attroff(COLOR_PAIR(002));
		
				attron(COLOR_PAIR(001));
				mvprintw(button_y, button_x_1, "[No]");
				attroff(COLOR_PAIR(001));
			}
			
			else if ((player_answer_selection == 5 || player_answer_selection == 4) && quit_choise_flag == 1)
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
	
	
	if (button_mod == 3)
	{
		do
		{
			attron(COLOR_PAIR(002));
			mvprintw(button_y, button_x_1, "[Create a character]");
			attroff(COLOR_PAIR(002));
		}
		while((player_answer_selection = getch()) != '\n');
		
		stop_render_flag = 0;
		
		return 1;
	}
	
	
	return 0;
}
