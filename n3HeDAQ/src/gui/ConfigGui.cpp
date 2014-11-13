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
    int ChangeParam()
    {
	int delete_me=0;

    	menu_t *menu = menu_push("SELECT THE DAQ RUNNING MODE");

    	menu_item_t *i_mode1 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode1, "MODE 1");
    	menu_item_t *i_mode2 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode2, "MODE 2");
    	menu_item_t *i_mode3 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode3, "MODE 3");
    	menu_item_t *i_mode4 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode4, "MODE 4");
    	menu_item_t *i_mode5 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode5, "MODE 5");

    	menu_newitem(menu, MENU_ITEM_LABEL);
    	menu_item_t *i_quit = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_quit, "<--GO BACK");

    	menu_item_t *ret = NULL;
    	do {
    	    if(ret == i_mode1)
    		delete_me=1;

    	    if(ret == i_mode2)
    		delete_me=2;

    	    if(ret == i_mode3)
    		delete_me=3;

    	    if(ret == i_mode4)
    		delete_me=4;

    	    if(ret == i_mode5)
    	        delete_me=5;

    	    ret = menu_wait(menu, -1);
    	}
    	while(ret != i_quit && ret != MENU_QUIT);

    	menu_pop(menu);

    	return 0;
    }


    int CustomConfig(int module)
    {
    	menu_t *menu = menu_push("SELECT THE PARAMETER");

    	menu_item_t *i_rate = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_rate, "SAMPLE RATE");
    	menu_item_t *i_mode = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode, "RUNNING MODE");
    	menu_item_t *i_length = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_length, "RUN LENGTH");
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
		    ChangeParam();
    	        if(ret == i_mode)
		    ChangeParam();
    	        if(ret == i_length)
		    ChangeParam();
    	        if(ret == i_res)
		    ChangeParam();
    	        if(ret == i_avg)
		    ChangeParam();
    	        if(ret == i_dec)
		    ChangeParam();
      
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
    		CustomConfig(21);

    	    if(ret_daq == i_daq22)
    		CustomConfig(22);

    	    if(ret_daq == i_daq23)
    		CustomConfig(23);

    	    if(ret_daq == i_daq24)
    		CustomConfig(24);

    	    if(ret_daq == i_daq30)
    		CustomConfig(30);

    	    ret_daq = menu_wait(menu_daq, -1);
    	}
    	while(ret_daq != i_quit_daq && ret_daq != MENU_QUIT);

    	menu_pop(menu_daq);

    	return 0;
    }

    int ConfigGui()
    {
    	menu_t *menu = menu_push("SELECT OPTION");

    	menu_item_t *i_default = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_default, "SET ALL TO n3HE DEFAULT CONFIG");
	menu_item_t *i_test = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_test, "SET ALL TO TEST CONFIG");

    	menu_item_t *i_custom = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_custom, "CUSTOMIZE EACH MODULE");

    	menu_newitem(menu, MENU_ITEM_LABEL);
    	menu_item_t *i_quit = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_quit, "<-- GO BACK");

    	menu_item_t *ret = NULL;
    	do {
    	    if(ret == i_default)
    	          CustomDaq();
	    if(ret == i_test)
    	          CustomDaq();
    	    if(ret == i_custom)
    		  CustomDaq();
	  
    	    ret = menu_wait(menu, -1);
    	}
    	while(ret != i_quit && ret != MENU_QUIT);

    	menu_pop(menu);

    	return 0;

    }

}

