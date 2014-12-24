// $Id: TBranchBinary.cc,v 1.4 2013/10/20 07:45:23 crawford Exp $   -*-c++-*-
// by Chris Crawford <chris2@lns.mit.edu> 2006/01/11
// 
// TBranchBinary
// 
// A read-only TBranch that reads raw data from a binary file.
//
//-----------------------------
#include "TBranchBinary.h"
#include "TSystem.h"
#include "TLeaf.h"
#include"Constants.h"
#include<iostream>

ClassImp(TBranchBinary)

ClassImp(TTreeBinary)

using namespace std;

//______________________________________________________________________

TBranchBinary::TBranchBinary
( TTree* tree, const char* file, const char* leaflist,
  const char* name, int length, int offset, int head)
#if ROOT_VERSION_CODE < ROOT_VERSION(5,0,0)
  : TBranch(name?name:"branch", 0, leaflist),
#else
  : TBranch(tree, name?name:"branch", 0, leaflist),
#endif
    fLeafList(leaflist), fRecLength(length), fRecOffset(offset),
    fFileHeader(head)
{
  // read record size from TBranch
  fTotBytes = 0;
  TLeaf* l; TIter next(&fLeaves);
  while ((l=(TLeaf*)next()))
    fTotBytes += l->GetLenStatic() * l->GetLenType();
  if (fRecLength==-1) fRecLength=fTotBytes;

  // calculate nentries
  Long_t id, size, flags, modtime;
  if (file!=0 && *file!=0 &&
      !gSystem->GetPathInfo(file, &id, &size, &flags, &modtime)) {
    fEntries = (size-fFileHeader)/fRecLength;
  }
  fReadEntry = fEntryNumber = -1;

  // open file for reading
  if (fEntries) {
    fFile=fopen(file,"r");
    if (fFile) fFileName=file;
  }
  fBuffer = new char[fTotBytes];
  SetAddress(fBuffer);
}

//______________________________________________________________________

TBranchBinary::~TBranchBinary()
{
  if (fFile) fclose(fFile);
}

//______________________________________________________________________

int TBranchBinary::GetEntry(Long64_t entry, Int_t /*getall*/)
{
  if (entry==fReadEntry) return fTotBytes;
  bzero(fBuffer, fTotBytes);
  if (fseek(fFile, fFileHeader+entry*fRecLength+fRecOffset, SEEK_SET)) return 0;
  if (fread(fBuffer, fTotBytes, 1, fFile)<=0) return 0;
  fReadEntry=entry;
  return fTotBytes;
}


TTree* binary_tree(char* file, char* leaflist, int length=-1, int offset=0)
{
  TTree* t=new TTree
    //(gSystem->BaseName(file),"");
    ("t","");
  TBranch* b = new TBranchBinary
    (t, file, leaflist,"TBranchBinary", length, offset);
  t->GetListOfBranches()->Add(b);
  t->SetEntries();
  return t;
}

//=========================================================
//=========Modification & Addintion By Kabir Starts Here===
//====== n3heTree() function for the n3He Experiment=======

TTree* n3HeTree(int run=0)
{

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
    TBranch* b = new TBranchBinary(t,dataFile[4],DaqLeaf[4],"b", -1, 0); 
    t->GetListOfBranches()->Add(b);

//----------------Set/Get Entries and Print Leaf List---------------
    t->SetEntries();
    t->GetEntries();
    t->Print();
    t->GetListOfLeaves()->Print();


//---------------------Sample Online Analysis-----------------------
//  t->Draw("d21[][0]/2.14748e+08:(Iteration$)","Entry$>3 && Entry$<100");
//  t->Draw("d21[][0]/2.14748e+08:(49*Entry$+Iteration$)","Entry$>3");
    return t;
}
