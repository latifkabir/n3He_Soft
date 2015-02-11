/*
GUI for reading field flux gate(A magnetometer from Bartington, Model:Mag-03DAM) using Ncurses
Author: Latiful Kabir
Date: 1/2/15
  
*/


#include<stdlib.h>
#include<ctype.h>
#include<curses.h>
#include<unistd.h>
#include<stdio.h>
#include<string>
#include<time.h>
#include<iomanip>
#include"FluxGate.h"
#include"n3HeMag.h"
#include"Constants.h"


char* CurrentTime(char *strname,int strlen);
extern char response;
extern int sleep_time;
extern bool stop;

int main(void) 
{

    WINDOW * mainwin;
    int value;

    int strlen=100;
    char *strname= new char[strlen];
    int loop=0;

    /*  Initialize ncurses  */

    if ( (mainwin = initscr()) == NULL ) 
    {
	fprintf(stderr, "Error initializing ncurses.\n");
	exit(EXIT_FAILURE);
    }

    noecho();                  /*  Turn off key echoing                 */
    keypad(mainwin, TRUE);     /*  Enable the keypad for non-char keys  */


    mvprintw(3, 30, "Welcome to n3He Flux Gate GUI Program ");
    mvprintw(4, 30,"Please wait while Flux Gate is initialized ... ...");
    refresh();

//---------------------------------------------------------
    bool signon=false;
    bool continuous=true;
    double field[8];

    SignOn(signon);
    if(signon)
    {
	FluxGate p(PORT,BAUD);
	if(p.CheckStatus()!=1);
	{

//------------------Null Scan------------------------
	    usleep(2000000);
	    p.Write("\1"); //Polled mode command token
	    usleep(sleep_time);
	    p.Write("\000"); //Channele 0 * 16 in Octal
	    usleep(sleep_time);
	    p.Write("\1"); //Checksum value
	    usleep(2*sleep_time);
	    p.Write("\201");
	    usleep(sleep_time);
	    p.Write("\17"); //Placeholder
	    usleep(sleep_time);
	    p.Write("\220"); //Checksum Value
	    usleep(2*sleep_time);
	    response=p.Read();

            clear();
//-----------------------------------------------------	
	    while(continuous && !stop)
	    {
		ReadField(p,field);

//-----------------------------Header of the Program---------------------
		mvprintw(2, 25, "----------------------------------------------- ");
		mvprintw(3, 30, "Welcome to n3He Flux Gate GUI Program ");
		mvprintw(4, 30, "\tTime :%s",CurrentTime(strname,strlen));
                mvprintw(5, 30, "\t\tLoop number:%d",loop);
		mvaddstr(6, 30, "\tPress Ctrl+C to quit...");               
                mvprintw(7, 30, "report bug to: latifulkabir@uky.edu");
		mvaddstr(8, 25, "-----------------------------------------------");

//----------The divisions of the enrire window------------------------	
		mvaddstr(10, 45, "|");
		mvaddstr(11, 45, "|");
		mvaddstr(12, 45, "|");
	
//--------------------------------------------------------------------


//-------------------------Parameters List------------------------------
		mvprintw(10, 10, "Field X1: %lf Gauss", field[0]);
		mvprintw(11, 10, "Field Y1: %lf Gauss", field[1]);
		mvprintw(12, 10, "Field Z1: %lf Gauss", field[2]);
		mvprintw(14, 30, "Max Range : %lf Gauss", field[6]);
		mvprintw(15, 30, "Offset : %lf Gauss", field[7]);
		mvprintw(10, 55, "Field X2: %lf Gauss", field[3]);
		mvprintw(11, 55, "Field Y2: %lf Gauss", field[4]);
		mvprintw(12, 55, "Field Z2: %lf Gauss", field[5]);
		// sleep(1);

//-----------Refresh the screen----------------------------
		refresh();
                loop++;
	    }
   
	}
    }

    /*  Clean up after ourselves  */

    delwin(mainwin);
    endwin();
    refresh();
    delete[] strname;
    return EXIT_SUCCESS;
}


/*  Struct to hold keycode/keyname information  */



/*  Returns a string describing a character passed to it  */


char* CurrentTime(char *strname,int strlen)
{
	time_t time_now;
	time(&time_now);
	struct tm my_time;
	localtime_r (&time_now,&my_time);
	snprintf(strname,strlen,"%04d-%02d-%02d-%02d-%02d-%02d",my_time.tm_year+1900,my_time.tm_mon+1,my_time.tm_mday,my_time.tm_hour,my_time.tm_min,my_time.tm_sec);
        return strname;
}

