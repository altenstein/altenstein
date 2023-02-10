#ifndef ITEMS_INCLUDE_GUARDIAN
#define ITEMS_INCLUDE_GUARDIAN

// Structures

typedef struct {
	char item[3][6];
} item_tile;

typedef struct {
	char backpack_name[32];
	int backpack_add_cells;
	int backpack_used;
	
	int backpack_cell[20]; // 20 is the maximum size of a backpack
} item_backpack;

// Initialization

int init_default_items(void);

// Functions

int item_backpack_create(int id, char name[32], int add_cells);
int render_item(int player_selected_cell, item_tile item, int ID);

// Variables

item_backpack backpack[255];
int inventory_cell[25];

// Items

extern item_tile tile_backpack;
extern item_tile tile_potion;
extern item_tile tile_poison;
extern item_tile tile_bottle;

#endif