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
    if(module!=30)
    counter+=ChangeLength(module,n3He_EVENT);
    if(module==30)
    counter+=ChangeLength(module,DIRTY_EVENT);
 
   //Change Resolution
    if(module!=30)
    counter+=ChangeRes(module,1);
    if(module==30)
    counter+=ChangeRes(module,0);

    //Change Sample Rate
    counter+=ChangeRate(module,n3He_RATE);

    //Change Decimation 
    if(module!=30) 
    counter+=ChangeDecimation(module,n3He_NACC); //nacc(16,16)
    if(module==30)
    counter+=ChangeDecimation(module,DIRTY_NACC); //nacc(1,1)

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
