//The Ncurses Menu for GUI mode
//Author: Latiful Kabir
//Date:11.9.14
//Version:1.0

#include"TakeRunGui.h"
extern "C"
{
#include "libmenu.h"
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include "ConfigGui.h"
}
extern "C"
{

    int SingleModule()
    {
    	menu_t *menu = menu_push("SELECT THE DAQ");

    	menu_item_t *i_daq21 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_daq21, "RUN DAQ 21");
	menu_item_t *i_daq22 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_daq22, "RUN DAQ 22");
    	menu_item_t *i_daq23 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_daq23, "RUN DAQ 23");
	menu_item_t *i_daq24 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_daq24, "RUN DAQ 24");
	menu_item_t *i_daq30 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_daq30, "RUN DAQ 30");

    	menu_newitem(menu, MENU_ITEM_LABEL);
    	menu_item_t *i_quit = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_quit, "<-- GO BACK");

    	menu_item_t *ret = NULL;
    	do {
    	    if(ret == i_daq21)
		RunSingleGui(21,RUN_LENGTH,RUN_NUMBER);
	    if(ret == i_daq22)
		RunSingleGui(22,RUN_LENGTH,RUN_NUMBER);
    	    if(ret == i_daq23)
		RunSingleGui(23,RUN_LENGTH,RUN_NUMBER);
	    if(ret == i_daq24)
    		RunSingleGui(24,RUN_LENGTH,RUN_NUMBER);
	    if(ret == i_daq30)
		RunSingleGui(30,RUN_LENGTH,RUN_NUMBER);
	  
    	    ret = menu_wait(menu, -1);
    	}
    	while(ret != i_quit && ret != MENU_QUIT);

    	menu_pop(menu);

    	return 0;

    }

    int Menu(void)
    {
	int base_x=25;
	int base_y=0;

	menu_t *menu = menu_push("USE UP/DOWN ARROW TO SELECT");
	menu_setwindow(menu,80,100,10,5);
	menu_item_t *i_start = menu_newitem(menu, MENU_ITEM_BUTTON);
	menu_setitem(i_start,"START THE RUN");
	menu_item_t *i_single = menu_newitem(menu, MENU_ITEM_BUTTON);
	menu_setitem(i_single,"RUN SINGLE MODULE");
	menu_item_t *i_length = menu_newitem(menu, MENU_ITEM_BUTTON);
	menu_setitem(i_length, "CHANGE RUN LENGTH");
	menu_item_t *i_config = menu_newitem(menu, MENU_ITEM_BUTTON);
	menu_setitem(i_config, "CHANGE DAQ CONFIG");

	menu_newitem(menu, MENU_ITEM_LABEL);
	menu_item_t *i_quit = menu_newitem(menu, MENU_ITEM_BUTTON);
	menu_setitem(i_quit, "QUIT");

	mvprintw(base_y, base_x+12,   "--------------------------------------------- ");
	mvprintw(base_y+1, base_x+12, "|    Welcome to n3He DAQ Control Program    |");
	mvprintw(base_y+2, base_x+12, "|              version:1.0                  |");
	mvaddstr(base_y+3, base_x+12, "|    report bug to: latifulkabir@uky.edu    |");
	mvaddstr(base_y+4, base_x+12, "---------------------------------------------");
	refresh();

	menu_item_t *ret = NULL;
	do {
	    if(ret == i_start)
	    {
		RunAllGui();
	    }
	    if(ret == i_single)
	     {
		SingleModule();
	    }
	    if(ret == i_config)
	    {
		ConfigGui();
	    }
	    if(ret == i_length)	
	    {
		ConfigGui();	
	    }
	    ret = menu_wait(menu, -1);
	}
	while(ret != i_quit && ret != MENU_QUIT);

	menu_pop(menu);

	return 0;
    }

}

