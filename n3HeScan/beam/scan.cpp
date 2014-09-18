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

int main(void)
{

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
	xy.Read();    //Read requested position

	xy.Write("N"); //Null absolute position resister

	// xy.Write("Y"); // Request Y position
        //sleep(3);
	// xy.Read(); //Read requested position
    }
    return(0);
}
