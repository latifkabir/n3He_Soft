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
#include"ProcessData.h"

using namespace std;
int lastrun=0;
int newrun=0; 
bool stop=false;  //Flip if Ctrl+C is pressed

int base_x2=20;
int base_y2=12;

void signalHandlerGui( int signum )  //Handle Ctrl+C Signal
{
	stop=true;		  
}

void HandleWinChange( int signum )  //Handle Window size change
{
    refresh();		  
}

//Routine to run a single DAQ module only 
int RunSingleGui(int module=MODULE,int runlength=RUN_LENGTH,int runNumber=RUN_NUMBER)
{
    stop=false;
    bool continuous=false; //Continuous or single run
    bool ready=true;  //Start if DAQ ready based on T0
    int counter=0;
    int stime=SLEEP_TIME; //Sleep time in second
    int trig=-1;
    double tol=0.99; //Tolerance
    const char *ip;
    const char *port=DAQ_PORT1;

    signal(SIGINT, signalHandlerGui); //Handle Ctrl+C Signal
    signal(SIGWINCH, &HandleWinChange); //Handle Window size change

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
    case 30:
    {
	ip=DAQ30_IP;
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

    while(!stop && (continuous || (counter <runNumber)))
    {

         if(ready)
         {
	     // if(has_colors() && COLOR_PAIRS >= 13)
	     // {
	     // 	 init_pair(2,COLOR_YELLOW,COLOR_BLACK);
	     // 	 color_set(2, NULL);
	     // }
	    
	     mvprintw(base_y2+7, base_x2, "----------------------------RUN DISPLAY----------------------------");	  
	     mvprintw(base_y2+24, base_x2, "-------------------------------------------------------------------");
	     mvprintw(base_y2+25, base_x2, "Note to users:");
	     mvprintw(base_y2+26, base_x2, "1. Press Ctrl+C if this would be the last run. Wait to finish");
	     mvprintw(base_y2+27, base_x2, "2. GUI Mode requires keeping window size as it is.");
	     mvprintw(base_y2+28, base_x2, "3. Resizing window will destroy the display and run.");

	     mvprintw(base_y2+8, base_x2, "Current Run Status:");
	     refresh();
		 
	     trig=Sync(false,true);//Disable the trigger 
	     sleep(1);  
	     if(trig==0)
	     {
		 mvprintw(base_y2+9, base_x2, "Trigger: Off");
	     }
	     else
	     {
		 mvprintw(base_y2+9, base_x2, "Trigger: Error");
	     }
	     refresh();

	     Daq daq(ip,port,module,runlength);
	     if(!daq.CheckStatus())
	     {
	          RunList(true);
		  time_t time_now;
		  time(&time_now);

		  mvprintw(base_y2+10, base_x2, "Run Number :%d",newrun);
		  mvprintw(base_y2+10, base_x2+30, "\tStarted:%s",ctime(&time_now));
		  refresh();
		  mvprintw(base_y2+12, base_x2, "\t\tRun %d in progress ...\t\t\t", newrun);
		  mvprintw(base_y2+14, base_x2, "Progress:    ", newrun);

		  refresh();

		  trig=Sync(true,true);//Enable the trigger    
		  if(trig==1)
		  {
		      mvprintw(base_y2+9, base_x2, "Trigger: On ");
		  }
		  else
		  { 
		      mvprintw(base_y2+9, base_x2, "Trigger: Error ");
		  }		  
		  refresh();
		  mvprintw(base_y2+15, base_x2, "                                                       ");
		  mvprintw(base_y2+15, base_x2, "                                                       ");
		  refresh();

		  daq.SaveData(true);
		  if(daq.GetFileSize()<tol*daq.filesize)
		  {
		      mvprintw(base_y2+8, base_x2+21, "PROBLEM WITH MODULES ,INCORRECT FILE SIZE");
		      refresh();
		      sleep(5);
		      break;
		  }
		  mvprintw(base_y2+17, base_x2, "                                                        ");
		  refresh();

		  mvprintw(base_y2+19, base_x2, "Last Run Status:");
		 
	          if(Rename(newrun,module,true)==1)
		  {
		      mvprintw(base_y2+20, base_x2, "Data Files for run number %d  have been renamed successfully.",newrun);
		  }
		  else
		  {
		      mvprintw(base_y2+20, base_x2, "Problem renaming data files for run number %d",newrun);		 
		  }
		 
		  mvprintw(base_y2+21, base_x2, "Phew!!! Done with run number : %d", newrun);
		  refresh();
		  if(!stop)
		      mvprintw(base_y2+12, base_x2, "\t\tNow initializing run number %d ... ... ", newrun+1);
		  else
		      mvprintw(base_y2+12, base_x2, "\t\t\tFinished Data Taking Process.");
		  refresh();
		  
               }
	       else
               {
		   mvprintw(base_y2+8, base_x2+20, "DAQ %d is NOT Connected",module);
		   refresh();
	           break;
	       }
         }
 
         if(!continuous)
         {
             counter=counter+1;
         }
    }    

}


//Running all the DAQ module
int RunAllGui (int runlength=RUN_LENGTH,int runNumber=RUN_NUMBER)
{
    stop=false;
    bool continuous=false; //Continuous or single run
    bool ready=true;  //Start if DAQ ready based on T0
    int counter=0;
    int stime=5; //Sleep time in second
    int trig=-1;
    double tol=0.99; //Tolerance

    signal(SIGINT, signalHandlerGui); //Handle Ctrl+C Signal  
    signal(SIGWINCH, &HandleWinChange); //Handle Window size change

    if(runNumber==0)
    {
	continuous=true;
    }

    while(!stop && (continuous || (counter <runNumber)))
    {
	if(ready)
	{
	    // if( has_colors() && COLOR_PAIRS >= 13 )
	    // {
	    // 	init_pair(2,COLOR_YELLOW,COLOR_BLACK);
	    // 	color_set(2, NULL);
	    // }
	    
	    mvprintw(base_y2+7, base_x2, "----------------------------RUN DISPLAY----------------------------");
	    mvprintw(base_y2+24, base_x2, "-------------------------------------------------------------------");
	    mvprintw(base_y2+25, base_x2, "Note to users:");
	    mvprintw(base_y2+26, base_x2, "1. Press Ctrl+C if this would be the last run. Wait to finish.");
	    mvprintw(base_y2+27, base_x2, "2. GUI Mode requires keeping window size as it is.");
	    mvprintw(base_y2+28, base_x2, "3. Resizing window size will destroy the display and run.");

	    mvprintw(base_y2+8, base_x2, "Current Run Status:");
	    refresh();
		 
	    trig=Sync(false,true);//Disable the trigger  
	    sleep(1);  
	    if(trig==0)
	    {
		mvprintw(base_y2+9, base_x2, "Trigger: Off");
	    }
	    else
	    {
		mvprintw(base_y2+9, base_x2, "Trigger: Error");
	    }
	    refresh();

	    Daq daq21(DAQ21_IP,DAQ_PORT1,DAQ21,runlength);
	    Daq daq22(DAQ22_IP,DAQ_PORT1,DAQ22,runlength);
	    Daq daq23(DAQ23_IP,DAQ_PORT1,DAQ23,runlength);
	    Daq daq24(DAQ24_IP,DAQ_PORT1,DAQ24,runlength);
	    Daq daq30(DAQ30_IP,DAQ_PORT1,DAQ30,runlength*DIRTY_FACTOR);

	    if(!daq21.CheckStatus() && !daq22.CheckStatus() && !daq23.CheckStatus() && !daq24.CheckStatus() && !daq30.CheckStatus())
	    {
		RunList(true);
		time_t time_now;
		time(&time_now);

		mvprintw(base_y2+10, base_x2, "Run Number :%d",newrun);
		mvprintw(base_y2+10, base_x2+30, "\tStarted:%s",ctime(&time_now));
		refresh();
		mvprintw(base_y2+12, base_x2, "\t\tRun %d in progress ...\t\t\t", newrun);
		mvprintw(base_y2+14, base_x2, "Progress:    ", newrun);
		refresh();

		trig=Sync(true,true);//Enable the trigger    
		if(trig==1)
		{
		    mvprintw(base_y2+9, base_x2, "Trigger: On ");
		}
		else
		{
		    mvprintw(base_y2+9, base_x2, "Trigger: Error ");
		}
		refresh();

		mvprintw(base_y2+15, base_x2, "                                                       ");

		mvprintw(base_y2+15, base_x2, "                                                       ");
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

		if(daq21.GetFileSize()<tol*daq21.filesize || daq22.GetFileSize()<tol*daq22.filesize || daq23.GetFileSize()<tol*daq23.filesize ||daq24.GetFileSize()<tol*daq24.filesize ||daq30.GetFileSize()<tol*daq30.filesize)
		{
		      mvprintw(base_y2+8, base_x2+21, "PROBLEM WITH MODULES ,INCORRECT FILE SIZE");
		      refresh();
		      sleep(5);
		      break;
		}
		mvprintw(base_y2+17, base_x2, "                                                        ");
		refresh();
		mvprintw(base_y2+19, base_x2, "Last Run Status:");
		 
	          if(Rename(newrun,DAQ21,true)==1 && Rename(newrun,DAQ22,true)==1 && Rename(newrun,DAQ23,true)==1 && Rename(newrun,DAQ24,true)==1 && ProcessData(newrun,DAQ30,true)==1)
		  {
		      mvprintw(base_y2+20, base_x2, "Data Files for run number %d  have been renamed successfully.",newrun);
		  }
		  else
		  {
		      mvprintw(base_y2+20, base_x2, "Problem renaming data files for run number %d",newrun);		 
		  }
		  mvprintw(base_y2+21, base_x2, "Phew!!! Done with run number : %d", newrun);
		  refresh();
		  if(!stop)
		      mvprintw(base_y2+12, base_x2, "\t\tNow initializing run number %d ... ... ", newrun+1);
		  else
		      mvprintw(base_y2+12, base_x2, "\t\t\tFinished Data Taking Process.");
		  refresh();
	    }
	    else
	    {
		mvprintw(base_y2+8, base_x2+20, "All DAQs are NOT Connected");
		refresh();
		break;
	    }
	}
 
	if(!continuous)
	{
	    counter=counter+1;
	}
    }      
}
