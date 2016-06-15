// Filename: PlotField.cpp
// Description: Live Magnetic fileds plot from six poobes of the fluxgate.
// Author: Latiful Kabir < siplukabir@gmail.com >
// Created: Wed Jun 15 15:02:27 2016 (-0400)
// URL: latifkabir.github.io

#include<fstream>
#include<iostream>
#include<unistd.h>
using namespace std;

void PlotField(int offset=1000)
{
    ifstream dataFile("/home/daq/NPDGamma/ReadMag/bin/magData.txt");

    if(!dataFile)
    {
        std::cout << "Data file does not exist" << std::endl;
	return;
    }
    double dateTime;
    double x1,y1,z1,x2,y2,z2,max,offSet;

    TGraph *gr[6];
    for(int i=0;i<6;i++)
	gr[i]=new TGraph();
    TCanvas *c1=new TCanvas("c","Live Magnetic Fields Plot",1600,800);
    gr[0]->SetTitle("X1 (Gauss vs x10 sec )");
    gr[1]->SetTitle("Y1 (Gauss vs x10 sec )");
    gr[2]->SetTitle("Z1 (Gauss vs x10 sec )");
    gr[3]->SetTitle("X2 (Gauss vs x10 sec )");
    gr[4]->SetTitle("Y2 (Gauss vs x10 sec )");
    gr[5]->SetTitle("Z3 (Gauss vs x10 sec )");
    c1->Divide(3,2);

    int points=0;
    int prevPoints;
    string dummy;
    int nLines=0;
    while(getline(dataFile,dummy))
	nLines++;
    dataFile.close();
    int History=offset; // The number lines from previous history you want to plot
    int startPoint=0;
    if(nLines>History)
	startPoint=nLines-History;

    dataFile.open("/home/daq/NPDGamma/ReadMag/bin/magData.txt");

    while (!dataFile.eof()) 
    {
	dataFile>>dateTime>>x1>>y1>>z1>>x2>>y2>>z2>>max>>offSet;
	if(points>=startPoint)
	{
	    c1->cd(1);
	    gr[0]->SetPoint(points-startPoint,points-startPoint,x1);
	    gr[0]->Draw("AP");

	    c1->cd(2);
	    gr[1]->SetPoint(points-startPoint,points-startPoint,y1);
	    gr[1]->Draw("AP");

	    c1->cd(3);
	    gr[2]->SetPoint(points-startPoint,points-startPoint,z1);
	    gr[2]->Draw("AP");

	    c1->cd(4);
	    gr[3]->SetPoint(points-startPoint,points-startPoint,x2);
	    gr[3]->Draw("AP");

	    c1->cd(5);
	    gr[4]->SetPoint(points-startPoint,points-startPoint,y2);
	    gr[4]->Draw("AP");

	    c1->cd(6);
	    gr[5]->SetPoint(points-startPoint,points-startPoint,z2);
	    gr[5]->Draw("AP");
	}
	points++;
    }
    c1->Update();
    prevPoints=points;
    points=0;
    dataFile.close();
    int fillPoint;

    while (1) 
    {    
    	sleep(10);	
        dataFile.open("/home/daq/NPDGamma/ReadMag/bin/magData.txt"); //If you read from a text file that has only updated value(as for Watchdog) then this openning and closing again and again will NOT be necessary.
    	while (!dataFile.eof()) 
    	{
    	    dataFile>>dateTime>>x1>>y1>>z1>>x2>>y2>>z2>>max>>offSet;	  
    	    points++;
    	    if(points>prevPoints)
    	    {
		fillPoint=points-startPoint;
		c1->cd(1);
		gr[0]->SetPoint(fillPoint-1,fillPoint,x1); //points-1 is important as last points++ is not filled and points start from 0. 
		gr[0]->Draw("AP");

		c1->cd(2);
		gr[1]->SetPoint(fillPoint-1,fillPoint,y1);
		gr[1]->Draw("AP");

		c1->cd(3);
		gr[2]->SetPoint(fillPoint-1,fillPoint,z1);
		gr[2]->Draw("AP");

		c1->cd(4);
		gr[3]->SetPoint(fillPoint-1,fillPoint,x2);
		gr[3]->Draw("AP");

		c1->cd(5);
		gr[4]->SetPoint(fillPoint-1,fillPoint,y2);
		gr[4]->Draw("AP");

		c1->cd(6);
		gr[5]->SetPoint(fillPoint-1,fillPoint,z2);
		gr[5]->Draw("AP");

    		c1->Update();
    	    }
    	}
    	prevPoints=points;
    	points=0;
    	dataFile.close();
    }  
}
