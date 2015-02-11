//The TTreeRaw Class that reads raw n3He data files in TTree format
//Author: Latiful Kabir
//Date: 12/25/14

#include "TTreeRaw.h"
#include "TBranchBinary.h"
#include <TBranch.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
void libn3He() {
}
;
using namespace std;

ClassImp(TTreeRaw)

//______________________________________________________________________
int TTreeRaw::module[5]={21,22,23,24,30};

TTreeRaw::TTreeRaw(int runNumber):TTree("n3He", "n3He raw data")
{

//-------------------Get The Data Path-----------------------------
    dataPath=DATA_PATH;

//------------------Get the Leaf list-------------------------------

    DaqLeaf[0]=DAQ21_LEAF;
    DaqLeaf[1]=DAQ22_LEAF;
    DaqLeaf[2]=DAQ23_LEAF;
    DaqLeaf[3]=DAQ24_LEAF;
    DaqLeaf[4]=DAQ30_LEAF;

//---------------Generate data file name for each DAQ--------------

    for(int i=0;i<5;i++)
    {
	dataFile[i]=dataPath;
	dataFile[i]+="run-";
	dataFile[i]+=runNumber;
	dataFile[i]+="data-";
	dataFile[i]+=module[i];
    }

    if(ifstream(dataFile[0]) && ifstream(dataFile[1]) && ifstream(dataFile[2]) && ifstream(dataFile[3]) && ifstream(dataFile[4]))
    {
//-------------Add the Branches to this tree-----------------------------------
 
//------------Branch for daq-21------------                            
    cout << "Reading clean daq file: " << dataFile[0] << endl;
    b21 = new TBranchBinary(this,dataFile[0],DaqLeaf[0],"b21", -1, 0);
    this->GetListOfBranches()->Add(b21);

//-----------Branch for daq-22-------------                                                     
    cout << "Reading clean daq file: " << dataFile[1] << endl;
    b22 = new TBranchBinary(this,dataFile[1],DaqLeaf[1],"b22", -1, 0);
    this->GetListOfBranches()->Add(b22);

//----------Branch for daq-23--------------                                                            
    cout << "Reading clean daq file: " << dataFile[2] << endl;
    b23 = new TBranchBinary(this,dataFile[2],DaqLeaf[2],"b23", -1, 0);
    this->GetListOfBranches()->Add(b23);

//--------Branch for daq-24----------------                                                            
    cout << "Reading clean daq file: " << dataFile[3] << endl;
    b24 = new TBranchBinary(this,dataFile[3],DaqLeaf[3],"b24", -1, 0);
    this->GetListOfBranches()->Add(b24);

//--------Branch for daq-30---------------
    cout << "Reading dirty daq file: " <<dataFile[4] << endl;
    b30 = new TBranchBinary(this,dataFile[4],DaqLeaf[4],"b30", -1, 0); 
    this->GetListOfBranches()->Add(b30);

//----------------Set/Get Entries and Print Leaf List---------------
    this->SetEntries();
    this->GetEntries();
    this->Print();
    this->GetListOfLeaves()->Print();

    }
    else
    {
	cout<<"No data files for requested run number"<<endl;
    }
    
}

TTreeRaw::~TTreeRaw()
{
//These things (Dustructions/free the memory) will be handled by ROOT automatically.
    // delete dataPath;
    // delete[] DaqLeaf;
    // delete[] dataFile;
    // delete b21;
    // delete b22;
    // delete b23;
    // delete b24;
    // delete b30;
}

