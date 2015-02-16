//The TTreeRaw Class that reads raw n3He data files in TTree format
//Author: Latiful Kabir
//Date: 12/25/14


#ifndef TTREEN3HE_H
#define TTREEN3HE_H

#include <TTree.h>
#include <TString.h>
#include <TBranch.h>
#include"Constants.h"

class TTreeRaw: public TTree
{

public:

   TString dataPath;
   TString *DaqLeaf;
   TString *dataFile;
   static int module[5];

   TBranch *b21,*b22,*b23,*b24,*b30;

     TTreeRaw(int runNumber);
    ~TTreeRaw();
protected:

ClassDef(TTreeRaw,0)
};

void libn3He();

#endif
