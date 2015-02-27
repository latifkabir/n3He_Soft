#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <unistd.h>
#include"watchdog.h"
using namespace std;

int lastRun=0;

//--------------Transfer the run to basestar------------------
int TransferData(int rNumber,int lastTransferred)
{
    int startRun=lastTransferred+1;  //last run transferred sucessfully.
    int stopRun=rNumber;   // Current run ready for transfer.

    int strlen=200;
    char *command=new char[strlen];
    snprintf(command,strlen,TRANS_COMMAND,startRun,stopRun+1);
    cout<<command<<endl;
    if(stopRun > (startRun-1))
    {
	cout<<"Now attempting to transfer the data files to basestar ..."<<endl;

	int tStatus=system(command);

	if(!tStatus)  //0 tStatus means successfully transferred
	{	
	    if(stopRun==startRun)
		cout<<"All data files for run number "<<stopRun<<" transferred to basestar successfully"<<endl;
	    else
		cout<<"All data files for run numbers "<<startRun<<" to "<<stopRun<<"transferred to basestar successfully"<<endl;
            //Update last transferred run---HERE-----
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
		if(stopRun==startRun)
		    cout<<"All data files for run number "<<stopRun<<" transferred to basestar successfully"<<endl;
		else
		    cout<<"All data files for run numbers "<<startRun<<" to "<<stopRun<<"transferred to basestar successfully"<<endl;
		//Update last transferred run---HERE-----

	    }
	    else
	    {
		if(stopRun==startRun)
		{
		    cout<<"Both attempts to transfer run "<<stopRun<<" data failed."<<endl;
		    cout<<"Adding run "<<stopRun<<" in the list of failed transfer."<<endl;
		} 
		else
		{
		    cout<<"Both attempts to transfer run: "<<startRun<<" to "<<stopRun<<" data files failed."<<endl;
		    cout<<"Adding run numbers in the list of failed transfer."<<endl; 
		}

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
    bool upStatus;       //If the DAQ program is Up for taking data
    int runStatus;  //If taking the data based on trigger status
    int runNumber;  //Run number which is done processing
    int lastTransRun; // Run number that was transferred last time
    double mag;       //Magnitude of the magnetic field
    double temp[5];     // The temperature values
    int loop=0;      // The loop number


//----------Loop over and Over starting here------------


//---------Check if all the required scripts are in place as expected---------------
    if(!(ifstream("upStatus.sh") && ifstream("transferFile.sh") && ifstream("textAlert.sh")))
    {
	cout<<"Could NOT locate all the required bash scripts"<<endl;
	return(-1);
    }

    int isUp=system("upStatus.sh >> /dev/null");
    if(isUp==0)
    {
	cout<<"Detected the DAQ program is Up for taking data"<<endl;
	upStatus=true;
    }
    else
    {
	cout<<"Detected the DAQ program is NOT Up for taking data"<<endl;
	upStatus=false;
    }

//-------Open the file containing parameters values.-----------
    ifstream daqStatus("daqStatus.txt");
    ifstream lastTrans("lastTrans.txt");
    ifstream magTemp("magTemp.txt");

//---------Check if all the required data files are in place as expected---------------
    if(!(daqStatus && lastTrans && magTemp))
    {
	cout<<"Could NOT locate all the required data files"<<endl;
	return(-1);
    }

//-----------Read params from a text file--------------------
    daqStatus>>runStatus>>runNumber;
    lastTrans>>lastTransRun;
    magTemp>>mag>>temp[0]>>temp[1]>>temp[2]>>temp[3]>>temp[4];

    daqStatus.close();
    lastTrans.close();
    magTemp.close();

//-----------------------------------------------------
    cout << "Daq Status:"<<isUp<<endl;
    cout << "Run Status:"<<runStatus <<endl;
    cout << "Run Number:"<<runNumber <<endl;
    cout << "Last run transferred:"<<lastTransRun<<endl;
    cout << "Mag Field:"<<mag<<endl;
    cout << "Temp zome 1:"<<temp[0]<<endl;


//-------------Loop the following Over & Over ---------------------------
    lastRun=lastTransRun; //before the loop

    if(upStatus && runStatus)
    {
	TransferData(runNumber,lastTransRun);
	// TextAlert();
	lastRun=runNumber;
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


//Input from DAQ progrem: last processed run number & trigger status.
//daqStatus.txt ---if trigger is active (trigger status) and last processed run number.
//upStatus.txt -- if the DAQ program is running.
//magTemp.txt -- Instant values of magnetic filed and temperatures.
//lastTransferred.txt -- Last successfully transferred run.
//Scripts list:textAlert.sh,transferFile.sh,upStatus.sh
