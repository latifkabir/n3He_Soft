//Changing DAQ Configuration.
//Author: Latiful Kabir
//Date:11.1.14
//Version:1.0

#include<iostream>
#include<fstream>
#include<unistd.h>
#include<cstdlib>
#include"Config.h"
#include"Daq.h"
#include"Constants.h"
#include"Help.h"
#include"DefConfig.h"
#include"CustomConfig.h"

int sleep_time=500000;
using namespace std;

char *command=new char[100];

int MakeChange(int module,char *command,int site)
{
    const char *dmodule;
    string change_config;
    if(site==0)
    {   
        change_config="set.site 0 ";
    }
    else
    {
        change_config="set.site 1 ";
    }

    change_config=change_config+command;
    switch (module)
    {
    case 21:
	dmodule=DAQ21_IP;
        break;
    case 22:
	dmodule=DAQ22_IP;
       break;
    case 23:
	dmodule=DAQ23_IP;
       break;
    case 24:
	dmodule=DAQ24_IP;
       break;
    case 30:	    
	dmodule=DAQ30_IP;
       break;
    default:
	cout<<"Invalid Module"<<endl;
	cout<<"Unable to make changes"<<endl;
	return(-1);
    }
    Daq daq(dmodule,DAQ_PORT2,module,RUN_LENGTH);        
    if(!daq.CheckStatus())
    {
	daq.WriteToSocket(change_config.c_str());
	usleep(sleep_time);
	return(1);
    }
    else
	return(-1);
}

//Change Frequency i.e. Sample Rate
int ChangeRate(int module,int rate)
{
    //Set the external clock
    sprintf(command,"fpmux xclk");
    MakeChange(module,command,0);	   

    //Set the clock
    sprintf(command,"clk 1,1,0");
    MakeChange(module,command,1);	   
          
    //Divide the clock
    sprintf(command,"clkdiv 1");
    MakeChange(module,command,1);	   
         
    //Set the mb_clock
    sprintf(command,"mb_clk 64000 %d",rate*1000);
    int crate= MakeChange(module,command,0);	   
   
    return(crate);
}

//Change Running Mode
int ChangeMode(int module,int mode)
{

    if(mode==1)
    {
	sprintf(command,"rgm=1,0,1"); //Triggered & Synchronized,d0, rising 
    }
    else if(mode==2)
    {
	sprintf(command,"rgm=0,0,0"); //Trigger Off
    }
    else if(mode==3)
    {
	sprintf(command,"rgm=1,0,0");//Triggered & Synchronized,d0,falling 
    }
    else if(mode==4)
    {
	sprintf(command,"rgm=2,0,1");//Triggered & Gated,d0,Rising 
    }
    else if(mode==5)
    {
	sprintf(command,"rgm=2,0,0");//Triggered & Gated,d0,Falling 
    }
    else if(mode==6)
    {
	sprintf(command,"rgm=3,0,1");//Triggered & Continuous,d0,Rising 
    }
    else if(mode==7)
    {
	sprintf(command,"rgm=3,0,0");//Triggered & Continuous,d0,Falling 
    }

    int cmode=MakeChange(module,command,1);	   
    return(cmode);
    //rgm=MODE,line (0=d0, front panel), edge
    //MODE :0=OFF, 2=RGM, 3=RTM, 1=SRTM
    //Edge: 0=falling, 1=rising
    //Repeating Gate Mode RGM : captures on active level of the trigger
    //Repeating Trigger Mode RTM : starts on active edge, continues nsamples
    //Sync RTM SRTM : resynchronises to the active edge, captures nsamples : Which is required for n3He!	   
}

//Change Event Length
int ChangeLength(int module,int length)
{
    //Change Event Length
    sprintf(command,"rtm_translen=%d",length);
    int clen= MakeChange(module,command,1);	   

    return(clen);
}


//Change Hi_Res_Mode
int ChangeRes(int module,int res)
{
    sprintf(command,"hi_res_mode=%d",res);
    int cres= MakeChange(module,command,1);	   
    return(cres);
}

//Change nacc (Averaging)
int ChangeAveraging(int module,int avg)
{
    sprintf(command,"nacc=%d,%d",avg,1);
    int cavg= MakeChange(module,command,1);	   
    return(cavg);
}

//Change nacc (Decimation)
int ChangeDecimation(int module,int dec)
{
    sprintf(command,"nacc=%d,%d",dec,dec);
    int cdec=MakeChange(module,command,1);	   
    return(cdec);
}    
    
int ChangeConfig(void)
{
    int option=0;
    int success;
    int daq[5]={21,22,23,24,30};

    Title();
    cout<<"\n\n\n\t\t ====================DAQ Configuration========================\n\n\n"<<endl;

    cout<<"Select Any Option:"<<endl;
    cout<<"1:To set n3he default DAQ setting for all the modules"<<endl;
    cout<<"2:To set continuous mode for all DAQ modules"<<endl;
    cout<<"3:To set Custom setting for each module"<<endl;
    cout<<"4:To Print current DAQ setting\n"<<endl;
    cout<<"Enter the number:"<<endl;
    cin>>option;

    switch(option)
    {
    case 1:
	for(int i=0;i<5;i++)
	{
	    success=0;
	    cout<<"Making Changes for DAQ "<<daq[i]<<". Please wait ... ..."<<endl;
	    success=n3heDefault(daq[i]);
	    if(success==5)
	    {
		cout<<"DAQ "<<daq[i]<<" successfully set to n3He default setting"<<endl;
	    }
	    else
	    {
		cout<<"Unable to make changes to DAQ "<<daq[i]<< ". NOT Connected."<<endl;
	    }
	}
	break;
    case 2:
	for(int i=0;i<5;i++)
	{
	    success=0;
	    cout<<"Making Changes for DAQ "<<daq[i]<<". Please wait ... ..."<<endl;
	    success=ContinuousMode(daq[i]);
	    if(success==4)
	    {
		cout<<"DAQ "<<daq[i]<<" successfully set to continuous mode"<<endl;
	    }
	    else
	    {
		cout<<"Unable to make changes to DAQ "<<daq[i]<< ". NOT Connected."<<endl;
	    }
	}
	break;
    case 3:
	CustomConfig();
	break;
    case 4:
    {
	const char *dmodule;

	for(int i=0;i<5;i++)
	{
	    if(i == 0)
		dmodule=DAQ21_IP;
	    if(i == 1)
		dmodule=DAQ22_IP;
	    if(i == 2)
		dmodule=DAQ23_IP;
	    if(i == 3)
		dmodule=DAQ24_IP;
	    if(i== 4)
		dmodule=DAQ30_IP;

	    sprintf(command,CONFIG_SH,daq[i]);
	    Daq daq_test(dmodule,DAQ_PORT2,daq[i],RUN_LENGTH);       
	    if(!daq_test.CheckStatus())
	    {
		if(ifstream(SH_SCRIPT))
		{
		    system(command);
		}
		else
		{
		    cout<<"Required Shell Script NOT found"<<endl;
		    break;
		}
	    }
	    else
	    {
		cout<<"DAQ "<<daq[i]<<" is NOT connected"<<endl;
	    }
	}
    }
    break;
    default:
	cout<<"Invalid Selection."<<endl;
    }

    return 0;
}
