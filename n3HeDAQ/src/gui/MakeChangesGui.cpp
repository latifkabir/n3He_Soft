//The Ncurses gui to select DAQ Config  
//Author: Latiful Kabir
//Date:11.9.14
//Version:1.0


#include"Constants.h"
#include"Config.h"
extern "C"
{
#include "libmenu.h"
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
}
bool main_menu=false;
int runlengthgui=RUN_LENGTH;

extern "C"
{
    //Select The REsolution of The DAQ
    int Resolution(int module)
    {
	int resolution=0;
	int x=30,y=25;

    	menu_t *menu = menu_push("SELECT THE RESOLUTION");

    	menu_item_t *i_res1 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_res1, "HI RESOLUTION MODE");
    	menu_item_t *i_res2 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_res2, "LOW RESOLUTION MODE");
    	menu_newitem(menu, MENU_ITEM_LABEL);
    	menu_item_t *i_quit = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_quit, "<--GO BACK");
	menu_item_t *i_main_menu = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_main_menu, "<--GO TO MAIN MENU");

    	menu_item_t *ret = NULL;
    	do {
    	    if(ret == i_res1)
	    {
		mvprintw(y, x,   "Making changes. Please Wait... ...");
		refresh();
		resolution=ChangeRes(module,1);
		if(resolution==1)
		mvprintw(y, x,   "DAQ %d successfully set to Hi Res Mode.",module);
		else
		mvprintw(y, x,   "Unable to Make Changes for DAQ %d",module);
		refresh();
	    }
    	    if(ret == i_res2)
	    {
		mvprintw(y, x,   "Making changes. Please Wait... ...");
		refresh();	
		resolution=ChangeRes(module,0);
		if(resolution==1)
		mvprintw(y, x,   "DAQ %d set to Low Res Mode",module);
		else
		mvprintw(y, x,   "Unable to Make Changes for DAQ %d",module);
		refresh();
	    }
	    if(ret == i_main_menu)
	    {
		main_menu=true;
		break;
	    }

    	    ret = menu_wait(menu, -1);
    	}
    	while(ret != i_quit && ret != MENU_QUIT);

    	menu_pop(menu);

    	return 0;
    }
    //Select The Running MOde of The DAQ
    int Mode(int module)
    {
	int mode=0;
	int mode_value=0;
	int x=30,y=35;

    	menu_t *menu = menu_push("SELECT THE DAQ RUNNING MODE");

    	menu_item_t *i_mode1 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode1, "MODE 1:Trig,Resync,Rising");
    	menu_item_t *i_mode2 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode2, "MODE 2:Trigger Off");
    	menu_item_t *i_mode3 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode3, "MODE 3:Trig,Resync,Falling");
    	menu_item_t *i_mode4 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode4, "MODE 4:Trig,Gated,Rising");
    	menu_item_t *i_mode5 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode5, "MODE 5:Trig,Gated,Falling");
	menu_item_t *i_mode6 = menu_newitem(menu, MENU_ITEM_BUTTON);
	menu_setitem(i_mode6, "MODE 6:Trig,Cont,Rising");

	menu_item_t *i_mode7 = menu_newitem(menu, MENU_ITEM_BUTTON);
	menu_setitem(i_mode7, "MODE 7:Trig,Cont,Falling");

    	menu_newitem(menu, MENU_ITEM_LABEL);
    	menu_item_t *i_quit = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_quit, "<--GO BACK");
	menu_item_t *i_main_menu = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_main_menu, "<--GO TO MAIN MENU");

    	menu_item_t *ret = NULL;
    	do {
	    if(ret!=NULL)
	    {
		mvprintw(y, x,   "Making changes. Please Wait... ...");
		refresh();
	    }
    	    if(ret == i_mode1)
	    {
		mode=ChangeMode(module,1);
		ChangeLength(module,650);
		mode_value=1;
	    }
    	    if(ret == i_mode2)
	    {
		mode=ChangeMode(module,2);
		mode_value=2;
	    }
    	    if(ret == i_mode3)
	    {
		mode=ChangeMode(module,3);
		ChangeLength(module,650);
		mode_value=3;
	    }
    	    if(ret == i_mode4)
	    {
		mode=ChangeMode(module,4);
		mode_value=4;
	    }
    	    if(ret == i_mode5)
	    {
		mode=ChangeMode(module,5);
		mode_value=5;
	    }
    	    if(ret == i_mode6)
	    {
		mode=ChangeMode(module,6);
		mode_value=6;
	    }
	    if(ret == i_mode7)
	    {
		mode=ChangeMode(module,7);
	    }
	    if(ret == i_main_menu)
	    {
		main_menu=true;
		break;
	    }

	    if(ret!=NULL)
	    {
		if(mode==1)
		    mvprintw(y, x,   "DAQ %d successfully set to Mode:%d",module,mode_value);
		else
		    mvprintw(y, x,   "Unable to Make Changes for DAQ %d",module);
		refresh();
	    }
    	    ret = menu_wait(menu, -1);
    	}
    	while(ret != i_quit && ret != MENU_QUIT);

    	menu_pop(menu);

    	return 0;
    }

    //Select The Averaging of the DAQ
    int Averaging(int module)
    {
	int average=0;
	int avg_value=0;
	int x=30,y=30;

    	menu_t *menu = menu_push("SELECT AVERAGING WITH NO DECIMATION");

    	menu_item_t *i_mode1 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode1, "AVERAGE 1 SAMPLE");
    	menu_item_t *i_mode2 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode2, "AVERAGE 2 SAMPLES");
    	menu_item_t *i_mode4 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode4, "AVERAGE 4 SAMPLES");
	menu_item_t *i_mode5 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode5, "AVERAGE 5 SAMPLES");
	menu_item_t *i_mode8 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode8, "AVERAGE 8 SAMPLES");
    
    	menu_item_t *i_mode10 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode10, "AVERAGE 10 SAMPLES");
    	menu_item_t *i_mode12 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode12, "AVERAGE 12 SAMPLES");
	menu_item_t *i_mode15 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode15, "AVERAGE 15 SAMPLES");

	menu_item_t *i_mode16 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode16, "AVERAGE 16 SAMPLES");
	menu_item_t *i_mode20 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode20, "AVERAGE 20 SAMPLES");
	menu_item_t *i_mode25 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode25, "AVERAGE 25 SAMPLES");
	menu_item_t *i_mode30 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode30, "AVERAGE 30 SAMPLES");
	menu_item_t *i_mode32 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode32, "AVERAGE 32 SAMPLES");

    	menu_newitem(menu, MENU_ITEM_LABEL);
    	menu_item_t *i_quit = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_quit, "<--GO BACK");
	menu_item_t *i_main_menu = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_main_menu, "<--GO TO MAIN MENU");

    	menu_item_t *ret = NULL;
    	do {
	    if(ret!=NULL)
	    {
		mvprintw(y, x,   "Making changes. Please Wait... ...");
		refresh();
	    }
    	    if(ret == i_mode1)
	    {
		average=ChangeAveraging(module,1);
		avg_value=1;
	    }
    	    if(ret == i_mode2)
	    {
		average=ChangeAveraging(module,2);
		avg_value=2;
	    }
    	    if(ret == i_mode4)
	    {
		average=ChangeAveraging(module,4);
		avg_value=4;
	    }
    	    if(ret == i_mode5)
	    {
		average=ChangeAveraging(module,5);
		avg_value=5;
	    }
    	    if(ret == i_mode8)
	    {
		average=ChangeAveraging(module,8);	       
		avg_value=8;
	    }
	    if(ret == i_mode10)
	    {
		average=ChangeAveraging(module,10);	       
		avg_value=10;
	    }
    	    if(ret == i_mode12)
	    {
		average=ChangeAveraging(module,12);	       
		avg_value=12;
	    }
    	    if(ret == i_mode15)
	    {
		average=ChangeAveraging(module,15);	       
		avg_value=15;
	    }
    	    if(ret == i_mode16)
	    {
		average=ChangeAveraging(module,16);	       
		avg_value=16;
	    }
    	    if(ret == i_mode20)
	    {
		average=ChangeAveraging(module,20);	       
		avg_value=20;
	    }
    	    if(ret == i_mode25)
	    {
		average=ChangeAveraging(module,25);	       
		avg_value=25;
	    }
    	    if(ret == i_mode30)
	    {
		average=ChangeAveraging(module,30);	       
		avg_value=30;
	    }
    	    if(ret == i_mode32)
	    {
		average=ChangeAveraging(module,32);	       
		avg_value=32;
	    }
	    if(ret == i_main_menu)
	    {
		main_menu=true;
		break;
	    }

	    if(ret!=NULL)
	    {
		if(average==1)
		    mvprintw(y, x,   "DAQ %d successfully changed averaging to %d",module,avg_value);
		else
		    mvprintw(y, x,   "Unable to Make Changes for DAQ %d",module);
		refresh();
	    }
    	    
    	    ret = menu_wait(menu, -1);
    	}
    	while(ret != i_quit && ret != MENU_QUIT);

    	menu_pop(menu);

    	return 0;
    }
    //Select The Decimation of the DAQ
    int Decimation(int module)
    {
	int decimation=0;
	int dec_value=0;
	int x=30,y=30;

    	menu_t *menu = menu_push("SELECT DECIMATION WITH EQUAL AVERAGING");

    	menu_item_t *i_mode1 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode1, "DECIMATE 1 SAMPLE");
    	menu_item_t *i_mode2 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode2, "DECIMATE 2 SAMPLES");
    	menu_item_t *i_mode4 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode4, "DECIMATE 4 SAMPLES");
	menu_item_t *i_mode5 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode5, "DECIMATE 5 SAMPLES");
	menu_item_t *i_mode8 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode8, "DECIMATE 8 SAMPLES");
    
    	menu_item_t *i_mode10 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode10, "DECIMATE 10 SAMPLES");
    	menu_item_t *i_mode12 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode12, "DECIMATE 12 SAMPLES");
	menu_item_t *i_mode15 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode15, "DECIMATE 15 SAMPLES");

	menu_item_t *i_mode16 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode16, "DECIMATE 16 SAMPLES");
	menu_item_t *i_mode20 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode20, "DECIMATE 20 SAMPLES");
	menu_item_t *i_mode25 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode25, "DECIMATE 25 SAMPLES");
	menu_item_t *i_mode30 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode30, "DECIMATE 30 SAMPLES");
	menu_item_t *i_mode32 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode32, "DECIMATE 32 SAMPLES");

    	menu_newitem(menu, MENU_ITEM_LABEL);
    	menu_item_t *i_quit = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_quit, "<--GO BACK");
	menu_item_t *i_main_menu = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_main_menu, "<--GO TO MAIN MENU");

    	menu_item_t *ret = NULL;
    	do {
	    if(ret!=NULL)
	    {
		mvprintw(y, x,   "Making changes. Please Wait... ...");
		refresh();
	    }
    	    if(ret == i_mode1)
	    {
		decimation=ChangeDecimation(module,1);
		dec_value=1;
	    }
    	    if(ret == i_mode2)
	    {
		decimation=ChangeDecimation(module,2);
		dec_value=2;
	    }
    	    if(ret == i_mode4)
	    {
		decimation=ChangeDecimation(module,4);
		dec_value=4;
	    }
    	    if(ret == i_mode5)
	    {
		decimation=ChangeDecimation(module,5);
		dec_value=5;
	    }
    	    if(ret == i_mode8)
	    {
		decimation=ChangeDecimation(module,8);	       
		dec_value=8;
	    }
	    if(ret == i_mode10)
	    {
		decimation=ChangeDecimation(module,10);	       
		dec_value=10;
	    }
    	    if(ret == i_mode12)
	    {
		decimation=ChangeDecimation(module,12);	       
		dec_value=12;
	    }
    	    if(ret == i_mode15)
	    {
		decimation=ChangeDecimation(module,15);	       
		dec_value=15;
	    }
    	    if(ret == i_mode16)
	    {
		decimation=ChangeDecimation(module,16);	       
		dec_value=16;
	    }
    	    if(ret == i_mode20)
	    {
		decimation=ChangeDecimation(module,20);	       
		dec_value=20;
	    }
    	    if(ret == i_mode25)
	    {
		decimation=ChangeDecimation(module,25);	       
		dec_value=25;
	    }
    	    if(ret == i_mode30)
	    {
		decimation=ChangeDecimation(module,30);	       
		dec_value=30;
	    }
    	    if(ret == i_mode32)
	    {
		decimation=ChangeDecimation(module,32);	       
		dec_value=32;
	    }
	    if(ret == i_main_menu)
	    {
		main_menu=true;
		break;
	    }

	    if(ret!=NULL)
	    {
		if(decimation==1)
		    mvprintw(y, x,   "DAQ %d successfully changed Decimation to %d",module,dec_value);
		else
		    mvprintw(y, x,   "Unable to Make Changes for DAQ %d",module);
		refresh();
    	    }
    	    ret = menu_wait(menu, -1);
    	}
    	while(ret != i_quit && ret != MENU_QUIT);

    	menu_pop(menu);

    	return 0;
    }

    //Select The Sample Rate of DAQ
    int Rate(int module)
    {
	int rate=0;
	int rate_value=0;
	int x=20,y=30;

    	menu_t *menu = menu_push("SELECT THE SAMPLE RATE IN KHz");

    	menu_item_t *i_mode1 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode1, "RATE 10KHz in Hi or 20KHz in Low Res");
    	menu_item_t *i_mode1_5 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode1_5, "RATE 15KHz in Hi or 30KHz in Low Res");
    	menu_item_t *i_mode2 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode2, "RATE 20KHz in Hi or 40KHz in Low Res");
	menu_item_t *i_mode2_5 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode2_5, "RATE 25KHz in Hi or 50KHz in Low Res");
	menu_item_t *i_mode3 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode3, "RATE 30KHz in Hi or 60KHz in Low Res");
    
    	menu_item_t *i_mode3_5 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode3_5, "RATE 35KHz in Hi or 70KHz in Low Res");
    	menu_item_t *i_mode4 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode4, "RATE 40KHz in Hi or 80KHz in Low Res");
	menu_item_t *i_mode4_5 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode4_5, "RATE 45KHz in Hi or 90KHz in Low Res");

	menu_item_t *i_mode5 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode5, "RATE 50KHz in Hi or 100KHz in Low Res");
	menu_item_t *i_mode5_2 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode5_2, "RATE 52KHz in Hi or 104KHz in Low Res");

	menu_item_t *i_mode5_5 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode5_5, "RATE 55KHz in Hi or 110KHz in Low Res");
	menu_item_t *i_mode6 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode6, "RATE 60KHz in Hi or 120KHz in Low Res");
	menu_item_t *i_mode6_4 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode6_4, "RATE 64KHz in Hi or 128KHz in Low Res");

    	menu_newitem(menu, MENU_ITEM_LABEL);
    	menu_item_t *i_quit = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_quit, "<--GO BACK");
	menu_item_t *i_main_menu = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_main_menu, "<--GO TO MAIN MENU");

    	menu_item_t *ret = NULL;
    	do {
	    if(ret!=NULL)
	    {
		mvprintw(y, x,   "Making changes. Please Wait... ...");
		refresh();
	    }
    	    if(ret == i_mode1)
	    {
		rate=ChangeRate(module,10);
		rate_value=10;
	    }
    	    if(ret == i_mode1_5)
	    {
		rate=ChangeRate(module,15);
		rate_value=15;
	    }
    	    if(ret == i_mode2)
	    {
		rate=ChangeRate(module,20);
		rate_value=20;
	    }
    	    if(ret == i_mode2_5)
	    {
		rate=ChangeRate(module,25);
		rate_value=25;
	    }
    	    if(ret == i_mode3)
	    {
		rate=ChangeRate(module,30);
		rate_value=30;
	    }
	    if(ret == i_mode3_5)
	    {
		rate=ChangeRate(module,35);
		rate_value=35;
	    }
    	    if(ret == i_mode4)
	    {
		rate=ChangeRate(module,40);
		rate_value=40;
	    }
    	    if(ret == i_mode4_5)
	    {
		rate=ChangeRate(module,45);
		rate_value=45;
	    }
    	    if(ret == i_mode5)
	    {
		rate=ChangeRate(module,50);
		rate_value=50;
	    }
    	    if(ret == i_mode5_2)
	    {
		rate=ChangeRate(module,52);
		rate_value=52;
	    }
	    if(ret == i_mode5_5)
	    {
		rate=ChangeRate(module,55);
		rate_value=55;
	    }
    	    if(ret == i_mode6)
	    {
		rate=ChangeRate(module,60);
		rate_value=60;
	    }
    	    if(ret == i_mode6_4)
	    {
		rate=ChangeRate(module,64);
		rate_value=64;
	    }
	    if(ret == i_main_menu)
	    {
		main_menu=true;
		break;
	    }

	    if(ret!=NULL)
	    {
		if(rate==1)
		{
		    mvprintw(y, x,   "DAQ %d successfully changed rate to %d in Hi res.",module,rate_value);
		    mvprintw(y+1, x, "Or to %d in Low res.",2*rate_value);
		}
		else
		    mvprintw(y, x,   "Unable to Make Changes for DAQ %d",module);
		refresh();
    	    }
    	    ret = menu_wait(menu, -1);
    	}
    	while(ret != i_quit && ret != MENU_QUIT);

    	menu_pop(menu);

    	return 0;
    }

    //Select The Event Length
    int Length(int module)
    {
	int length=0;
	int len_value=0;
	int x=30,y=35;

    	menu_t *menu = menu_push("SELECT NUMBER OF SAMPLES PER EVENT");

    	menu_item_t *i_mode3 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode3, "30 SAMPLES");
    	menu_item_t *i_mode3_5 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode3_5, "35 SAMPLES");
    	menu_item_t *i_mode4 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode4, "40 SAMPLES");
	menu_item_t *i_mode4_5 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode4_5, "45 SAMPLES");
	menu_item_t *i_mode5 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode5, "50 SAMPLES");
    
    	menu_item_t *i_mode5_5 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode5_5, "55 SAMPLES");
    	menu_item_t *i_mode6 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode6, "60 SAMPLES");
	menu_item_t *i_mode10 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode10, "100 SAMPLES");

	menu_item_t *i_mode20 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode20, "200 SAMPLES");
	menu_item_t *i_mode30 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode30, "300 SAMPLES");
	menu_item_t *i_mode40 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode40, "400 SAMPLES");
	menu_item_t *i_mode50 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode50, "500 SAMPLES");
	menu_item_t *i_mode60 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode60, "600 SAMPLES");
	menu_item_t *i_mode65 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode65, "650 SAMPLES");
	menu_item_t *i_mode70 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode70, "700 SAMPLES");
	menu_item_t *i_mode80 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode80, "800 SAMPLES");
	menu_item_t *i_mode90 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode90, "900 SAMPLES");
	menu_item_t *i_mode100 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode100, "1000 SAMPLES");

    	menu_newitem(menu, MENU_ITEM_LABEL);
    	menu_item_t *i_quit = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_quit, "<--GO BACK");
	menu_item_t *i_main_menu = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_main_menu, "<--GO TO MAIN MENU");

    	menu_item_t *ret = NULL;
    	do {
	    if(ret!=NULL)
	    {
		mvprintw(y, x,   "Making changes. Please Wait... ...");
		refresh();
	    }
    	    if(ret == i_mode3)
	    {
		length=ChangeLength(module,30);
		len_value=30;
	    }
    	    if(ret == i_mode3_5)
	    {
		length=ChangeLength(module,35);
		len_value=35;
	    }
    	    if(ret == i_mode4)
	    {	
		length=ChangeLength(module,40);
		len_value=40;
	    }
    	    if(ret == i_mode4_5)
	    {	
		length=ChangeLength(module,45);
		len_value=45;
	    }
    	    if(ret == i_mode5)
	    {	
		length=ChangeLength(module,50);
		len_value=50;
	    }
	    if(ret == i_mode5_5)
	    {
		length=ChangeLength(module,55);
		len_value=55;
	    }
    	    if(ret == i_mode6)
	    {
		length=ChangeLength(module,60);
		len_value=60;
	    }
    	    if(ret == i_mode10)
	    {	
		length=ChangeLength(module,100);
		len_value=100;
	    }
    	    if(ret == i_mode20)
	    {	
		length=ChangeLength(module,200);
		len_value=200;
	    }
    	    if(ret == i_mode30)
	    {	
		length=ChangeLength(module,300);
		len_value=300;
	    }
    	    if(ret == i_mode40)
	    {
		length=ChangeLength(module,400);	       
		len_value=400;
	    }
    	    if(ret == i_mode50)
	    {	
		length=ChangeLength(module,500);
		len_value=500;
	    }
    	    if(ret == i_mode60)
	    {	
		length=ChangeLength(module,600);
		len_value=600;
	    }
	    if(ret == i_mode65)
	    {	
		length=ChangeLength(module,650);
		len_value=650;
	    }
	    if(ret == i_mode70)
	    {	
		length=ChangeLength(module,700);
		len_value=700;
	    }
	    if(ret == i_mode80)
	    {	
		length=ChangeLength(module,800);
		len_value=800;
	    }
	    if(ret == i_mode90)
	    {	
		length=ChangeLength(module,900);
		len_value=900;
	    }
	    if(ret == i_mode100)
	    {	
		length=ChangeLength(module,1000);
		len_value=1000;
	    }
	    if(ret == i_main_menu)
	    {
		main_menu=true;
		break;
	    }
	   
	    if(ret!=NULL)
	    {
		if(length==1)
		    mvprintw(y, x,   "DAQ %d successfully changed event length to %d",module,len_value);
		else
		    mvprintw(y, x,   "Unable to Make Changes for DAQ %d",module);
		refresh();
    	    }
    	    ret = menu_wait(menu, -1);
    	}
    	while(ret != i_quit && ret != MENU_QUIT);

    	menu_pop(menu);

    	return 0;
    }

    //Select the Run Length
    int ChangeRunLength()
    {
	int x=20,y=35;

    	menu_t *menu = menu_push("SELECT THE RUN LENGTH IN MB");

    	menu_item_t *i_mode1 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode1, "5 MB");
    	menu_item_t *i_mode2 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode2, "10 MB");
    	menu_item_t *i_mode3 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode3, "15 MB");
	menu_item_t *i_mode4 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode4, "20 MB");
	menu_item_t *i_mode5 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode5, "50 MB");    
    	menu_item_t *i_mode6 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode6, "100 MB");
    	menu_item_t *i_mode7 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode7, "200 MB");
	menu_item_t *i_mode8 = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_mode8, "300 MB");

    	menu_newitem(menu, MENU_ITEM_LABEL);
    	menu_item_t *i_quit = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_quit, "<--GO BACK");
	menu_item_t *i_main_menu = menu_newitem(menu, MENU_ITEM_BUTTON);
    	menu_setitem(i_main_menu, "<--GO TO MAIN MENU");

    	menu_item_t *ret = NULL;
    	do {
    	    if(ret == i_mode1)
	    {
		runlengthgui=5e6;
	    }
    	    if(ret == i_mode2)
	    {
		runlengthgui=10e6;
	    }
    	    if(ret == i_mode3)
	    {
		runlengthgui=15e6;
	    }
    	    if(ret == i_mode4)
	    {
		runlengthgui=20e6;
	    }
    	    if(ret == i_mode5)
	    {
		runlengthgui=50e6;
	    }
	    if(ret == i_mode6)
	    {
		runlengthgui=100e6;
	    }
    	    if(ret == i_mode7)
	    {
		runlengthgui=200e6;
	    }
    	    if(ret == i_mode8)
	    {
		runlengthgui=300e6;
	    }
	    if(ret == i_main_menu)
	    {
		main_menu=true;
		break;
	    }

	    if(ret!=NULL)
	    {
		mvprintw(y, x,   "Run Length for All DAQ changed to %d Bytes",runlengthgui);
		refresh();
    	    }
    	    ret = menu_wait(menu, -1);
    	}
    	while(ret != i_quit && ret != MENU_QUIT);

    	menu_pop(menu);

    	return 0;
    }


}
