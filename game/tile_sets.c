#include "tile_sets.h"
#include "../media/gfx/media.h"
//#include "../core/sprites.h"



extern u16 *oam_data;


const u8 tile_set_lengths[TILE_TYPE_COUNT] = {
	sizeof(blank_tile_data) / (sizeof(u16)*64), //blank
	sizeof(road_tile_data) / (sizeof(u16)*64), //road
	sizeof(building_tile_data) / (sizeof(u16)*64), //buildings
	sizeof(shadow_tile_data) / (sizeof(u16)*64), //shadows
	sizeof(font_tile_data) / (sizeof(u16)*64), //font
	sizeof(spotlight_tile_data) / (sizeof(u16)*64), //spotlight
	sizeof(car_sprite_tile_data) / (sizeof(u16)*64), //car
};


const u16 *tile_set_data_addr[TILE_TYPE_COUNT] ={
	blank_tile_data,
	road_tile_data,
	building_tile_data,
	shadow_tile_data,
	font_tile_data,
	spotlight_tile_data,
	car_sprite_tile_data,
};


const u16 *tile_data_addr[2] = {
	((u16*) (REG_TILE_BASE + 0x4000)), ((u16*)(0x6010000)),
};


const u16 *tile_palette_data_addr[2] ={
	gfx_palette, gfx_palette,
};


const u16 *tile_palette_addr[2] = {
	((u16*)(REG_PALETTE_BASE)), ((u16*)0x5000200), 
};
