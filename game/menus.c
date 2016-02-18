#include "../core/gba.h"
#include "../core/types.h"
#include "../core/core.h"
#include "../core/menu_screens.h"
#include "../core/tile_alloc.h"

#include "menus.h"



extern u16 brightness_mod;
//#define MAX_BRIGHTNESS_MOD (u16)40
//#define MIN_BRIGHTNESS_MOD (u16)0



u8 start_game(u8 *param)
{
	init_game();
	while (game_loop());
}


u8 mod_brightness(u8 *param)
{
	if (*param==1) //inc brightness
	{
		if (brightness_mod >= MAX_BRIGHTNESS_MOD)
			return;
		
		brightness_mod++;
	} else {
	//dec brightness
		if (brightness_mod <= MIN_BRIGHTNESS_MOD)
			return;

		brightness_mod--;
	}
	
	load_tile_palette();
}



void basic_welcome_menu(void)
{
	a_menu_option_text options_text[4];
	a_menu_function options[4];
	u8 result=0;
	u8 param=0;
	
	options[0]=&start_game;
	strcpy(options_text[0],"start game...");
	options[1]=&mod_brightness;
	strcpy(options_text[1],"increase brightness");
	options[2]=&mod_brightness;
	strcpy(options_text[2],"decrease brightness");
	options[3]=null;
	strcpy(options_text[3],"cant select this!");

	result = make_menu( options_text, options , 4, &param , 0);
}