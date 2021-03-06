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
#include"Constants.h"

using namespace std;

FluxGate::FluxGate(const char *portName,int sspeed):Serial(portName,sspeed)
{
    magData.open(DATA_FILE,ofstream::app);  
}

FluxGate::~FluxGate()
{
    magData.close();
}

double FluxGate::ReadFG(int ch)
{
    if(ch==0)
    {
        CurrentTime();
    }
    nout = read(serial_fd,buf,256);
    // nout = read(serial_fd,buffer,bufferSize);
    //printf("bytes: %d\n",nout);
    //for(i=0;i<nout;i++)
    //{
    //	printf(" %d: 0x%i\n",i,buf[i]);
    //}
    // printf(" %d: 0x%s\n",i,buffer);
    // return((int)buf[0]);
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

void FluxGate::CurrentTime()
{
	time_t time_now;
	time(&time_now);
	struct tm my_time;
	localtime_r (&time_now,&my_time);
	int strlen=100;
	char *strname=new char[strlen];
	snprintf(strname,strlen,"%04d-%02d-%02d-%02d-%02d-%02d",my_time.tm_year+1900,my_time.tm_mon+1,my_time.tm_mday,my_time.tm_hour,my_time.tm_min,my_time.tm_sec);
	magData<<strname<<"	";
	// cout<<"\n";
	// cout<<"-------------------------"<<endl;
	// cout<<strname<<":"<<endl;
	// cout<<"-------------------------"<<endl<<endl;

	delete[] strname;
}
