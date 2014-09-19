//The basic XY movement program
//Author: Latiful Kabir
//Version:0.0
//Date:09.12.14


#include<iostream>
#include<string>
#include<cstdio>
#include <unistd.h>
#include"Serial.h"

using namespace std;

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

    char read_buf[10];
//Movement using char array with increment from user
    char move1[200];
    int increment=4800;
    sprintf(move1,"CI2M%d\rR",increment);


//Movement using string with additive properties
    string incre="800";
    string move2="CI1M" + incre + "\rR";

    Serial xy("/dev/ttyUSB0",9600);

    if(xy.CheckStatus()!=1)
    {

	// cout<<"Enabling Online mode ... ..."<<endl;
	// xy.Write("F");
    	// sleep(2);

	xy.Write(move2.c_str());
	sleep(2);
	xy.Write(move1);
	sleep(2);

	xy.Write("X"); //Request X position
	sleep(1);  
	xy.Read(read_buf);    //Read requested position

	int pos=GetPosition(read_buf);
	cout<<"Position: "<<pos<<endl;

	xy.Write("Y"); //Request X position
	sleep(1);  
	xy.Read(read_buf);    //Read requested position

        pos=GetPosition(read_buf);
	cout<<"Position: "<<pos<<endl;



	// xy.Write("N"); //Null absolute position resister
	// xy.Write("Y"); // Request Y position
        //sleep(3);
	// xy.Read(); //Read requested position
    }
    return(0);
}
