// Filename: PlotIntensity.cc
// Description: Plot the intensity of desired run and event.
// Author: Latiful Kabir < siplukabir@gmail.com >
// Created: Fri Apr 10 14:50:00 2015 (-0400)
// URL: latifkabir.github.io
#include<iostream>
using namespace std;

#include<TFile.h>
#include<TTree.h>
#include<TBranch.h>
#include<TString.h>
#include<TSystem.h>
#include<TH2D.h>
#include"Wire2adc.h"
#include"Constants.h"

struct myData
{
    double sumc[4][36];
};

void PlotIntensity(int run,int event=0) 
{
    // Create a histogram for the values we read.
    TH2D *gr = new TH2D("h","h",16,0,16,9,0,9);
 
    TString fName;
    fName=ROOT_FILE_PATH;
    fName+="run-";
    fName+=run;
    fName+=".root";
 
    //============ Open the file containing the tree==================
    bool status=gSystem->AccessPathName(fName); //Note bizzare return type convention
    if(status) 
    {
	cout << "\n--------->The root file for run number :"<<run<<" does NOT exist<-------------" <<endl;
	return;
    }

    // Open the file containing the tree.
    TFile *myFile = TFile::Open(fName);
    TTree *T=(TTree*)myFile->Get("T");

    myData md;
    TBranch *b=T->GetBranch("sumc");
    b->SetAddress(&md.sumc[0][0]);

    int l=0; //The layer number
    int w=0; //The wire number
    b->GetEntry(event);
    int point=0;
    for(int i=0;i<16;i++)
    {
	for(int j=0;j<9;j++)
	{
	    l=i;
	    w=j;
	    Wire2adc(l,w);		  
	    if(i==0 && (j==5 || j==6))
	    {
		l=0;
		w=6;
		Wire2adc(l,w);	
		gr->Fill(i,j,0.5*md.sumc[l][w]);
	    }
	    else		
		gr->Fill(i,j,md.sumc[l][w]);
	    cout <<"Layer: "<<i<<"  Wire:" <<j<<" Intensity:"<<md.sumc[l][w] <<endl;
	    point++;
	}
    }
    
    // gr->Draw("colz");
    gr->GetXaxis()->SetTitle("Layer#");
    gr->GetYaxis()->SetTitle("Wire#");
    gr->GetZaxis()->SetTitle("Intensity(Volts)");    
    gr->Draw("lego2");
}
