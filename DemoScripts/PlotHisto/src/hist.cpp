//This script can make Histogram of the data for specified channel.
//Latiful Kabir
// Date:05/20/2014


#include<iostream>
#include<cmath>
#include<fstream>
#include<TCanvas.h>
#include<TH1F.h>
#include<TRint.h>
#include<TAxis.h>
#include"ReadBinary.h"
#include"Constants.h"

using namespace std;

int PlotHist(int run,int module,int ch=0,int init=0)
{
    char *file_name=new char[200];
    sprintf(file_name,DATA_FILE,run,module);

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

//Calculate Range of the Histogram
    int minValue = 0;
    int maxValue = 0;
    int temp;
    for(int i = start;i < entries;i++)
    {
	if(fa.GetValue(0,i)!=ES_MAGIC)
	{
	    temp=fa.GetValue(ch,i);
	    if(temp < minValue)
		minValue = temp;
	    if(temp > maxValue)
		maxValue = temp;
	}
    }

    double histo_max=(maxValue+(maxValue-minValue)*.1)*ADC_TO_VOLT;
    double histo_min=(minValue-(maxValue-minValue)*.1)*ADC_TO_VOLT;
//Making a manual histogram
    TCanvas *c1=new TCanvas("c1","Manual Histogram");
    TH1F *histo=new TH1F("test","Histogram for the Channel",100,histo_min,histo_max);

    for(int i = start;i < entries;i++)
    {
	if(fa.GetValue(0,i)!=ES_MAGIC)
	    histo->Fill(fa.GetValue(ch,i)*ADC_TO_VOLT);
    }
    histo->GetXaxis()->SetTitle("Volt");
    histo->GetYaxis()->SetTitle("Frequency");

    histo->Draw();

    delete[] file_name;
    return(0);
}

int main(int argc, char** argv)
{
    int run,channel,module,start=0;
  
    if(argc!=4)
    {
	cout<<"Usage:./hist RUN_NUMBER MODULE CHANNEL"<<endl;
	return(-1);
    }

    run=atoi(argv[1]);
    module=atoi(argv[2]);
    channel=atoi(argv[3]);

    gApplication = new TRint("hist", &argc,argv,0,0,kTRUE);
    PlotHist(run,module,channel,start);
    gApplication->Run();
    return(0);
}
