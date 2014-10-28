//The FluxGate driver for n3He
//Author: Latiful Kabir
//Date:09.5.14
//Version:1.0

#include<iostream>
#include<string>
#include <string.h>
#include<csignal>
#include"FluxGate.h"
#include"Help.h"
#include"Constants.h"

using namespace std;

char response;
int sleep_time=SLEEP_TIME;
bool stop=false; //Flip if Ctrl+C is pressed

int SignOn(bool &signon);
void ReadField(FluxGate &p);
void signalHandler( int signum );

int SignOn(bool &signon)
{
    bool sleep=true;
    bool failed=false;
    int counter_sleep=0;
    int counter_signon=0;

    while(!signon && !failed)
    {
	FluxGate s(PORT,WAKE_UP_BAUD);
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
		    cout<<"The Flux Gate is now awake "<<endl;
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
		    cout<<"Baud Code Confirmed !!!"<<endl;
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

void ReadField(FluxGate &p)
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
	    response=p.ReadFG(0);
    	
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
	    response=p.ReadFG(1);
 
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
	    response=p.ReadFG(2);
 
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
	    response=p.ReadFG(3);
	    
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
	    response=p.ReadFG(4);
    	
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
	    response=p.ReadFG(5);
    	
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
	    response=p.ReadFG(6);
    	
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
	    response=p.ReadFG(7);

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

int main(int argc,char *argv[])
{

    bool signon=false;
    char cont='c';
    bool continuous=true;
    int j=-1;

    string list[]={"help","single","scan"};
    if(argc==1 || argc>2)
    {
	DefaultIns();
	return(1);
    }

    if(argc==2)
    {
	for(int i=0;i<3;i++)
	{
	    if(list[i]==argv[1])
	    {
	        j=i;
		break;
	    }
	}
    }

    if(j==0)
    {
	Instruction();
	return(1);
    }

    Title();
    cout<<"The Flux Gate is being initialized .... Please wait..."<<endl;
    SignOn(signon);
    if(signon)
    {
	FluxGate p(PORT,BAUD);
	if(p.CheckStatus()!=1);
	{

//------------------Null Scan------------------------
	    usleep(2000000);
	    p.Write("\1"); //Polled mode command token
	    usleep(sleep_time);
	    p.Write("\000"); //Channele 0 * 16 in Octal
	    usleep(sleep_time);
	    p.Write("\1"); //Checksum value
	    usleep(2*sleep_time);
	    p.Write("\201");
	    usleep(sleep_time);
	    p.Write("\17"); //Placeholder
	    usleep(sleep_time);
	    p.Write("\220"); //Checksum Value
	    usleep(2*sleep_time);
	    response=p.Read();

	    cout<<"Done with initialization ... ... ..."<<endl;

	    switch(j)
	    {
	    case 1:
		while(cont=='c')
		{
		    ReadField(p);
		    cout<<"To continue with another run press 'c' & Enter"<<endl;
		    cin>>cont;
		}
		break;
	    case 2:
		signal(SIGINT, signalHandler); //Handle Ctrl+C Signal    	
		while(continuous && !stop)
		{
		    ReadField(p);
		}
		break;
	    default:
		while(cont=='c')
		{
		    ReadField(p);
		    cout<<"To continue with another run press 'c' & Enter"<<endl;
		    cin>>cont;
		}

	    }
	}
    }
    return(0);

}
