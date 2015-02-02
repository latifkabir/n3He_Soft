/*
GUI for reading field flux gate using Ncurses
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
#include"Serial.h"
char* CurrentTime(char *strname,int strlen);
bool continuous=true;
bool stop=false;

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


    mvprintw(3, 30, "Welcome to n3He Temperature Monitoring GUI Program ");
    mvprintw(4, 30,"Please wait while temperature monitor is initialized ... ...");
    refresh();

//---------------------------------------------------------
    Serial temp("/dev/ttyUSB0",4800);
    char cTemp[48];
    int zone[12];
   
    if(temp.CheckStatus()!=1)
    {
//-----------------------------------------------------	
	while(continuous && !stop)
	{
	// cout<<"Reading the temperatures ..."<<endl;
	temp.Write("L");
	sleep(1);
	temp.Write("0"); //Passcode manually set to the device
	sleep(1);
	temp.Write("T");
	sleep(1);


	clear();

	    temp.Read(cTemp);
	    for(int j=0;j<12;j++)
	    {
		zone[j]=1000*((int)cTemp[4*j]-48)+100*((int)cTemp[4*j+1]-48)+10*((int)cTemp[4*j+2]-48)+((int)cTemp[4*j+3]-48);
		// cout<<zone[j]<<endl;
	    }


//-----------------------------Header of the Program---------------------
	    mvprintw(2, 25, "----------------------------------------------- ");
	    mvprintw(3, 30, "Welcome to n3He Temperature Monitoring GUI Program ");
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
	    mvprintw(10, 10, "zone 1: %d deg C", zone[0]);
	    mvprintw(11, 10, "zone 2: %d Deg C", zone[1]);
	    mvprintw(12, 10, "zone 3: %d Deg C", zone[2]);
	    mvprintw(10, 55, "zone 4: %d Deg C", zone[3]);
	    mvprintw(11, 55, "zone 5: %d Deg C", zone[4]);
	    mvprintw(12, 55, "zone 6: %d Deg C", zone[5]);
	    // sleep(1);

//-----------Refresh the screen----------------------------
	    refresh();
	    loop++;
	    sleep(5);
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

