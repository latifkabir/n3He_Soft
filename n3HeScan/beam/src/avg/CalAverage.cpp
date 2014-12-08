//Routine to calculate average beam intensity
//Author:Latiful Kabir
//Date:05/05/2014


#include<iostream>
#include<fstream>
#include"ReadBinary.h"
#include"CalAverage.h"
#include"Constants.h"
#include"ConstantsRB.h"

using namespace std;
double CalAverage(int run=0,int module=30,int ch=0)
{

    char *file_name=new char[200];
    sprintf(file_name,NEW_FILE,run,module);
    if(!ifstream(file_name))
    {
	cout<<"No data file... exiting... !!!!"<<endl;
	return(-1);
    }
    if(ch<0 || ch >47)
    {
	cout<<"Invalid Channel"<<endl;
	return(-1);
    }
    ReadBinary fa(file_name);

 	   
    int entries=(int)(8*fa.GetFileSize()/(NCHAN*32));               
    double total=0.0;
    double average=0.0;
    int counter=0;
	
    if(entries==0)
    {
	cout<<"No data file or file is empty... Exiting!!!"<<endl;
	return(-1);
    }
    else
    {
	    
	for(int i=0;i<(entries-1);i++)
	{
            if(fa.GetValue(0,i)!=ES_MAGIC)
	    {
		total=total+ADC_TO_VOLT*fa.GetValue(ch,i);
                counter++;
            }
	}
    }
    average=total/counter;

    delete[] file_name;
    return(average);
}
