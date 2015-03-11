//Demo Online Analysis using n3He Library.(By Online I mean  'from CINT, doing analysis on the fly, less thoughtful but preferred by in some conditions')
//Author: Latiful Kabir
//Date: 12/23/14

void OnlineAnalysis()
{
    gSystem->Load("libTree");    //You need to load libTree first in order to Load libn3He. This is not necessary if you include TTree.h
    gSystem->Load("libn3He.so");

    TTreeRaw *t=new TTreeRaw(19900);
    t->Draw("d21[][0]:Iteration$");
}
