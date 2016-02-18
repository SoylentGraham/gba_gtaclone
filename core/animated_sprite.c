#include "gba.h"
#include "types.h"
#include "sprites.h"
#include "animated_sprite.h"


a_sprite_anim sprite_animations[MAX_SPRITES];





void init_anims(void)
{
	u8 i;
	for (i=0; i<MAX_SPRITES; i++)
		end_sprite_anim( &sprite_animations[i] );
}


void process_anims(void)
{
	u8 i;
	for (i=0; i<MAX_SPRITES; i++)
		process_sprite_anim( &sprite_animations[i] );
}


void end_sprite_anim( a_sprite_anim *anim)
{
	anim->sprite=0;
}


void make_sprite_anim( a_sprite_anim *anim, a_sprite *sprite, u8 start_tile, u8 loop_length, u8 looping, u8 frame_delay)
{
	anim->sprite = sprite;
	
	anim->start_tile = start_tile;
	anim->end_tile = start_tile + loop_length; //calc now ,rather than lots of times in the loops
	
	anim->looping = looping;
	anim->paused = false;
	anim->delay_counter = 0;
	anim->frame_delay = frame_delay;

	//in case the current sprite's tile is out of our range make sure the animation will work
	set_sprite_tile(anim->sprite, (u16)start_tile);
}

void un_pause_anim(a_sprite_anim *anim)
{
	anim->paused=false;
}

void force_anim_frame(a_sprite_anim *anim, u8 frame)
{
	u16 new_frame;
	new_frame = anim->start_tile + frame;
	if ( new_frame < anim->start_tile || new_frame > anim->end_tile )
		return;
	anim->paused=true;
	set_sprite_tile(anim->sprite, new_frame);
}


void process_sprite_anim(a_sprite_anim *anim)
{
	u8 current_tile;

	if (!anim->sprite) return; //remove this pointer to disable anim
	//extract the current tile from the actual sprite
	current_tile = get_sprite_tile( anim->sprite );
	
	if (!anim->paused)
		anim->delay_counter++;

	if ( anim->delay_counter >= anim->frame_delay) //next frame
	{
		anim->delay_counter = 0;
		current_tile++;

		if ( current_tile > anim->end_tile ) //got to end of frames
		{
			if (!anim->looping) //stop anim on the last frame
			{
				end_sprite_anim(anim);
				return; //done all i need to seeing as we've finished looping once
			}
			current_tile = anim->start_tile;  //go back to start frame
		}

		//set sprite to the new tile
		set_sprite_tile(anim->sprite, current_tile);
	}
}


