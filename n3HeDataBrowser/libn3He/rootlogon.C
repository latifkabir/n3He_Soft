{
  #include <TBranch.h>
  cout << "Attempting to load libn3He.so ... ";
  gROOT->LoadMacro("lib/libn3He.so");
  cout << "attempt completed\n";
}
