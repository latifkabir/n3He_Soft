//The SerialXY derived class with Serial as base class(For Velmex motor with XY stage through Serial(RS232) port.)

//Author: Latiful Kabir
//Date:09.22.14
//Version:1.0


#include<stdio.h>
#include<string>
#include<iostream>
#include<time.h>
#include<iomanip>
#include<cmath>
#include"SerialXY.h"


using namespace std;

SerialXY::SerialXY(const char *portName,int sspeed):Serial(portName,sspeed)
{
    BeamData.open("BeamData.txt",ofstream::app);  
}

SerialXY::~SerialXY()
{
    BeamData.close();
}

void SerialXY::MoveXY( char axis,int increment)
{
    sleep_time=abs((int)(0.0006*increment));
 
    sprintf(move_x,"CI1M%d\rR",increment);
    sprintf(move_y,"CI2M%d\rR",increment);

    if(axis=='X')
    {
	cout<<"Moving "<<increment<<" Steps along X axis ....."<<endl;
	Write(move_x);
    }
    else if(axis=='Y')
    {
	cout<<"Moving "<<increment<<" Steps along Y axis ....."<<endl;
	Write(move_y);
    }

    sleep(sleep_time);
    sleep(3);

    
}

int SerialXY::GetPosition(char axis) 
{
    int position;
    int j;

    if(axis=='X')
    {
	Write("X");
    }
    else if(axis=='Y')
    {
	Write("Y");
    }
    sleep(1);
    Read();

    for(int i=0;i<10;i++)
    {
	if(buf[i]=='+' || buf[i]=='-')
	{
	    j=i;
	}
    }
    position=(1e6)*((int)buf[j+1]-48)+(1e5)*((int)buf[j+2]-48)+(1e4)*((int)buf[j+3]-48)+(1e3)*((int)buf[j+4]-48)+(1e2)*((int)buf[j+5]-48)+10*((int)buf[j+6]-48)+((int)buf[j+7]-48);

    if(buf[j]=='+')
    {
	return(position);
    }
    else if(buf[j]=='-')
    {
	return(-1*position);
    }
    else
    {
	return(-1);
    }
}


void SerialXY::CurrentTime()
{
	time_t time_now;
	time(&time_now);
	struct tm my_time;
	localtime_r (&time_now,&my_time);
	int strlen=100;
	char strname[strlen];
	snprintf(strname,strlen,"%04d-%02d-%02d-%02d-%02d-%02d",my_time.tm_year+1900,my_time.tm_mon+1,my_time.tm_mday,my_time.tm_hour,my_time.tm_min,my_time.tm_sec);
	BeamData<<strname<<"	";
	cout<<"\n";
	cout<<"-------------------------"<<endl;
	cout<<strname<<":"<<endl;
	cout<<"-------------------------"<<endl<<endl;
}

