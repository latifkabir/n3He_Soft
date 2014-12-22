Instruction:
1. Change the constants inside Constants.h file to fit your system.
2. Open Root.
3. If *.so shared library is not lready created ,then create on by doing : root -l > .L TBranchBinary.cc+
3. Load TTreeRaw with desired run number. ex: .x TTreeRaw(855).C
4. Do analysis on the fly with the created Tree 't'
