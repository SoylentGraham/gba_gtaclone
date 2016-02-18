#include "gba.h"
#include "collisions.h"
#include "map.h"
#include "../media/misc/car_mask_data.h"

//const u16 car_mask [ CAR_MASK_COUNT ] [ CAR_MASK_W * CAR_MASK_H ];
const u16 tile_mask[ TILE_W * TILE_H ]={15}; //all collidable

extern const u16 car_mask [ CAR_MASK_COUNT ] [ CAR_MASK_W * CAR_MASK_H ];
//extern const u16 tile_mask[ TILE_W * TILE_H ]; //all collidable



u8 mask_on_mask_check( u8 *collision_bit_a ,u8 *collision_bit_b ,
						u8 x_a, u8 y_a, u8 x_b, u8 y_b,	u8 *mask_a, u8 *mask_b,
						u8 w_a, u8 w_b )
{
	*collision_bit_a = mask_a [ XY_ARRAY( x_a, y_a , w_a) ];
	*collision_bit_b = mask_b [ XY_ARRAY( x_b, y_b , w_b) ];
	return ( *collision_bit_a  & *collision_bit_b );
}




//not quick/easy to calc if angle is signed, and itll be done somewhere else anyways
void get_mask_n ( u16 angle, byte *mask_n, byte *mask_mode )
{
	*mask_n = roll_u16( ( angle +2 ) / 5, 0, 71 );
}



// checks collisions for two masks at relative positions. returns tr/fa and fills crash id's (where on mask collided)
u8 check_collisions ( u8 width_a, u8 width_b, u8 height_a, u8 height_b,
			 u8 *mask_a, u8 *mask_b, s16 x_coord_a, s16 y_coord_a, s16 x_coord_b, s16 y_coord_b,
			  u8 *crash_id_a, u8 *crash_id_b ) 
{

	u8 overlap_x_a,overlap_x_b,overlap_y_a,overlap_y_b;
	u8 overlap_width,overlap_height;
	//loop nums
	u8 x,y;
	u8 left,top,width,height; //boundries
	u32 loop_no=0;
	u8 bit_a,bit_b;

	
	//if no chance of overlap, return
	if ( x_coord_a > x_coord_b + width_b ) return false;
	if ( x_coord_a + width_a < x_coord_b ) return false;
	if ( x_coord_b > x_coord_a + width_a ) return false;
	if ( x_coord_b + width_b < x_coord_a ) return false;

	if ( y_coord_a > y_coord_b + height_b ) return false;
	if ( y_coord_a + height_a < y_coord_b ) return false;
	if ( y_coord_b > y_coord_a + height_a ) return false;
	if ( y_coord_b + height_b < y_coord_a ) return false;


	

	//calculate start of overlaps for each mask. 
	//the different versions per a/b mean we dont have lots of ifs later on

//#define COORD_OFF - 1
//#define SIZE_OFF 1
#define COORD_OFF 0
#define SIZE_OFF 0

	if ( x_coord_a < x_coord_b )
	{
		overlap_x_b = 0;
		overlap_x_a = ( x_coord_b - x_coord_a ) + COORD_OFF;
	} else {
		overlap_x_b = ( x_coord_a - x_coord_b ) + COORD_OFF;
		overlap_x_a = 0;
	}


	if ( y_coord_a < y_coord_b )
	{
		overlap_y_b = 0;
		overlap_y_a = ( y_coord_b - y_coord_a ) + COORD_OFF ;
	} else {
		overlap_y_b = ( y_coord_a - y_coord_b ) + COORD_OFF ;
		overlap_y_a = 0;
	}


	//pick smallest width
	if ( width_a < width_b )
		overlap_width = width_a;
	else 
		overlap_width = width_b;
	//offset width to not cover non-existant pixels
	if ( x_coord_a < x_coord_b )
		overlap_width = overlap_width - overlap_x_a;
	else
		overlap_width = overlap_width - overlap_x_b;


	//pick smallest height
	if ( height_a < height_b )
		overlap_height = height_a;
	else overlap_height = height_b;
	//offset height to not cover non-existant pixels
	if ( y_coord_a < y_coord_b )
		overlap_height = overlap_height - overlap_y_a;
	else
		overlap_height = overlap_height - overlap_y_b;
	


	overlap_width+=SIZE_OFF;
	overlap_height+=SIZE_OFF;


	//instead of going left/right/top/down; loop around the mask and go towards the center (more accurate!)
	left = 0 ;
	width = overlap_width ;
	top = 0 ;
	height= overlap_height ;


//	draw_text(0,12,true,"%2d %2d",overlap_x_a ,overlap_y_a);
//	draw_text(0,13,true,"%2d %2d",overlap_x_b,overlap_y_b);
//	draw_text(0,14,true,"%2d %2d",overlap_width,overlap_height);


//basic forx/y version, WORKS!
//	for (y=0; y<overlap_height; y++)
//		for (x=0; x<overlap_width; x++)
//			if ( mask_on_mask_check( crash_id_a ,crash_id_b , x + overlap_x_a, y + overlap_y_a, x + overlap_x_b, y + overlap_y_b, mask_a, mask_b) )
//				return true;




	//loop through the overlap rectangle around in a circle (above) and check each pixel for nonzero's
	//if bit check returns true, the crash_id's are set when calling the func
	while ( top < height && left<width ) //when they overlap or == we've covered that column/row
	{ 
		//loop_no++;
		//draw_text(0,6,true,"%4d",loop_no);

//		draw_text(0,10,true,"%2d %2d -> %2d %2d",top,left,height,width);

		//from top left to top right
		y=top;
		for (x=left; x<width; x++)
		{
			//draw_text(0,10,true,"1 %2d %2d",x,y);
			if ( mask_on_mask_check( crash_id_a ,crash_id_b , x + overlap_x_a, y + overlap_y_a, x + overlap_x_b, y + overlap_y_b, mask_a, mask_b, width_a, width_b) )
				return true;
		}

		//top right to bottom right
		x = width-1;
		for (y=top; y<height; y++)
		{
			//draw_text(0,10,true,"2 %2d %2d",x,y);
			if ( mask_on_mask_check( crash_id_a ,crash_id_b , x + overlap_x_a, y + overlap_y_a, x + overlap_x_b, y + overlap_y_b, mask_a, mask_b, width_a, width_b) )
				return true;
		}


		//bottom right to bottom left
		y = height;
		for (x=width; x>left; x--)
		{
			//draw_text(0,10,true,"3 %2d %2d",x,y);
			if ( mask_on_mask_check( crash_id_a ,crash_id_b , x + overlap_x_a, y + overlap_y_a, x + overlap_x_b, y + overlap_y_b, mask_a, mask_b, width_a, width_b) )
				return true;
		}

		//bottom left to top left
		x = left;
		for (y=height; y>top; y--) //normally >=top but we already did that one at the start
		{
			//draw_text(0,10,true,"4 %2d %2d",x,y);
			if ( mask_on_mask_check( crash_id_a ,crash_id_b , x + overlap_x_a, y + overlap_y_a, x + overlap_x_b, y + overlap_y_b, mask_a, mask_b, width_a, width_b) )
				return true;
		}

		//back to top left again, so move our top-left, and boundries
		left++;
		top++;
		width--;
		height--;
	}





	return false; // didnt collide
}			




void set_collision_car_data( a_car *car, u8 *mask_n, s16 *x, s16 *y )
{
	u16 ang;
	ang = roll_u16( (car->travel_ang>>8) ,0,360) ;
	get_mask_n ( ang, mask_n, 0);
	//after those pixel pos revalations, do i need +8??
	*x = ( car->real_x >> 8 ); 
	*y = ( car->real_y >> 8 );
}


byte check_car_car_collision( byte *collision_id_a, byte *collision_id_b, a_car *car_a, a_car *car_b)
{
	s16 x[2],y[2]; //sprite coords to check
	u8 mask[2];

	set_collision_car_data( car_a, &mask[0], &x[0], &y[0] );
	set_collision_car_data( car_b, &mask[1], &x[1], &y[1] );

	return ( check_collisions ( CAR_W , CAR_W, CAR_H , CAR_H ,
		 CAR_MASK(mask[0]) , CAR_MASK(mask[1]) , x[0] , y[0] , x[1] , y[1], 
		 collision_id_a, collision_id_b ) );
}



//true/false
u8 check_tiles_around_car( u8 *collision_id_a, u8 *collision_id_b,  s16 *collided_tile_x, s16 *collided_tile_y, a_car *car, u8 radius)
{
	s16 x,y;//loop
	s16 s_x,s_y; //sprite coords
	s16 sprite_tile_x;//find closest center tile for checking
	s16 sprite_tile_y;
	u8 mask_n;

	set_collision_car_data( car, &mask_n, &s_x, &s_y );
	
	//sprites position relative to tiles
	//+16 is center. +8 is closer to top left
	sprite_tile_x = ( ( s_x+16 )/8 )-1;
	sprite_tile_y = ( ( s_y+16 )/8 )-1;


	for ( x = sprite_tile_x-radius; x<sprite_tile_x+radius; x++)
		for ( y = sprite_tile_y-radius; y<sprite_tile_y+radius; y++)
			if ( coord_in_map( x/3 , y/3 ) )
				if ( get_building_tile_data(building_map, x, y, MAP_W, MAP_H) )
				{
						if (check_collisions ( CAR_W , TILE_W, CAR_H , TILE_H,
								((u8*)CAR_MASK(mask_n)) , ((u8*)tile_mask) , s_x , s_y , x*TILE_W , y*TILE_H, 
								collision_id_a, collision_id_b ) )
						{
							*collided_tile_x = x;
							*collided_tile_y = y;
							return true;
						}
				}
		


	return false;
}

/*


	//stack is too slow for a radius of 2 or so. probably
	/*
  	two_coords *stack;
	byte stack_n=0;
	byte stack_size= ( ((radius*2)+1) * ((radius*2)+1) ) +1;


 	stack = malloc( sizeof(two_coords) * stack_size );
	memset( stack, -1, stack_size*2 );

	stack[stack_n][X] = s_x ;
	stack[stack_n][Y] = s_y ;

	stack[stack_n+1][X] = -1 ;
	stack[stack_n+1][Y] = -1 ;

	//use stack and go from s_x/s_y outwards
	while (stack[stack_n][X]>-1 && stack[stack_n][Y]>-1) //some coord to test
	{
		x=stack[stack_n][X];
		y=stack[stack_n][Y];

		//test current stack entry
		if ( coord_in_screen(x,y) )
		if ( get_building_tile(building_map,x,y)!=0 )
		{
			collision = check_collisions ( SPRITE_W , TILE_W , SPRITE_H , TILE_H ,
				 car_mask[mask_n] , mask_mode, tile_mask , TILE_MASK_MODE ,
				  s_x , s_y , x*TILE_W , y*TILE_H, collision_id_a, collision_id_b );

			if (collision)
			{
				//handle collision. shunt the car based on impact pos (collision_location)
				*collided_tile_x = x;
				*collided_tile_y = y;
				

				//collision_id_a and collision_id_b are set
				return true;
			}
		}
		
		//add surroudning tiles to stack, as long as its still in the radius
		addtostack( stack_n , stack_size , stack , x+1 , y , radius , s_x , s_y );
		addtostack( stack_n , stack_size , stack , x-1 , y , radius , s_x , s_y );
		addtostack( stack_n , stack_size , stack , x , y+1 , radius , s_x , s_y );
		addtostack( stack_n , stack_size , stack , x , y-1 , radius , s_x , s_y );
		
		//goto next stack entry
		stack_n++;
		if (stack_n>=stack_size) break; //full
	}

	free(stack);
*/

/*
void addtostack(byte current_stack_pos, byte stack_size, two_coords *stack , s16 x , s16 y , byte radius , s16 sprite_x , s16 sprite_y )
{
	//check new x/y arent too far from sprite_x/y
	if ( abs( x - sprite_x ) > radius )	return;
	if ( abs( y - sprite_y ) > radius )	return;

	//check is a valid tile
	if (coord_in_screen(x/3,y/3)) 
		return;

	//find new pos
	while ( stack[current_stack_pos][X] > -1 && stack[current_stack_pos][Y] > -1 )
	{
		if ( stack[current_stack_pos][X] == x && stack[current_stack_pos][Y] == y )
			return; //already in stack

		if (current_stack_pos>=stack_size-1) //dont overload
			return; //full
		current_stack_pos++;
	}

	stack[current_stack_pos][X] = x;
	stack[current_stack_pos][Y] = y;

	stack[current_stack_pos+1][X] = -1;
	stack[current_stack_pos+1][Y] = -1;
}
*/