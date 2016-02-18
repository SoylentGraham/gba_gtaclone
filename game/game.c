#include "game.h"
#include "tile_sets.h"

#include "../core/gba.h"
#include "../core/core.h"
#include "../core/types.h"
#include "../core/tile_alloc.h"
#include "../core/map.h"
#include "../core/sprites.h"
#include "../core/keypad.h"
#include "../core/car.h"
#include "../core/camera.h"

extern s16 camera_tiny_x_scroll;
extern s16 camera_tiny_y_scroll;
extern s16 camera_x_scroll;
extern s16 camera_y_scroll;


extern const u8 tile_set_lengths[TILE_TYPE_COUNT] ;
extern a_sprite sprites[MAX_SPRITES];

extern a_car *player_controlled_car;


a_car_type car_types[CAR_TYPE_COUNT];
a_car car_pool[CAR_COUNT];





void init_game(void)
{
	hide_all_backgrounds;

	REG_BLDMOD = TARGET_TOP_BG1 | TARGET_LOW_BG3 | TARGET_LOW_BG2 | TARGET_LOW_OBJ | BLEND_NEG;
	REG_COLEV = BLEND_LEVEL(8);

	clear_current_tiledata(BG);
	clear_current_tiledata(OBJ);
	
	load_tile_palette();
	
	load_tile_set(BG,BUILDING_TILES);
	load_tile_set(BG,BLANK_TILES);
	load_tile_set(BG,ROAD_TILES);
	load_tile_set(BG,SHADOW_TILES);
	load_tile_set(BG,FONT_TILES);

	load_tile_set(OBJ,BUILDING_TILES);
	load_tile_set(OBJ,FONT_TILES);
	load_tile_set(OBJ,CAR_TILES);

	clear_tile_map( BG_TILE(BLANK_TILES), HUD_BACKGROUND);
	clear_tile_map( BG_TILE(BLANK_TILES), ROAD_BACKGROUND);
	clear_tile_map( BG_TILE(BLANK_TILES), ROOFTOP_BACKGROUND);
	clear_tile_map( BG_TILE(BLANK_TILES), SHADOW_BACKGROUND);

	scrollbackground( -2, -2, HUD_BACKGROUND );

	reset_game_tilemap(0,0);
	set_text_boundries( 0, VISIBLE_TILE_H );
	draw_string(0, 0, true, "http://ferk.co.uk/");

	init_anims();
	init_sprites(); //hides em all

	init_sprite( &sprites[0], SIZE_16, CAR_TILES, 0, 3, 0);
	init_sprite( &sprites[1], SIZE_16, CAR_TILES, 0, 3, 1);

	set_car_type( &car_types[0], OBJ_TILE(CAR_TILES,0), 40, 100);
	init_car( &car_pool[0], &sprites[0], &car_types[0] , 2, 2, 0 , COLLIDE_ALL , AI_NONE);
	init_car( &car_pool[1], &sprites[1], &car_types[0] , (17*3), (15*3), 45 , COLLIDE_ALL , AI_NONE );

	bind_player_car(&car_pool[0]);
	unbind_camera();
	bind_camera(&car_pool[0]);

	show_all_backgrounds;
}




u8 game_loop(void)
{
	wait_for_vblank();

	lock_camera();

	update_players_car();

	process_car(&car_pool[0]);
	process_car(&car_pool[1]);

	draw_text(0,VISIBLE_TILE_H-6,true, "%5d" , player_controlled_car->real_speed );
	draw_text(0,VISIBLE_TILE_H-5,true, "%5d" , player_controlled_car->real_x>>8 );
	draw_text(0,VISIBLE_TILE_H-4,true, "%5d" , player_controlled_car->real_y>>8 );
	draw_text(0,VISIBLE_TILE_H-3,true, "%5d" , player_controlled_car->travel_ang>>8 );
	draw_text(0,VISIBLE_TILE_H-2,true, "%5d" , player_controlled_car->movement & ACCEL_FOWARD );

	draw_text(10,VISIBLE_TILE_H-6,true, "%5d" , CAM_SCROLL_TILE_X);
	draw_text(10,VISIBLE_TILE_H-5,true, "%5d" , CAM_SCROLL_TILE_Y);
	
		

	release_camera();
	process_anims();
	update_sprites();
	wait_for_end_of_vblank();
	return true;
}
