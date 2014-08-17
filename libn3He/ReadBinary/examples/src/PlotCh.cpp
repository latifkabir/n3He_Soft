//This script can plot the data for specified channel in specified region.
//Latiful Kabir
// Date:05/20/2014


#include<iostream>
#include"ReadBinary.h"
#include<cmath>
#include<fstream>
#include<TCanvas.h>
#include<TGraph.h>
#include<TRint.h>
#include<TAxis.h>

using namespace std;

void PlotCh(int ch=0,int init=0){

  ReadBinary fa("/home/daq/DATA/ACQ2006/bigrawfile");
  //1.Getting the data in arrays

  const long filesize=18410897408 ;//In Byte
  const long entries=(long)(8*filesize)/(32*64);
  const int start=init;

 //2.Plotting the Sync pulse and pre-amp pick pick-up signal

   TCanvas *c1 = new TCanvas("c1","Plot for the channel");

   TGraph *gr1 = new TGraph((entries-start));
   for(long i=start;i<entries;i++)
   {
       gr1->SetPoint(i,i,fa.GetValue(ch,i));
   }   
   gr1->Draw("AP");
   gr1->SetTitle("Plot for the channel");
   gr1->GetXaxis()->SetTitle("Entry$");
   gr1->GetYaxis()->SetTitle("ADC Count");
 
}

int main(int argc, char** argv)
{

    if(ifstream("/home/daq/DATA/ACQ2006/bigrawfile")) 
    {
	int channel,start;
	cout<<"Enter the channel number:"<<endl;
	cin>>channel;
	cout<<"Enter the entry number to start:"<<endl;
	cin>>start;
 
	gApplication = new TRint("PlotCh", &argc,argv,0,0,kTRUE);
	PlotCh(channel,start);
	gApplication->Run();
    }
    else
    {
	cout<<"No data file... exiting... !!!!"<<endl;
    }    
}
