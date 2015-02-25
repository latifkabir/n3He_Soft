//Demo Offline Analysis using n3He Library.(By Offline I mean  'in a script more thoughtful and serious analysis unlike from CINT)
//This script shows how to accress Tree using SetAddress
// and plots only the all event/pulses of channel-0
//Author: Latiful Kabir
//Date: 01/14/15
//This is the fastest and most preferred method for reading Tree 

#include<TTree.h>
#include<TBranch.h>
#include<TGraph.h>

void OfflineAnalysis1(){

    //Load the library unless loaded automatically by ROOT
     gSystem->Load("libTree");
     gSystem->Load("libn3He.so");
 
  TTreeRaw *t=new TTreeRaw(15142);
  t->Print();
  int ch=0; //Channel to analyze

  struct myData
  {
      int header[48];
      int det[49][48];  
  };

  myData md;
  
  //Get the branch you want to analyze
  TBranch *b=t->GetBranch("b21");
  b->SetAddress(&md.header[ch]);

//--------------------------------------------------

  TGraph *g=new TGraph();

  //Loop through all the events in the run.
  for(int i = 0;i < b->GetEntries();i++)
  {
      //Load the samples for a event/pulse in buffer
      b->GetEntry(i);

      //Loops through the sample for the loaded event
      for(int k=0;k<49;k++)
 	  g->SetPoint(i*49+k,i*49+k,md.det[k][ch]);
  }

  g->Draw("AP");
  delete t;
}
