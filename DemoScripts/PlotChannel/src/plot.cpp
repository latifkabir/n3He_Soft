//This script can plot the data for specified channel in specified region.
//Latiful Kabir
// Date:05/20/2014


#include<iostream>
#include<cmath>
#include<fstream>
#include<cstdlib>
#include<TCanvas.h>
#include<TGraph.h>
#include<TRint.h>
#include<TAxis.h>
#include"ReadBinary.h"
#include"Constants.h"

using namespace std;

int PlotCh(int run,int module,int ch=0,int init=0)
{
    char *file_name=new char[200];
    sprintf(file_name,DATA_FILE,run,module);

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

    //2.Plotting the Sync pulse and pre-amp pick pick-up signal

    TCanvas *c1 = new TCanvas("c1","Plot for the channel");

    TGraph *gr1 = new TGraph();
    for(long i=start;i<entries;i++)
    {
	if(fa.GetValue(0,i)!=ES_MAGIC)
	    gr1->SetPoint(i-start,i,fa.GetValue(ch-1,i)*ADC_TO_VOLT);
    }   
   
    gr1->SetTitle("Plot for the channel");
    gr1->GetXaxis()->SetTitle("Entry$");
    gr1->GetYaxis()->SetTitle("Volt");
    gr1->Draw("AP");

    delete[] file_name;
    return(0);
}

int main(int argc, char** argv)
{
    int run,channel,module,start=0;
  
    if(argc!=4)
    {
	cout<<"Usage:./plot RUN_NUMBER MODULE CHANNEL"<<endl;
	return(-1);
    }

    run=atoi(argv[1]);
    module=atoi(argv[2]);
    channel=atoi(argv[3]);

    gApplication = new TRint("plot", &argc,argv,0,0,kTRUE);
    PlotCh(run,module,channel,start);
    gApplication->Run();
    return(0);
}
