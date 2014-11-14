#include<iostream>
#include<unistd.h>
#include"Daq.h"
#include"Constants.h"

using namespace std;

int Sync(bool status)
{
    
    Daq daq(DAQ30_IP,DAQ_PORT2,DAQ21,RUN_LENGTH);
    if(!daq.CheckStatus())
    {
	{
	    if(status)
	    {
		cout<<"Trigger Enabled"<<endl;
		daq.WriteToSocket("do4_3 1");
	    }
	    else if(!status)
	    {
		cout<<"Trigger Disabled"<<endl;
		daq.WriteToSocket("do4_3 0");
	    }
	}
    }
    return(0);
}

int main()
{
    for(int i=0;i<1000000;i++)
    {
	Sync(true);
	sleep(1);
	Sync(false);
	sleep(1);
    }
    return(0);
}
