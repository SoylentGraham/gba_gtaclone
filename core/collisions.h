#ifndef CORE_COLLISIONS_H
#define CORE_COLLISIONS_H


#include "gba.h"
#include "types.h"
#include "car.h"



//collision locations
#define COL_NONE 0x0
#define COL_FRONT 0x1
#define COL_BACK 0x2
#define COL_LEFT 0x4
#define COL_RIGHT 0x8

//mask sizes
#define CAR_MASK_COUNT 360/5
#define CAR_MASK_W 16
#define CAR_MASK_H 16
#define TILE_MASK_MODE 0x0



//extern const u16 car_mask [ CAR_MASK_COUNT ] [ CAR_MASK_W * CAR_MASK_H ];
//extern const u16 tile_mask[ TILE_W * TILE_H ]; //all collidable
#define CAR_MASK( n ) ((u8*)car_mask + sizeof(u8)* ( ( (n - (n&1)) *256) + ( 16 * (n&1) ) ) )





u8 check_tiles_around_car( u8 *collision_id_a, u8 *collision_id_b,  s16 *collided_tile_x, s16 *collided_tile_y, a_car *car, u8 radius);



#endif

