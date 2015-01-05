//Loading libn3He automatically eact time you start root.
//Author: Latiful kabir 
{
  cout << "Attempting to load libn3He.so ... ";
  gSystem->Load("libTree");
  gSystem->Load("libn3He.so");
  cout << "attempt completed\n";
}


//Place this script inside "macros" directory under your ROOT installation directory.  
//In that case each time you start root , it will load libn3he.so automatically.
