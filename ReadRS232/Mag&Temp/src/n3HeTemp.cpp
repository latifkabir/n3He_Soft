// Reading the temperature and writing to a text file
//Author: latiful Kabir
//Date: 03.02.15

#include<fstream>
#include<iomanip>
#include"currentTime.h"
#include"Constants.h"
#include"Serial.h"

using namespace std;

void ReadTemp(Serial &temp, int *zone)
{

    ofstream tempData(TEMP_DATA_FILE,ofstream::app);
    ofstream temp_watch(WATCHDOG_DATA);
    char *cTemp=new char[48];
    int strlen=100;
    char *current_time=new char[strlen];

    //-------------Read Temperature-----------------
    temp.Write("L");
    sleep(1);
    temp.Write("0"); //Passcode manually set to the device
    sleep(1);
    temp.Write("T");
    sleep(1);
    temp.Read(cTemp);
    for(int j=0;j<12;j++)
    {
	zone[j]=1000*((int)cTemp[4*j]-48)+100*((int)cTemp[4*j+1]-48)+10*((int)cTemp[4*j+2]-48)+((int)cTemp[4*j+3]-48);
	// cout<<zone[j]<<endl;
    }
//-----Get the current time-------
    CurrentTime(current_time,strlen);

//-----------Write Temperature to data files-------
    if(tempData)
    {
	tempData <<setw(10);
	tempData<<current_time<<"	"<<zone[0]<<"  	"<<zone[1]<<"	"<<zone[2]<<"	"<<zone[3]<<"	"<<zone[4]<<endl;
	tempData.close();
    }
    if(temp_watch)
    {
	temp_watch<<setw(10);
	temp_watch<<zone[0]<<"  	"<<zone[1]<<"	"<<zone[2]<<"	"<<zone[3]<<"	"<<zone[4]<<endl;
	temp_watch.close();
    }

    delete[] cTemp;
    delete[] current_time;
}
