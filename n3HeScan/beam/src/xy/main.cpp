//The XY movement program for beam scan
//Author: Latiful Kabir
//Version:1.0
//Date:09.23.14


#include<iostream>
#include<string>
#include<cstdio>
#include<fstream>
#include<unistd.h>
#include<iomanip>
#include"SerialXY.h"
#include"TakeRun.h"
#include"CalAverage.h"
#include"ConstantsXY.h"

using namespace std;


int main(void)
{
    int unit_x=UNIT_X;
    int unit_y=UNIT_Y;
    int max_x=MAX_X;      //For 14 Inches(40355 actual steps)
    int max_y=MAX_Y;
    int short_sleep=3;
    int X_r,Y_r;  //Requested X,Y Coordinate
    int X_m,Y_m;  //X,Y Coord actually moved
    double intensity=0;
    int custom_x=0;
    int custom_y=0;
    int current_run=0;

    int start_x=START_X;
    int end_x=END_X;
    int start_y=START_Y;
    int end_y=END_Y;
    char home='n';
    char work='n';
    //Open the serial port at 9600 baud rate
    SerialXY xy(SERIAL_PORT,BAUD);


    if(xy.CheckStatus()!=1)
    {
        //Enable online mode with echo off
	cout<<"Enabling Online mode ... ..."<<endl;
	xy.Write("F");
    	sleep(3);

        cout<<"If you want to go to Sweet Home & Null register, Enter 'y', otherwise enter 'n'"<<endl;
        cin>>home;

        if(home=='y')
	{
	    cout<<"Now going Sweet Home!!!"<<endl;
	    xy.MoveXY('X',max_x);
	    xy.MoveXY('Y',max_y);


	    xy.Write("N"); //Null absolute position resister

	    X_m=xy.GetPosition('X');
	    Y_m=xy.GetPosition('Y');
	    X_r=Y_r=0;

	    cout<<"Moved to Y:"<<Y_m<<" X:"<<X_m<<endl;
	    cout<<"Now at Sweet Home!"<<endl<<endl;
	}

        cout<<"To go to start Scan edge, Enter 'e',to go to specific position enter 's', otherwise enter 'n'"<<endl;
        cin>>work;

	switch(work)
	{
	case 'e' :
	{
	    xy.MoveXY('X',start_x);
	    xy.MoveXY('Y',start_y);
	    X_m=xy.GetPosition('X');
	    Y_m=xy.GetPosition('Y');
	    start_x=X_m;
	    start_y=Y_m;
	    cout<<"Moved to Y:"<<Y_m<<" X:"<<X_m<<endl;
	    cout<<"Now at Scan starting edge"<<endl<<endl;
	}
	break;

	case 's' :
	{
	    cout<<"Enter the X and Y diplacement(in unit of steps),for example: 400 -800"<<endl;
	    cin>>custom_x;
	    cin>>custom_y;    
	    if(custom_x!=0 && custom_x<end_x && custom_y!=0 && custom_y < end_y)
	    {
		xy.MoveXY('X',custom_x);
		xy.MoveXY('Y',custom_y);
		X_m=xy.GetPosition('X');
		Y_m=xy.GetPosition('Y');
		start_x=X_m;
		start_y=Y_m;
		cout<<"Moved to Y:"<<Y_m<<" X:"<<X_m<<endl;
		cout<<"Now at custom location"<<endl<<endl;
	    }
	    else
	    {
		cout<<"Invalid Displacement"<<endl;
		return(-1);
	    }
	}
	break;

	default:
	    cout<<"Invalid Option"<<endl;
	    return(-1);
	}

	for(Y_r=start_y;Y_r<=end_y;Y_r=Y_r+unit_y)
	{
	    if(Y_r!=start_y)
	    {
		xy.MoveXY('Y',-1*unit_y);
		Y_m=xy.GetPosition('Y');

		if(Y_m>=end_y)
		{
		    break;
		}
	    }
	   

	    for(X_r=start_x;X_r<=end_x;X_r=X_r+unit_x)
	    {
		cout<<"Now moving to Y: "<<-1*Y_r<<" & X: "<<-1*X_r<<"... ..."<<endl;
		if(X_r!=start_x)
		{	
		    xy.MoveXY('X',-1*unit_x);
		    X_m=xy.GetPosition('X');

		    if(X_m>=end_x)
		    {
			break;
		    }
	
		}
	   
		cout<<"Now at Y: "<<-1*Y_m<<" & X: "<<-1*X_m<<endl;

		cout<<"Recording the beam ... ..."<<endl;
	        
		current_run=RunSingle(DIRTY_DAQ,RUN_LENGTH,1);

		//Calculate the mean here
		intensity=CalAverage(current_run,DIRTY_DAQ,CHANNEL);

		cout<<"Y_req : "<<-1*Y_r<<"    "<<"Y_moved : "<<Y_m<<"    "<<"X_req : "<<-1*X_r<<"    "<<"X_moved : "<<X_m<<"    "<<"intensity : "<<intensity<<endl<<endl;
		//Save to Data File
		xy.BeamData <<setprecision(10);
		xy.BeamData <<setw(10)<<-1*Y_r<<"        "<<setw(10)<<Y_m<<"        "<<setw(10)<<-1*X_r<<"        "<<setw(10)<<X_m<<"        "<<setw(10)<<setprecision(10)<<intensity<<"        "<<endl;
	    }
	    xy.MoveXY('X',-1*X_m);
	    X_m=xy.GetPosition('X');
	    start_x=X_m;
	}
    }
    return(0);
}
