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
}
extern "C"
{

    int Option1()
    {
	menu_t *menu = menu_push("This is the title of main Menu");

	menu_item_t *i_pos = menu_newitem(menu, MENU_ITEM_BUTTON);
	menu_setitem(i_pos,
		     "Put Your Option-1 here");
	menu_item_t *i_comm = menu_newitem(menu, MENU_ITEM_BUTTON);
	menu_setitem(i_comm, "Put Your Option-2 here");
	menu_newitem(menu, MENU_ITEM_LABEL);
	menu_item_t *i_quit = menu_newitem(menu, MENU_ITEM_BUTTON);
	menu_setitem(i_quit, "Quit Current Menu");

	menu_item_t *ret = NULL;
	do {
	    if(ret == i_pos)
		RunSingleGui();
	    if(ret == i_comm)
		RunSingleGui();
      
	    ret = menu_wait(menu, -1);
	}
	while(ret != i_quit && ret != MENU_QUIT);

	menu_pop(menu);

	return 0;

    }
 
    int Option2()
    {

	WINDOW * mainwin;

    
	/*  Initialize ncurses  */

	if ( (mainwin = initscr()) == NULL ) {
	    fprintf(stderr, "Error initialising ncurses.\n");
	    exit(EXIT_FAILURE);
	}


	/*  Display "Hello, world!" in the centre of the
	    screen, call refresh() to show our changes, and
	    sleep() for a few seconds to get the full screen effect  */

	mvaddstr(13, 33, "Hello, world!");
	refresh();
	sleep(3);


	/*  Clean up after ourselves  */

	delwin(mainwin);
	endwin();
	refresh();

	return EXIT_SUCCESS;
    }

    int Menu(void)
    {
	int base_x=25;
	int base_y=0;



	menu_t *menu = menu_push("USE UP/DOWN ARROW TO SELECT");
	menu_setwindow(menu,60,100,12,6);
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


	mvprintw(base_y, base_x+5,   "--------------------------------------------- ");
	mvprintw(base_y+1, base_x+5, "|    Welcome to n3He DAQ Control Program    |");
	mvprintw(base_y+2, base_x+5, "|              version:1.0                  |");
	mvaddstr(base_y+3, base_x+5, "|        Press Ctrl+C to quit...            |");
	mvaddstr(base_y+4, base_x+5, "---------------------------------------------");
	mvaddstr(base_y+5, base_x+5, "     report bug to latifulkabir@uky.edu      ");
	refresh();


	menu_item_t *ret = NULL;
	do {
	    if(ret == i_start)
	    {
		clear();
		RunAllGui();
	    }
	    if(ret == i_single)
	     {
		clear();
		RunSingleGui();
	    }
	    if(ret == i_config)
	    {
		clear();
		RunSingleGui();
	    }
	    if(ret == i_length)
		Option2();
	    ret = menu_wait(menu, -1);
	}
	while(ret != i_quit && ret != MENU_QUIT);

	menu_pop(menu);

	return 0;
    }

}
