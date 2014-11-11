//The Ncurses gui window to show data taking process
//Author: Latiful Kabir
//Date:11.9.14
//Version:1.0

#include<curses.h>
#include<iostream>
#include<fstream>
#include<cstdio>
#include<thread>
#include<stdio.h>
#include<csignal>
#include"Daq.h"
#include"Constants.h"
#include"TakeRun.h"

using namespace std;
int lastrun=0;
int newrun=0; 
bool stop=false;  //Flip if Ctrl+C is pressed


//Routine to run a single DAQ module only 
int RunSingleGui(int module=MODULE,int runlength=RUN_LENGTH,int runNumber=RUN_NUMBER)
{
//---------------------------GUI Code--------------------------------
    WINDOW * mainwin;
    int value;
    int base_x=20;
    int base_y=2;
   
    /*  Initialize ncurses  */

    if ( (mainwin = initscr()) == NULL ) 
    {
	fprintf(stderr, "Error initializing ncurses.\n");
	exit(EXIT_FAILURE);
    }
    //Uncomment if you want border
    // wborder(mainwin, '|', '|', '-', '-', '+', '+', '+', '+');
    noecho();                  /*  Turn off key echoing                 */
    keypad(mainwin, TRUE);     /*  Enable the keypad for non-char keys  */

	mvprintw(base_y, base_x+5,   "--------------------------------------------- ");
	mvprintw(base_y+1, base_x+5, "|    Welcome to n3He DAQ Control Program    |");
	mvprintw(base_y+2, base_x+5, "|              version:1.0                  |");
	mvaddstr(base_y+3, base_x+5, "|        Press Ctrl+C to quit...            |");
	mvaddstr(base_y+4, base_x+5, "---------------------------------------------");
	mvaddstr(base_y+5, base_x+5, "     report bug to latifulkabir@uky.edu      ");
	refresh();
	sleep(10);
//-----------------------------------------------------------

    bool continuous=false; //Continuous or single run
    bool ready=true;  //Start if DAQ ready based on T0
    int counter=0;
    int stime=SLEEP_TIME; //Sleep time in second
    const char *ip;
    const char *port=DAQ_PORT1;

    // signal(SIGINT, signalHandler); //Handle Ctrl+C Signal

    switch(module)
    {
    case 21:
    {
	ip=DAQ21_IP;
	break;
    }
    case 22:
    {
	ip=DAQ22_IP;
	break;
    }
    case 23:
    {
	ip=DAQ23_IP;
	break;
    }

    case 24:
    {
	ip=DAQ24_IP;
	break;
    }
    default:
    {
	ip=DAQ21_IP;
    }
    }

    if(runNumber==0)
    {
	continuous=true;
    }

    // Sync(true,true); //Enable the Trigger
    while(!stop && (continuous || (counter <runNumber)))
    {

         if(ready)
         {
 	      Daq daq(ip,port,module,runlength);
	      if(!daq.CheckStatus())
	      {
	          RunList(true);
		  time_t time_now;
		  time(&time_now);

		  mvprintw(base_y+8, base_x, "CURRENT RUN STATUS:");
		  refresh();

		  mvprintw(base_y+10, base_x, "Run Number :%d",newrun);
		  mvprintw(base_y+10, base_x+20, "\tStarted:%s",ctime(&time_now));
		  refresh();
		  mvprintw(base_y+12, base_x, "\t\tRun %d in progress ...\t\t\t", newrun);
		  mvprintw(base_y+14, base_x, "Progress:    ", newrun);

		  refresh();

		  mvprintw(base_y+15, base_x, "                                                       ");
		  refresh();

		  mvprintw(base_y+15, base_x, "                                                       ");
		  refresh();
		 
	          daq.SaveData(true);
		  if(daq.GetFileSize()<daq.filesize)
		  {
		      mvprintw(base_y+12, base_x, "\nPROBLEM WITH MODULES , DID NOT RECEIVE REQUESTED FILE SIZE");
		      refresh();
		      sleep(5);
		      break;
		  }
		  mvprintw(base_y+17, base_x, "                                                        ");
		  refresh();

		  mvprintw(base_y+22, base_x, "LAST RUN STATUS:");
		 
	          if(Rename(newrun,module,true))
		  {
		      mvprintw(base_y+24, base_x, "Data Files for run number %d  have been renamed successfully.",newrun);
		  }
		  else
		  {
		      mvprintw(base_y+24, base_x, "Problem renaming data files for run number %d",newrun);		 
		  }
		 
		  mvprintw(base_y+25, base_x, "Phew!!! Done with run number : %d", newrun);
		  refresh();
		  mvprintw(base_y+12, base_x, "\t\tNow initializing run number %d ... ... ", newrun+1);
		  refresh();
               }
	       else
               {
	           break;
	       }
         }
 
         if(!continuous)
         {
             counter=counter+1;
         }
	 // Sync(false,true); //Disable the Trigger
	 sleep(20);
    }    
//-------------------------GUI Code-----------------------------
    delwin(mainwin);
    endwin();
    refresh();
    return EXIT_SUCCESS;

//-------------------------------------------------------------

}


//Running all the DAQ module
int RunAllGui (int runlength=RUN_LENGTH,int runNumber=RUN_NUMBER)
{
//---------------------------GUI Code--------------------------------
    WINDOW * mainwin;
    int value;
    int base_x=20;
    int base_y=2;
   
    /*  Initialize ncurses  */

    if ( (mainwin = initscr()) == NULL ) 
    {
	fprintf(stderr, "Error initializing ncurses.\n");
	exit(EXIT_FAILURE);
    }
    //Uncomment if you want border
    // wborder(mainwin, '|', '|', '-', '-', '+', '+', '+', '+');
    noecho();                  /*  Turn off key echoing                 */
    keypad(mainwin, TRUE);     /*  Enable the keypad for non-char keys  */

    mvprintw(base_y, base_x+5,   "--------------------------------------------- ");
    mvprintw(base_y+1, base_x+5, "|    Welcome to n3He DAQ Control Program    |");
    mvprintw(base_y+2, base_x+5, "|              version:1.0                  |");
    mvaddstr(base_y+3, base_x+5, "|        Press Ctrl+C to quit...            |");
    mvaddstr(base_y+4, base_x+5, "---------------------------------------------");
    mvaddstr(base_y+5, base_x+5, "     report bug to latifulkabir@uky.edu      ");
    refresh();
    sleep(10);
//-----------------------------------------------------------


    bool continuous=false; //Continuous or single run
    bool ready=true;  //Start if DAQ ready based on T0
    int counter=0;
    int stime=5; //Sleep time in second

    signal(SIGINT, signalHandler); //Handle Ctrl+C Signal  


    if(runNumber==0)
    {
	continuous=true;
    }

    Sync(true,true); //Enable the Trigger
    while(!stop && (continuous || (counter <runNumber)))
    {
	if(ready)
	{
	    Daq daq21(DAQ21_IP,DAQ_PORT1,DAQ21,runlength);
	    Daq daq22(DAQ22_IP,DAQ_PORT1,DAQ22,runlength);
	    Daq daq23(DAQ23_IP,DAQ_PORT1,DAQ23,runlength);
	    Daq daq24(DAQ24_IP,DAQ_PORT1,DAQ24,runlength);
	    Daq daq30(DAQ30_IP,DAQ_PORT1,DAQ30,runlength);

	    if(!daq21.CheckStatus() && !daq22.CheckStatus() && !daq23.CheckStatus() && !daq24.CheckStatus() && !daq30.CheckStatus())
	    {
		RunList(true);
		time_t time_now;
		time(&time_now);

		mvprintw(base_y+8, base_x, "CURRENT RUN STATUS:");
		refresh();

		mvprintw(base_y+10, base_x, "Run Number :%d",newrun);
		mvprintw(base_y+10, base_x+20, "\tStarted:%s",ctime(&time_now));
		refresh();
		mvprintw(base_y+12, base_x, "\t\tRun %d in progress ...\t\t\t", newrun);
		mvprintw(base_y+14, base_x, "Progress:    ", newrun);

		refresh();

		mvprintw(base_y+15, base_x, "                                                       ");
		refresh();

		mvprintw(base_y+15, base_x, "                                                       ");
		refresh();

		thread t21(&Daq::SaveData,&daq21,true);
		thread t22(&Daq::SaveData,&daq22,false);
		thread t23(&Daq::SaveData,&daq23,false);
		thread t24(&Daq::SaveData,&daq24,false);
		thread t30(&Daq::SaveData,&daq30,false);

		t21.join();
		t22.join();
		t23.join();
		t24.join();
		t30.join();

		if(daq21.GetFileSize()<daq21.filesize || daq22.GetFileSize()<daq22.filesize || daq23.GetFileSize()<daq23.filesize ||daq24.GetFileSize()<daq24.filesize ||daq30.GetFileSize()<daq30.filesize)
		{
		    mvprintw(base_y+12, base_x, "\nPROBLEM WITH MODULES , DID NOT RECEIVE REQUESTED FILE SIZE");
		    refresh();
		    sleep(5);
		    break;
		}
		  mvprintw(base_y+17, base_x, "                                                        ");
		  refresh();

		  mvprintw(base_y+22, base_x, "LAST RUN STATUS:");
		 
	          if(Rename(newrun,DAQ21,true) && Rename(newrun,DAQ22,true) && Rename(newrun,DAQ23,true) && Rename(newrun,DAQ24,true) && Rename(newrun,DAQ30,true))
		  {
		      mvprintw(base_y+24, base_x, "Data Files for run number %d  have been renamed successfully.",newrun);
		  }
		  else
		  {
		      mvprintw(base_y+24, base_x, "Problem renaming data files for run number %d",newrun);		 
		  }

		  mvprintw(base_y+25, base_x, "Phew!!! Done with run number : %d", newrun);
		  refresh();
		  mvprintw(base_y+12, base_x, "\t\tNow initializing run number %d ... ... ", newrun+1);
		  refresh();

	    }
	    else
	    {
		break;
	    }
	}
 
	if(!continuous)
	{
	    counter=counter+1;
	}
    }
    Sync(false,true);//Disable the trigger
    sleep(20);
//-------------------------GUI Code-----------------------------
    delwin(mainwin);
    endwin();
    refresh();
    return EXIT_SUCCESS;

//-------------------------------------------------------------
      
}
