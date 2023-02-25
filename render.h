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

int launch(int player_y, int player_x, interface_tile current_map);

int action_6_switch_inv(int mod, interface_tile map);
int action_1_special(int mod, int player_x, int player_y, interface_tile map);
int action_2_inventory_usage(int mod, int item_id);

int map_color_num(char char_for_find_color, int map_type);
int map_player_movement(int player_y, int player_x, interface_tile map);

int render_map_entities(int player_x, int player_y, interface_tile map);
int render_selected_cell(int selected_cell, int action_6_flag);
int render_default_interface(interface_tile map, interface_tile inventory, interface_tile stats, interface_tile actions, interface_tile world_info);
int render_inventory(void);
int render_structure_chest(int chest_selected_cell, int chest_id);
int render_chest_selected_cell(int chest_selected_cell,int chest_id);
int render_chest_items(int chest_id);
int render_player_info(void);

// Variables

bool dev_mode;

int player_hp;
int player_hp_max;
int player_balance;
int player_level;
int player_exp;
int player_potion_cooldown;

int player_selected_cell;
int player_inventory_limit;
int player_additional_limit;
int player_inventory_used;
int player_spell_book_limit;
int player_spell_book_used;

int buffer_inventory_selected_cell;
int buffer_spell_book_selected_cell;
int buffer_item_to_move;
int buffer_cell_to_move;

int current_inventory_item;
int transfer_inside_inventory_flag;

int action_1_mod;
int action_2_mod;
int action_6_mod;
int action_6_flag;

// Tiles

extern interface_tile current_map_tile;
extern interface_tile current_inventory_tile;

extern interface_tile tile_inventory;
extern interface_tile tile_spell_book;
extern interface_tile tile_chest;
extern interface_tile tile_character_info;
extern interface_tile tile_actions;
extern interface_tile tile_world_info;

// Map tiles

extern interface_tile tile_map_0001_default;
extern interface_tile tile_map_0002_dev;

#endif
