//Changing DAQ Configuration.
//Author: Latiful Kabir
//Date:11.23.14
//Version:1.0


#include<iostream>
#include"Constants.h"
#include"Help.h"
#include"Config.h"
using namespace std;

int CustomConfig()
{
    unsigned int param;
    unsigned int value;
    unsigned int module;
    char more1='y';
    char more2='c';

    Title();
    cout<<"\n\n\n\t\t ====================Change DAQ Configuration========================\n\n\n"<<endl;
    while(more1=='y')
    { 
	more1='n';
	cout<<"\nEnter Module:"<<endl;
	cin>>module; //DAQ Module
	if(!(module==21 ||  module==22 || module==23 || module==24 || module==30))
	{
	    cout<<"Invalid Module"<<endl;
	    return(1);
	}
	while(more2=='c')
	{ 
	    more2='q';
	    int change_status=0;
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
		if(value<1 || value >128)
		{
		    cout<<"Invalid Rate. It should be between 1-128 KHz"<<endl;
		    return(1);
		}
		else
		{
		    cout<<"Making Changes. Please wait ... ..."<<endl;
		    change_status=ChangeRate(module,value);
		}
	    }
	    if(param==2)
	    {
		if(value<1 || value >7) 
		{
		    cout<<"Invalid mode. Check Syntax"<<endl;
		    return(1);
		}
		else
		{
		    cout<<"Making Changes. Please wait ... ..."<<endl;
		    change_status= ChangeMode(module,value);
                    if(value==1 || value==3)
                    ChangeLength(module,650);
		}
	    }
	    if(param==3)
	    {
		if(value<39)
		{
		    cout<<"Invalid Event Length.Must be greater than 39."<<endl;
		    return(1);
		}
		else
		{
		    cout<<"Making Changes. Please wait ... ..."<<endl;
		    change_status=ChangeLength(module,value);
		}
	    }
	    if(param==4)
	    {
		if((value <0) || (value>1))
		{
		    cout<<"Invalid Hi_Res_Mode"<<endl;
		    return(1);
		}
		else
		{
		    cout<<"Making Changes. Please wait ... ..."<<endl;
		    change_status=ChangeRes(module,value);
		}
	    }
	    if(param==5)
	    {
		if((value < 1) || (value > 64))
		{
		    cout<<"Invalid Averaging."<<endl;
		    return(1);
		}
		else
		{
		    cout<<"Making Changes. Please wait ... ..."<<endl;
		    change_status=ChangeAveraging(module,value);
		}
	    }
	    if(param==6)
	    {
		if((value!=1 && value!=value)|| ((value & (value - 1))) || value<1)
		{
		    cout <<"Invalid Decimation.Note it should be power of 2." <<endl; 
		    return(1);
		}
		else
		{
		    cout<<"Making Changes. Please wait ... ..."<<endl;
		    change_status=ChangeDecimation(module,value);
		}
	    }
	    if(change_status==1)
	    {
		cout<<"\nDone with the changes !!!"<<endl;
	    }
	    else
	    {
		cout<<"\nUnable to make changes."<<endl;
	    }
	    cout<<"\nTo make another change for Module: "<<module<<" enter 'c' or 'q' to quit Config menu for Module: "<<module<<endl;
	    cin>>more2;	    
	}
	cout<<"\nTo Change config for another module enter 'y', otherwise 'n' to quit Config menu"<<endl;
	cin>>more1;
	more2='c';
    }
    return 0;
}
