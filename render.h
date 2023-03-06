#define Potion Зелье

#ifndef RENDER_INCLUDE_GUARDIAN
#define RENDER_INCLUDE_GUARDIAN

// Structures

typedef struct {
	char tile[30][120];
} interface_tile;

// Initialization

int init_color_location_map(void);
int init_color_service(void);
int init_color_entities(void);
int init_actions(void);

// Functions

int launch(interface_tile current_map);

int action_6_switch_inv(int mod, interface_tile map);
int action_1_special(int mod, interface_tile map);
int action_2_inventory_usage(int mod, int item_id);

int map_color_num(char char_for_find_color, int map_type);
int map_player_movement(interface_tile map);

int render_map_entities(interface_tile map);
int render_selected_cell(int selected_cell, int action_6_flag);
int render_default_interface(interface_tile map, interface_tile inventory, interface_tile stats, interface_tile actions, interface_tile world_info);
int render_inventory(void);
int render_structure_chest(int chest_selected_cell, int chest_id);
int render_chest_selected_cell(int chest_selected_cell,int chest_id);
int render_chest_items(int chest_id);
int render_player_info(void);
int render_loaded_location(void);
int render_message(int mod, int msg_id);
int render_text_cbc(int cbc_y, int cbc_x, char cbc_text[]);
int render_text_frame(int frame_y, int frame_x, int frame_height, int frame_width);

// Variables

extern bool dev_mode;
extern bool stop_render_flag;
extern bool quit_cbc_flag;

extern int player_y;
extern int player_x;
extern int player_hp;
extern int player_hp_max;
extern int player_balance;
extern int player_level;
extern int player_exp;
extern int player_potion_cooldown;

extern int player_selected_cell;
extern int player_inventory_limit;
extern int player_additional_limit;
extern int player_inventory_used;
extern int player_spell_book_limit;
extern int player_spell_book_used;

extern int buffer_inventory_selected_cell;
extern int buffer_spell_book_selected_cell;
extern int buffer_item_to_move;
extern int buffer_cell_to_move;
extern int buffer_player_y;
extern int buffer_player_x;	

extern int current_inventory_item;
extern int transfer_inside_inventory_flag;

extern int action_1_mod;
extern int action_2_mod;
extern int action_6_mod;
extern int action_6_flag;

// Tiles

extern interface_tile preload_map_tile;
extern interface_tile current_map_tile;
extern interface_tile current_inventory_tile;

extern interface_tile tile_inventory;
extern interface_tile tile_spell_book;
extern interface_tile tile_chest;
extern interface_tile tile_character_info;
extern interface_tile tile_actions;
extern interface_tile tile_world_info;

// Map tiles

extern interface_tile tile_chargen;

extern interface_tile tile_map_0001_default;
extern interface_tile tile_map_0002_dev;
extern interface_tile tile_map_0003_chargen;

#endif
