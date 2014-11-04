//The program to take the data
//Author: Latiful Kabir
//Date:10.9.14
//Version:2.0

#include<iostream>
#include<fstream>
#include<cstdio>
#include<thread>
#include<stdio.h>
#include<csignal>
#include"Daq.h"
#include"Constants.h"

using namespace std;

int lastrun=0;
int newrun=0; 
bool stop=false;  //Flip if Ctrl+C is pressed

void RunList()
{
    //Generate current date and time of the run in desired format
    time_t time_now;
    time(&time_now);
    struct tm my_time;
    localtime_r (&time_now,&my_time);
    int strlen=100;
    char *strname=new char[100];
    snprintf(strname,strlen,"%04d-%02d-%02d-%02d-%02d-%02d",my_time.tm_year+1900,my_time.tm_mon+1,my_time.tm_mday,my_time.tm_hour,my_time.tm_min,my_time.tm_sec);

 
    // Read last run number and generate run number for current run
    fstream runRecord(LAST_RUN,ios::in | ios::out);
    if(runRecord)
    {
	runRecord>>lastrun;	
	newrun=lastrun+1;
	runRecord.seekg(0,ios::beg);
	runRecord<<newrun;
	runRecord.close();
    }

    //Save Date and time of current run to the file RunList.txt
    ofstream runlist(RUN_LIST,ofstream::app);
    if(runlist)
    {
	runlist<<strname<<"          "<<newrun<<endl;
	runlist.close();
    }
    cout<<"====================Initializing Run number: "<<newrun<<"====================="<<"\n\t\tDate & Time: "<<ctime(&time_now)<<endl<<endl; 
   
}

//Rename all the data files (just taken) adding the run number
void Rename(int run,int module)
{
    char *file_old=new char[200];
    char *file_new=new char[200];

    sprintf(file_old,OLD_FILE,module);
    sprintf(file_new,NEW_FILE,run,module);

    if(rename(file_old, file_new) == 0)
    {
	cout<<"\n \n"<< file_old<<" has been renamed to "<<file_new<<endl;
    }
    else
    {
        cout<<"Error renaming "<<file_old<<endl;
    }
}

//Synchronize with T_0 at the start of DAQ by enabling and disabling Trigger
int Sync(bool status)
{
    
    Daq daq(DAQ30_IP,DAQ_PORT2,DAQ30,RUN_LENGTH);
    if(!daq.CheckStatus())
    {
	{
	    if(status)
	    {
		cout<<"Trigger Enabled"<<endl<<endl;
		daq.WriteToSocket("do4_3 1");
	    }
	    else if(!status)
	    {
		cout<<"Trigger Disabled"<<endl<<endl;
		daq.WriteToSocket("do4_3 0");
	    }
	}
    }
    return(0);
}


//Handling ctrl+C signal to stop DAQ program smoothly/after finishing current run
void signalHandler( int signum )
{
    cout << "\n\nRequest to stop DAQ received.Program will stop once current run finishes.Wait please ...\n\n";
    stop=true;

    // cleanup and close up stuff here  
    // terminate program  
    // exit(signum);  

}



//Routine to run a single DAQ module only 
void RunSingle(int module=MODULE,int runlength=RUN_LENGTH,int runNumber=RUN_NUMBER)
{
    bool continuous=false; //Continuous or single run
    bool ready=true;  //Start if DAQ ready based on T0
    int counter=0;
    int stime=SLEEP_TIME; //Sleep time in second
    const char *ip;
    const char *port=DAQ_PORT1;

    signal(SIGINT, signalHandler); //Handle Ctrl+C Signal

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

    Sync(true); //Enable the Trigger
    while(!stop && (continuous || (counter <runNumber)))
    {

         if(ready)
         {
 	      Daq daq(ip,port,module,runlength);
	      if(!daq.CheckStatus())
	      {
	          RunList();
		  cout<<"Run "<<newrun<<" in progress ... ... "<<endl<<endl;
	          daq.SaveData(true);
		  if(daq.GetFileSize()<daq.filesize)
		  {
		      cout<<"\nPROBLEM WITH MODULES , DID NOT RECEIVE REQUESTED FILE SIZE"<<endl;
		      break;
		  }
	          Rename(newrun,module);
	          cout<<"\nPhew!!! Done with run number : "<<newrun<<endl<<endl;
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

    Sync(false);//Disable the trigger    
}

//Running all the DAQ module
void RunAll (int runlength=RUN_LENGTH,int runNumber=RUN_NUMBER)
{
    bool continuous=false; //Continuous or single run
    bool ready=true;  //Start if DAQ ready based on T0
    int counter=0;
    int stime=5; //Sleep time in second

    signal(SIGINT, signalHandler); //Handle Ctrl+C Signal  


    if(runNumber==0)
    {
	continuous=true;
    }

    Sync(true); //Enable the Trigger
    while(!stop && (continuous || (counter <runNumber)))
    {
	if(ready)
	{
	    Daq daq21(DAQ21_IP,DAQ_PORT1,DAQ21,runlength);
	    Daq daq22(DAQ22_IP,DAQ_PORT1,DAQ22,runlength);
	    Daq daq23(DAQ23_IP,DAQ_PORT1,DAQ23,runlength);
	    Daq daq24(DAQ24_IP,DAQ_PORT1,DAQ24,runlength);

	    if(!daq21.CheckStatus() && !daq22.CheckStatus() && !daq23.CheckStatus() && !daq24.CheckStatus())
	    {
		RunList();
		cout<<"Run "<<newrun<<" in progress ... ... "<<endl<<endl;
		thread t21(&Daq::SaveData,&daq21,true);
		thread t22(&Daq::SaveData,&daq22,false);
		thread t23(&Daq::SaveData,&daq23,false);
		thread t24(&Daq::SaveData,&daq24,false);

		t21.join();
		t22.join();
		t23.join();
		t24.join();

		if(daq21.GetFileSize()<daq21.filesize || daq22.GetFileSize()<daq22.filesize || daq23.GetFileSize()<daq23.filesize ||daq24.GetFileSize()<daq24.filesize)
		{
		    cout<<"\nPROBLEM WITH MODULES , DID NOT RECEIVE REQUESTED FILE SIZE"<<endl;
		    break;
		}
		Rename(newrun,DAQ21);
		Rename(newrun,DAQ22);
		Rename(newrun,DAQ23);
		Rename(newrun,DAQ24);

		cout<<"\nPhew!!! Done with run number : "<<newrun<<endl<<endl;
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
    Sync(false);//Disable the trigger      
}
