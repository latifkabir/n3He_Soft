//Demo Offline Analysis using n3He Library.(By Offline I mean  'in a script more thoughtful and serious analysis unlike from CINT)
//Author: Latiful Kabir
//Date: 12/23/14
//This is approach is much slower than SetAddress() approach and encouraged NOT to use.
//This for demonstration purpose only for how to access individual branch and leaf.

#include<TTree.h>
#include<TLeaf.h>
#include<TGraph.h>
#include<TSystem.h>
#include<TMath.h>
#include<TCanvas.h>
#include<TRint.h>
#include<TAxis.h>
#include<iostream>
#include"Constants.h"

using namespace std;


void OfflineAnalysis2()
{
    //-------------Load the n3He Library----------------------------
    gSystem->Load("libn3He.so"); //Use complete path unless libn3He.so is in a directory under LD_LIBRARY_PATH

    //---------Create a Tree for desired run number-----------------
    TTreeRaw *t=new TTreeRaw(15142);

    int leaf_index;
    int adc_count;
    double volts;

    //---------------Clean DAQ21 Channel-0 analysis/Plotting---------
    int entries=t->GetEntries("d21");//Get total number of Events for desired DAQ module(branch)

    TCanvas *c1=new TCanvas("c1","Demo Clean DAQ plot");
    TGraph *gr1=new TGraph();
    int channel=0; //Specify channel number to be analyzed.

    //Loop over all Events(Entries)
    for (int ientry = 0; ientry <entries; ientry++)
    {
	t->GetEntry(ientry);  //Load the event.

        //Loop over all tbins(samples) for each event(Entry).
	for (int isample=0; isample<EL_CLEAN; isample++)
	{
	    leaf_index = isample*NC_CLEAN + channel;  	    
	    adc_count= t->GetLeaf("d21")->GetValue(leaf_index);
	    volts = (adc_count>>8)*FACTOR; //>>8 to throw away last 8 bits & FACTOR to convert ADC count to Volt

	    gr1->SetPoint(ientry*EL_CLEAN+isample,ientry*EL_CLEAN+isample,volts);

	}

       //--------Other Clean DAQ analysis will come here-------------------------
       //
    }

    gr1->GetXaxis()->SetTitle("tbin");
    gr1->GetYaxis()->SetTitle("Volts");
    gr1->SetTitle("Plot for DAQ21 Channel-0");
    gr1->Draw("AP");

//------------------Dirty DAQ Channel-0 analysis/Plotting-----------------------
    entries=t->GetEntries("d30");//Get total number of Events for desired DAQ module(branch)
    TCanvas *c2=new TCanvas("c2","Demo Dirty DAQ Plot");
    TGraph *gr2=new TGraph();
    channel=0; //Specify channel number to be analyzed.

    //Loop over all Events(Entries)
    for (int ientry = 0; ientry <entries; ientry++)
    {
    	t->GetEntry(ientry);

    	//Dirty DAQ30 Channel-0 analysis
        //Loop over all tbins(samples) for each event(Entry).
    	for (int isample=0; isample<EL_DIRTY; isample++)
    	{
    	    leaf_index = isample*NC_DIRTY + channel;  	    
    	    adc_count= t->GetLeaf("d30")->GetValue(leaf_index);
    	    volts = (adc_count>>8)*FACTOR; //>>8 to throw away last 8 bits & FACTOR to convert ADC count to Volt

    	    gr2->SetPoint(ientry*EL_DIRTY+isample,ientry*EL_DIRTY+isample,volts);

    	}

    }
    gr2->GetXaxis()->SetTitle("tbin");
    gr2->GetYaxis()->SetTitle("Volts");
    gr2->SetTitle("Plot for DAQ30 Channel-0");
    gr2->Draw("AP");
    delete t;
}
