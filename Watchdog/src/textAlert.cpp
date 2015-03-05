//Program for sending text alert when DAQ fails or critical parameters are out of range.
//Author: Latiful Kabir
//Date:03/03/15

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "constants.h"
using namespace std;

bool automated=false;
//-----------------Send text alert if any param goes out of range----------

int SendAlert(string msg)
{
    int strlen=200;
    char *command=new char[strlen];
    int errorCode=0;

    sprintf(command,ALERT_COMMAND,msg.c_str());
    cout<<"\n\t\tABNORMAL ACTIVITY DETECTED. "<<msg<<". Sending text alert ... ..."<<endl;
    int txt=system(command);
    sleep(5);
    delete[] command;
    return txt;
}

int TextAlert(int run_number,int last_run,double mag, double* temp, bool* alert_enabled)
{

//------------Range of Critical values-----------------------
    double mag_upper=9.12;
    double mag_lower=9.08;
    double temp_upper=31;
    double temp_lower=16;

    string msg;

    if(run_number==last_run)
    {
	msg="Problem with n3He DAQ. DAQ NOT taking data.";
	cout<<"\n\t\t"<<msg<<endl;
	if(alert_enabled[0])
	{
	    SendAlert(msg);
	    alert_enabled[0]=false;
	}
	if(automated && alert_enabled[0])
	{
	    int atm=system("gnome-terminal --geometry=120x35+0+0 -t \"n3HeDAQ\"-e \"/home/daq/Diagnosis/diagnosis.sh auto\"");
	    msg="Initiated alternative automated n3He data taking process.";
	    cout<<msg<<endl;
	    SendAlert(msg);
	}
    }
    else
    {
	cout<<"\t\tThe DAQ is working fine."<<endl;
	alert_enabled[0]=true;
    }

    if(-1*mag>mag_upper || -1*mag < mag_lower)
    {
	msg="n3He Magnetic field out of range.";
	cout<<"\n\t\t"<<msg<<endl;
	if(alert_enabled[1])
	{
	    SendAlert(msg);
	    alert_enabled[1]=false;
	}
    }
    else
    {
	cout<<"\t\tThe magnetic field is OK."<<endl;
	alert_enabled[1]=true;
    }

    if((temp[0]>temp_upper || temp[1] > temp_upper || temp[2] > temp_upper || temp[3] > temp_upper) || (temp[0]<temp_lower || temp[1] < temp_lower || temp[2] < temp_lower || temp[3] < temp_lower))
    {
	msg="n3He Temperature out of range.";
	cout<<"\n\t\t"<<msg<<endl;
	if(alert_enabled[2])
	{
	    SendAlert(msg);
	    alert_enabled[2]=false;
	}
    }
    else
    {
	cout<<"\t\tThe temperatures are OK."<<endl;
	alert_enabled[2]=true;
    }

    return 0;
}
