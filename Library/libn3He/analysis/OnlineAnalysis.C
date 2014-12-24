//Demo Online Analysis using n3He Library.(By Online I mean  'from CINT, doing analysis on the fly, less thoughtful but preferred by many or in some conditions')
//Author: Latiful Kabir
//Date: 12/23/14

void OnlineAnalysis()
{
    gSystem->Load("../lib/libn3He.so");

    TTree *t=n3HeTree(855);
    t->Draw("d21[][0]:Iteration$","Entry$>3");
}
