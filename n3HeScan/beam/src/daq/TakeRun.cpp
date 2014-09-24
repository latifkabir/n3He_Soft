//The program to take the data
//Author: Latiful Kabir
//Date:08.15.14
//Version:1.0

#include<iostream>
#include<fstream>
#include<cstdio>
#include<thread>
#include<unistd.h>
#include"Daq.h"

using namespace std;

int lastrun=0;
int newrun=0; 
  

void RunList()
{
 
    // Read last run number and generate run number for current run
    fstream runRecord("LastRun.txt",ios::in | ios::out);
    if(runRecord)
    {
	runRecord>>lastrun;	
	newrun=lastrun+1;
	runRecord.seekg(0,ios::beg);
	runRecord<<newrun;
	runRecord.close();
    }

    //Save Date and time of current run to the file RunList.txt
    ofstream runlist("RunList.txt",ofstream::app);
    if(runlist)
    {
	runlist<<__DATE__<<"    "<<__TIME__<<"    "<<newrun<<endl;
	runlist.close();
    }
    cout<<"=======Initializing Run number: "<<newrun<<" on "<<__DATE__<<" at "<<__TIME__<<"======="<<endl<<endl; 
   
}

//Rename all the data files (just taken) adding the run number
void Rename(int run,int module)
{
    char file_old[200];
    char file_new[200];

    sprintf(file_old,"data_file-%d",module);
    sprintf(file_new,"run%ddata_file-%d",run,module);

    if(rename(file_old, file_new) == 0)
    {
	cout<< file_old<<" has been renamed to "<<file_new<<endl;
    }
    else
    {
        cout<<"Error renaming "<<file_old<<endl;
    }
}




//Routine to run a single DAQ module only 
void RunSingle(int module=21,int runlength=100000000,int runNumber=0)
{
    bool continuous=false; //Continuous or single run
    bool ready=true;  //Start if DAQ ready based on T0
    int counter=0;
    int stime=15; //Sleep time in second
    const char *ip;
    const char *port="1234";

    switch(module)
    {
    case 21:
    {
	ip="127.0.0.1";
	break;
    }
    case 22:
    {
	ip="192.168.0.22";
	break;
    }
    case 23:
    {
	ip="192.168.0.23";
	break;
    }

    case 30:
    {
	ip="127.0.0.1";
	break;
    }
    default:
    {
	ip="192.168.0.21";
    }
    }

    if(runNumber==0)
    {
	continuous=true;
    }
    while(continuous || (counter <runNumber))
    {

         if(ready)
         {
 	      Daq daq(ip,port,module,runlength);
	      if(!daq.CheckStatus())
	      {
	          RunList();
		  cout<<"Run "<<newrun<<" in progress ... ... "<<endl<<endl;
	          daq.SaveData();
	          Rename(newrun,module);
	          cout<<"Phew!!! Done with run number : "<<newrun<<endl;
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
         cout<<"----->DAQ is now sleeping for "<<stime<<" seconds, Press Crtl+C if no further run is expected<------"<<endl<<endl;

	 sleep(stime);
    }    
}

//Running all the DAQ module
void RunAll (int runlength=100000000,int runNumber=0)
{
    bool continuous=false; //Continuous or single run
    bool ready=true;  //Start if DAQ ready based on T0
    int counter=0;
    int stime=15; //Sleep time in second

    if(runNumber==0)
    {
	continuous=true;
    }
    while(continuous || (counter <runNumber))
    {
	if(ready)
	{
	    Daq daq21("127.0.0.1","1234",21,runlength);
	    Daq daq22("127.0.0.1","1235",22,runlength);
	    Daq daq23("127.0.0.1","1236",23,runlength);
	    Daq daq30("127.0.0.1","1237",30,runlength);

	    if(!daq21.CheckStatus() && !daq22.CheckStatus() && !daq23.CheckStatus() && !daq30.CheckStatus())
	    {
		RunList();
                cout<<"Run "<<newrun<<" in progress ... ... "<<endl<<endl;
		thread t21(&Daq::SaveData,&daq21);
		thread t22(&Daq::SaveData,&daq22);
		thread t23(&Daq::SaveData,&daq23);
		thread t30(&Daq::SaveData,&daq30);

		t21.join();
		t22.join();
		t23.join();
		t30.join();

		Rename(newrun,21);
		Rename(newrun,22);
		Rename(newrun,23);
		Rename(newrun,30);

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
	cout<<"----->DAQ is now sleeping for "<<stime<<" seconds, Press Crtl+C if no further run is expected<------"<<endl<<endl;

	sleep(stime);
    }
   
}
