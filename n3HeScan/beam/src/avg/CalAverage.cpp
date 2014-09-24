//This script can scan through binary data for specific channel.
//Latiful Kabir
// Date:05/05/2014


#include<iostream>
#include<fstream>
#include"ReadBinary.h"
#include"CalAverage.h"

using namespace std;

double CalAverage(int ch=0)
{

    if(fstream("../data/000"))
    {
	   
	ReadBinary fa("../data/000");
	int entries=(int)8*fa.GetFileSize()/(64*32);                
	double multiplier=4.65661287e-9; //Convert ADC count to Volt
	double total=0.0;
	double average=0.0;
	
	if(entries==0)
	{
	    cout<<"No data file or file is empty... Exiting!!!"<<endl;
	    return(-1);
	}
	else
	{
	    cout<<"Printing "<<n<<" entries starting from "<<start<<" for channel-"<<ch<<endl;
	    
	    for(int i=0;i<(entries-1);i++)
	    {
		cout<<i<<"   "<<fa.GetValue(ch,i)<<endl;
		total=total+multiplier*fa.GetValue(ch,i);
	    }
	}
	average=total/entries;
	return(average);
    }
    else
    {
	return(-1);
    }  
}

