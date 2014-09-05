//The FluxGate derived class with Serial as base class
//Author: Latiful Kabir
//Date:09.5.14
//Version:1.0


#include<stdio.h>
#include<string>
#include<iostream>
#include <sstream>

#include"FluxGate.h"

using namespace std;

FluxGate::FluxGate(const char *portName,int sspeed):Serial(portName,sspeed)
{
   
}

FluxGate::~FluxGate()
{

}

int FluxGate::ReadFG(int ch)
{
    string fld;
    nout = read(serial_fd,buf,256);
    // nout = read(serial_fd,buffer,bufferSize);
    printf("bytes: %d\n",nout);
    for(i=0;i<nout;i++)
    {
	printf(" %d: 0x%x\n",i,buf[i]);
    }
    // printf(" %d: 0x%s\n",i,buffer);
    fld=buf[0];
    fld=string("0x")+fld;
    string s(fld);
    unsigned long value;
        istringstream iss(s);
        iss >> hex >> value;
        cout << value << endl;
    //cout<<fld;
    // return((int)buf[0]);
    return(buf[0]);
}

void FluxGate::WriteFG(int ch)
{

}

