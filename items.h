#ifndef ITEMS_INCLUDE_GUARDIAN
#define ITEMS_INCLUDE_GUARDIAN

// Structures

typedef struct {
	char item[3][6];
} item_tile;

typedef struct {
	char item_name[32];
	char item_description[32];
	char item_description2[32];
	bool item_usable_self;
	bool item_usable_ta; // ta - to another (object/summon)
	bool item_usable; // just usable tag; functional flags ^^^
	

	int item_drop_map_id_1; // X...
	int item_drop_map_id_2; // .X..
	int item_drop_map_id_3; // ..X.
	int item_drop_map_id_4; // ...X
	int item_drop_y;
	int item_drop_x;
	
	int item_cost;
} item_info;

typedef struct {
	char backpack_name[32];
	char backpack_description[32];
	char backpack_description2[32];
	int backpack_add_cells;
	int backpack_used;
	int backpack_cell[20]; // 20 is the maximum size of a backpack
	
	int backpack_drop_map_id_1; // X...
	int backpack_drop_map_id_2; // .X..
	int backpack_drop_map_id_3; // ..X.
	int backpack_drop_map_id_4; // ...X
	int backpack_drop_y;
	int backpack_drop_x;
} item_backpack;

typedef struct {
	char chest_name[64];
	char chest_type[16];
	int chest_cell[16]; // Default chest size
	
	int chest_map_id_1; // X...
	int chest_map_id_2; // .X..
	int chest_map_id_3; // ..X.
	int chest_map_id_4; // ...X
	int chest_y;
	int chest_x;
} structure_chest;

// Initialization

int init_default_items(void);
int init_items_with_info(void);

// Functions

int item_backpack_create(int id, char name[32], char description[32], int add_cells);
int action_structure_usage(int structure_type, int structure_id);
int action_transfer_from_chest(int chest_id, int chest_selected_cell);
int action_transfer_to_chest(int chest_id, int player_selected_cell);
int action_transfer_inside_inventory(void);
int render_item(int selected_cell, item_tile selected_item, int color_map_id, int mod_y, int mod_x);

// Variables

extern item_backpack backpack[255];
extern item_info item_with_info[8192];
extern structure_chest chest[1024];
extern int inventory_cell[25];

// Items

extern item_tile tile_empty;
extern item_tile tile_backpack;
extern item_tile tile_potion;
extern item_tile tile_poison;
extern item_tile tile_bottle;
extern item_tile tile_ale;
extern item_tile tile_money_1;
extern item_tile tile_money_2;
extern item_tile tile_money_3;
extern item_tile tile_money_4;
extern item_tile tile_mug;

// Items usages

int usage_item_potion_heal(int potion_id);

#endif
