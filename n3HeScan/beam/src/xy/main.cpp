//The main program for beam scan
//Author: Latiful Kabir
//Version:1.0
//Date:09.23.14

#include<iostream>
#include"BeamScan.h"

using namespace std;

void Instruction()
{
    cout<<"========= Beam Scan Program Instruction=========="<<endl;
    cout<<"Usage:"<<endl;
    cout<<"./bscan scan"<<endl;
    cout<<"\tThis will make an auomatic full grid scan"<<endl;
cout<<"./bscan custom"<<endl;
    cout<<"\tThis is to move XY table to specific position and take one run"<<endl;
    cout<<"./bscan help"<<endl;
    cout<<"\tThis will pull this help session"<<endl;
    cout<<"Sign Convension for XY displacements:"<<endl;
    cout<<"\tDisplacement is in units of Steps"<<endl;
    cout<<"\t+ for moving away from the motor"<<endl;
    cout<<"\t- for moving  towards the motor"<<endl;
    cout<<"\t 4000 Steps equals 1 Inch"<<endl;
}


int main(int argc,char *argv[])
{
    int j=-1;
  
//make a list of all available options and command and assign a number for that
    string list[]={"help","scan","custom"};
    if(argc>1)
    {
	for(int i=0;i<3;i++)
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
	Instruction();
	return(-1);
    }
 
    switch(j)
    {
    case 0 :
	Instruction();
	break;
    case 1 :
    {
	BeamScan();
	break;
    }
    case 2 :
    {
        CustomMove();
    }
    break;
    default:
       Instruction();
    }
    return(0);   
}
