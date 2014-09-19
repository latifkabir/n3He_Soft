//The basic XY movement program
//Author: Latiful Kabir
//Version:0.0
//Date:09.12.14


#include<iostream>
#include<string>
#include<cstdio>
#include<fstream>
#include <unistd.h>
#include<iomanip>
#include"Serial.h"

using namespace std;
int GetPosition(char *read_buf);


int GetPosition(char *read_buf)
{
    int position;
    int j;
    for(int i=0;i<10;i++)
    {
	if(read_buf[i]=='+' || read_buf[i]=='-')
	{
	    j=i;
	}
    }
    position=(1e6)*((int)read_buf[j+1]-48)+(1e5)*((int)read_buf[j+2]-48)+(1e4)*((int)read_buf[j+3]-48)+(1e3)*((int)read_buf[j+4]-48)+(1e2)*((int)read_buf[j+5]-48)+10*((int)read_buf[j+6]-48)+((int)read_buf[j+7]-48);

    if(read_buf[j]=='+')
    {
	return(position);
    }
    else if(read_buf[j]=='-')
    {
	return(-1*position);
    }
    else
    {
	return(-1);
    }
}


int main(void)
{
    int unit_x=400;
    int unit_y=400;
    int max_x=1000;
    int max_y=1000;
    int sleep_time_move=3;
    int sleep_time=3;
    int X,Y;    //X, Y Coord for printing
    int X_r,Y_r;  //Requested X,Y Coordinate
    int X_m,Y_m;  //X,Y Coord actually moved
    double intensity=0;
    char read_buf[10];

//Movement using char array with increment from user
    char move_x[200];
    char move_y[200];
    char home_x[200];
    char home_y[200];

    ofstream BeamData("Beamdata.txt",ofstream::app);

    sprintf(move_x,"CI1M%d\rR",unit_x);
    sprintf(move_y,"CI2M%d\rR",unit_y);
    sprintf(home_x,"CI1M%d\rR",max_x);
    sprintf(home_y,"CI2M%d\rR",max_y);


//Open the serial port at 9600 baud rate
    Serial xy("/dev/ttyUSB0",9600);



    if(xy.CheckStatus()!=1)
    {
//Enable online mode with echo off
	cout<<"Enabling Online mode ... ..."<<endl;
	xy.Write("F");
    	sleep(sleep_time);

	cout<<"Now going Sweet Home!!! ...."<<endl;
	xy.Write(home_x);
	sleep(sleep_time_move);
	xy.Write(home_y);
	sleep(sleep_time_move);

	xy.Write("N"); //Null absolute position resister

	xy.Write("X"); //Request X position
	sleep(sleep_time);  
	xy.Read(read_buf);    //Read requested position
	X_m=GetPosition(read_buf);

	xy.Write("Y"); //Request Y position
	sleep(sleep_time);  
	xy.Read(read_buf);    //Read requested position
	Y_m=GetPosition(read_buf);
	cout<<"Moved X:"<<X_m<<"Y:"<<Y_m<<endl;

	cout<<"Now at Sweet Home!"<<endl;
	X=0;
	Y=0;
	cout<<"Recording the beam ... ..."<<endl;
        //Call to TakeData() here;
        //Calculate the mean here
        cout<<"X : "<<X<<"    "<<"Y : "<<Y<<"    "<<"intensity : "<<intensity<<endl;
        //Save to Data File
	BeamData <<setw(10);
	BeamData << setprecision(8)<<X<<"    "<<Y<<"    "<<intensity<<endl;

	X=X+unit_x;
	Y=Y+unit_y;
	cout<<"Now moving to X: "<<X<<" & Y: "<<Y<<"... ..."<<endl;
	xy.Write(move_x);
	sleep(sleep_time_move);
	xy.Write(move_y);
	sleep(sleep_time_move);

	xy.Write("X"); //Request X position
	sleep(sleep_time);  
	xy.Read(read_buf);    //Read requested position
	X_m=GetPosition(read_buf);

	sleep(sleep_time);
	xy.Write("Y"); //Request Y position
	sleep(sleep_time);  
	xy.Read(read_buf);    //Read requested position
	Y_m=GetPosition(read_buf);
	cout<<"Moved X:"<<X_m<<"Y:"<<Y_m<<endl;


	cout<<"Now at X: "<<X<<" & Y: "<<Y<<endl;

	cout<<"Recording the beam ... ..."<<endl;
        //Call to TakeData() here;
        //Calculate the mean here
        cout<<"X : "<<X<<"    "<<"Y : "<<Y<<"    "<<"Intensity : "<<intensity<<endl;
        //Save to Data File
	BeamData <<setw(10);
	BeamData << setprecision(8)<<X<<"    "<<Y<<"    "<<intensity<<endl;

    }
    return(0);
}
