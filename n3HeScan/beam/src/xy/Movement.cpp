//The XY movement program for beam scan
//Author: Latiful Kabir
//Version:1.0
//Date:09.23.14


#include<iostream>
#include<string>
#include<cstdio>
#include<fstream>
#include <unistd.h>
#include<iomanip>
#include"SerialXY.h"
#include"TakeRun.h"
#include"CalAverage.h"

using namespace std;


int main(void)
{
    int unit_x=400;
    int unit_y=400;
    int max_x=1000;
    int max_y=1000;
    int short_sleep=3;
    int X_r,Y_r;  //Requested X,Y Coordinate
    int X_m,Y_m;  //X,Y Coord actually moved
    int X_l,Y_l;  //X,Y Coord of last move
    double intensity=0;


    //Open the serial port at 9600 baud rate
    SerialXY xy("/dev/ttyUSB0",9600);


    if(xy.CheckStatus()!=1)
    {
        //Enable online mode with echo off
	cout<<"Enabling Online mode ... ..."<<endl;
	xy.Write("F");
    	sleep(3);

	cout<<"Now going Sweet Home!!!"<<endl;
	xy.MoveXY('X',-1*max_x);
	xy.MoveXY('Y',-1*max_y);


	xy.Write("N"); //Null absolute position resister

	X_m=X_l=xy.GetPosition('X');
	Y_m=X_l=xy.GetPosition('Y');
	X_r=Y_r=0;

	cout<<"Moved to Y:"<<Y_m<<" X:"<<X_m<<endl;
	cout<<"Now at Sweet Home!"<<endl<<endl;

	for(Y_r=0;Y_r<=max_y;Y_r=Y_r+unit_y)
	{
	    if(Y_r!=0)
	    {
		xy.MoveXY('Y',unit_y);
		Y_l=Y_m;
		Y_m=xy.GetPosition('Y');

		if(Y_m==Y_l)
		{
		    break;
		}
	    }
	   

	    for(X_r=0;X_r<=max_x;X_r=X_r+unit_x)
	    {
		cout<<"Now moving to Y: "<<Y_r<<" & X: "<<X_r<<"... ..."<<endl;
		if(X_r!=0)
		{	
		    xy.MoveXY('X',unit_x);
		    X_l=X_m;
		    X_m=xy.GetPosition('X');

		    if(X_m==X_l)
		    {
			break;
		    }
	
		}
	   
		cout<<"Now at Y: "<<Y_m<<" & X: "<<X_m<<endl;

		cout<<"Recording the beam ... ..."<<endl;
	        
		TakeData(21,1e8,1);

		//Calculate the mean here
		intensity=CalAverage();

		cout<<"Y_req : "<<Y_r<<"    "<<"Y_moved : "<<Y_m<<"    "<<"X_req : "<<X_r<<"    "<<"X_moved : "<<X_m<<"    "<<"intensity : "<<intensity<<endl<<endl;
		//Save to Data File
		xy.BeamData <<setprecision(10);
		xy.BeamData <<setw(10)<<Y_r<<"        "<<setw(10)<<Y_m<<"        "<<setw(10)<<X_r<<"        "<<setw(10)<<X_m<<"        "<<setw(10)<<setprecision(10)<<intensity<<"        "<<endl;
	    }
	    xy.MoveXY('X',-X_m);
	    X_m=xy.GetPosition('X');
	}
    }
    return(0);
}
