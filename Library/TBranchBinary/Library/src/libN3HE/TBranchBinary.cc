// $Id: TBranchBinary.cc,v 1.1 2006/01/13 18:13:43 chris2 Exp $   -*-c++-*-
// by Chris Crawford <chris2@lns.mit.edu> 2006/01/11
// 
// TBranchBinary
// 
// A read-only TBranch that reads raw data from a binary file.
//

#include "TBranchBinary.h"
#include "TSystem.h"
#include "TLeaf.h"
#include <iostream>
using namespace std;
ClassImp(TBranchBinary)

//______________________________________________________________________

TBranchBinary::TBranchBinary(TTree* tree, int nfiles, const char** filelist,
		const char* leaflist, const char* name, int length, int offset)
#if ROOT_VERSION_CODE < ROOT_VERSION(5,12,0)
: TBranch(name?name:"branch", 0, leaflist),
#else
:
		TBranch(tree, name ? name : "branch", 0, leaflist),
#endif
				fNfiles(nfiles), fFileList(filelist), fLeafList(leaflist), fRecLength(
						length), fRecOffset(offset) {
	// read record size from TBranch
	fTotBytes = 0;
	TLeaf* l;
	TIter next(&fLeaves);
	while ((l = (TLeaf*) next()))
		fTotBytes += l->GetLenStatic() * l->GetLenType();
	if (fRecLength == -1)
		fRecLength = fTotBytes;

	// calculate nentries
	fFileIndex = fFileIndexOrig = (new int[fNfiles + 1]);
	fFileIndex[0] = 0;
	Long_t id, size = 0, flags, modtime;
	for (int irun = 0; irun < fNfiles; ++irun) {
		if (fFileList[irun] != 0 && *fFileList[irun] != 0
				&& !gSystem->AccessPathName(fFileList[irun], kReadPermission)
				&& !gSystem->GetPathInfo(fFileList[irun], &id, &size, &flags,
						&modtime)) {
			fFileIndex[irun + 1] = fFileIndex[irun] + fEntries
					+ size / fRecLength; // fEntries?
		} else {
			fFileIndex[irun + 1] = fFileIndex[irun];
		}
	}

	fFile = fopen(fFileList[fCurrentFile = 0], "r");

	fEntries = fFileIndex[fNfiles];
	
	fReadEntry = fEntryNumber = -1;
	fBuffer = new char[fTotBytes];
	SetAddress(fBuffer);
}

//______________________________________________________________________

TBranchBinary::~TBranchBinary() {
	delete[] fBuffer;
	delete[] fFileIndexOrig;
	if (fFile)
		fclose(fFile);
}

//______________________________________________________________________

int TBranchBinary::GetEntry(Long64_t entry, Int_t /*getall*/) {
	void *fBuffer = fAddress;

	if (entry == fReadEntry)
		return fTotBytes;

	static int fentry;
	int oldfile = fCurrentFile;

	while ((fentry = entry - fFileIndex[fCurrentFile]) < 0) {
		if (fCurrentFile <= 0)
			return 0;
		--fCurrentFile;
	}

	while (entry >= fFileIndex[fCurrentFile + 1]) {
		if (fCurrentFile >= fNfiles - 1)
			return 0;
		fentry = entry - fFileIndex[++fCurrentFile];
	}

	if (fCurrentFile != oldfile) {
		if (fFile)
			fclose(fFile);
		fFile = fopen(fFileList[fCurrentFile], "rb");
		if (!fFile) {
			cout << "Warning: can't open file: " << fFileList[fCurrentFile]
					<< endl;
		}
	}

	bzero(fBuffer, fTotBytes);
	if (!fFile)
		return 0;
	if (fseek(fFile, fentry * fRecLength + fRecOffset, SEEK_SET))
		return 0;
	if (fread(fBuffer, fTotBytes, 1, fFile) <= 0)
		return 0;

	fReadEntry = entry;
	return fTotBytes;
}
