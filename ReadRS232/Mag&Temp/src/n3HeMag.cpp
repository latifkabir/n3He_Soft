//The FluxGate driver for n3He
// Reading field from flux gate(A magnetometer from Bartington, Model:Mag-03DAM)
//Author: Latiful Kabir
//Date:09.5.14
//Version:1.0

#include<iostream>
#include<string>
#include <string.h>
#include<csignal>
#include"FluxGate.h"
#include"Constants.h"
#include"n3HeMag.h"
using namespace std;

char response;
int sleep_time=SLEEP_TIME;
bool stop=false; //Flip if Ctrl+C is pressed

int SignOn(bool &signon)
{
    bool sleep=true;
    bool failed=false;
    int counter_sleep=0;
    int counter_signon=0;

    while(!signon && !failed)
    {
	FluxGate s(PORT_MAG,WAKE_UP_BAUD);
	if(s.CheckStatus()!=1);
	{
	    while(sleep)
	    {
		usleep(2000000);
		s.Write("\000");
		usleep(200000);
		response=s.Read();
		if(response==3) 
		{         
		    // cout<<"The Flux Gate is now awake "<<endl;
		    sleep=false;
		}
		if(counter_sleep>=10)
		{
		    cout<<"Failed to awake up Flux Gate, exiting..."<<endl;
		    failed=true;
		    return(1);
		}
		counter_sleep++;
	    }
	    if(!sleep)
	    {
		usleep(200000);
		s.Write("\231"); //Short SignOn request
		usleep(100000);
		s.Write("\0");  //Baud Code
		usleep(200000);
		response=s.Read();
            
		if(response==0)
		{
		    // cout<<"Baud Code Confirmed !!!"<<endl;
		    signon=true;
		}
		else if((response!=0) && (counter_signon<3))
		{
		    cout<<"Baud Code did NOT match, trying again..."<<endl;        
		    sleep=true;
		    counter_signon++;
		}
		else if(counter_signon>=3)
		{
		    cout<<"Failed to Sign on with requested baud rate, exiting..."<<endl;
		    return(1);
		}
	    }

	}
    }

    return(0);

}

void ReadField(FluxGate &p,double *fValue)
{
//------------------Channel 0 Scan------------------------    	
	    p.Write("\1"); //Polled mode command token
	    usleep(sleep_time);
	    p.Write("\000"); //Channele 0 * 16
	    usleep(sleep_time);
	    p.Write("\1"); //Checksum value
	    usleep(sleep_time);
	    p.Write("\201");
	    usleep(sleep_time);
	    p.Write("\17"); //Placeholder
	    usleep(sleep_time);
	    p.Write("\220"); //Checksum Value
	    usleep(sleep_time);
	    fValue[0]=p.ReadFG(0);
    	
//------------------Channel 1 Scan------------------------     	
	    p.Write("\1"); //Polled mode command token
	    usleep(sleep_time);
	    p.Write("\020"); //Channele 1 * 16
	    usleep(sleep_time);
	    p.Write("\21"); //Checksum value
	    usleep(sleep_time);
	    p.Write("\201");
	    usleep(sleep_time);
	    p.Write("\17"); //Placeholder
	    usleep(sleep_time);
	    p.Write("\220"); //Checksum Value
	    usleep(sleep_time);
	    fValue[1]=p.ReadFG(1);
 
//------------------Channel 2 Scan------------------------ 
	    p.Write("\1"); //Polled mode command token
	    usleep(sleep_time);
	    p.Write("\040"); //Channele 2 * 16
	    usleep(sleep_time);
	    p.Write("\41"); //Checksum value
	    usleep(sleep_time);
	    p.Write("\201");
	    usleep(sleep_time);
	    p.Write("\17"); //Placeholder
	    usleep(sleep_time);
	    p.Write("\220"); //Checksum Value
	    usleep(sleep_time);
	    fValue[2]=p.ReadFG(2);
 
//------------------Channel 3 Scan------------------------ 
	    p.Write("\1"); //Polled mode command token
	    usleep(sleep_time);
	    p.Write("\060"); //Channele 3 *16 in Octal
	    usleep(sleep_time);
	    p.Write("\61"); //Checksum value
	    usleep(sleep_time);
	    p.Write("\201");
	    usleep(sleep_time);
	    p.Write("\17"); //Placeholder
	    usleep(sleep_time);
	    p.Write("\220"); //Checksum Value
	    usleep(sleep_time);
	    fValue[3]=p.ReadFG(3);
	    
//------------------Channel 4 Scan------------------------ 
	    p.Write("\1"); //Polled mode command token
	    usleep(sleep_time);
	    p.Write("\100"); //Channele 4 *16 in Octal
	    usleep(sleep_time);
	    p.Write("\101"); //Checksum value
	    usleep(sleep_time);
	    p.Write("\201");
	    usleep(sleep_time);
	    p.Write("\17"); //Placeholder
	    usleep(sleep_time);
	    p.Write("\220"); //Checksum Value
	    usleep(sleep_time);
	    fValue[4]=p.ReadFG(4);
    	
//------------------Channel 5 Scan------------------------     	
	    p.Write("\1"); //Polled mode command token
	    usleep(sleep_time);
	    p.Write("\120"); //Channele 5 *16 in Octal
	    usleep(sleep_time);
	    p.Write("\121"); //Checksum value
	    usleep(sleep_time);
	    p.Write("\201");
	    usleep(sleep_time);
	    p.Write("\17"); //Placeholder
	    usleep(sleep_time);
	    p.Write("\220"); //Checksum Value
	    usleep(sleep_time);
	    fValue[5]=p.ReadFG(5);
    	
//------------------Channel 6 Scan------------------------     	
	    p.Write("\1"); //Polled mode command token
	    usleep(sleep_time);
	    p.Write("\140"); //Channele 6 *16 in Octal
	    usleep(sleep_time);
	    p.Write("\141"); //Checksum value
	    usleep(sleep_time);
	    p.Write("\201");
	    usleep(sleep_time);
	    p.Write("\17"); //Placeholder
	    usleep(sleep_time);
	    p.Write("\220"); //Checksum Value
	    usleep(sleep_time);
	    fValue[6]=p.ReadFG(6);
    	
//------------------Channel 7 Scan------------------------ 
	    p.Write("\1"); //Polled mode command token
	    usleep(sleep_time);
	    p.Write("\160"); //Channele 7 *16 in Octal
	    usleep(sleep_time);
	    p.Write("\161"); //Checksum value
	    usleep(sleep_time);
	    p.Write("\201");
	    usleep(sleep_time);
	    p.Write("\17"); //Placeholder
	    usleep(sleep_time);
	    p.Write("\220"); //Checksum Value
	    usleep(sleep_time);
	    fValue[7]=p.ReadFG(7);

}

//Handling ctrl+C signal to stop DAQ program smoothly/after finishing current run
void signalHandler( int signum )
{
    cout << "\n\nRequest to stop FluxGate received.Program will stop once current run finishes.Wait please ...\n\n";
    stop=true;
// cleanup and close up stuff here
// terminate program
// exit(signum);
}

