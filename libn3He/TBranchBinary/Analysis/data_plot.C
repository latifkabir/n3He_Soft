void data_plot(){

     gSystem->Load("libTree");
     gSystem->Load("libHist");
     gSystem->Load("libN3HE.so");
 
  TTree t("t","");
  char* fn[1]={"../Data/000"};
  TBranchBinary b(&t, 1, fn,"d[64]/I");
  b.SetName("data");
  t.GetListOfBranches()->Add(&b);
  t.SetEntries();

  int entryData[64];
  b.SetAddress(&entryData[0]);

  int minValue = 0;
  int maxValue = 0;
  for(int i = 0;i < b.GetEntries();i++){
    b.GetEntry(i);
    if(entryData[0] < minValue)
      minValue = entryData[0];

    if(entryData[0] > maxValue)
      maxValue = entryData[0];
  }
 
  //Making a manual histogram 
  TCanvas *c1=new TCanvas("c1","Manual Histogram");
 
  TH1F *histo=new TH1F("test","test,value,frequency",100,minValue-(maxValue-minValue)*.1,maxValue+(maxValue-minValue)*.1);

  for(int i = 0;i < b.GetEntries();i++){
    b.GetEntry(i);
    cout<<i<<" "<<entryData[0]<<endl; //Printing The ADC values for channel-1
    histo->Fill(entryData[0]);
    
  }

  histo->Draw();
  
  // 2D Histogram using TTree
  TCanvas *c2=new TCanvas("c2","NTuple Plot");
  t.Draw("d[0]:Entry$"); 
  
  // 1D Histogram using TTree
  TCanvas *c3=new TCanvas("c3","NTuple Histogram");
  t.Draw("d[0]");  
}
