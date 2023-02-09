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
	
	int backpack_cell_1;
	int backpack_cell_2;
	int backpack_cell_3;
	int backpack_cell_4;
	int backpack_cell_5;
	int backpack_cell_6;
	int backpack_cell_7;
	int backpack_cell_8;
	int backpack_cell_9;
	int backpack_cell_10;
} item_backpack;

// Initialization

int init_default_items(void);

// Functions

int item_backpack_create(int id, char name[32], int add_cells);
int render_item(int player_selected_cell, item_tile item);

// Variables

item_backpack backpack[255];

// Cells

int inventory_cell_1;
int inventory_cell_2;
int inventory_cell_3;
int inventory_cell_4;
int inventory_cell_5;
int inventory_cell_6;
int inventory_cell_7;
int inventory_cell_8;
int inventory_cell_9;
int inventory_cell_10;
int inventory_cell_11;
int inventory_cell_12;
int inventory_cell_13;
int inventory_cell_14;
int inventory_cell_15;
int inventory_cell_16;
int inventory_cell_17;
int inventory_cell_18;
int inventory_cell_19;
int inventory_cell_20;
int inventory_cell_21;
int inventory_cell_22;
int inventory_cell_23;
int inventory_cell_24;
int inventory_cell_25;

// Items

extern item_tile tile_backpack;
extern item_tile tile_potion;
extern item_tile tile_bottle;

#endif