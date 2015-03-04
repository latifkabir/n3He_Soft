//The program to take the data in command line mode
//Author: Latiful Kabir
//Date:10.9.14
//Version:2.0

#include<iostream>
#include<fstream>
#include<cstdio>
#include<thread>
#include<stdio.h>
#include<csignal>
#include<cstdlib>
#include"Daq.h"
#include"ProcessData.h"
#include"Constants.h"

using namespace std;

extern int lastrun;
extern int newrun; 
extern bool stop;  //Flip if Ctrl+C is pressed
bool fexit=false;

void RunList(bool gui_mode)
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
    ifstream runRecord(LAST_RUN);
    if(runRecord)
    {
	runRecord>>lastrun;	
	newrun=lastrun+1;
	runRecord.close();
    }

    //Save Date and time of current run to the file RunList.txt
    ofstream runlist(RUN_LIST,ofstream::app);
    if(runlist)
    {
	runlist<<strname<<"          "<<newrun<<endl;
	runlist.close();
    }

    if(!gui_mode)
	cout<<"\t\t====================Initializing Run number: "<<newrun<<"====================="<<"\n\t\t\t\tDate & Time: "<<ctime(&time_now)<<endl<<endl; 

    delete[] strname;   
}
void UpdateRun()
{
    ofstream runRecord(LAST_RUN);
    if(runRecord)
    {
	runRecord<<newrun;
	runRecord.close();
    }
}

//Rename all the data files (just taken) adding the run number
int Rename(int run,int module,bool gui_mode)
{
    char *file_old=new char[200];
    char *file_new=new char[200];

    sprintf(file_old,OLD_FILE,module);

    if(module==30)
	sprintf(file_new,NEW_FILE,run,DAQTEMP);//Rename as temporary file for dirty daq only
    else
	sprintf(file_new,NEW_FILE,run,module);

    if(rename(file_old, file_new) == 0)
    {
	if(!gui_mode)
	    cout<<"\n \n\t\t"<< file_old<<" has been renamed to "<<file_new<<endl;
	return(1);
    }
    else
    {
	if(!gui_mode)
	    cout<<"\t\tError renaming "<<file_old<<endl;
	return(-1);
    }
    delete[] file_old;
    delete[] file_new;
}

//Synchronize with T_0 at the start of DAQ by enabling and disabling Trigger
int Sync(bool status,bool gui_mode)
{
    if(status)
	sleep(2);
    Daq daq(DAQ30_IP,DAQ_PORT2,DAQ30,RUN_LENGTH);
    ofstream daqStatus(DAQ_STATUS);

    if(!daq.CheckStatus())
    {
	if(status)
	{
	    if(!gui_mode)
		cout<<"\t\tTrigger Enabled"<<endl<<endl;

	    daq.WriteToSocket("do4_3 1");
	    if(daqStatus)
		daqStatus<<1<<"        "<<(newrun-1);
	    return(1);
	}
	else if(!status)
	{
	    if(!gui_mode)
		cout<<"\t\tTrigger Disabled"<<endl<<endl;

	    daq.WriteToSocket("do4_3 0");
	    if(daqStatus)
		daqStatus<<0<<"        "<<(newrun-1);
	    return(0);
	}
    }
    else
    {
	if(!gui_mode)
	    cout<<"\t\tUnable to switch trigger"<<endl;
	return(-1);

    }
    daqStatus.close();
}


//Handling ctrl+C signal to stop DAQ program smoothly/after finishing current run
void signalHandler( int signum )
{
    if(!fexit)
    {
        cout <<"\n\n\t\tRequest to stop DAQ received.\n\t\tProgram will stop once current run finishes.Please wait...\n\t\tTo quit program forcefully press Ctrl+C again.\n\n";
	stop=true;
	fexit=true;
    }
    else
	exit(signum);
}

//Process Dirty DAQ data from previous run while taking current run
int ProcessDirty(int count,bool gui_mode)
{
    if(count!=0)
	ProcessData(newrun-1,DAQ30,gui_mode);

    return 0;
}

//Routine to run a single DAQ module only 
void RunSingle(int module=MODULE,int runlength=RUN_LENGTH,int runNumber=RUN_NUMBER)
{
    bool continuous=false; //Continuous or single run
    bool ready=true;  //Start if DAQ ready based on T0
    int counter=0;
    int stime=SLEEP_TIME; //Sleep time in second
    double tol=0.99;   //Tolerance
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
	continuous=true;

    while(!stop && (continuous || (counter <runNumber)))
    {

	if(ready)
	{
	    Sync(false,false);//Disable the trigger    
	    sleep(2);
	    Daq daq(ip,port,module,runlength);
	    if(!daq.CheckStatus())
	    {
		RunList(false);
		cout<<"\t\tRun "<<newrun<<" in progress ... ... "<<endl<<endl;
		Sync(true,false); //Enable the Trigger
		daq.SaveData(true);
		if(daq.GetFileSize()<tol*daq.filesize)
		{
		    cout<<"\n\t\tPROBLEM WITH MODULES , DID NOT RECEIVE REQUESTED FILE SIZE"<<endl;
		    break;
		}
		Rename(newrun,module,false);
		if(module==30)
		    ProcessData(newrun,DAQ30,false);
		UpdateRun();
		cout<<"\n\t\tPhew!!! Done with run number : "<<newrun<<endl<<endl;
	    }
	    else
	    {
		cout<<"DAQ "<<module<<" is NOT connected"<<endl;
		break;
	    }
	}
 
	if(!continuous)
	    counter++;
    }
    Sync(false,false); //Disable the trigger
}

//Running all the DAQ module
void RunAll (int runlength=RUN_LENGTH,int runNumber=RUN_NUMBER)
{
    bool continuous=false; //Continuous or single run
    bool ready=true;  //Start if DAQ ready based on T0
    int counter=0;
    int runCount=0;
    int stime=5; //Sleep time in second
    double tol=0.99; //Tolerance
    signal(SIGINT, signalHandler); //Handle Ctrl+C Signal  

    if(runNumber==0)
	continuous=true;

    while(!stop && (continuous || (counter <runNumber)))
    {
	if(ready)
	{
	    Sync(false,false); //Disable the trigger   
	    sleep(2); 	     
	    Daq daq21(DAQ21_IP,DAQ_PORT1,DAQ21,runlength);
	    Daq daq22(DAQ22_IP,DAQ_PORT1,DAQ22,runlength);
	    Daq daq23(DAQ23_IP,DAQ_PORT1,DAQ23,runlength);
	    Daq daq24(DAQ24_IP,DAQ_PORT1,DAQ24,runlength);
	    Daq daq30(DAQ30_IP,DAQ_PORT1,DAQ30,runlength*DIRTY_FACTOR);

	    if(!daq21.CheckStatus() && !daq22.CheckStatus() && !daq23.CheckStatus() && !daq24.CheckStatus() && !daq30.CheckStatus())
	    {
		RunList(false);
		cout<<"\t\tRun "<<newrun<<" in progress ... ... "<<endl<<endl;

		thread t21(&Daq::SaveData,&daq21,true);
		thread t22(&Daq::SaveData,&daq22,false);
		thread t23(&Daq::SaveData,&daq23,false);
		thread t24(&Daq::SaveData,&daq24,false);
		thread t30(&Daq::SaveData,&daq30,false);
		thread t(Sync,true,false);    //Enable the trigger
		thread t0(ProcessDirty,runCount,false);    //Process dirty DAQ data of previous run


		t21.join();
		t22.join();
		t23.join();
		t24.join();
		t30.join();
		t.join();        //Enable the trigger
		t0.join();       

		if(daq21.GetFileSize()<tol*daq21.filesize || daq22.GetFileSize()<tol*daq22.filesize || daq23.GetFileSize()<tol*daq23.filesize ||daq24.GetFileSize()<tol*daq24.filesize ||daq30.GetFileSize()<tol*daq30.filesize)
		{
		    cout<<"\n\t\tPROBLEM WITH MODULES , DID NOT RECEIVE REQUESTED FILE SIZE"<<endl;
		    break;
		}
		Rename(newrun,DAQ21,false);
		Rename(newrun,DAQ22,false);
		Rename(newrun,DAQ23,false);
		Rename(newrun,DAQ24,false);
		Rename(newrun,DAQ30,false);  

		if(stop || ((counter+1 >= runNumber) && runNumber!=0))
		    ProcessData(newrun,DAQ30,false);
		UpdateRun();
		cout<<"\n\t\tPhew!!! Done with run number : "<<newrun<<endl<<endl;
	    }
	    else
	    {
		cout<<"All the DAQs are NOT connected"<<endl;
		break;
	    }
	}
	runCount++;
	if(!continuous)
	    counter++;
    }
    Sync(false,false); //Disable the trigger
}
