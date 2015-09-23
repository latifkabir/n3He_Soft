// $Id:$   -*-c++-*-
// by Chris Crawford <chris2@lns.mit.edu> 2006/09/25
// 
// $ root -l tx_pol_cuts.C ntp5/mcstas.root

#include "TCut.h"
#include "TApplication.h"
#include "spline.C"
#include <iostream>
using namespace std;

/// calculate FOM for SM bender (w/r beam at end of guide):
//
// TH1* sum=new TH1F("sum","",1,0,1);
// mcstas->Draw("0>>sum","p5"*chop_tx("f1",70,132)*chop_tx("g2",97,167),"goff"); 
// //mcstas->Draw("0>>sum","p5","goff"); //alternate normalization
//   n=sum->Integral();
// mcstas->Draw("0>>sum","p_h2"*chop_tx("f1",70,132)*chop_tx("g2",97,167)*lh2_cap(),"goff"); 
//   tn=sum->Integral();
// mcstas->Draw("0>>sum","pol*p_h2"*chop_tx("f1",70,132)*chop_tx("g2",97,167)*lh2_cap()*rfsf_pol(234)*lh2_pol(),"goff"); 
//   ptn=sum->Integral();
//
/// calculate FOM for 3He cell (w/r beam at end of guide):
//
// mcstas->Draw("0>>sum","p_h2"*chop_tx("f1",70,132)*chop_tx("g2",97,167)*col_tx()*he3_tx()*lh2_cap(),"goff"); 
//   tn=sum->Integral();
// mcstas->Draw("0>>sum","p_h2"*chop_tx("f1",70,132)*chop_tx("g2",97,167)*col_tx()*he3_tx()*lh2_cap()*he3_pol()*rfsf_pol(234)*lh2_pol(),"goff"); 
//   ptn=sum->Integral();
//
// t   = tn/n;   		// tx
// p   = ptn/tn;		// pol
// pt  = ptn/n;   		// FOM
// p2t = ptn/n * ptn/tn;	// FOM


/// Chopper
//
// recommended values (18m):
//   rfsf:phi=234, "f1":phi1=70,eta1=132, "g2":phi2=97,eta2=167

// nominal phases

double cf[]={  73,  98, 117, 136 };
double cw[]={ 125, 168, 201, 234 };

void print_naive_angles()
{
  int ch_ind[6][2]={{1,2},{2,3},{3,4},{1,3},{2,4},{1,4}};
  for (int iv=0; iv<6;iv++) {
    cout<<"200"; cout<<"\t";
    cout<<int(cf[ch_ind[iv][0]-1]); cout<<"\t";
    cout<<int(cw[ch_ind[iv][0]-1]); cout<<"\t";
    cout<<int(cf[ch_ind[iv][1]-1]); cout<<"\t";
    cout<<int(cw[ch_ind[iv][1]-1]); cout<<"\t";
    cout<<endl;
  }
}

// var = a##i, eg. "f1" where
//   a="f"(cw),"g"(ccw) and i="1","2","3","4"
// 0<= var < 360 required range of chopper variable
// 0<= phi < 360 phase at opening
// 0<= open<=360 opening angle

TCut chop_tx(const char* var, double phi, double open)
{
  while (phi<0) phi+=360;
  while (phi>=360) phi-=360;
  TString* str=new TString;
  if (phi+open<360)
    *str = TString::Format("%f<%s&&%s<%f", phi, var,var, phi+open);
  else
    *str = TString::Format("%f<%s||%s<%f", phi, var,var, phi+open-360);
  return str->Data();
}

TCut chop_tx(const char* var)
{
  if (!var||!var[0]||var[1]<'1'||var[1]>'4') return TCut("");
  return chop_tx(var,cf[var[1]-'1'],cw[var[1]-'1']);
}

TCut chop_tx()
{
  TCut c1=chop_tx("f1",70,132);
  TCut c2=chop_tx("g2",97,167);
  TCut cc=c1*c2;
  return cc;
}

/// He3 cell
//
// ksig = 0.07855/(Amg.cm.Ang)  =  5327 b * 2200 m/s * mn/h
// 0<pol<1, nl = 4.0 Amg.cm

double ksig=0.07855;

TCut he3_tx(double pol=0.6, double nl=4.0)
{
  return TString::Format("exp(%f*l)*cosh(%f*l)", -nl*ksig, pol*nl*ksig).Data();
}

TCut he3_pol(double pol=0.6, double nl=4.0)
{
  return TString::Format("tanh(%f*l)", pol*nl*ksig).Data();
}


/// Collimators
//

TCut col_tx(char* col="5", double d=9.0)
{
  return TString::Format("x%s^2+y%s^2<%f", col,col,d*d/4/100/100).Data();
}


/// RFSF
//
// dist [m]	effective distance of the RFSF (a tuning parameter)
// -360<=phi	(phase = t*freq*360deg) when the spin flipper starts
// freq=60Hz	accelerator pulse frequency
// 111		circumvents fmod(-x) quirk
// abs_np	number of pulses away from correct one
// k_eps	average efficiency over location in spin sequence
// eps		efficiency of spin flipper (when on; else -1)
// note:	final result also averaged over up/down pulses
//		we assume that polarization asymmetry cancelled by geometry

TCut rfsf_pol(double phi=200, double dist=17.65, double freq=60.)	// lanl: 15.868
{
  // recommended value (18m): phi=234
  TString abs_np=TString::Format		// 0,1,2,3,4
    ("((abs(t_sf*%g-%g)+0.5)%%8)", freq, phi/360+0.5);
  TString k_eps =TString::Format		// 1, -1/2, 0, 1/2, -1
    ("((8728785<<3*%s&14680064)/2097152-2)/2", abs_np.Data());
  TString eps   =TString::Format		// RFSF efficiency (+/-)
    ("cos(%g/vz_sf/(fmod(t_sf+%g,%g)+%g))",
     acos(-1)*dist, (111-phi/360)/freq, 1/freq, phi/360/freq );
  TString rfsf = k_eps+"*(1-"+eps+")/2";	// RFSF on/off, spin seq ave
  return rfsf.Data();
}


/// LH2 para-hydrogen target
//
// capture cross section:  sigma = 1.66 b/sqrt(E/meV), nl = 1.33/b
//   kcap = 1.66 b
//   knl  = 1.33 /b
//   kmeV = sqrt(2meV/nm) = 437.39 m/s
// cutoff [meV]	is the highest neutron energy in which polarization is preserved
//   kmn = 2/mn = 191312.97 (m/s)^2/meV;  v=sqrt(2E/mn)=sqrt(kmn*E)

double kcap = 1.66;   // b   = sigma(1meV)
double kmeV = 437.39; // m/s = sqrt(2*1meV/mn)
double knl  = 1.33;   // 1/b

TCut lh2_cap()
{
  return TString::Format("1-exp(-%f/v)",kcap*knl*kmeV).Data();
}

double kmn=191312.97;

TCut lh2_pol(double cutoff=15)
{
  return TString::Format("v<%f",sqrt(kmn*cutoff)).Data();
}


// He4 transmission, 3.97K from Sommers et al., PR97,855(1955)
//   

float he4_lambda[]={3,     4,     5,     6,     7,     8,     9,     10,   11,    12,    13,    14,    15,    16,    17   };
float he4_sigma []={0.667, 0.615, 0.537, 0.366, 0.217, 0.154, 0.129, 0.12, 0.116, 0.12,  0.122, 0.126, 0.13,  0.134, 0.138};
float he4_tx_ref[]={0.407, 0.437, 0.485, 0.611, 0.746, 0.813, 0.84, 0.851, 0.855, 0.851, 0.848, 0.844, 0.839, 0.835, 0.83 };
float he4_th_ref  = 0.6913; // [m] = 27+7/32 in
float he4_y2[15]={0};

double he4_tx(double l, double th)
{
  if (he4_y2[0]==0)
    spline(he4_lambda-1, he4_tx_ref-1, he4_y2-1, 15);
  return pow(splint(he4_lambda-1, he4_tx_ref-1, he4_y2-1, 15, l),
	     th/he4_th_ref);
}

TCut he4_tx(double th) // [m] thickness
{
  return TString::Format("he4_tx(l,%f)",th).Data();
}

/// end of cuts


void tx_pol_cuts()
{
}

#ifndef __CINT__
int main(int argc, char** argv)
{
  gApplication = new TApplication("tx_pol_cuts", &argc, argv);
  tx_pol_cuts();
}
#endif
