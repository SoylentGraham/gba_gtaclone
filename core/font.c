#include "gba.h"
#include "types.h"
#include <stdarg.h>

#include "font.h"
#include "tile_alloc.h"



u8 font_higher_limit;
u8 font_lower_limit;


unsigned char alphabet[ALPHABET_LENGTH]=
" abcdefghijklmnopqrstuvwxyz0123456789!?/.,\":$()-";



a_fontchar find_char_raw(char the_char)
{
	u16 l,i;
	a_fontchar result;

	for (l=0; l<ALPHABET_LENGTH; l++) //go through eahc char 
		if ( alphabet[l] == the_char )
		{
			result.char_id=l;
			result.extra_data=0;
			return result;
		}

	result.char_id=0; // ' '
	result.extra_data=0;
	return result;

}

byte get_font_tile(char letter, byte extra_data)
{
	a_fontchar font_char;
	byte tile_pos;

	if ( letter>='A' && letter<='Z' )
		letter+='a' - 'A';

	font_char=find_char_raw(letter);

	if (font_char.char_id==0)
		return ( BG_TILE(BLANK_TILES) );

	return ( font_char.char_id + BG_TILE(FONT_TILES) -1 ); // -1 for space
}









void draw_text(u16 x, u16 y, u8 wrap, char *fmt, ...)
{
	char newstring[30*28];
	va_list	ap;
	u16 x_off,y_off;
	byte tile;
	u16 c;

	if (fmt == NULL) return;

	va_start(ap, fmt);
	    vsprintf(newstring, fmt, ap);
	va_end(ap);

	draw_string(x, y, wrap, newstring);

	return;

	/*
	x_off=x;
	y_off=y;


	for (c=0; c<strlen(newstring); c++)
	{
		tile=get_font_tile( newstring[c], 0);

	//	if (coord_in_screen(x_off, y_off))
	//		if (tile_map[ HUD_BACKGROUND ][( (y_off) *(MAX_W))+ (x_off)] != tile) //only redraw if diff
				draw_tile( x_off, y_off, tile, HUD_BACKGROUND);

		x_off++;
		if (x_off >= 30) //visible across
		{
			if (!wrap) return;
			x_off=0;
			y_off++;
			//if (y_off>=28) return;
		}
	}
	*/

}



void draw_string(u16 x, u16 y, u8 wrap, char *string)
{
	u16 x_off,y_off;
	byte tile;
	u16 c;


	//if ( font_lower_limit-font_higher_limit ==0 )		return;

	x_off=x;
	y_off=y;


	for (c=0; c<strlen(string); c++)
	{
		tile=get_font_tile( string[c], 0);

	//	if (coord_in_screen(x_off, y_off))
	//		if (tile_map[ HUD_BACKGROUND ][( (y_off) *(MAX_W))+ (x_off)] != tile) //only redraw if diff
		if ( y_off >= font_higher_limit && y_off <= font_lower_limit )
				draw_tile( x_off, y_off, tile, HUD_BACKGROUND);

		x_off++;
		if (x_off >= VISIBLE_TILE_W) //visible across
		{
			if (!wrap) return;
			x_off=0;
			y_off++;
			//if (y_off>=28) return;
		}
	}

}


void set_text_boundries( byte higher_limit, byte lower_limit )
{
	u8 line;
	font_higher_limit = higher_limit;
	font_lower_limit = lower_limit;
	//set some limit vars in the font funcs so they dont draw above the top, or below the bottom
	for (line = higher_limit; line<lower_limit; line++)
		clear_tile_map_row( BG_TILE(BLANK_TILES) , HUD_BACKGROUND, line);

}
