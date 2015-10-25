// $ Chris Crawford <crawford@pa.uky.edu> 2014-07-29
// $ root -l b45/ ../../n3HeSim.C+ -geom_xyz=1 -rho3=0.5 -xcol=0.08 -ntof=1 -verbose=3
// $ root -l poly_sm6/ ../n3HeSim.C+(1e4,300) #defaults: -geom_xyz=0 -rho3=0.5 -xcol=0.08 -ntof=1 #compare: sim_2015-03-12.cint
// $ g++ -g `root-config --cflags --glibs` n3HeSim.C && a.out

#include "TNtuple.h"
#include "TFile.h"
#include "TH1.h"
#include "TROOT.h"
#include "TSystem.h"
#include "TRint.h"
#include "TMatrixDSym.h"
#include "TString.h"

#include <math.h>
#include <assert.h>
#include <iostream>
using namespace std;

#define BRANCH(var)							\
  float var; TBranch* b_##var=ntp->GetBranch(#var);			\
  if(b_##var) ntp->SetBranchAddress(#var,&var)
#define PI 3.14159265359
#define NTOF 42
#define NDIV 128

TH1F hl5("hl5","",100,0,10);  // unpolarized spectrum
TH1F hl6("hl6","",100,0,10);  // unchopped spectrum
TH1F hlc("hlc","",100,0,10);  // chopped spectrum
TH1F hls("hls","",100,0,10);  // rfsf-chopped spectrum
TH1F hlx("hlx","",100,0,10);  // collimated spectrum
int    ntof=1;		// number of TOF bins in optimization //125 //40
int    nz  =100;	// number of steps in zev (vertex)
int    na  =20;		// number of steps in aa (cosine of p track)
int    nb  =20;		// number of steps in bb (phi of p track)
int    geom_xyz=0;	// direction of geometry factors x=0 y=1 z=2
int    nev=1e9;		// number of events to analyze
int    cnt =1000;	//  number of events per "."
int    verbose = 3;	// 0 none, 1 dots, 2 global, 3 cell, 4 matrices, 5 cov
float  rfsf_phi=234/360.;	// spin flipper phase
const int    nch =2;		// number of choppers
const char*  vch[]={"f1","g2"};	// chopper variables
float  ch_phi[2]={0,0};		// chopper phases	//{70,97}
float  ch_open[2]={360,360};    // chopper opening	//{132,167}

float  freq=60;		// pulse frequency
float  zcol=17.95;	// position of collimator
float  xcol=0.08, ycol=0;  // rectangular collimator width,height
float  z6  =15.4;	// end of SMpol
float  zsf =17.65;	// position of RF spin flipper
float  ksf =17.65;	// RFSF fine tuning (lanl: 15.868)
float  k_rfsf =PI*ksf*freq;
float  rho3=0.5;   	// number density (Amg)
float  ksig=7.855;	// 5327b*(2200m/s)*(mn/h) [(Amg.m.Ang)^-1]

float  zwc =18.00;	// position of front of WC
float  lwc =0.338;	//  length of WC
float  z1w=0.013;	// range of active ion collection in z
float  z2w=0.317;	//  must be <= nwz cells
float  x1w=-.080;	// range of active ion collection in x
float  x2w=0.080;	//  must be <= nwx cells
float  y1w=-.080;	// range of active ion collection in y
float  y2w=0.080;	//
const int nwz=16,nwx=9, nwc=nwz*nwx; // number of WC cells
float  z0w=0.013;	// full thickness start of first cell in z
float  dzw=0.019;	//  uniform thickness of WC cells in z
float  x0w=-0.0855;	// full thickness start of first cell in x
float  dxw=0.019;	//  uniform thickness of WC cells in x

// other globals
float  dsf =1;		// -1=std RFSF, .95=strict RFSF, 5% deadtime
float  psf =1;		// fixed pol for wrap; 1: cut on rfsf window (dsf)

// ionization
int kzx[nwc]; float kbeta[nwc];	// ionization in cells

float  beta_pt[]={	// #ions deposited from p,t between d1r,d2r
  80.95, 73.81, 102.4, 161.9, 297.6, 533.3, 676.2, 771.4, 871.4, 940.5, //triton
  373.8, 383.3, 390.5, 400.0, 409.5, 419.0, 431.0, 445.2, 454.8, 471.4, 488.1, 504.8, 526.2, 547.6, 576.2, 607.1, 642.9, 690.5, 740.5, 809.5, 890.5, 952.4, 852.4, 488.1, 104.8 //proton
};
float  d1r=-0.020/rho3;	//  lowest xb (triton endpoint)
float  d2r= 0.050/rho3;	//  highest xb (proton endpoint)
const int nbet=sizeof(beta_pt)/sizeof(float);
float  ddr= (d2r-d1r)/nbet; // beta function step size
float beta_int[nbet+1]={0}; // cumulative ionization, filled below

float beta_fn(float d)
{
  if (d<d1r) 
      return 0; 
  if (d>d2r) 
      return beta_int[nbet];
  d=(d-d1r)/ddr; 
  int k(d);
  return beta_int[k]*(k+1-d) + beta_int[k+1]*(d-k);
}

float n3HeSim(int nev_=0, float rfsf_phi_=300, int sev=0)
{
  // commandline option '-var=val' to change any global
  for (int i=1; i<gApplication->Argc(); ++i) 
  {
      TString opt(gApplication->Argv(i));
      if ((opt[0]=='-' || opt[0]=='+') && opt.Contains("="))
	  gROOT->ProcessLine(opt=opt.Append(";").Strip(TString::kLeading,'-'));
  }

  if (nev_) 
      nev = nev_;
  if (rfsf_phi_!=0) 
      rfsf_phi=rfsf_phi_/360.;
  TFile* f = new TFile("/home/siplu/GIT/n3He_Soft/Github/Simulation/data/mcstas.root");
  TNtuple* ntp = (TNtuple*)f->Get("mcstas");

  // set up ntuple
  BRANCH(l);
  BRANCH(pol);
  BRANCH(p5);
  BRANCH(p6);
  BRANCH(t6);
  BRANCH(x6);
  BRANCH(y6); 
  BRANCH(vx6);
  BRANCH(vy6);
  BRANCH(vz6);
  
  float chop[4]; 
  TBranch* b_chop[4];
  for (int j=0;j<nch;++j) 
  {
      b_chop[j]=ntp->GetBranch(vch[j]);
      ntp->SetBranchAddress(vch[j],&chop[j]);
  }

  // precalculate track projections
  float dwc = lwc/nz;			// WC parameters
  float da  = 2./na, a0=-1+da/2;	// polar [cos(theta)] integration
  float db  = 2*PI/nb, b0=-PI+db/2;	// azimuthal [phi] integration
  float cxyz[3], &cx=cxyz[0],&cy=cxyz[1],&cz=cxyz[2];	// projection cosines
  float ccz[NDIV], ccx[NDIV][NDIV], ccy[NDIV][NDIV], as; // cached values
  float aa=a0; 
  for (int ia=0; ia<na; ++ia, aa+=da) 
  {
      ccz[ia]=aa; 
      if (ccz[ia]==0) 
	  ccz[ia]=1e-11; 
      as=sqrt(1-aa*aa);
      float bb=b0; 
      for (int ib=0; ib<nb; ++ib, bb+=db) 
      {
	  ccx[ia][ib]=as*cos(bb); 
	  if (ccx[ia][ib]==0) 
	      ccx[ia][ib]=1e-11;
	  ccy[ia][ib]=as*sin(bb); 
	  if (ccy[ia][ib]==0) 
	      ccy[ia][ib]=1e-11;
      }
  }

  // cumulative beta distribution
  for (int i=0;i<nbet;++i) 
      beta_int[i+1]=beta_int[i]+beta_pt[i];

  // initialize WC response matrices
  double  n5 = 0;			// pre-polarizer neutrons
  double   N[NTOF]={0};			// chopped neutrons at end of SMpol
  double P2N[NTOF]={0};			//  " * P^2
  double  WN[NTOF]={0};			// captures in 3He target
  double  BN[NTOF][nwc]={{0}};		// N_i = N beta_i    = \sum{n_i} ions
  double GBN[NTOF][nwc]={{0}};		// M_i = N_i gamma_i = \sum{n_i gamma}
  double D2N[NTOF][nwc][nwc]={{{0}}};	// delta^2 N_ij = covariance
  double  GW[NTOF][nwc]={{0}};		// weight of each element

  // loop over events, fill "n","p2n" histograms, wc response matrices
  if (ntp->GetEntries()<nev) 
      nev=ntp->GetEntries();
  for (int iev=sev;iev<sev+nev;++iev) 
  {
      if (verbose && cnt) 
      {		// :........:....
	  if      (iev%(50*cnt)==0) 
	      cout<<endl<<" :"<<flush;
	  else if (iev%(10*cnt)==0) 
	      cout<<":"<<flush;
	  else if (iev%cnt==0) cout<<"."<<flush;
      }

      // read variables
      ntp->GetEntry(iev);
      hl5.Fill(l,p5*1.4/2*60); 
      n5 += p5;
      hl6.Fill(l,p6*1.4/2*60);

      // polarizer
      float tx = 1; //Transmission
      b_pol->GetEntry(iev);
      if (pol!=pol) 
	  pol=0; //nan

      // choppers
      for (int j=0;j<nch;++j) 
      {
	  float chw = chop[j]-ch_phi[j];
	  if (chw<0) 
	      chw += 360;
	  if (chw>ch_open[j]) 
	  {
	      tx=0; 
	      break; 
	  }
      }
      if (tx==0) 
	  continue;
      hlc.Fill(l,p6*1.4/2*60);

    // RFSF, averaged over spin sequence
    float t_sf = (t6+(zsf-z6)/vz6)*freq;
    static const float spin_seq_ave[]={1, -0.5, 0, 0.5, -1, 0.5, 0, -0.5};
    if (psf==1 && (t_sf<rfsf_phi || t_sf>rfsf_phi+dsf)) 
	continue;
    if (t_sf!=0) 
    {
	if (dsf<0) 
	{
	    pol*= spin_seq_ave[int(fabs(t_sf-rfsf_phi-0.5)+0.5)%8];
	    pol*=(1-cos(k_rfsf/vz6/(fmod(t_sf-rfsf_phi+10,1)+rfsf_phi)))/2.;
	} 
	else 
	{
	    if (t_sf<rfsf_phi || t_sf>rfsf_phi+dsf) pol*=psf;
	}
    }
    hls.Fill(l,p6*1.4/2*60);

    // fill histograms for N,P2N
    float dtev=(zwc-z6)/vz6, tev=fmod((t6+dtev)*freq, 1);
    int it((tev*ntof+1)-1); 
    assert(it>=0 && it<ntof);
    float n = p6 * tx;
    N  [it] += n;
    P2N[it] += n * pol*pol;
	
    // collimator
    float xx=x6+vx6*(zwc-z6)/vz6;
    if (xcol>0 && fabs(xx)>xcol/2) 
	continue;
    float yy=y6+vy6*(zwc-z6)/vz6;
    if (ycol>0 && fabs(yy)>ycol/2) 
	continue;
    hlx.Fill(l,p6*1.4/2*60);

    // simulate ion chamber response
    float zev=dwc/2.; 
    for (int iz=0; iz<nz; ++iz, zev+=dwc) 
    {
	dtev=(zev+zwc-z6)/vz6; 
	tev=fmod((t6+dtev)*freq, 1);
	it  = int(tev*ntof+1)-1;
	assert(it>=0 && it<ntof);
	float xev=x6+vx6*dtev, yev=y6+vy6*dtev;
	float rhosig=rho3*ksig*l; // attenuation const and weight
	float wza = (exp(-rhosig*zev)-exp(-rhosig*(zev+dwc)))*da/2*db/2/PI;
	for (int ia=0; ia<na; ++ia) 
	{ 
	    cz=ccz[ia];
	    for (int ib=0; ib<nb; ++ib) 
	    { 
		cx=ccx[ia][ib]; 
		cy=ccy[ia][ib];
		float d1=d1r, d2=d2r, d1t,d2t; // ionization range
		
		// restrict ionization to active volume of wc
		if (cz>0) 
		    d1t=(z1w-zev)/cz, d2t=(z2w-zev)/cz;
		else      
		    d1t=(z2w-zev)/cz, d2t=(z1w-zev)/cz;
		if (d1<d1t) 
		    d1=d1t;  
		if (d2>d2t) 
		    d2=d2t;
		
		if (cx>0) 
		    d1t=(x1w-xev)/cx, d2t=(x2w-xev)/cx;
		else	   
		    d1t=(x2w-xev)/cx, d2t=(x1w-xev)/cx;
		if (d1<d1t) 
		    d1=d1t;  
		if (d2>d2t) d2=d2t;

		if (cy>0) 
		    d1t=(y1w-yev)/cy, d2t=(y2w-yev)/cy;
		else	    
		    d1t=(y2w-yev)/cy, d2t=(y1w-yev)/cy;
		if (d1<d1t) 
		    d1=d1t;  
		if (d2>d2t) 
		    d2=d2t;

		if (d2<d1) 
		    continue;  // not in active volume

		// iterate over ionized cells
		float beta1, beta0=beta_fn(d1);

		float wz=(z0w-zev)/cz, dwz=dzw/cz;
		int jz((d1-wz)/dwz), djz=1; 
		if (jz==nwz)
		    --jz;
		wz+=dwz*jz; 
		if (cz>0) 
		    wz+=dwz; 
		else 
		    dwz*=-1, djz*=-1;

		float wx=(x0w-xev)/cx, dwx=dxw/cx;
		int jx((d1-wx)/dwx), djx=1; 
		if (jx==nwx) 
		    --jx;
		wx+=dwx*jx; 
		if (cx>0) 
		    wx+=dwx; 
		else 
		    dwx*=-1, djx*=-1;

		int k=0;
		assert(0<=jz&&jz<nwz && 0<=jx&&jx<nwx);
		while (0<=jz&&jz<nwz && 0<=jx&&jx<nwx) 
		{
		    kzx[k] = jz*nwx + jx;
		    if (d2<=wz && d2<=wx) 
		    { 
			kbeta[k++]=beta_fn(d2)-beta0; 
			break; 
		    }
		    if (wz<wx) 
		    { 
			beta1=beta_fn(wz); 
			jz+=djz; 
			d1=wz; 
			wz+=dwz; 
		    }
		    else       
		    { 
			beta1=beta_fn(wx); 
			jx+=djx; 
			d1=wx; 
			wx+=dwx; 
		    }
		    kbeta[k++]=beta1-beta0; 
		    beta0=beta1;
	  }

		// tabulate ion response
		WN[it] += n*wza;
		for (int i=0;i<k;++i) 
		{
		    float ni= n*wza*kbeta[i];
		    BN [it][kzx[i]] += ni;
		    GBN[it][kzx[i]] += ni*cxyz[geom_xyz];
		    for (int j=0;j<k;++j) 
		    {
			D2N[it][kzx[i]][kzx[j]] += ni*kbeta[j];
		    }
		}
	    }
	}
    }
  }
  f->Close();

  // calculate FOM=p2n, projection; draw both
  double N_tot=0, P2N_tot=0, WN_tot=0, xd2a_tot=0;
  for (int it=0;it<ntof;++it) 
  {
      
      TMatrixDSym mat(nwc, &**D2N[it]);
      if (verbose>3 && ntof==1) 
      {
	  cout<<"\n delta^2 N_ij :\n"; 
	  mat.Print(); 
      }
      // for (int i=0;i<nwc;++i) for (int j=0;j<nwc;++j) if (i!=j) mat(i,j)=0;
      mat.Invert();
      if (verbose>3 && ntof==1) 
      { 
	  cout<<"\n delta^-2 N_ij :\n"; 
	  mat.Print(); 
      }
      
      double xd2a=0;
      for (int i=0;i<nwc;++i) 
      {
	  for (int j=0;j<nwc;++j) 
	  {
	      GW[it][i] += GBN[it][i]*GBN[it][j]*mat(i,j);
	  }
	  xd2a += GW[it][i];
      }
      N_tot  += N[it];
      P2N_tot+= P2N[it];
      WN_tot += WN[it];
      xd2a_tot += xd2a;

      if (verbose > 2) 
      {
	  
	  printf("\n  beta_i:");
	  for (int i=0;i<nwc;++i) 
	  {
	      if (!(i%nwx)) 
		  printf("\n  ");
	      printf(" %9.5g",BN[it][i]/N[it]);
	  }

	  printf("\n\n  gamma_i:");
	  for (int i=0;i<nwc;++i) 
	  {
	      if (!(i%nwx)) 
		  printf("\n  ");
	      printf(" %9.5g",GBN[it][i]/BN[it][i]);
	  }

	  printf("\n\n  weight_i:");
	  for (int i=0;i<nwc;++i)
	  {
	      if (!(i%nwx)) 
		  printf("\n  ");
	      printf(" %9.5g",GW[it][i]);
	  }
	  printf("\n\n");	  
      }
      
      if (verbose > 4) 
      {	
	  printf("\n\n  beta_i:");
	  for (int j=0;j<nwc;++j) 
	  {
	      printf(" %9.5g",BN[it][j]/N[it]);
	  }

	  printf("\n\n  beta_ij:");
	  for (int i=0;i<nwc;++i) 
	  {
	      printf("\n  ");
	      for (int j=0;j<nwc;++j) 
	      {
		  printf(" %9.5g", D2N[it][i][j]/N[it]);
	      }
	  }	  
      }

      if (verbose>1 && ntof>1) 
      {
	  cout<<"  N          = "<< N[it] <<endl;
	  cout<<"  <P^2>      = "<< P2N[it] / N[it] <<endl;
	  cout<<"  <W>        = "<< WN[it] / N[it] <<endl;
	  cout<<"  delta^-2 A = "<< xd2a*P2N[it]/N[it] <<endl;
	  cout<<"  sigma_d    = "<< sqrt(N[it] / xd2a) <<endl<<endl<<endl;
      }
  }
  cout<<"All TOF bins combined"<<endl;
  cout<<"  N0         = "<< n5  <<endl;
  cout<<"  N          = "<< N_tot <<endl;
  cout<<"  <P^2>      = "<< P2N_tot/N_tot <<endl;
  cout<<"  <W>        = "<< WN_tot / N_tot <<endl;
  cout<<"  delta^-2 A = "<< xd2a_tot*P2N_tot/N_tot <<endl;
  cout<<"  sigma_d    = "<< sqrt(N_tot / xd2a_tot) <<endl;

  return sqrt(N_tot / xd2a_tot);
}


#ifndef __CINT__
int main(int argc, char** argv)
{
    gApplication = new TRint("n3HeSim", &argc, argv);
    gSystem->ChangeDirectory("poly_sm6");
    n3HeSim(1e4);
    gApplication->Run();
}
#endif
