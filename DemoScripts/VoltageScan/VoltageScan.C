//target stability analysis
//looking at target stability with respect to M1 and proton beam power
//changing to storing pulse averages
//analysis loosely based on OfflineAnalysis.C from Kabir (01/14/2015)
//
// 2015/11/27 M McCrea

#include <iostream>
#include <iomanip>
#include <fstream>

#include "TCanvas"
#include "TGraph"
#include "TGraphErrors"
#include "TH1D"
#include "TH2D"

using namespace std;

//Tcanas and TGraph for plotting
TCanvas *cPlot = new TCanvas();
TGraph *gNormalized = new TGraph();

int numpoints = 0;

//wire map reading stuff
//convert index to plane and wire number
int IndextoPlane(int wireindex, int &plane, int &wire)
{
  if(wireindex<1 || wireindex>144)return 0; //index out of range, exit
  
  plane = ceil(wireindex/9.0);
  
  wire = wireindex-(plane-1)*9;
  
  return 1; //successfully calculated
}
int PlanetoIndex(int plane, int wire, int &wireindex)
{
  if(plane<1 || plane>16) return 0;
  if(wire<1 || wire>16) return 0;
  
  wireindex = (plane-1)*9 + wire;
  
  return wireindex; //successfully calculated
}
// takes wire index from 1-144 and returns daq number and channel.
int GetDaqChannel(int wireindex, int &DaqNum, int &ChanNum)
{
  if(wireindex<1 || wireindex>144)return 0; //index out of range
  
  int Layer_to_ADC_channel_map[16][9] =
  {
    {0,1,2,3,4,5,6,7,8},
    {0,1,2,3,4,5,6,7,8},
    {9,10,11,12,13,14,15,16,17},
    {9,10,11,12,13,14,15,16,17},
    {24,25,26,27,28,29,30,31,32},
    {24,25,26,27,28,29,30,31,32},
    {33,34,35,36,37,38,39,40,41},
    {33,34,35,36,37,38,39,40,41},
    {0,1,2,3,4,5,6,7,8},
    {0,1,2,3,4,5,6,7,8},
    {9,10,11,12,13,14,15,16,17},
    {9,10,11,12,13,14,15,16,17},
    {24,25,26,27,28,29,30,31,32},
    {24,25,26,27,28,29,30,31,32},
    {33,34,35,36,37,38,39,40,41},
    {33,34,35,36,37,38,39,40,41},
  };
  
  int Layer_to_DAQ_map[16]={21, 23, 21, 23, 21, 23, 21, 23,
    22, 24, 22, 24, 22, 24, 22, 24};
  
  int layer = ceil(wireindex/9.0)-1;//minus 1 for array index
  int wire = wireindex-layer*9-1;
  
  DaqNum = Layer_to_DAQ_map[layer]-20;
  ChanNum = Layer_to_ADC_channel_map[layer][wire];
  
  //cout<<" DaqNum = "<<DaqNum<<endl;
  //cout<<" ChanNum = "<<ChanNum<<endl;
  
  return 1;
}
int DaqChanneltoIndex()
{
  cout<<"Not completed, chek back later"<<endl;
  return 0;
}
//takes wire and plane then returns daq and channel number
//plane from 1-16
//wire from 1-9
int GetDaqChannel(int plane, int wire, int &xx, int &yy)
{
  
  if(plane<1 || plane>16) return 0;
  if(wire<1 || wire>16) return 0;
  
  int index = 0;
  PlantetoIndex(plane,wire,index)
  GetDaqChannel(index,xx,yy);
  
  //cout<<" DaqNum = "<<xx<<endl;
  //cout<<" ChanNum = "<<yy<<endl;
  
  return 1;
}


//returns average signal of target chamber divide by m1
double CalcAvg(int run_num){
  //Load the library unless loaded automatically by ROOT
  gSystem->Load("libTree");
  gSystem->Load("libn3He.so");
  
  //Create a TTreeRaw object with desired run number
  TTreeRaw *t=new TTreeRaw(run_num);
  
  //Create a struc buffer to keep your events from clean DAQ
  struct myData
  {
    int header[48];
    int det[49][48];
  };
  myData md[4];
  
  //dirt daq event buffers
  struct DirtyData
  {
    int header[2];
    int det[1624][2];
  };
  DirtyData dd;
  
  //Get the branch you want to analyze
  TBranch *b[5];
  b[0]=t->GetBranch("b21");//clean daqs
  b[1]=t->GetBranch("b22");
  b[2]=t->GetBranch("b23");
  b[3]=t->GetBranch("b24");
  b[4]=t->GetBranch("b30");//dirty daq
  b[0]->SetAddress(&md[0].header[0]);
  b[1]->SetAddress(&md[1].header[0]);
  b[2]->SetAddress(&md[2].header[0]);
  b[3]->SetAddress(&md[3].header[0]);
  b[4]->SetAddress(&dd.header[0]);
  
  //for use in resolving daq and channel from index via GetDaqChannel()
  int channel;
  int daq;
  
  double wireSum = 0;
  double m1Sum = 0;
  
  double counter = 0;
  
  //calculating averages
  //Loop through events in the run. skip entry zero.
  for(int i = 1 ; i< 50 ; i++)//i<b[0]->GetEntries() ; i++)//
  {
    counter++;
    //Load the samples for a event/pulse in buffer
    for(int q = 0 ; q<5 ; q++){b[q]->GetEntry(i);}
    
    //loop over all wires
    for(int j = 1 ; j<=144 ; j++)//wire index
    {
      GetDaqChannel(j,daq,channel);
      //Loops through the samples for the loaded event (wires)
      for(int k=0 ; k<49 ; k++)
      {
        wireSum+=(md[daq-1].det[k][channel]>>8);
      }
    }
    for(int kk = 0 ; kk<1624 ; kk++)
    {
      m1Sum+=(dd.det[kk][0]>>8);
    }
    if(i%50==0)cout<<"entry "<<i<<" complete"<<endl;//
  }

  //divide by number of entries to form averages from sums
  cout<<"counter = "<<counter<<endl;
  wireSum = wireSum/(counter*49.0*144.0);
  m1Sum = m1Sum/(counter*1624.0);
  cout<<"wireSum="<<wireSum<<" m1Sum="<<m1Sum<<endl;

  delete t;
  
  return wireSum/m1Sum;
}

int AddPoint(int run_num, double voltage)
{

  gNormalized->SetPoint(numpoints, voltage, CalcAvg(run_num));
  gNormalized->Draw("APL*");
  numpoints++;
  
  return 0;
}


