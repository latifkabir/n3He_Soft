//The XY movement program for beam scan
//Author: Latiful Kabir
//Version:1.0
//Date:09.23.14


#include<iostream>
#include<cstdlib>
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

int current_run=0;
double intensity_m4=0;
double intensity_m1=0;
extern bool stop;

int BeamScan(void)
{
    int unit_x=UNIT_X;
    int unit_y=UNIT_Y;
    int max_x=MAX_X;      //For 14 Inches(40355 actual steps)
    int max_y=MAX_Y;
    int short_sleep=3;
    int X_r,Y_r;  //Requested X,Y Coordinate
    int X_m,Y_m;  //X,Y Coord actually moved
    int custom_x=0;
    int custom_y=0;

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
	    xy.MoveXY('X',-1*start_x);
	    xy.MoveXY('Y',-1*start_y);
	    X_m=xy.GetPosition('X');
	    Y_m=xy.GetPosition('Y');
	    start_x=-1*X_m;
	    start_y=-1*Y_m;
	    cout<<"Moved to Y:"<<Y_m<<" X:"<<X_m<<endl;
	    cout<<"Now at Scan starting edge"<<endl<<endl;
	}
	break;

	case 's' :
	{
	    cout<<"Enter the X and Y diplacement(in unit of steps),for example: 400 -800"<<endl;
	    cin>>custom_x;
	    cin>>custom_y;    
	    if(custom_x<end_x && custom_y < end_y)
	    {
		if(custom_x!=0)
		    xy.MoveXY('X',custom_x);
		if(custom_y!=0)
		    xy.MoveXY('Y',custom_y);
		X_m=xy.GetPosition('X');
		Y_m=xy.GetPosition('Y');
		start_x=-1*X_m;
		start_y=-1*Y_m;
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
	    cout<<"Invalid Option or You chose not to scan."<<endl;
	    return(-1);
	}

	for(Y_r=start_y;Y_r<=end_y;Y_r=Y_r+unit_y)
	{
	    if(stop)
		break;
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
		if(stop)
		    break;
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
	   
		cout<<"Now at Y: "<<Y_m<<" & X: "<<X_m<<endl;

		cout<<"Recording the beam ... ..."<<endl;
	        
		current_run=RunSingle(DIRTY_DAQ,RUN_LENGTH,1);

		//Calculate the mean here
		intensity_m4=CalAverage(current_run,DIRTY_DAQ,CHANNEL_M4);
		intensity_m1=CalAverage(current_run,DIRTY_DAQ,CHANNEL_M1);

		cout<<"Y_req : "<<-1*Y_r<<"    "<<"Y_moved : "<<Y_m<<"    "<<"X_req : "<<-1*X_r<<"    "<<"X_moved : "<<X_m<<"    "<<"intensity : "<<intensity_m4<<endl<<endl;
		//Save to Data File
		xy.BeamData <<setprecision(10);
		xy.BeamData <<setw(10)<<current_run<<"        "<<setw(10)<<-1*Y_r<<"        "<<setw(10)<<Y_m<<"        "<<setw(10)<<-1*X_r<<"        "<<setw(10)<<X_m<<"        "<<setw(10)<<setprecision(10)<<intensity_m4<<"        "<<setw(10)<<setprecision(10)<<intensity_m1<<endl;
	    }
	    if(!stop && Y_r<end_y)
	    {
		xy.MoveXY('X',(-1*X_m-START_X));
		X_m=xy.GetPosition('X');
		start_x=(-1*X_m);
	    }
	    if(Y_r>=end_y)
	    {
		cout<<"Current Location Y: "<<Y_m<<" X : "<<X_m<<endl;
		cout<<"Done with the Scan !!!"<<endl;
		// xy.BeamData <<setw(10)<<current_run<<"        "<<setw(10)<<Y_m<<"        "<<setw(10)<<Y_m<<"        "<<setw(10)<<X_m<<"        "<<setw(10)<<X_m<<"        "<<"        "<<endl;
	    }
	}
    }
    return(0);
}


int CustomMove()
{
    int x=0;
    int y=0;
    int x_m=0;
    int y_m=0;
    char shot='n';

    cout<<"Enter X and Y displacement separated by space:";
    cin>>x;
    cin>>y;
    if(abs(x)>MAX_X || abs(y)>MAX_Y)
    {
	cout<<"Requested displacement is out of range"<<endl;
	return(-1);
    }

    SerialXY xy(SERIAL_PORT,BAUD);

    if(xy.CheckStatus()!=1)
    {
        //Enable online mode with echo off
	cout<<"Enabling Online mode ... ..."<<endl;
	xy.Write("F");
    	sleep(3);
	
	if(x!=0)
	    xy.MoveXY('X',x);
	if(y!=0)
	    xy.MoveXY('Y',y);
	x_m=xy.GetPosition('X');
	y_m=xy.GetPosition('Y');
	cout<<"Moved to Y:"<<y_m<<" X:"<<x_m<<endl;	
    }
	cout<<"If you want to take data at this position, enter 'y', otherwise enter 'n'"<<endl;
	cin>>shot;

	if(shot=='y')
	{

		current_run=RunSingle(DIRTY_DAQ,RUN_LENGTH,1);

		//Calculate the mean here
		intensity_m4=CalAverage(current_run,DIRTY_DAQ,CHANNEL_M4);
		intensity_m1=CalAverage(current_run,DIRTY_DAQ,CHANNEL_M1);

		cout<<"Y_req : "<<y<<"    "<<"Y_moved : "<<y_m<<"    "<<"X_req : "<<x<<"    "<<"X_moved : "<<x_m<<"    "<<"intensity : "<<intensity_m4<<endl<<endl;
		//Save to Data File
		xy.BeamData <<setprecision(10);
		xy.BeamData <<setw(10)<<current_run<<"        "<<setw(10)<<y<<"        "<<setw(10)<<y_m<<"        "<<setw(10)<<x<<"        "<<setw(10)<<x_m<<"        "<<setw(10)<<setprecision(10)<<intensity_m4<<"        "<<setw(10)<<setprecision(10)<<intensity_m1<<endl;
	    
	}
	return(0);
}
