//The FluxGate derived class with Serial as base class
//Author: Latiful Kabir
//Date:09.5.14
//Version:1.0


#include<stdio.h>
#include<string>
#include<iostream>
#include<time.h>
#include<iomanip>
#include"FluxGate.h"
#include"currentTime.h"
#include"Constants.h"

using namespace std;

FluxGate::FluxGate(const char *portName,int sspeed):Serial(portName,sspeed)
{
    magData.open(MAG_DATA_FILE,ofstream::app);
    current_time=new char[100];  
}

FluxGate::~FluxGate()
{
    magData.close();
    delete[] current_time;
}

double FluxGate::ReadFG(int ch)
{
    if(ch==0)
    {
        CurrentTime(current_time,100);
	magData<<current_time<<"	";
    }
    nout = read(serial_fd,buf,256);
    btod[0]=(int)buf[0];
    btod[1]=(int)buf[1];
    btod[2]=(int)buf[2];
    btod[3]=(int)buf[3];
    //cout<<btod[0]<<"	"<<btod[1]<<"	"<<btod[2]<<"	"<<btod[3]<<"	"<<endl;
    ADC_Count=btod[1]+256*btod[2]+65536*btod[3];
    mVolt=(ADC_Count*0.0005960464)-5000;
    gauss=mVolt*0.002;
    // cout<<"Channel:"<<ch+1<<" ADC Count :"<<ADC_Count<<"          ";
    // cout<<"Channel:"<<ch+1<<" Gauss : "<<gauss<<endl;
    magData <<setw(10); 
    magData << setprecision(8)<<gauss<<"	";
    if(ch==7)
    {
    	magData<<endl;
    }
    
    return gauss;
}

void FluxGate::WriteFG(int ch)
{

}
