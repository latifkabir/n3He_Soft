//Program for 24/7 DAQ status and other critical parameters watchdog.
//Author: Latiful Kabir
//Date:03/03/15

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
extern bool automated;
 
void signalHandler( int signum )
{
    exit(signum);
}

int main(int argc,char *argv[])
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
    string atm="auto";

    if(argc==2 && argv[1]==atm)
	automated=true;

    cout<<"\n\t\t=================================================="<<endl;
    cout<<"\t\t\tWelcome to n3He 24/7 DAQ Watchdog program"<<endl;
    cout<<"\t\t\treport bug to: latifulkabir@uky.edu"<<endl;
    cout<<"\t\t=================================================="<<endl;

//---------Check if all the required scripts are in place as expected---------------
    if(!(ifstream(UP_STATUS_SH) && ifstream(FILE_TRANS_SH) && ifstream(TXT_ALERT_SH) && ifstream(PING_IP_SH)))
    {
	cout<<"\n\t\tCould NOT locate all the required bash scripts"<<endl;
	return(-1);
    }

    cout<<"\n\t\tChecking if Network connection is OK ...."<<endl;
    int is_connected=system(PING_COMMAND);

    if(is_connected==0)
    {
	cout<<"\n\t\tDetected Picard is Connected to Cyclonous"<<endl;
    }
    else
    {
	cout<<"\n\t\tDetected Picard is NOT connected to Cyclonous. Please fix the problem"<<endl;
	sleep(60);
	return(-1);
    }


    signal(SIGINT, signalHandler); //Handle Ctrl+C Signal

//----------Loop over and Over starting here------------
    while(true)
    {
	time_t time_now;
	time(&time_now);

	cout<<"\n\t\tloop number: "<<loop<<" Time:"<<ctime(&time_now)<<endl;

	int is_up=system(STATUS_COMMAND);
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
	ifstream daq_status(DAQ_STATUS_TXT);
	ifstream last_transf(LAST_TRANS_TXT);
	ifstream mag_temp(MAG_TEMP_TXT);

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
	    if(loop>1)
		TextAlert(run_number,last_run,mag,temp,alert_enabled);
	    TransferData(run_number,last_trans);
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
	    loop=0;
	    sleep(450);
	}

	loop++;
    }
    return 0;
}


//Input from DAQ progrem: last processed run number & trigger status.
//daqStatus.txt ---if trigger is active (trigger status) and last processed run number.
//magTemp.txt -- Instant values of magnetic filed and temperatures.
//lastTransferred.txt -- Last successfully transferred run.
//Scripts list:textAlert.sh,transferFile.sh,upStatus.sh,pingip.sh
