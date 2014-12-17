//The Centroid calculation and 2DGraph for beam scan data
//Author: Latiful Kabir
//Date:12.10.14
void ScanUp1()
{
   TCanvas *c = new TCanvas("c","Graph2D example",0,0,600,400);

   ifstream data,BG;
	double x[35000],y[35000],z[35000],bg[35000];
	int index=0;
	int index2=0;
	double factor=-6.35e-4;
	double cen_x=0;
	double cen_y=0;
	double sum_int=0;

	data.open("data_7");

	while(!data.eof())
	{	
	    data >>y[index]>>x[index]>>z[index];
	    index++;
	}
	cout<<"Total number of Entries "<<(index-1)<<endl;
	

   TGraph2D *dt = new TGraph2D();

   for (Int_t N=0; N<(index-1); N++) 
   {
       sum_int=sum_int+z[N];
       cen_x=cen_x+x[N]*factor*z[N];
       cen_y=cen_y+y[N]*factor*z[N];

       dt->SetPoint(N,x[N]*factor,y[N]*factor,z[N]);
   }

   double c_x=cen_x/sum_int;
   double c_y=cen_y/sum_int;

   cout<<"The centroid is: "<<endl;
   cout<<"C_x:"<<c_x<<"    "<<"C_y:"<<c_y<<endl;

   gStyle->SetPalette(1);
   dt->GetXaxis()->SetTitle("X Displacement(Steps)");
   dt->GetYaxis()->SetTitle("Y Displacement(Steps)");
   dt->GetZaxis()->SetTitle("Average Intensity");
   dt->Draw("surf1");
   // return c;
}
