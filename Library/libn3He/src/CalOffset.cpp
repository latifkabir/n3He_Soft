// The Dynamic Offset Calculation to go around issues with data stream for first few events from the DAQ


#include "ReadBinary.h"
#include<iostream>
using namespace std;

#define ES_MAGIC1 0xaa55f154
#define ES_MAGIC2 0xaa55f15f

int CalOffset(const char* filename,int module)
{
    int match;
    if(module!=30)
	match=3330; //The number of samples for Clean Event#5
    else
	match=6650; //The number of samples for Dirty Event#5

    ReadBinary fa(filename);
    int skipSamples=0;

    for(int i=8000;i<15000;i++)
    {
    	if(fa.GetValue(0,i)==match)
    	{
    	    skipSamples=i;
    	    break;
    	}
    }

    // cout<<"DAQ "<<module<<" Offset :"<<skipSamples<<endl;
    return skipSamples;
}


//Expected offset Clean:9606(if data stream is perfect) +- 48(or it's multiple) when data stream is not perfect 
//Expected offset Dirty: 13001(if data stream if perfect)+-2(or it's multiple) when data stream is not perfect
