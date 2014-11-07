#include<iostream>
#include<unistd.h>
#include"Config.h"
#include"Daq.h"
#include"Constants.h"

#define SLEEP 15e5
using namespace std;

int DaqConfig(unsigned int *param)
{
    string change_config="set.site 1 ";
    char *command=new char[100];

    Daq daq(DAQ30_IP,DAQ_PORT2,DAQ30,RUN_LENGTH);
    if(!daq.CheckStatus())
    {
        //Change Frequency
	if(param[1]!=0)
	{
            //Set the external clock
	    sprintf(command,"fpmux xclk");
	    // change_config=change_config+command;
	    daq.WriteToSocket(command);

	    //Set the clock
	    sprintf(command,"clk 1,1,0");
	    change_config=change_config+command;
	    daq.WriteToSocket(change_config.c_str());
          
            //Divide the clock
	    sprintf(command,"clkdiv 1");
	    change_config=change_config+command;
	    daq.WriteToSocket(change_config.c_str());
         
            //Set the mb_clock
	    sprintf(command,"mb_clk 64000 %d",param[1]);
	    // change_config=change_config+command;
	    daq.WriteToSocket(command);
	}

        //Change Running Mode
	if(param[2]!=0)
	{
	    if(param[2]==1)
	    {
		sprintf(command,"rgm=1,0,1"); //Triggered & Synchronized,d0, rising 
	    }
	    else if(param[2]==2)
	    {
		sprintf(command,"rgm=0,0,0"); //Trigger Off
	    }
	    else if(param[2]==3)
	    {
		sprintf(command,"rgm=1,0,0");//Triggered & Synchronized,d0,falling 
	    }
	    else if(param[2]==4)
	    {
		sprintf(command,"rgm=2,0,1");//Triggered & Gated,d0,Rising 
	    }
	    else if(param[2]==5)
	    {
		sprintf(command,"rgm=2,0,0");//Triggered & Gated,d0,Falling 
	    }
	    else if(param[2]==7)
	    {
		sprintf(command,"rgm=3,0,1");//Triggered & Continuous,d0,Rising 
	    }
	    else if(param[2]==8)
	    {
		sprintf(command,"rgm=3,0,0");//Triggered & Continuous,d0,Falling 
	    }
	   
	    change_config=change_config+command;
	    daq.WriteToSocket(change_config.c_str());
	    usleep(SLEEP);

          //rgm=MODE,line (0=d0, front panel), edge
          //MODE :0=OFF, 2=RGM, 3=RTM, 1=SRTM
          //Edge: 0=falling, 1=rising
          //Repeating Gate Mode RGM : captures on active level of the trigger
          //Repeating Trigger Mode RTM : starts on active edge, continues nsamples
          //Sync RTM SRTM : resynchronises to the active edge, captures nsamples : Which is required for n3He!	   
	}

        //Change Event Length
	if(param[3]!=0)
	{
	    sprintf(command,"rtm_translen=%d",param[3]);
	    change_config=change_config+command;
	    daq.WriteToSocket(change_config.c_str());
	    usleep(SLEEP);
	}

       //Change Hi_Res_Mode (Averaging and Decimation)
	if(param[4]!=0)
	{
	    sprintf(command,"hi_res_mode=%d",param[4]-1);
	    change_config=change_config+command;
	    daq.WriteToSocket(change_config.c_str());
	    usleep(SLEEP);
	}

        //Change nacc (Averaging and Decimation)
	if(param[5]!=0 && param[6]!=0)
	{
	    sprintf(command,"nacc=%d,%d",param[5],param[6]);
	    change_config=change_config+command;
	    daq.WriteToSocket(change_config.c_str());
	    usleep(SLEEP);
	}
    }
    delete[] command;
    return(0);
}

int ChangeConfig(void)
// int main(void)
{
    unsigned int *param=new unsigned int[7];

//cout<<"Select Options"<<endl;
//cout<<"1:To set n3he default DAQ setting for all the modules"<<endl;
//cout<<"2:To set n3he default DAQ setting for one modules"<<endl;
//cout<<"3:To set Custom setting for each module"<<endl;
//cout<<"4:To Print current DAQ setting"<<endl; 

    cout<<"Enter Config in the following format. Enter Zero in a field if you do not want to that parameter. "<<endl;    
    cout<<"MODULE RATE MODE EVENT_LENGTH HI_RES_MODE AVERAGING DECIMATION"<<endl;
    cin>>param[0];  //DAQ Module
    cin>>param[1];  //Sample Rate
    cin>>param[2];  //Running Moade
    cin>>param[3];  //Event Length
    cin>>param[4];  //Hi_Res_Mode
    cin>>param[5];  //Averaging
    cin>>param[6];  //Decimation
    
    cout<<"You entered: \nModule:"<<param[0]<<"  \nRate:"<<param[1]<<" \nMode:"<<param[2]<<" \nEvent Length:"<<param[3]<<"  \nHi Res Mode:"<<param[4]<<"  \nAveraging:"<<param[5]<<"  \nDecimation:"<<param[6]<<endl;

    if(!(param[0]==21 ||  param[0]==22 || param[0]==23 || param[0]==24 ||param[0]==26 || param[0]==30))
    {
	cout<<"Invalid Module"<<endl;
        return(1);
    }
    if(param[1]<0 || param[1] >128)
    {
	cout<<"Invalid Rate. It should be between 1-128 KHz"<<endl;
        return(1);
    }
    if(param[2]<0 || param[2] >8) 
    {
	cout<<"Invalid mode. Check Syntax"<<endl;
        return(1);
    }
    if(param[3]<39 && param[3]!=0)
    {
	cout<<"Invalid Event Length.Must be greater than 39."<<endl;
        return(1);
    }
    if(param[4] <0 || param[4] >2)
    {
	cout<<"Invalid Hi_Res_Mode"<<endl;
        return(1);
    }
    if(param[5] < 0 || param[5] > 64 )
    {
	cout<<"Invalid Averaging."<<endl;
        return(1);
    }
    if((param[6]!=1 && param[6]!=param[6] && param[6]!=0)|| ((param[6] & (param[6] - 1))) || param[6]<0)
    {
        cout <<"Invalid Decimation.Note it should be power of 2." <<endl; 
        return(1);
    }
    DaqConfig(param);
    cout<<"Done with the changes !!!"<<endl;
    delete[] param;
    return 0;
}

//Suggested demo use:
        //daq.WriteToSocket(command);
        //Suggested Use
    	// daq.WriteToSocket("nacc=1,1");
    	// daq.WriteToSocket("do4_0 1");
    	// daq.WriteToSocket("set.site 1 rgm=1,0,1");
    	// daq.WriteToSocket("set.site 1 hi_res_mode=1");
