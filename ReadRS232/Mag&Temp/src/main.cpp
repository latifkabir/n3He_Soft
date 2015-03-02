/*
GUI for reading & displaying magnetic field from flux gate(A magnetometer from Bartington, Model:Mag-03DAM) & temperature from Omega temperature monitor on Ncurses window
Author: Latiful Kabir
Date: 03/2/15
  
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
#include"n3HeTemp.h"
#include"Constants.h"
#include"currentTime.h"

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

    //  Initialize ncurses 
    if ( (mainwin = initscr()) == NULL ) 
    {
	fprintf(stderr, "Error initializing ncurses.\n");
	exit(EXIT_FAILURE);
    }

    noecho();                  //  Turn off key echoing                
    keypad(mainwin, TRUE);     //  Enable the keypad for non-char keys


    mvprintw(3, 30, "Welcome to n3He Field & Temperature Monitoring GUI Program ");
    mvprintw(4, 30,"Please wait while the devices are initialized ... ...");
    refresh();

//---------------------------------------------------------
    bool signon=false;
    bool continuous=true;
    double field[8]; //Magnetic field value
    int zone[12];    //Temperature values for different zones

    SignOn(signon);
    if(signon)
    {
	FluxGate p(PORT_MAG,BAUD_MAG);  //For Magnetic field 
	Serial temp(PORT_TEMP,BAUD_TEMP); //For temperature

	if(p.CheckStatus()!=1 && temp.CheckStatus()!=1);
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
//-----------Read Magnetic field---------------
		ReadField(p,field);


//-------------Read Temperature-----------------
		ReadTemp(temp,zone);

//--------------Get the current time----------------
		CurrentTime(strname,strlen);

//-----------------------------Header of the Program---------------------
		mvprintw(2, 25, "----------------------------------------------- ");
		mvprintw(3, 30, "Welcome to n3He Field & Temperature monitoring Program ");
		mvprintw(4, 30, "\tTime :%s",strname);
                mvprintw(5, 30, "\t\tLoop number:%d",loop);
		mvaddstr(6, 30, "\tPress Ctrl+C to quit...");               
                mvprintw(7, 30, "report bug to: latifulkabir@uky.edu");
		mvaddstr(8, 25, "-----------------------------------------------");

//----------The divisions of the enrire window------------------------	
		mvaddstr(10, 45, "|");
		mvaddstr(11, 45, "|");
		mvaddstr(12, 45, "|");

		mvaddstr(18, 45, "|");
		mvaddstr(19, 45, "|");
		mvaddstr(20, 45, "|");
	
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

		mvprintw(18, 10, "Temp Zone1: %d Deg C", zone[0]);
		mvprintw(19, 10, "Temp Zone2: %d Deg C", zone[1]);
		mvprintw(20, 10, "Temp Zone3: %d Deg C", zone[2]);
		mvprintw(18, 55, "Temp Zone4: %d Deg C", zone[3]);
		mvprintw(19, 55, "Temp Zone5: %d Deg C", zone[4]);
		mvprintw(20, 55, "Temp Zone6: %d Deg C", zone[5]);

//-----------Refresh the screen----------------------------
		refresh();
                loop++;
	    }
   
	}
    }

    //  Clean up stuff
    delwin(mainwin);
    endwin();
    refresh();
    delete[] strname;
    return EXIT_SUCCESS;
}

