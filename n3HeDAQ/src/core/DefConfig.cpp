//Changing DAQ Configuration.
//Author: Latiful Kabir
//Date:11.23.14
//Version:1.0


#include "Constants.h"
#include "Config.h"

int n3heDefault(int module)
{
    int counter=0;
    //Change Mode
    counter+=ChangeMode(module,1);
    //Change Event Length
    counter+=ChangeLength(module,n3He_EVENT);
    //Change Resolution
    counter+=ChangeRes(module,1);
    //Change Sample Rate
    counter+=ChangeRate(module,n3He_RATE);
    //Change Decimation  
    counter+=ChangeDecimation(module,n3He_NACC); //nacc(16,16)
    return(counter);
}

int ContinuousMode(int module)
{
    int counter=0;
    //Change Mode
    counter+=ChangeMode(module,2);
    //Change Resolution
    counter+=ChangeRes(module,1);
    //Change Sample Rate
    counter+=ChangeRate(module,CONT_RATE);
    //Change Decimation  
    counter+=ChangeDecimation(module,CONT_NACC); //nacc(16,16)
    return(counter);
}
