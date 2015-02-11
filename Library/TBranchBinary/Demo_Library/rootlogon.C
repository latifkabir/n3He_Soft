{
  #include <TBranch.h>
  cout << "Attempting to load libN3HE.so ... ";
  gROOT->LoadMacro("lib/libN3HE.so");
  cout << "attempt completed\n";
}
