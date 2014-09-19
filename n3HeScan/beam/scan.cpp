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
    position=(1e6)*read_buf[3]+(1e5)*read_buf[4]+(1e4)*read_buf[5]+(1e3)*read_buf[6]+(1e2)*read_buf[7]
	+10*read_buf[8]+read_buf[9];
    return(position);
}

int main(void)
{

    char read_buf[10];
//Movement using char array with increment from user
    char move1[200];
    int increment=-800;
    sprintf(move1,"CI1M%d\rR",increment);


//Movement using string with additive properties
    string incre="-800";
    string move2="CI1M" + incre + "\rR";

    Serial xy("/dev/ttyUSB0",9600);

    if(xy.CheckStatus()!=1)
    {
	xy.Write(move2.c_str());
	sleep(2);
	xy.Write(move1);
	sleep(2);

	xy.Write("X"); //Request X position
	sleep(3);  
	xy.Read(read_buf);    //Read requested position
	int pos=GetPosition(read_buf);
	cout<<"Position: "<<pos<<endl;

	xy.Write("N"); //Null absolute position resister
	// xy.Write("Y"); // Request Y position
        //sleep(3);
	// xy.Read(); //Read requested position
    }
    return(0);
}
