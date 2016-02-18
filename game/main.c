#include "../core/gba.h"
#include "../core/types.h"
#include "../core/core.h"
#include "../core/menu_screens.h"

#include "main.h"




int main(void)
{
	//required init code
	hide_all_backgrounds;

	while (1)
		basic_welcome_menu();
/*
	init_game();
	while (game_loop());
*/
}

