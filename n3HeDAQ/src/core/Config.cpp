//Changing DAQ Configuration.
//Author: Latiful Kabir
//Date:11.1.14
//Version:1.0

#include<iostream>
#include<unistd.h>
#include"Config.h"
#include"Daq.h"
#include"Constants.h"
#include"Help.h"

using namespace std;

char *command=new char[100];

int MakeChange(int module,char *command,int site)
{
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
	    
    Daq daq(DAQ30_IP,DAQ_PORT2,DAQ30,RUN_LENGTH);
    if(!daq.CheckStatus())
    {
  	    daq.WriteToSocket(change_config.c_str());
    }
    return(0);
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
    MakeChange(module,command,0);	   
   
    return(0);
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

    MakeChange(module,command,1);	   
    return(0);
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
    MakeChange(module,command,1);	   

    return(0);
}


//Change Hi_Res_Mode
int ChangeRes(int module,int res)
{
    sprintf(command,"hi_res_mode=%d",res);
    MakeChange(module,command,1);	   
    return(0);
}

//Change nacc (Averaging)
int ChangeAveraging(int module,int avg)
{
    sprintf(command,"nacc=%d,%d",avg,1);
    MakeChange(module,command,1);	   
    return(0);
}

//Change nacc (Decimation)
int ChangeDecimation(int module,int dec)
{
    sprintf(command,"nacc=%d,%d",dec,dec);
    MakeChange(module,command,1);	   
    return(0);
}    
    
int ChangeConfig(void)
{
    unsigned int param;
    unsigned int value;
    unsigned int module;
    char more1='c';
    char more2='c';
//cout<<"Select Options"<<endl;
//cout<<"1:To set n3he default DAQ setting for all the modules"<<endl;
//cout<<"2:To set n3he default DAQ setting for one modules"<<endl;
//cout<<"3:To set Custom setting for each module"<<endl;
//cout<<"4:To Print current DAQ setting"<<endl;
    Title();
    cout<<"\n\n\n\t\t ====================Change DAQ Configuration========================\n\n\n"<<endl;
    while(more1=='c')
    { 
	cout<<"\nEnter Module:"<<endl;
	cin>>module; //DAQ Module
	if(!(module==21 ||  module==22 || module==23 || module==24 ||module==26 || module==30))
	{
	    cout<<"Invalid Module"<<endl;
	    return(1);
	}
	while(more2=='c')
	{
	    cout<<"\nCheck the following table to choose the correct integer value "<<endl<<endl;    
            cout<<"PARAMETER_CODE\t\tPOSSIBLE VALUES"<<endl;
	    cout<<"=============\t\t==============="<<endl;
	    cout<<"1:RATE \t\t\t 0-128KHz "<<endl;
	    cout<<"2:MODE \t\t\t 1:Triggered,Sync,Rising 2:Trigg Off 3:Trigger,Sync,Falling \n\t\t\t 4:Trig,Gated,Rising 5:Trig,Gated,Falling 6:Trig,Continuous,Rising 7:Trig,Continuous,Falling"<<endl;
	    cout<<"3:EVENT_LENGTH \t\t Integer above 39 "<<endl;
	    cout<<"4:HI_RES_MODE \t\t 0:Low Res Mode 1:Hi Res Mode"<<endl;
	    cout<<"5:AVERAGING \t\t 1-64 (This will set decimation 1)"<<endl;
	    cout<<"6:DECIMATION\t\t Integer,power of 2,This will also set averaging, nacc=n,n"<<endl;
	    cout<<"\nEnter Parameter Code followed by it's value:"<<endl;
	    cin>>param;  //Parameter Code
	    cin>>value;  //Parameter Value
	  
	    if(param==1)
	    {
		if(value<0 || value >128)
		{
		    cout<<"Invalid Rate. It should be between 1-128 KHz"<<endl;
		    return(1);
		}
		else
		    ChangeRate(module,value);
	    }
	    if(param==2)
	    {
		if(value<0 || value >8) 
		{
		    cout<<"Invalid mode. Check Syntax"<<endl;
		    return(1);
		}
		else
		    ChangeMode(module,value);
	    }
	    if(param==3)
	    {
		if(value<39 && value!=0)
		{
		    cout<<"Invalid Event Length.Must be greater than 39."<<endl;
		    return(1);
		}
		else
		    ChangeLength(module,value);
	    }
	    if(param==4)
	    {
		if(value <0 || value >2)
		{
		    cout<<"Invalid Hi_Res_Mode"<<endl;
		    return(1);
		}
		else
		    ChangeRes(module,value);
	    }
	    if(param==5)
	    {
		if(value < 0 || value > 64 )
		{
		    cout<<"Invalid Averaging."<<endl;
		    return(1);
		}
		else
		    ChangeAveraging(module,value);
	    }
	    if(param==6)
	    {
		if((value!=1 && value!=value && value!=0)|| ((value & (value - 1))) || value<0)
		{
		    cout <<"Invalid Decimation.Note it should be power of 2." <<endl; 
		    return(1);
		}
		else
		    ChangeDecimation(module,value);
	    }
	    cout<<"\nDone with the changes !!!"<<endl;
	    cout<<"\nTo make another change for Module: "<<module<<" enter 'c' or 'q' to quit Config menu for Module: "<<module<<endl;
	    cin>>more2;
	}
	cout<<"\nTo Change config for another module enter 'c', otherwise 'q' to quit Config menu"<<endl;
	cin>>more1;
    }
    return 0;
}
