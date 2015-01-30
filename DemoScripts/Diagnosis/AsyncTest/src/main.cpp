//This script can read/plot the data for specified channel in specified region.
//Author:Latiful Kabir
// Date:05/20/2014


#include<iostream>
#include<cmath>
#include<fstream>
#include<cstdlib>
#include"ReadBinary.h"
#include"Constants.h"

using namespace std;

int PlotCh(int run,int ch=0,int init=0)
{
    char *file_name=new char[200];
    sprintf(file_name,DATA_FILE,run);

    if(!ifstream(file_name))
    {
	cout<<"No data file... exiting... !!!!"<<endl;
	return(-1);
    }
    if(ch<1 || ch >48)
    {
	cout<<"Invalid Channel"<<endl;
	return(-1);
    }    
 
    ReadBinary fa(file_name);
    //1.Getting the data in arrays

    const long filesize=fa.GetFileSize() ;//In Byte
    const long entries=(long)(8*filesize)/(32*NCHAN);
    const int start=init;

    if(entries==0)
    {
	cout<<"No data file or file is empty... Exiting!!!"<<endl;
	return(-1);
    }
    if(init>entries)
    {
	cout<<"Requested entries exceed total number of entries. Exiting!!!"<<endl;
	return(-1);
    }

    	if(fa.GetValue(0,0)==ES_MAGIC1 && fa.GetValue(24,0)==ES_MAGIC2)
	    return(1);
	else 
	    return (-5);

    delete[] file_name;
    return(0);
}

int main(int argc, char** argv)
{
    int p=-1;
  
    for(int k=100;k<1000;k++)
    {
	p=PlotCh(k,1,0);
	if(p==-5)
	    cout<<"Bingo !!! Found it for shot"<<k<<endl;
    }

    return(0);
}
