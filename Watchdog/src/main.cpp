#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<unistd.h>
#include<csignal>
#include"constants.h"
#include"transferData.h"
#include"textAlert.h"

using namespace std;

int last_run=0;

void signalHandler( int signum )
{
    exit(signum);
}

int main(void)
{

//-------------List of parameters------------------------
    bool up_status;       //If the DAQ program is Up for taking data
    int run_status;  //If DAQ taking the data based on trigger status
    int run_number;  //Run number which is done processing
    int last_trans; // Run number that was transferred last time
    double mag;       //Magnitude of the magnetic field
    double temp[5];     // The temperature values
    long long loop=0;      // The loop number
    bool alert_enabled[3];

    cout<<"\n\t\t=================================================="<<endl;
    cout<<"\t\t\tWelcome to n3He 24/7 DAQ Watchdog program"<<endl;
    cout<<"\t\t\treport bug to: latifulkabir@uky.edu"<<endl;
    cout<<"\t\t=================================================="<<endl;

//---------Check if all the required scripts are in place as expected---------------
    if(!(ifstream("upStatus.sh") && ifstream("transferFile.sh") && ifstream("textAlert.sh")))
    {
	cout<<"\n\t\tCould NOT locate all the required bash scripts"<<endl;
	return(-1);
    }
    signal(SIGINT, signalHandler); //Handle Ctrl+C Signal

//----------Loop over and Over starting here------------
    while(true)
    {
	cout<<"\n\t\tloop number: "<<loop<<endl;

	int is_up=system("upStatus.sh >> /dev/null");
	if(is_up==0)
	{
	    cout<<"\n\t\tDetected the DAQ program is Up for taking data"<<endl;
	    up_status=true;
	}
	else
	{
	    cout<<"\n\t\tDetected the DAQ program is NOT Up for taking data"<<endl;
	    up_status=false;
	}

//-------Open the file containing parameters values.-----------
	ifstream daq_status("daqStatus.txt");
	ifstream last_transf("lastTrans.txt");
	ifstream mag_temp("magTemp.txt");

//---------Check if all the required data files are in place as expected---------------
	if(!(daq_status && last_transf && mag_temp))
	{
	    cout<<"\n\t\tCould NOT locate all the required data files"<<endl;
	    break;
	}

//-----------Read params from the text files--------------------
	daq_status>>run_status>>run_number;
	last_transf>>last_trans;
	mag_temp>>mag>>temp[0]>>temp[1]>>temp[2]>>temp[3]>>temp[4];

	daq_status.close();
	last_transf.close();
	mag_temp.close();

//---------------------Printing for verification--------------------------------
	cout<<"\n\t\t----------------Printing status for verification----------------"<<endl;
	cout << "\t\tDaq Status:"<<up_status<<endl;
	cout << "\t\tRun Status:"<<run_status <<endl;
	cout << "\t\tRun Number:"<<run_number <<endl;
	cout << "\t\tLast run transferred:"<<last_trans<<endl;
	cout << "\t\tMag Field:"<<mag<<endl;
	cout << "\t\tTemperatures: Zone 1: "<<temp[0]<<" Zone 2: "<<temp[1]<<" Zone 3: "<<temp[2]<<" Zone 4: "<<temp[3]<<" Zone 5: "<<temp[4]<<endl;
	cout<<"\t\t-----------------------------------------------------------------"<<endl;

	if(loop==0)
	    last_run=last_trans;

	if(loop%10==0)
	{
	    alert_enabled[0]=true;      //Enable DAQ status text alert
	    alert_enabled[1]=true;       //Enable Magnetic field status text alert
	    alert_enabled[3]=true;       //Enable Temperature status text alert 
	}

	if(up_status && run_status)
	{
	    TransferData(run_number,last_trans);
	    TextAlert(run_number,last_run,mag,temp,alert_enabled);
	    last_run=run_number;
	}
	else
	{
	    cout<<"\n\t\tSeems NO n3He Data taking process is in progress. So I got some time for a nap :) ."<<endl;
	    cout<<"\t\t-------------------WATCHDOG SYSTEM IN SLEEP---------------------"<<endl;
	    cout<<"\t\t-------------------WATCHDOG SYSTEM IN SLEEP---------------------"<<endl;
	    cout<<"\t\t-------------------WATCHDOG SYSTEM IN SLEEP---------------------"<<endl;
	    cout<<"\t\t-------------------WATCHDOG SYSTEM IN SLEEP---------------------"<<endl;
	    cout<<"\t\t-------------------DO NOT CLOSE THE PROGRAM---------------------"<<endl;
	    //sleep(480);
	    sleep(8);
	}

	loop++;
    }
    return 0;
}


//Input from DAQ progrem: last processed run number & trigger status.
//daq_status.txt ---if trigger is active (trigger status) and last processed run number.
//mag_temp.txt -- Instant values of magnetic filed and temperatures.
//lastTransferred.txt -- Last successfully transferred run.
//Scripts list:textAlert.sh,transferFile.sh,upStatus.sh
