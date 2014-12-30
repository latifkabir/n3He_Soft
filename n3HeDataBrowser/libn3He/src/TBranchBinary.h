// $Id: TBranchBinary.h,v 1.5 2013/10/20 07:45:23 crawford Exp $   -*-c++-*-

#ifndef TBRANCHBINARY_H
#define TBRANCHBINARY_H

#include "TBranch.h"
#include "TTree.h"
#include "TSystem.h"
#include "TString.h"

#define LINE_LENGTH 4096
#define MAX_LEAFS 1024

class TBranchBinary : public TBranch {

public:

  const  char* fLeafList;	// list of ntuple columns
  FILE*  fFile;			// data file handle
  void*  fBuffer;		// buffer to read entries
  int    fRecLength;		// binary file record length
  int    fRecOffset;		// offset to fields of interest
  int    fFileHeader;		// bytes to skip at file beginning

  TBranchBinary() {}
  TBranchBinary(TTree* tree, const char* file, const char* leaflist,
		const char* name=0, int length=-1, int offset=0, int head=0);
  ~TBranchBinary();
  int GetEntry(Long64_t entry=0, Int_t getall = 0);

protected:
  
  ClassDef(TBranchBinary,0)
};

#endif
