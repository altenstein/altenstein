#ifndef RENDER_INCLUDE_GUARDIAN
#define RENDER_INCLUDE_GUARDIAN

// Structures

typedef struct {
	char tile[30][120];
} interface_tile;

typedef struct {
	char item[6][6];
} item_tile;

// Initialization

int init_color_location_map(void);
int init_color_service(void);
int init_color_entities(void);
int init_actions(void);

// Functions

int action_6_switch_inv(int mod, interface_tile map);

int map_color_num(char char_for_find_color, int map_type);
int map_player_movement(int player_y, int player_x, interface_tile map);

int render_map_entities(int player_x, int player_y, interface_tile map);
int render_default_interface(interface_tile map, interface_tile inventory, interface_tile stats, interface_tile actions, interface_tile world_info);

// Variables

int player_hp;
int player_hp_max;
int player_balance;

int action_6_mod;

extern interface_tile tile_inventory;
extern interface_tile tile_spell_book;
extern interface_tile tile_character_info;
extern interface_tile tile_actions;
extern interface_tile tile_world_info;

extern interface_tile tile_map_0000_deafult;

#endif
