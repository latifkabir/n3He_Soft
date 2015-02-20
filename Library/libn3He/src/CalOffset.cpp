// The Dynamic Offset Calculation to go around issues with data stream for first few events from the DAQ


#include "ReadBinary.h"

#define ES_MAGIC1 0xaa55f154
#define ES_MAGIC2 0xaa55f15f

int CalOffset(const char* filename,int module)
{
    ReadBinary fa(filename);
    int h=0;
    int skipSamples=0;

    for(int i=0;i<20000;i++)
    {
	if(fa.GetValue(0,i)==5)
	{
	    skipSamples=i;
	    break;
	}
    }

    return skipSamples;
}
