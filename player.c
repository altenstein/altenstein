#include<stdio.h>
#include<stdlib.h>
#include<curses.h>
#include<string.h>
#include<pthread.h>
#include<windows.h> // Comment for linux build
#include"render.h"
#include"items.h"

int player_hp_max;
int player_hp;
int player_balance;
int player_level = 0;
int player_exp = 0;
int player_potion_cooldown = 0;

int player_selected_cell = 1;
int player_inventory_limit = 5;
int player_additional_limit = 5;
int player_inventory_used = 0;
int player_spell_book_limit = 3;
int player_spell_book_used = 0;

int buffer_inventory_selected_cell = 1;
int buffer_spell_book_selected_cell = 1;
int buffer_item_to_move;
int buffer_cell_to_move;

int current_inventory_item = 0;

int map_player_movement(int player_y, int player_x, interface_tile map)
{
	bool dev_mode = 0;
	
	if(dev_mode == 1) { player_hp = 4200; player_hp_max = 5000; player_balance = 5000; }
	
	player_additional_limit = player_inventory_limit;
	
	attron(COLOR_PAIR(100));
	mvaddch(player_y, player_x, '@');
	attroff(COLOR_PAIR(100));
	
	render_selected_cell(player_selected_cell, action_6_flag);
	render_inventory();
	render_player_info();
	
	char player_action;
	
	do
	{
		int buffer_player_y = player_y;
		int buffer_player_x = player_x;
		
		if(dev_mode == 1 && player_hp < 1000) player_hp = 1000;
		attron(COLOR_PAIR(004));
		if(dev_mode == 1 ) mvprintw(19, 1, "DEV MODE");
		attroff(COLOR_PAIR(004));
		
		if ((player_action == 'w') && ((player_y - 1) != 0) && (map.tile[player_y - 1][player_x] == ' ')) player_y--;
		else if ((player_action == 's') && ((player_y + 1) != 20) && (map.tile[player_y + 1][player_x] == ' ')) player_y++;
		else if ((player_action == 'a') && ((player_x - 1) != 0) && (map.tile[player_y][player_x - 1] == ' ')) player_x--;
		else if ((player_action == 'd') && ((player_x - 1) != 77) && (map.tile[player_y][player_x + 1] == ' ')) player_x++;
		
		char key_buffer = player_action;
		
		if(action_6_flag == 1){ // Player cell selection
			
			if((key_buffer) == 2 && player_selected_cell + 5 <= player_additional_limit) player_selected_cell += 5;
			else if((key_buffer) == 3) player_selected_cell -= 5;
			else if((key_buffer) == 4) player_selected_cell -= 1;
			else if((key_buffer) == 5 && player_selected_cell + 1 <= player_additional_limit) player_selected_cell += 1;
			
			if(player_selected_cell > player_additional_limit) player_selected_cell = 1;
			else if(player_selected_cell < 1) player_selected_cell = player_additional_limit;
			
		} else if (action_6_flag == 0){
			
			if((key_buffer) == 2  && player_selected_cell + 1 <= player_spell_book_limit) player_selected_cell += 1;
			else if((key_buffer) == 3) player_selected_cell -= 1;
			
			if(player_selected_cell > 10) player_selected_cell = 1;
			else if(player_selected_cell < 1) player_selected_cell = 10;
		}
		
		//int *asd = &player_y;
		//int *bsd = &player_x;
	
		//attron(COLOR_PAIR(001));
		//mvprintw(29, 0, "%p %p", asd, bsd); // Underline information
		//attroff(COLOR_PAIR(001));
		
		if (player_action == '6')
		{ 
			action_6_switch_inv(action_6_mod, map); // Action 6 button
			if(action_6_flag == 1) render_inventory();
		}
		
		else if (player_action == '1' || player_action == 32)
		{
			if (action_1_mod == 1) action_1_special(11, player_y, player_x, map);
		}
		
		else if (player_action == '\n') 
		{
			if(action_6_flag == 1) { action_transfer_inside_inventory(); render_inventory(); }
		}
		
		else if (player_action == '2') 
		{
			if(action_2_mod == 1) { action_2_inventory_usage(3, inventory_cell[buffer_inventory_selected_cell]); }
			render_inventory();
		}
		
		attron(COLOR_PAIR(200));
		mvaddch(buffer_player_y, buffer_player_x, ' ');
		attroff(COLOR_PAIR(200));
		attron(COLOR_PAIR(100));
		mvaddch(player_y, player_x, '@');
		attroff(COLOR_PAIR(100));
		
		render_selected_cell(player_selected_cell, action_6_flag);
		render_map_entities(player_y, player_x, map);
		render_player_info();
	}
	while ((player_action = getch()) != 27);
	
	return 0;
}

int launch(int player_y, int player_x, interface_tile current_map)
{
	int res;
	
	pthread_t thread_render_engine;
	
	void *thread_func_render_engine(void * arg) 
	{
		/* RENDER ENGINE REALIZATION*/
		
		pthread_exit(NULL);
	}
	
	res = pthread_create (&thread_render_engine, NULL, thread_func_render_engine, NULL);
	
	if (res != 0) {
		mvprintw(29, 0, "main error: can't create thread, status = %d\n", res);
		exit(-10);
	}

	res = pthread_detach(thread_render_engine);
	
	if (res != 0) {
		mvprintw(29, 0, "main error: can't detach thread, status = %d\n", res);
		exit(-11);
	}
	
	map_player_movement(player_y, player_x, current_map);
	
	return 0;
}
