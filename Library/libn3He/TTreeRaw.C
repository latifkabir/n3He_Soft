//n3He Library for Online Analysis
//Latest Modification by: Latiful Kabir
//Date:12/22/14

#include"Constants.h"
  

void TTreeRaw(int run=855)
{
//------------------Load The Library-------------------------------

    gSystem->Load(_LIBRARY_);

//-------------------Get The Data Path-----------------------------
    TString dataPath=DATA_PATH;

//------------------Get the Leaf list-------------------------------
    TString *DaqLeaf=new TString[5];
    DaqLeaf[0]=DAQ21_LEAF;
    DaqLeaf[1]=DAQ22_LEAF;
    DaqLeaf[2]=DAQ23_LEAF;
    DaqLeaf[3]=DAQ24_LEAF;
    DaqLeaf[4]=DAQ30_LEAF;

//---------------Generate data file name for each DAQ--------------
    TString *dataFile=new TString[5];
    int module[5]={21,22,23,24,30};

  for(int i=0;i<5;i++)
  {
      dataFile[i]=dataPath;
      dataFile[i]+="run-";
      dataFile[i]+=run;
      dataFile[i]+="data-";
      dataFile[i]+=module[i];
  }


//------------------Create The Tree----------------------------------

    TTree* t=new TTree("t","");

//-------------Add the Branches-----------------------------------
 
//------------Brach for daq-21------------                                                        
    cout << "Reading clean daq file: " << dataFile[0] << endl;
    TBranch* b21 = new TBranchBinary(t,dataFile[0],DaqLeaf[0],"b21", -1, 0);
    t->GetListOfBranches()->Add(b21);

//-----------Branch for daq-22-------------                                                     
    cout << "Reading clean daq file: " << dataFile[1] << endl;
    TBranch* b22 = new TBranchBinary(t,dataFile[1],DaqLeaf[1],"b22", -1, 0);
    t->GetListOfBranches()->Add(b22);

//----------Branch for daq-23--------------                                                            
    cout << "Reading clean daq file: " << dataFile[2] << endl;
    TBranch* b23 = new TBranchBinary(t,dataFile[2],DaqLeaf[2],"b23", -1, 0);
    t->GetListOfBranches()->Add(b23);

//--------Branch for daq-24----------------                                                            
    cout << "Reading clean daq file: " << dataFile[3] << endl;
    TBranch* b24 = new TBranchBinary(t,dataFile[3],DaqLeaf[3],"b24", -1, 0);
    t->GetListOfBranches()->Add(b24);

//--------Branch for daq-30---------------
    cout << "Reading dirty daq file: " <<dataFile[4] << endl;
    TBranch* b = new TBranchBinary(t,dataFile[4],DaqLeaf[4],"b", -1, 0);  t->GetListOfBranches()->Add(b);

//----------------Set/Get Entries and Print Leaf List---------------
    t->SetEntries();
    t->GetEntries();
    t->Print();
    t->GetListOfLeaves()->Print();


//---------------------Sample Online Analysis-----------------------
    t->Draw("d21[][0]/2.14748e+08:(Iteration$)","Entry$>3 && Entry$<100");
//  t->Draw("d21[][0]/2.14748e+08:(49*Entry$+Iteration$)","Entry$>3");

}
