//The Ncurses Menu for GUI mode
//Author: Latiful Kabir
//Date:11.9.14
//Version:1.0

#include"Constants.h"
extern "C"
{
#include "libmenu.h"
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include"MakeChangesGui.h"
}
extern bool main_menu;
extern int runlengthgui;
extern "C"
{
    int CustomConfig(int module)
    {
    	menu_t *menu = menu_push("SELECT THE PARAMETER");

    	menu_item_t *i_rate = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_rate, "SAMPLE RATE");
    	menu_item_t *i_mode = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode, "RUNNING MODE");
    	menu_item_t *i_length = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_length, "EVENT LENGTH");
    	menu_item_t *i_res = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_res, "RESOLUTION");
    	menu_item_t *i_avg = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_avg, "AVERAGING");
    	menu_item_t *i_dec = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_dec, "DECIMATION");

    	menu_newitem(menu, MENU_ITEM_LABEL);
    	menu_item_t *i_quit = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_quit, "<-- GO BACK");

    	menu_item_t *ret = NULL;
    	do {
	    if(ret == i_rate)
	    {
		Rate(module);
		if(main_menu)
		{
		    break;
		}
	    }	
	    if(ret == i_mode)
	    {   Mode(module);
		if(main_menu)
		{
		    break;
		}
	    }
	    if(ret == i_length)
	    {   Length(module);
		if(main_menu)
		{
		    break;
		}
	    }
	    if(ret == i_res)
	    {
		Resolution(module);
		if(main_menu)
		{
		    break;
		}
	    }
	    if(ret == i_avg)
	    {
		Averaging(module);
		if(main_menu)
		{
		    break;
		}
	    }
	    if(ret == i_dec)
	    {
		Decimation(module);
		if(main_menu)
		{
		    break;
		}
	    }
      
	    ret = menu_wait(menu, -1);
    	  }
    	while(ret != i_quit && ret != MENU_QUIT);

    	menu_pop(menu);

    	return 0;

    }

    int CustomDaq()
    {
    	menu_t *menu_daq = menu_push("SELECT THE DAQ MODULE");

    	menu_item_t *i_daq21 = menu_newitem(menu_daq, MENU_ITEM_BUTTON);
    	menu_setitem(i_daq21, "DAQ 21");
    	menu_item_t *i_daq22 = menu_newitem(menu_daq, MENU_ITEM_BUTTON);
    	menu_setitem(i_daq22, "DAQ 22");
    	menu_item_t *i_daq23 = menu_newitem(menu_daq, MENU_ITEM_BUTTON);
    	menu_setitem(i_daq23, "DAQ 23");
    	menu_item_t *i_daq24 = menu_newitem(menu_daq, MENU_ITEM_BUTTON);
    	menu_setitem(i_daq24, "DAQ 24");
    	menu_item_t *i_daq30 = menu_newitem(menu_daq, MENU_ITEM_BUTTON);
    	menu_setitem(i_daq30, "DAQ 30");

    	menu_newitem(menu_daq, MENU_ITEM_LABEL);
    	menu_item_t *i_quit_daq = menu_newitem(menu_daq, MENU_ITEM_BUTTON);
    	menu_setitem(i_quit_daq, "<-- GO BACK");
   
    	menu_item_t *ret_daq = NULL;
    	do {
    	    if(ret_daq == i_daq21)
	    {
    		CustomConfig(21);
		if(main_menu)
		{
		    break;
		}
	    }
    	    if(ret_daq == i_daq22)
	    {
    		CustomConfig(22);
		if(main_menu)
		{
		    break;
		}
	    }

    	    if(ret_daq == i_daq23)
	    {	CustomConfig(23);
		if(main_menu)
		{
		    break;
		}
	    }

    	    if(ret_daq == i_daq24)
	    {	CustomConfig(24);
		if(main_menu)
		{
		    break;
		}
	    }

    	    if(ret_daq == i_daq30)
	    {
		CustomConfig(30);
		if(main_menu)
		{
		    break;
		}
	    }

	    ret_daq = menu_wait(menu_daq, -1);
    	}
    	while(ret_daq != i_quit_daq && ret_daq != MENU_QUIT);

    	menu_pop(menu_daq);

    	return 0;
    }

    int ConfigGui()
    {
	int x=20,y=25;

    	menu_t *menu = menu_push("SELECT OPTION & HIT ENTER");

    	menu_item_t *i_default = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_default, "SET ALL TO n3HE DEFAULT CONFIG");
	menu_item_t *i_cont = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_cont, "SET ALL TO CONTINUOUS CONFIG");

	menu_item_t *i_test1 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_test1, "SET ALL TO TEST CONFIG-1");
	
	menu_item_t *i_test2 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_test2, "SET ALL TO TEST CONFIG-2");

    	menu_item_t *i_custom = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_custom, "CUSTOMIZE EACH MODULE");

    	menu_newitem(menu, MENU_ITEM_LABEL);
    	menu_item_t *i_quit = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_quit, "<-- GO BACK");

    	menu_item_t *ret = NULL;
    	do {
    	    if(ret == i_default)
	    {
		// CustomDaq();
		mvprintw(y, x,   "Currently this Config is NOT set.Please try later.");
		refresh();
	    }
	    if(ret == i_cont)
	    {
		// CustomDaq();
		mvprintw(y, x,   "Currently this Config is NOT set.Please try later.");
		refresh();
	    }
	    if(ret == i_test1)
	    {
		// CustomDaq();
		mvprintw(y, x,   "Currently this Config is NOT set.Please try later.");
		refresh();
	    }
	    if(ret == i_test2)
	    {
		// CustomDaq();
		mvprintw(y, x,   "Currently this Config is NOT set.Please try later.");
		refresh();
	    }
    	    if(ret == i_custom)
	    {
		CustomDaq();
		if(main_menu)
		{
		    break;
		}
	    }
    	    ret = menu_wait(menu, -1);
    	}
    	while(ret != i_quit && ret != MENU_QUIT);

    	menu_pop(menu);

    	return 0;

    }

    int RunLength()
    {
	int x=30,y=25;

    	menu_t *menu_daq = menu_push("SELECT THE OPTION");
	menu_item_t *i_default = menu_newitem(menu_daq, MENU_ITEM_BUTTON);
    	menu_setitem(i_default, "SET RUN LENGTH to n3He DEFAULT");
    	menu_item_t *i_short = menu_newitem(menu_daq, MENU_ITEM_BUTTON);
    	menu_setitem(i_short, "SET RUN LENGTH TO SHORT");
    	menu_item_t *i_custom = menu_newitem(menu_daq, MENU_ITEM_BUTTON);
    	menu_setitem(i_custom, "SET CUSTOM RUN LENGTH");
    	
    	menu_newitem(menu_daq, MENU_ITEM_LABEL);
    	menu_item_t *i_quit_daq = menu_newitem(menu_daq, MENU_ITEM_BUTTON);
    	menu_setitem(i_quit_daq, "<-- GO BACK");

    	menu_item_t *ret_daq = NULL;
    	do {
    	    if(ret_daq == i_default)
	    {
		runlengthgui=RUN_LENGTH;
		mvprintw(y, x,   "Run Length for All modules set to :%d Bytes",runlengthgui);
		refresh();    	
	    }

    	    if(ret_daq == i_short)
	    {
		runlengthgui=SHORT_RUN_LENGTH;
		mvprintw(y, x,   "Run Length for All modules set to :%d Bytes",runlengthgui);
		refresh();
	    }

    	    if(ret_daq == i_custom)
	    {
		ChangeRunLength();
		if(main_menu)
		{
		    break;
		}
	    }

    	    ret_daq = menu_wait(menu_daq, -1);
    	}
    	while(ret_daq != i_quit_daq && ret_daq != MENU_QUIT);

    	menu_pop(menu_daq);

    	return 0;
    }


}

