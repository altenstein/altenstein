typedef struct {
	char tile[30][120];
} interface_tile;

int map_color_num(char char_for_find_color, int map_type);
int init_color_location_map(void);
int init_color_service(void);
int init_color_entities(void);

int render_map_entities(int player_x, int player_y, interface_tile map);
int render_default_interface(interface_tile map, interface_tile inventory, interface_tile stats, interface_tile actions, interface_tile world_info);