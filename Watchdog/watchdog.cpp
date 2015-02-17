#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <unistd.h>
#include"watchdog.h"
using namespace std;


//--------------Transfer the run to basestar------------------
int TransferData(int rNumber)
{
    int lastRun=0;  //last run transferred sucessfully.
    int currentRun=rNumber;   // Current run ready for transfer.

    int strlen=200;
    char *command=new char[strlen];
    snprintf(command,strlen,TRANS_COMMAND,currentRun,lastRun);
    cout<<command<<endl;
    if(currentRun > lastRun)
    {
	cout<<"Now attempting to transfer the data files to basestar ..."<<endl;

	int tStatus=system(command);

	if(!tStatus)  //0 tStatus means successfully transferred
	{	
	    lastRun=currentRun;
	    if(currentRun==lastRun+1)
		cout<<"All data files for run number "<<currentRun<<" transferred to basestar successfully"<<endl;
	    else
		cout<<"All data files for run numbers "<<lastRun<<" to "<<currentRun<<"transferred to basestar successfully"<<endl;
	    cout<<"Now waiting for next run ... ..."<<endl;
	    //wait till current run finishes
	    sleep(180);    
	}
	else
	{
	    cout<<"The first attenpt to send data files to basestar failed.Will initiate the second attempt shortly ... .."<<endl;
	    sleep(180);
	    cout<<"Second attempt to transfer data to basestar ..."<<endl;
	    int tStatus=system(command);
	    if(!tStatus)
	    {
		lastRun=currentRun;
		cout<<"All data files for run number "<<currentRun<<" transferred to basestar successfully"<<endl;
	    }
	    else
	    {
		cout<<"Both attempts to transfer run "<<currentRun<<"data failed."<<endl;
		cout<<"Adding run "<<currentRun<<" in the list of failed transfer."<<endl; 
		//Routing to add current run to failed list   
		cout<<"Now waiting for next run ... ..."<<endl;
		sleep(180);
	    }
	}
    }

    delete[] command;
}


//-----------------Send text alert if any param goes out of range----------

int TextAlert(int runNumber, int mag, int * temp)
{

//------------Range of Critical values-----------------------
    double magUpper=9.2;
    double magLower=8.9;
    double tempUpper=32;
    int lastRun=0;

    int errorCode=0;
    const char *msg=new char[200];

    if(runNumber==lastRun)
    {
	errorCode=1;
	msg="Problem with DAQ. DAQ NOT taking data";
    }
    if(mag>magUpper || mag < magLower)
    {
	errorCode=2;
	msg="Magnetic field out of range.";
    }
    if(temp[0]>tempUpper || temp[1] > tempUpper || temp[2] > tempUpper || temp[3] > tempUpper)
    {
	errorCode=3;
	msg="Temperature out of range";
    }


    int strlen=200;
    char *command=new char[strlen];
    snprintf(command,strlen,"./textAlert.sh %s",msg);

    if(errorCode!=0)
	int txt=system(command);
    
    delete[] msg;
    delete command;

}

int main(void)
{

//-------------List of parameters------------------------
    int daqStatus; //If the DAQ program is running
    int runStatus; //If taking the data based on trigger status
    int runNumber; // Current run number
    int mag;
    int temp1;
    int loop=0;

//Check if all the required files are in place as expected
    // if(ifstream("") && ifstream("") && ... ...)

//-------------Loop the following Over & Over ---------------------------

//-------Open the file containing parameters values.-----------
    ifstream paramFile("./params");


//-----------Read params from a text file--------------------
    paramFile>>daqStatus>>runStatus>>runNumber>>mag>>temp1;
    paramFile.close();

    cout << "Daq Status:"<<daqStatus <<endl;
    cout << "Run Status:"<<runStatus <<endl;
    cout << "Run Number:"<<runNumber <<endl;
    cout << "Mag Field:"<<mag <<endl;
    cout << "Temp zome 1:"<<temp1 <<endl;

    if(daqStatus && runStatus)
    {
	TransferData(runNumber);
	// TextAlert();
    }
    else
    {
	cout<<"Seems NO n3He Data taking is in progress. So I got some time for a nap :) ."<<endl;
	cout<<"------------------SYSTEM IN SLEEP---------------------"<<endl;
	cout<<"------------------SYSTEM IN SLEEP---------------------"<<endl;
	cout<<"------------------SYSTEM IN SLEEP---------------------"<<endl;
	cout<<"------------------SYSTEM IN SLEEP---------------------"<<endl;
	sleep(600);
    }
    return 0;
}
