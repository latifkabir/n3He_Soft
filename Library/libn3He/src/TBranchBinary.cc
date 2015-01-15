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
#include<iostream>

ClassImp(TBranchBinary)


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
  if (fread(fAddress, fTotBytes, 1, fFile)<=0) return 0;
  fReadEntry=entry;
  return fTotBytes;
}
