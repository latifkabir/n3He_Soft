#include<iostream>
#include<string>
#include <string.h>
#include"Serial.h"

using namespace std;

int main(void)
{

    bool signon1=true;
    bool signon2=true;
    bool sleep=true;
    int counter_sleep=0;
    int counter_signon=0;
    char response;

//    while(signon1)
    {
	Serial s("/dev/ttyUSB0",300);
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
		    break;
		    return(1);
		}
		counter_sleep++;
	    }

	    usleep(200000);
	    s.Write("\231"); //Short SignOn request
	    usleep(100000);
	    s.Write("\0");  //Baud Code
	    usleep(200000);
	    response=s.Read();
            
	    if(response==0)
	    {
	    	cout<<"Baud Code Confirmed !!!"<<endl;
                signon1=false;
	    }
	    else
	    {
	    	cout<<"Baud Code did NOT match, trying again..."<<endl;        
	    	sleep=true;
	    	counter_sleep++;
	    }

	}
    }

    Serial p("/dev/ttyUSB0",9600);
    if(p.CheckStatus()!=1);
    {

//------------------Null Scan------------------------
	usleep(4000000);
	p.Write("\1"); //Polled mode command token
        usleep(200000);
	p.Write("\000"); //Channele 0 * 16 in Octal
	usleep(200000);
	p.Write("\1"); //Checksum value
	///////////////////////////////////////////
	usleep(2000000);
	p.Write("\201");
	usleep(200000);
	p.Write("\17"); //Placeholder
	usleep(200000);
	p.Write("\220"); //Checksum Value
    	usleep(200000);
    	response=p.Read();
    	
//------------------Channel 0 Scan------------------------    	
    	p.Write("\1"); //Polled mode command token
        usleep(200000);
	p.Write("\000"); //Channele 0 * 16
	usleep(200000);
	p.Write("\1"); //Checksum value
	///////////////////////////////////////////
	usleep(2000000);
	p.Write("\201");
	usleep(200000);
	p.Write("\17"); //Placeholder
	usleep(200000);
	p.Write("\220"); //Checksum Value
    	usleep(200000);
    	response=p.Read();
    	
//------------------Channel 1 Scan------------------------     	
    	p.Write("\1"); //Polled mode command token
    	usleep(200000);
	p.Write("\020"); //Channele 1 * 16
	usleep(200000);
	p.Write("\21"); //Checksum value
	///////////////////////////////////////////
	usleep(2000000);
	p.Write("\201");
	usleep(200000);
	p.Write("\17"); //Placeholder
	usleep(200000);
	p.Write("\220"); //Checksum Value
    	usleep(200000);
    	response=p.Read();
 
//------------------Channel 2 Scan------------------------ 
    	p.Write("\1"); //Polled mode command token
    	usleep(200000);
	p.Write("\040"); //Channele 2 * 16
	usleep(200000);
	p.Write("\41"); //Checksum value
	///////////////////////////////////////////
	usleep(2000000);
	p.Write("\201");
	usleep(200000);
	p.Write("\17"); //Placeholder
	usleep(200000);
	p.Write("\220"); //Checksum Value
    	usleep(200000);
    	response=p.Read();
 
//------------------Channel 3 Scan------------------------ 
    	p.Write("\1"); //Polled mode command token
    	usleep(200000);
	p.Write("\060"); //Channele 3 *16 in Octal
	usleep(200000);
	p.Write("\61"); //Checksum value
	///////////////////////////////////////////
	usleep(2000000);
	p.Write("\201");
	usleep(200000);
	p.Write("\17"); //Placeholder
	usleep(200000);
	p.Write("\220"); //Checksum Value
    	usleep(200000);
    	response=p.Read();
    	
//------------------Channel 4 Scan------------------------ 
    	p.Write("\1"); //Polled mode command token
    	usleep(200000);
	p.Write("\100"); //Channele 4 *16 in Octal
	usleep(200000);
	p.Write("\101"); //Checksum value
	///////////////////////////////////////////
	usleep(2000000);
	p.Write("\201");
	usleep(200000);
	p.Write("\17"); //Placeholder
	usleep(200000);
	p.Write("\220"); //Checksum Value
    	usleep(200000);
    	response=p.Read();
    	
//------------------Channel 5 Scan------------------------     	
    	p.Write("\1"); //Polled mode command token
    	usleep(200000);
	p.Write("\120"); //Channele 5 *16 in Octal
	usleep(200000);
	p.Write("\121"); //Checksum value
	///////////////////////////////////////////
	usleep(2000000);
	p.Write("\201");
	usleep(200000);
	p.Write("\17"); //Placeholder
	usleep(200000);
	p.Write("\220"); //Checksum Value
    	usleep(200000);
    	response=p.Read();
    	
//------------------Channel 6 Scan------------------------     	
    	p.Write("\1"); //Polled mode command token
    	usleep(200000);
	p.Write("\140"); //Channele 6 *16 in Octal
	usleep(200000);
	p.Write("\141"); //Checksum value
	///////////////////////////////////////////
	usleep(2000000);
	p.Write("\201");
	usleep(200000);
	p.Write("\17"); //Placeholder
	usleep(200000);
	p.Write("\220"); //Checksum Value
    	usleep(200000);
    	response=p.Read();
    	
//------------------Channel 7 Scan------------------------ 
    	p.Write("\1"); //Polled mode command token
    	usleep(200000);
	p.Write("\160"); //Channele 7 *16 in Octal
	usleep(200000);
	p.Write("\161"); //Checksum value
	///////////////////////////////////////////
	usleep(2000000);
	p.Write("\201");
	usleep(200000);
	p.Write("\17"); //Placeholder
	usleep(200000);
	p.Write("\220"); //Checksum Value
    	usleep(200000);
    	response=p.Read();

    }
 
    return(0);

}
