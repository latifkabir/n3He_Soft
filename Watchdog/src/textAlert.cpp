#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

//-----------------Send text alert if any param goes out of range----------

int SendAlert(string msg)
{
    int strlen=200;
    char *command=new char[strlen];
    int errorCode=0;

    sprintf(command,"./textAlert.sh \"%s\"",msg.c_str());
    cout<<"\n\t\tABNORMAL ACTIVITY DETECTED. "<<msg<<". Sending text alert ... ..."<<endl;
    int txt=system(command);

    delete[] command;
    return txt;
}

int TextAlert(int run_number,int last_run,double mag, double* temp, bool* alert_enabled)
{

//------------Range of Critical values-----------------------
    double mag_upper=9.2;
    double mag_lower=8.9;
    double temp_upper=32;
    double temp_lower=18;

    string msg;

    if(run_number==last_run)
    {
	msg="Problem with DAQ. DAQ NOT taking data.";
	cout<<"\n\t\t"<<msg<<endl;
	if(alert_enabled[0])
	{
	    SendAlert(msg);
	    alert_enabled[0]=false;
	}
    }
    else
    {
	cout<<"\t\tThe DAQ is working fine."<<endl;
	alert_enabled[0]=true;
    }

    if(mag>mag_upper || mag < mag_lower)
    {
	msg="Magnetic field out of range.";
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
	msg="Temperature out of range.";
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
