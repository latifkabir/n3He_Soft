//The main program to interact with user
//Author: Latiful Kabir
//Date:08.15.14
//Version:1.0



#include<iostream>
#include<cstdlib>
#include<fstream>
#include<stdio.h>
#include<string>
#include "Help.h"
#include "TakeRun.h"

using namespace std;

int main(int argc,char *argv[])
{
    int j=-1;
    int arg2=0;
    int arg3=0;
    int arg4=0;

    if(argc==3)
    {
	arg2=atof(argv[2]);
    }
    if(argc==4)
    {
	arg2=atof(argv[2]);
        arg3=atof(argv[3]);
    }
    if(argc==5)
    {
	arg2=atof(argv[2]);
        arg3=atof(argv[3]);
        arg4=atof(argv[4]);
    }

//make a list of all available options and command and assign a number for that
    string list[]={"help","start","daq","config"};
    if(argc>1)
    {
	for(int i=0;i<4;i++)
	{
	    if(list[i]==argv[1])
	    {
	        j=i;
		break;
	    }
	}
    }


//Switch to the option or command specified.
    if(argc<2)
    {
	DefaultIns();
    }
    else
    {
	switch(j)
	{
	case 0 :	
	    Instruction();
	    break;
	case 1 :
	{
	    if(arg2==0 && arg3==0)
	    {	
                Title();
		RunAll();
	    }
	    if(arg2!=0 && arg3==0)
	    {	
		Title();
		RunAll(arg2*1e6);
	    }
	    if(arg2!=0 && arg3!=0)
	    {	
		Title();
		RunAll(arg2*1e6,arg3);
	    }
	    break;

	}
	case 2 :	
	{  
	    if(arg2==0 && arg3==0 && arg4==0)
	    {	
		Title();
		RunSingle();
	    }
	    if(arg2!=0 && arg3==0 && arg4==0)
	    {	
		Title();
		RunSingle(arg2);
	    }
	    if(arg2!=0 && arg3!=0 && arg4==0)
	    {	
		Title();
		RunSingle(arg2,arg3*1e6);
	    }
	    if(arg2!=0 && arg3!=0 && arg4!=0)
	    {	
		Title();
		RunSingle(arg2,arg3*1e6,arg4);
	    }
	    break;   
	}
	case 3 :
	{
	    Config();
	    break;
	}
       
	default:
	{
	    DefaultIns();
	}
	}
    }
	
    return(0);
}
