//Demo Online Analysis using n3He Library.(By Online I mean  'from CINT, doing analysis on the fly, less thoughtful but preferred by many or in some conditions')
//Author: Latiful Kabir
//Date: 12/23/14

void OnlineAnalysis()
{
    gSystem->Load("libTree");    //You need to load libTree first in order to Load libn3He. This is not necessary if you include TTree.h
//file like the Offline analysis script.
    gSystem->Load("libn3He.so");

    TTreeRaw *t=new TTreeRaw(15142);
    t->Draw("d21[][0]:Iteration$","Entry$>3");
}
