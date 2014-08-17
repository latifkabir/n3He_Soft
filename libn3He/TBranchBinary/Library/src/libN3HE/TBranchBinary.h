// $Id: TBranchBinary.h,v 1.1 2006/01/13 18:13:43 chris2 Exp $   -*-c++-*-

#ifndef TBRANCHBINARY_H
#define TBRANCHBINARY_H

#include "TBranch.h"

class TBranchBinary: public TBranch {

public:

	int fNfiles;		// number of runs
	const char** fFileList;	// list of files for each run
	const char* fLeafList;	// list of ntuple columns
	int* fFileIndex;	// cumulative list of entries
	int* fFileIndexOrig;	//   for destructor
	int fCurrentFile;	// current file index
	FILE* fFile;		// current file handle
	int fRecLength;		// binary file record length
	int fRecOffset;		// offset to fields of interest
	char *fBuffer;		// buffer

	TBranchBinary() :
			fFileIndex(0) {
	}
	TBranchBinary(TTree* tree, int nfiles, const char** filelist,
			const char* leaflist, const char* name = 0, int length = -1,
			int offset = 0);
	~TBranchBinary();
	int GetEntry(Long64_t entry = 0, Int_t getall = 0);
	int* GetFileIndex() {
		return fFileIndex;
	}
	void SetFileIndex(int* index) {
		fFileIndex = index;
		fEntries = fFileIndex[fNfiles];
	}

protected:

ClassDef(TBranchBinary,0)
};

#endif
