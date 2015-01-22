//The Daq derived class with Socket as base class
//Author: Latiful Kabir
//Date:08.15.14
//Version:1.0

#include"Daq.h"
#include"Progress.h"

using namespace std;

//Constructor for Derived Daq class
Daq::Daq(const char *ip,const char *port,int module,int length):Socket(ip,port,module)
{
    filesize=length;
}


Daq::~Daq()
{

}


void Daq::SaveData(bool pStatus)
{


    int sleepCount = 0;
    bool condn=true;  //Flip it to stop the run
    totRet=0;

    //Implement condition when Socket to be terminated or data taking is finished.For the time being up to desired data file size.
    while ((retVal = ReadData(totRet,filesize)) > -1 && condn)
    {
	WriteData();
	totRet=totRet+retVal;
	//Terminate if server does not respond more than 2 sec
	if (retVal == 0) 
	{
	    if (sleepCount < 2) 
	    {
		sleep(1);
		sleepCount++;
	    }
	    else
		break;
	} 
	else
	    sleepCount = 0;
	if(pStatus)
	{
	    printProgBar((int)(100*totRet/filesize));
	}
	//Stop after the desied run length
	if(totRet>=filesize)
	{
	    condn=false;
	}
    }

}

