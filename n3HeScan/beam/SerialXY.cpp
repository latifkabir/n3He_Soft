//The SerialXY derived class with Serial as base class
//Author: Latiful Kabir
//Date:09.5.14
//Version:1.0


#include<stdio.h>
#include<string>
#include<iostream>
#include<time.h>
#include<iomanip>
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
    sprintf(move_x,"CI1M%d\rR",increment);
    sprintf(move_y,"CI2M%d\rR",increment);

    if(axis=='X')
    {
	Write(move_x);
    }
    else if(axis=='Y')
    {
	Write(move_y);
    }

    
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


int main()
{
    SerialXY test("/dev/ttyUSB0",9600);
    if(test.CheckStatus()!=1)
    {
	test.Write("N");
	sleep(3);
	test.MoveXY('X',20000);
	sleep(30);
	test.MoveXY('Y',400);
	int x=test.GetPosition('X');
	int y=test.GetPosition('Y');
	cout<<"X:"<<x<<" Y:"<<y<<endl;
    }
    return(0);
}
