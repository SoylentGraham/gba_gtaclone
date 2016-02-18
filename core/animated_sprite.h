#ifndef CORE_ANIMATED_SPRITES_H
#define CORE_ANIMATED_SPRITES_H



#include "gba.h"
#include "sprites.h"



typedef struct{
	a_sprite *sprite; //the sprite we apply stuff to and extract stuff from
	u8 start_tile;
	u8 end_tile; //pre-calc'd rather than frame length of anim
	u8 looping; //! stop the anim when we reach our end_tile
	u8 paused; //can pause anim
	u8 frame_delay; //so it doesnt loop incoherantly, we can slow the anim over several frames
	u8 delay_counter; //the counter for ^^^
} a_sprite_anim;




void init_anims(void);
void process_anims(void);

void end_sprite_anim( a_sprite_anim *anim);
void make_sprite_anim( a_sprite_anim *anim, a_sprite *sprite, u8 start_tile, u8 loop_length, u8 looping, u8 frame_delay);
void un_pause_anim(a_sprite_anim *anim);
void force_anim_frame(a_sprite_anim *anim, u8 frame);
void process_sprite_anim(a_sprite_anim *anim);




#endif

