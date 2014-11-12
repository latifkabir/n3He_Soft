//The Ncurses Menu for GUI mode
//Author: Latiful Kabir
//Date:11.9.14
//Version:1.0


#include"Config.h"
extern "C"
{
#include "libmenu.h"
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
}
extern "C"
{
    int ChangeConfigGui()
    {
	menu_t *menu = menu_push("SELECT OPTION");

	menu_item_t *i_pos = menu_newitem(menu, MENU_ITEM_BUTTON);
	menu_setitem(i_pos,"SET ALL TO n3HE DEFAULT");
	menu_item_t *i_comm = menu_newitem(menu, MENU_ITEM_BUTTON);
	menu_setitem(i_comm, "CUSTOM CHANGE");
	menu_newitem(menu, MENU_ITEM_LABEL);
	menu_item_t *i_quit = menu_newitem(menu, MENU_ITEM_BUTTON);
	menu_setitem(i_quit, "Quit Current Menu");

	menu_item_t *ret = NULL;
	do {
	    if(ret == i_pos)
		//RunSingleGui();
	    if(ret == i_comm)
		//RunSingleGui();
      
	    ret = menu_wait(menu, -1);
	}
	while(ret != i_quit && ret != MENU_QUIT);

	menu_pop(menu);

	return 0;

    }
}

