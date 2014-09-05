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

	    // usleep(200000);
	    // s.Write("\207"); //Clear Checksum
	    usleep(200000);
	    // response=s.Read();
	    // s.Write("\210"); //Normal SignOn request
	    s.Write("\231"); //Short SignOn request
	    usleep(100000);
	    s.Write("\5");  //Baud Code
	    usleep(200000);
	    response=s.Read();
            
	    if(response==5)
	    {
	    	cout<<"Baud Code Confirmed !!!"<<endl;
                signon1=false;
	    }
	    else
	    {
	    	cout<<"Baud Code did NOT match, trying again..."<<endl;        
	    	sleep=true;
	    }

	    // if(counter_signon>=5)
	    // {
	    // 	cout<<"Failed to Sign On to Flux Gate, exiting..."<<endl;
	    // 	break;
	    // 	return(1);
	    // }
	    // counter_signon++;
	}
    }

    Serial p("/dev/ttyUSB0",300);
    if(p.CheckStatus()!=1);
    {
// 	cout<<"Starting Echo Test"<<endl;
//	usleep(200000);
//   	p.Write("\7"); //Echo Testing
// 	usleep(200000);
// 	response=p.Read();

// //Optional Echo Testing .......................
// 	if(response==7)
// 	{
// 	    cout<<"Passed the Echo Test"<<endl;
// 	}
// 	else
// 	{
// 	    cout<<"Did Not pass the echo test, Trying again ... Response was"<<response<<endl;
// 	}

// 	p.Write("\000"); //End Echo test

// 	usleep(10000);
// 	p.Write("\204"); //Token for Mode register
// 	usleep(10000);

// 	p.Write("0"); //MODEREGHI
// 	p.Write("135"); //MODEREGMID
// 	p.Write("\207"); //Checksum

// 	p.Write("161"); //MODEREGLO
// 	p.Write("\207"); //Checksum

// 	usleep(10000);
// 	p.Write("4"); //Token for averaging
// 	usleep(10000);

// 	p.Write("0"); //Average
// 	p.Write("2"); //Filter
// 	p.Write("\207"); //Checksum

// 	p.Write("1"); //Polled Mode
// 	usleep(10000);
//         p.Read();

//------------------------------------------
	usleep(4000000);
	p.Write("\1"); //Polled mode command token
        usleep(200000);
	// p.Write("\1"); //Control code
	// usleep(200000);
	p.Write("\000"); //Channele
	usleep(200000);
	// p.Write("\32"); //channel 2 * 16
	// usleep(200000);
	// p.Write("\207"); //Checksum code
	// usleep(200000);
	p.Write("\1"); //Checksum value
	///////////////////////////////////////////
	usleep(6000000);
	// // usleep(200000);
	// p.Write("\2");
	// usleep(2000000);
	// p.Write("\201");
	// usleep(200000);
	// response=p.Read();
	// usleep(200000);
	// // p.Write(" ");
	// // usleep(200000);
	p.Write("\201");
	usleep(200000);
	p.Write("\17"); //Placeholder
	usleep(200000);
	p.Write("\220"); //Checksum Value
     	//usleep(200000);
    	usleep(200000);
    	response=p.Read();
	// usleep(200000);
	// p.Write("\201");
	// usleep(200000);
    	// response=p.Read();
	// usleep(200000);
	// p.Write("\201");
	// usleep(200000);
    	// response=p.Read();

    }
 
    return(0);

}
