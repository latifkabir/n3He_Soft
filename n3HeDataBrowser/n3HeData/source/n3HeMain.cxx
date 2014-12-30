#include <n3HeMain.h>
#include <TROOT.h>
#include <math.h>
#include "TTreeRaw.h"
#include <TH1D.h>
#include "TFormula.h"
#include <iostream>
#include <TRandom3.h>
#include <time.h>
#include <TStyle.h>

using namespace std;

///////////////////////////////////////////////////////////////////////
//     This class provides the Graphical User Interface for n3He        //
// experiment at FNBL13 at SNS.                                          //
//  If you have new ideas or suggestions, feel free to produce a new        //
// version of this code and document your classes or improvements in the    //
// Readme File and in the n3Heamma on-line analysis technical notes         //
//                                                                          //
//  Any command entered in the User interface command combo box will be     //
// passed to the CINT interpreter. This combo box will keep the commands history //
//  and will allow you to re-execute the same commands during an editor      //
//  session.                                                                 //
///////////////////////////////////////////////////////////////////////////

n3HeMain::n3HeMain(const TGWindow *p, ClineArgs clargs, UInt_t w, UInt_t h) :
		TGMainFrame(p, w, h) {
	//set_new_handler(0);
	SetCleanup (kDeepCleanup);
	dMWWidth = w;
	dMWHeight = h;
	seconds = time(NULL);

	toggle_det_cuts = true;

	rgen = new TRandom3(seconds);

	draw_mod_10 = 10; // 0 means all

	fLabel = NULL;
	txt1 = NULL;
	txt2 = NULL;
	txt3 = NULL;
	dUtilityFrame = NULL;

	dHorizontal3DLine = NULL;
	dTabLayout = NULL;
	dMainCanvas = NULL;
	dMainTabFrame = NULL;
	dMainCnvLayout = NULL;
	dMainTabLayout = NULL;

	dDetCanvas1 = NULL;
	dDetCnvFrame1 = NULL;
	dDetTabFrame1 = NULL;
	dDetTabLayout1 = NULL;
	dDetCnvLayout1 = NULL;
	dDetMenu1 = NULL;

	dDetCanvas2 = NULL;
	dDetCnvFrame2 = NULL;
	dDetTabFrame2 = NULL;
	dDetTabLayout2 = NULL;
	dDetCnvLayout2 = NULL;
	dDetMenu2 = NULL;

	dDetCanvas3 = NULL;
	dDetCnvFrame3 = NULL;
	dDetTabFrame3 = NULL;
	dDetTabLayout3 = NULL;
	dDetCnvLayout3 = NULL;
	dDetMenu3 = NULL;

	dDetCanvas4 = NULL;
	dDetCnvFrame4 = NULL;
	dDetTabFrame4 = NULL;
	dDetTabLayout4 = NULL;
	dDetCnvLayout4 = NULL;
	dDetMenu4 = NULL;

	dUserCanvas = NULL;
	dUserTabFrame = NULL;
	dUserTabLayout = NULL;
	dUserCnvLayout = NULL;
	dUserMenu = NULL;

	dMonTabFrame = NULL;
	dMonCnvFrame = NULL;
	dMonCnvLayout = NULL;
	dMonTabLayout = NULL;
	dMonCanvas = NULL;
	dMonMenu = NULL;

	dSFLTabFrame = NULL;
	dSFLCnvFrame = NULL;
	dSFLCnvLayout = NULL;
	dSFLTabLayout = NULL;
	dSFLCanvas = NULL;
	dSFLMenu = NULL;

	dLogTabLayout = NULL;
	dLogTabFrame = NULL;
	dLogEditLayout = NULL;
	dLogText = NULL;
	dLogEdit = NULL;

	dMenuBar = NULL;
	dMenuBarLayout = NULL;
	dMenuBarItemLayout = NULL;
	dMenuBarHelpLayout = NULL;
	dMenuFile = NULL;
	dMenuHelp = NULL;
	dMenuTools = NULL;

	SetLogFileOpen (kFalse);

	MakeMenuLayout();
	MakeUtilityLayout();
	MakeMainTab();
	SetWindowName("n3He Data Analysis");
	MapSubwindows();
	Resize (GetDefaultSize());

	MapWindow();
	MakeDetectorTab1();
	MakeDetectorTab2();
	MakeDetectorTab3();
	MakeDetectorTab4();
	MakeLogTab();
	MakeSpinFlipperTab();
	MakeMonitorTab();

	MakeUserTab();

}

n3HeMain::~n3HeMain() {
	delete txt1;
	delete txt2;
	delete txt3;
	delete fLabel;
	delete dTab;
	delete dLogTabFrame;
	delete dMainTabFrame;
	delete dMainCanvas;

	delete dMainCnvLayout;
	delete dMainTabLayout;
	delete dTabLayout;
	delete dMainCnvLayout;
	delete dLogTabLayout;
	delete dLogEditLayout;

	delete dMenuBar;
	delete dMenuFile, delete dMenuTools, delete dMenuHelp;
	delete dMenuBarLayout;
	delete dMenuBarItemLayout;
	delete dMenuBarHelpLayout;
	delete dDetMenu1;
	delete dDetMenu2;
	delete dDetMenu3;
	delete dDetMenu4;
	delete dMonMenu;
	delete dSFLMenu;

	delete dDetCanvas1;
	delete dDetCnvFrame1;
	delete dDetTabFrame1;
	delete dDetTabLayout1;
	delete dDetCnvLayout1;

	delete dDetCanvas2;
	delete dDetCnvFrame2;
	delete dDetTabFrame2;
	delete dDetTabLayout2;
	delete dDetCnvLayout2;

	delete dDetCanvas3;
	delete dDetCnvFrame3;
	delete dDetTabFrame3;
	delete dDetTabLayout3;
	delete dDetCnvLayout3;

	delete dDetCanvas4;
	delete dDetCnvFrame4;
	delete dDetTabFrame4;
	delete dDetTabLayout4;
	delete dDetCnvLayout4;

	delete dUserCanvas;
	delete dUserTabFrame;
	delete dUserTabLayout;
	delete dUserCnvLayout;
	delete dUserMenu;

	delete dMonTabFrame;
	delete dMonCnvFrame;
	delete dMonTabLayout;
	delete dMonCanvas;

	delete dSFLTabFrame;
	delete dSFLCnvLayout;
	delete dSFLTabLayout;
	delete dSFLCanvas;

	delete fL1;
	delete fL3;

	delete dUtilityFrame;
	delete dHorizontal3DLine;

	delete dLogText;
	delete dLogEdit;
}

void n3HeMain::MakeMenuLayout() {
	fPid = gSystem->GetPid(); // TProcessID::GetSessionProcessID();

	dMenuBarLayout = new TGLayoutHints(
			kLHintsTop | kLHintsLeft | kLHintsExpandX, 0, 0, 1, 1);
	dMenuBarItemLayout = new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 4, 0,
			0);
	dMenuBarHelpLayout = new TGLayoutHints(kLHintsTop | kLHintsRight);

	dMenuFile = new TGPopupMenu(fClient->GetRoot());

	dMenuFile->AddSeparator();
	dMenuFile->AddEntry("View Log", M_VIEW_LOG);
	dMenuFile->AddEntry("View Detector Data", M_VIEW_DET_DATA);
	dMenuFile->AddEntry("View Monitor Data", M_VIEW_MON_DATA);
	dMenuFile->AddEntry("View Spin Flipper Data", M_VIEW_SFL_DATA);
	dMenuFile->AddEntry("Plot Detectors Entry$%10", M_SET_MOD);

	dMenuFile->AddEntry("View User Interface", M_VIEW_USER);

	dMenuFile->AddSeparator();
	dMenuFile->AddEntry("E&xit", M_FILE_EXIT);

	dMenuSettings = new TGPopupMenu(fClient->GetRoot());
	dMenuSettings->AddEntry("Set Config Options...", M_SET_CONFIG);

	dMenuTools = new TGPopupMenu(fClient->GetRoot());

	dMenuTools->AddEntry("Generate Pedestal Data", M_GEN_PEDS);
	dMenuTools->AddEntry("Generate Unpolarized M2/M1 Ratio", M_GEN_UPR);
	dMenuTools->AddEntry("Generate Unpolarized M3/M1 Ratio", M_GEN_UPR2);
	dMenuTools->AddEntry("Generate Unpolarized M3/M2 Ratio", M_GEN_UPR3);
	dMenuTools->AddEntry("Generate Background Data", M_GEN_BGRND);
	dMenuTools->AddEntry("User Interface", M_USER_OPTIONS);

	dMenuHelp = new TGPopupMenu(fClient->GetRoot());
	dMenuHelp->AddEntry("&Contents", M_HELP_CONTENTS);
	dMenuHelp->AddEntry("&About", M_HELP_ABOUT);

	dMenuFile->Associate(this);
	dMenuSettings->Associate(this);
	dMenuTools->Associate(this);
	dMenuHelp->Associate(this);

	dMenuBar = new TGMenuBar(this, 1, 1, kHorizontalFrame);
	dMenuBar->AddPopup("&File", dMenuFile, dMenuBarItemLayout);
	dMenuBar->AddPopup("&Settings", dMenuSettings, dMenuBarItemLayout);
	dMenuBar->AddPopup("&Tools", dMenuTools, dMenuBarItemLayout);
	dMenuBar->AddPopup("&Help", dMenuHelp, dMenuBarItemLayout);

	AddFrame(dMenuBar, dMenuBarLayout);

	dMenuFile->UnCheckEntry(M_VIEW_DET_DATA);
	dMenuFile->UnCheckEntry(M_VIEW_MON_DATA);
	dMenuFile->UnCheckEntry(M_VIEW_SFL_DATA);
	dMenuFile->UnCheckEntry(M_VIEW_USER);
	dMenuFile->UnCheckEntry(M_VIEW_LOG);
	dMenuFile->CheckEntry(M_SET_MOD);
}

//--------------------------------

void n3HeMain::MakeUtilityLayout() {

	fL1 = new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX, 2, 2, 2,
			2);
	fL3 = new TGLayoutHints(kLHintsTop | kLHintsLeft, 2, 2, 2, 2);
	dHorizontal3DLine = new TGHorizontal3DLine(this);
	AddFrame(dHorizontal3DLine, new TGLayoutHints(kLHintsTop | kLHintsExpandX));

	dUtilityFrame = new TGHorizontalFrame(this, 60, 10);
	fF1 = new TGCompositeFrame(dUtilityFrame, 60, 60,
			kHorizontalFrame | kSunkenFrame);
	fF1->AddFrame(new TGLabel(fF1, "Enter Run:"), fL3);

	fNumber = new TGNumberEntry(fF1, 0, 9, 999999, TGNumberFormat::kNESInteger,
			TGNumberFormat::kNEANonNegative, TGNumberFormat::kNELLimitMinMax, 0,
			999999);
	fNumber->Connect("ValueSet(Long_t)", "n3HeMain", this, "DoSetLabel()");
	fF1->AddFrame(fNumber,
			new TGLayoutHints(kLHintsTop | kLHintsLeft, 5, 5, 5, 5));
	//Insert the button "Enter"
	txt1 = new TGTextButton(fF1, "Enter", 1);
	txt1->SetToolTipText("Click me to enter run number");
	txt1->Connect("Clicked()", "n3HeMain", this, "DoSetLabel()");
	fF1->AddFrame(txt1, fL3);

	//Add the group frame:
	fGframe = new TGGroupFrame(fF1, "Run# entered:");
	fLabel = new TGLabel(fGframe, "No input.");
	fGframe->AddFrame(fLabel,
			new TGLayoutHints(kLHintsTop | kLHintsLeft, 1, 1, 1, 1));
	fF1->AddFrame(fGframe, fL3);

	//Add the button "Read"
	txt2 = new TGTextButton(fF1, "Read", 1);
	txt2->SetToolTipText("Click me to read the run.");
	txt2->Connect("Clicked()", "n3HeMain", this, "OpenRun()");

	fF1->AddFrame(txt2, fL3);

	//Add the button "Read NEXT"
	txt3 = new TGTextButton(fF1, "Read NEXT", 1);
	txt3->SetToolTipText("Click me to read the NEXT run.");
	txt3->Connect("Clicked()", "n3HeMain", this, "OpenNextRun()");

	fF1->AddFrame(txt3, fL3);

	dUtilityFrame->AddFrame(fF1, fL1);

	AddFrame(dUtilityFrame, fL1);
}

void n3HeMain::MakeMainTab() {
	dTabLayout = new TGLayoutHints(
			kLHintsBottom | kLHintsExpandX | kLHintsExpandY, 2, 2, 5, 1);
	dTab = new TGTab(this, dMWWidth - 15, dMWHeight - 80);

	if (TabActive("Main"))
		return;

	dMainTabLayout = new TGLayoutHints(
			kLHintsLeft | kLHintsTop | kLHintsExpandX | kLHintsExpandY);
	dMainCnvLayout = new TGLayoutHints(
			kLHintsTop | kLHintsExpandX | kLHintsExpandY, 0, 0, 1, 2);

	TGCompositeFrame *tf = dTab->AddTab("Main");

	dMainTabFrame = new TGHorizontalFrame(tf, 10, 10);
	dMainCanvas = new TRootEmbeddedCanvas("pC", dMainTabFrame, 10, 10);
	dMainTabFrame->AddFrame(dMainCanvas, dMainCnvLayout);
	dMainTabFrame->Resize(dMWWidth - 15, dMWHeight - 110);
	tf->AddFrame(dMainTabFrame, dMainTabLayout);
	AddFrame(dTab, dTabLayout);

	dMainCanvas->GetCanvas()->SetBorderMode(0);
	dMainCanvas->GetCanvas()->Connect("Picked(TPad*, TObject*, Int_t)",
			"n3HeMain", this, "PadIsPicked(TPad*, TObject*, Int_t)");

}

void n3HeMain::MakeDetectorTab1() {
	if (TabActive("DAQ21"))
		return;

	dDetTabLayout1 = new TGLayoutHints(
			kLHintsLeft | kLHintsTop | kLHintsExpandX | kLHintsExpandY);
	dDetCnvLayout1 = new TGLayoutHints(
			kLHintsTop | kLHintsExpandX | kLHintsExpandY, 0, 0, 1, 2);

	TGCompositeFrame *tf = dTab->AddTab("DAQ21");

	dDetTabFrame1 = new TGHorizontalFrame(tf, 10, 10);
	dDetCanvas1 = new TRootEmbeddedCanvas("dC", dDetTabFrame1, 10, 10);
	dDetTabFrame1->AddFrame(dDetCanvas1, dDetCnvLayout1);
	dDetTabFrame1->Resize(dMWWidth - 15, dMWHeight - 80);
	tf->AddFrame(dDetTabFrame1, dDetTabLayout1);
	dTab->MapSubwindows();
	dTab->Layout();

	dDetCanvas1->GetCanvas()->SetBorderMode(0);

	dDetMenu1 = new TGPopupMenu(fClient->GetRoot());
	dDetMenu1->AddEntry("Detector Histograms", M_VIEW_DET_HIST);
	dDetMenu1->Associate(this);
	dMenuBar->AddPopup("&DAQ21", dDetMenu1, dMenuBarItemLayout);
	dMenuBar->MapSubwindows();
	dMenuBar->Layout();

	dMenuFile->CheckEntry(M_VIEW_DET_DATA);

}


void n3HeMain::MakeDetectorTab2() {
	if (TabActive("DAQ22"))
		return;

	dDetTabLayout2 = new TGLayoutHints(
			kLHintsLeft | kLHintsTop | kLHintsExpandX | kLHintsExpandY);
	dDetCnvLayout2 = new TGLayoutHints(
			kLHintsTop | kLHintsExpandX | kLHintsExpandY, 0, 0, 1, 2);

	TGCompositeFrame *tf = dTab->AddTab("DAQ22");

	dDetTabFrame2 = new TGHorizontalFrame(tf, 10, 10);
	dDetCanvas2 = new TRootEmbeddedCanvas("dC", dDetTabFrame2, 10, 10);
	dDetTabFrame2->AddFrame(dDetCanvas2, dDetCnvLayout2);
	dDetTabFrame2->Resize(dMWWidth - 15, dMWHeight - 80);
	tf->AddFrame(dDetTabFrame2, dDetTabLayout2);
	dTab->MapSubwindows();
	dTab->Layout();

	dDetCanvas2->GetCanvas()->SetBorderMode(0);

	dDetMenu2 = new TGPopupMenu(fClient->GetRoot());
	dDetMenu2->AddEntry("Detector Histograms", M_VIEW_DET_HIST);
	dDetMenu2->Associate(this);
	dMenuBar->AddPopup("&DAQ22", dDetMenu2, dMenuBarItemLayout);
	dMenuBar->MapSubwindows();
	dMenuBar->Layout();

	dMenuFile->CheckEntry(M_VIEW_DET_DATA);

}

void n3HeMain::MakeDetectorTab3() {
	if (TabActive("DAQ23"))
		return;

	dDetTabLayout3 = new TGLayoutHints(
			kLHintsLeft | kLHintsTop | kLHintsExpandX | kLHintsExpandY);
	dDetCnvLayout3 = new TGLayoutHints(
			kLHintsTop | kLHintsExpandX | kLHintsExpandY, 0, 0, 1, 2);

	TGCompositeFrame *tf = dTab->AddTab("DAQ23");

	dDetTabFrame3 = new TGHorizontalFrame(tf, 10, 10);
	dDetCanvas3 = new TRootEmbeddedCanvas("dC", dDetTabFrame3, 10, 10);
	dDetTabFrame3->AddFrame(dDetCanvas3, dDetCnvLayout3);
	dDetTabFrame3->Resize(dMWWidth - 15, dMWHeight - 80);
	tf->AddFrame(dDetTabFrame3, dDetTabLayout3);
	dTab->MapSubwindows();
	dTab->Layout();

	dDetCanvas3->GetCanvas()->SetBorderMode(0);

	dDetMenu3 = new TGPopupMenu(fClient->GetRoot());
	dDetMenu3->AddEntry("Detector Histograms", M_VIEW_DET_HIST);
	dDetMenu3->Associate(this);
	dMenuBar->AddPopup("&DAQ23", dDetMenu3, dMenuBarItemLayout);
	dMenuBar->MapSubwindows();
	dMenuBar->Layout();

	dMenuFile->CheckEntry(M_VIEW_DET_DATA);

}

void n3HeMain::MakeDetectorTab4() {
	if (TabActive("DAQ24"))
		return;

	dDetTabLayout4 = new TGLayoutHints(
			kLHintsLeft | kLHintsTop | kLHintsExpandX | kLHintsExpandY);
	dDetCnvLayout4 = new TGLayoutHints(
			kLHintsTop | kLHintsExpandX | kLHintsExpandY, 0, 0, 1, 2);

	TGCompositeFrame *tf = dTab->AddTab("DAQ24");

	dDetTabFrame4 = new TGHorizontalFrame(tf, 10, 10);
	dDetCanvas4 = new TRootEmbeddedCanvas("dC", dDetTabFrame4, 10, 10);
	dDetTabFrame4->AddFrame(dDetCanvas4, dDetCnvLayout4);
	dDetTabFrame4->Resize(dMWWidth - 15, dMWHeight - 80);
	tf->AddFrame(dDetTabFrame4, dDetTabLayout4);
	dTab->MapSubwindows();
	dTab->Layout();

	dDetCanvas4->GetCanvas()->SetBorderMode(0);

	dDetMenu4 = new TGPopupMenu(fClient->GetRoot());
	dDetMenu4->AddEntry("Detector Histograms", M_VIEW_DET_HIST);
	dDetMenu4->Associate(this);
	dMenuBar->AddPopup("&DAQ24", dDetMenu4, dMenuBarItemLayout);
	dMenuBar->MapSubwindows();
	dMenuBar->Layout();

	dMenuFile->CheckEntry(M_VIEW_DET_DATA);

}


void n3HeMain::MakeMonitorTab() {
	if (TabActive("Monitors"))
		return;

	dMonTabLayout = new TGLayoutHints(
			kLHintsLeft | kLHintsTop | kLHintsExpandX | kLHintsExpandY);
	dMonCnvLayout = new TGLayoutHints(
			kLHintsTop | kLHintsExpandX | kLHintsExpandY, 0, 0, 1, 2);

	TGCompositeFrame *tf = dTab->AddTab("Monitors");

	dMonTabFrame = new TGHorizontalFrame(tf, 10, 10);
	dMonCanvas = new TRootEmbeddedCanvas("mC", dMonTabFrame, 10, 10);
	dMonTabFrame->AddFrame(dMonCanvas, dMonCnvLayout);
	dMonTabFrame->Resize(dMWWidth - 15, dMWHeight - 80);
	tf->AddFrame(dMonTabFrame, dMonTabLayout);

	dMonCanvas->GetCanvas()->SetBorderMode(0);

	dMonMenu = new TGPopupMenu(fClient->GetRoot());
	dMonMenu->AddEntry("Histograms", M_VIEW_MON_HIST);
	dMonMenu->Associate(this);
	dMenuBar->AddPopup("&Beam Monitors", dMonMenu, dMenuBarItemLayout);
	dMenuBar->MapSubwindows();
	dMenuBar->Layout();

	dMenuFile->CheckEntry(M_VIEW_MON_DATA);

	dTab->MapSubwindows();
	dTab->Layout();

}

void n3HeMain::MakeUserTab() {
	if (TabActive("User Interface"))
		return;

	dUserTabLayout = new TGLayoutHints(
			kLHintsLeft | kLHintsTop | kLHintsExpandX | kLHintsExpandY);
	dUserCnvLayout = new TGLayoutHints(
			kLHintsTop | kLHintsExpandX | kLHintsExpandY, 0, 0, 1, 2);
	//----------------------------------------------

	TGCompositeFrame *tf = dTab->AddTab("User Interface");
	// Create the horizontal frame for CINT command 
	TGHorizontalFrame *fHL2 = new TGHorizontalFrame(tf, 70, 100);
	tf->AddFrame(fHL2, new TGLayoutHints(kLHintsNormal, 5, 5, 5, 5));
	TGLabel *fInlabel = new TGLabel(fHL2, "Command (local):");
	fHL2->AddFrame(fInlabel, new TGLayoutHints(kLHintsCenterY));

	fCommandBuf = new TGTextBuffer(256);
	fComboCmd = new TGComboBox(fHL2, "", 1);
	fCommand = fComboCmd->GetTextEntry();
	fCommandBuf = fCommand->GetBuffer();
	fCommand->Associate(this);
	fComboCmd->Resize(450, fCommand->GetDefaultHeight());
	fHL2->AddFrame(fComboCmd,
			new TGLayoutHints(kLHintsCenterY | kLHintsRight | kLHintsExpandX,
					20, 0, 0, 0));

	//Get root commands from the file .root_hist, in the Home directory
	TString defhist(
			Form("%s/.root_hist",
					gSystem->UnixPathName(gSystem->HomeDirectory())));
	FILE *lunin = fopen(defhist.Data(), "rt");
	if (lunin) {
		char histline[256];
		while (fgets(histline, 256, lunin)) {
			histline[strlen(histline) - 1] = 0; // remove trailing "\n"
			fComboCmd->InsertEntry(histline, 0, -1);
		}
		fclose(lunin);
	}

	//Choose the background colour for the Output window:

	Pixel_t backpxl;
	gClient->GetColorByName("#c0c0c0", backpxl);
	fTextView = new TGTextView(this, 500, 94, 1, kFixedWidth | kFixedHeight);
	//   fTextView->SetBackground(backpxl);
	tf->AddFrame(fTextView, new TGLayoutHints(kLHintsExpandX));

	//---------------------------------------------------
	dUserTabFrame = new TGVerticalFrame(tf, 10, 10);
	dUserCanvas = new TRootEmbeddedCanvas("uC", dUserTabFrame, 10, 10);
	dUserTabFrame->AddFrame(dUserCanvas, dUserCnvLayout);
	dUserTabFrame->Resize(dMWWidth - 15, dMWHeight - 80);
	tf->AddFrame(dUserTabFrame, dUserTabLayout);

	dUserCanvas->GetCanvas()->SetBorderMode(0);

	dUserCanvas->GetCanvas()->Connect("Picked(TPad*, TObject*, Int_t)",
			"n3HeMain", this, "PadIsPicked(TPad*, TObject*, Int_t)");

	dMenuFile->CheckEntry(M_VIEW_USER);

	dTab->MapSubwindows();
	dTab->Layout();

	//-------------------   
}

void n3HeMain::MakeLogTab() {
	if (TabActive("Log Book"))
		return;

	dLogTabLayout = new TGLayoutHints(
			kLHintsLeft | kLHintsTop | kLHintsExpandX | kLHintsExpandY);
	dLogEditLayout = new TGLayoutHints(
			kLHintsTop | kLHintsExpandX | kLHintsExpandY, 0, 0, 1, 2);

	TGCompositeFrame *tf = dTab->AddTab("Log Book");

	dLogTabFrame = new TGHorizontalFrame(tf, 10, 10);
	dLogEdit = new TGTextEdit(dLogTabFrame, 10, 10, kSunkenFrame);
	dLogTabFrame->AddFrame(dLogEdit, dLogEditLayout);
	dLogTabFrame->Resize(dMWWidth - 15, dMWHeight - 80);
	tf->AddFrame(dLogTabFrame, dLogTabLayout);

	dTab->MapSubwindows();
	dTab->Layout();

	dLogEdit->Connect("Opened()", "n3HeMain", this, "LogOpened()");
	dLogEdit->Connect("Closed()", "n3HeMain", this, "LogClosed()");
	dLogEdit->Connect("Saved()", "n3HeMain", this, "LogSaved()");
	dLogEdit->Connect("SavedAs()", "n3HeMain", this, "LogSavedAs()");

	if (dLogText) {
		dLogEdit->SetText(dLogText);
		dLogText = NULL;
	} else {
		sprintf(dMiscbuffer, "New Log Session Started: %s at %s", GetDate(),
				GetTime());
		Append (dMiscbuffer);
	}
	dMenuFile->CheckEntry(M_VIEW_LOG);
}

void n3HeMain::MakeSpinFlipperTab() {
	if (TabActive("Spin Flipper"))
		return;

	dSFLTabLayout = new TGLayoutHints(
			kLHintsLeft | kLHintsTop | kLHintsExpandX | kLHintsExpandY);
	dSFLCnvLayout = new TGLayoutHints(
			kLHintsTop | kLHintsExpandX | kLHintsExpandY, 0, 0, 1, 2);

	TGCompositeFrame *tf = dTab->AddTab("Spin Flipper");

	dSFLTabFrame = new TGVerticalFrame(tf, 10, 10);

	dSFLCanvas = new TRootEmbeddedCanvas("sC", dSFLTabFrame, 10, 10);
	dSFLTabFrame->AddFrame(dSFLCanvas, dSFLCnvLayout);
	dSFLTabFrame->Resize(dMWWidth - 15, dMWHeight - 80);
	tf->AddFrame(dSFLTabFrame, dSFLTabLayout);

	dSFLCanvas->GetCanvas()->SetBorderMode(0);

	dSFLMenu = new TGPopupMenu(fClient->GetRoot());
	dSFLMenu->AddEntry("Histograms", M_VIEW_SFL_HIST);

	dSFLMenu->Associate(this);
	dMenuBar->AddPopup("&Spin Flipper", dSFLMenu, dMenuBarItemLayout);
	dMenuBar->MapSubwindows();
	dMenuBar->Layout();
	dMenuFile->CheckEntry(M_VIEW_SFL_DATA);

	dTab->MapSubwindows();
	dTab->Layout();

}

Char_t *n3HeMain::GetTime() {
	time_t *cutime;
	tm *ltime;
	cutime = new time_t;
	time(cutime);
	ltime = localtime((const time_t*) cutime);
	if (ltime->tm_sec < 10)
		sprintf(dTime, "%d:%d:0%d", ltime->tm_hour, ltime->tm_min,
				ltime->tm_sec);
	else if (ltime->tm_min < 10)
		sprintf(dTime, "%d:0%d:%d", ltime->tm_hour, ltime->tm_min,
				ltime->tm_sec);
	else if (ltime->tm_hour < 10)
		sprintf(dTime, "0%d:%d:%d", ltime->tm_hour, ltime->tm_min,
				ltime->tm_sec);
	else
		sprintf(dTime, "%d:%d:%d", ltime->tm_hour, ltime->tm_min,
				ltime->tm_sec);
	return dTime;
}

Char_t *n3HeMain::GetDate() {
	time_t cutime;
	time(&cutime);
	tm *date = localtime((const time_t*) &cutime);
	sprintf(dDate, "%d-%d-%d", date->tm_mon + 1, date->tm_mday,
			date->tm_year + 1900);
	return dDate;
}

void n3HeMain::RemoveDetectorTab1() {
	if (!TabActive("DAQ21"))
		return;
	int tab = GetTabIndex("DAQ21");
	if (tab < 0)
		return;

	dTab->RemoveTab(tab);
	dTab->Layout();

	delete dDetCanvas1;
	dDetCanvas1 = NULL;
	delete dDetCnvLayout1;
	dDetCnvLayout1 = NULL;
	delete dDetTabFrame1;
	dDetTabFrame1 = NULL;
	delete dDetTabLayout1;
	dDetTabLayout1 = NULL;

	dMenuFile->UnCheckEntry(M_VIEW_DET_DATA);

	dMenuBar->RemovePopup("DAQ1");
	delete dDetMenu1;
	dMenuBar->MapSubwindows();
	dMenuBar->Layout();
}


void n3HeMain::RemoveDetectorTab2() {
	if (!TabActive("DAQ22"))
		return;
	int tab = GetTabIndex("DAQ22");
	if (tab < 0)
		return;

	dTab->RemoveTab(tab);
	dTab->Layout();

	delete dDetCanvas2;
	dDetCanvas2 = NULL;
	delete dDetCnvLayout2;
	dDetCnvLayout2 = NULL;
	delete dDetTabFrame2;
	dDetTabFrame2 = NULL;
	delete dDetTabLayout2;
	dDetTabLayout2 = NULL;

	dMenuFile->UnCheckEntry(M_VIEW_DET_DATA);

	dMenuBar->RemovePopup("DAQ22");
	delete dDetMenu2;
	dMenuBar->MapSubwindows();
	dMenuBar->Layout();
}


void n3HeMain::RemoveDetectorTab3() {
	if (!TabActive("DAQ23"))
		return;
	int tab = GetTabIndex("DAQ23");
	if (tab < 0)
		return;

	dTab->RemoveTab(tab);
	dTab->Layout();

	delete dDetCanvas3;
	dDetCanvas3 = NULL;
	delete dDetCnvLayout3;
	dDetCnvLayout3 = NULL;
	delete dDetTabFrame3;
	dDetTabFrame3 = NULL;
	delete dDetTabLayout3;
	dDetTabLayout3 = NULL;

	dMenuFile->UnCheckEntry(M_VIEW_DET_DATA);

	dMenuBar->RemovePopup("DAQ23");
	delete dDetMenu3;
	dMenuBar->MapSubwindows();
	dMenuBar->Layout();
}


void n3HeMain::RemoveDetectorTab4() {
	if (!TabActive("DAQ24"))
		return;
	int tab = GetTabIndex("DAQ24");
	if (tab < 0)
		return;

	dTab->RemoveTab(tab);
	dTab->Layout();

	delete dDetCanvas4;
	dDetCanvas4 = NULL;
	delete dDetCnvLayout4;
	dDetCnvLayout4 = NULL;
	delete dDetTabFrame4;
	dDetTabFrame4 = NULL;
	delete dDetTabLayout4;
	dDetTabLayout4 = NULL;

	dMenuFile->UnCheckEntry(M_VIEW_DET_DATA);

	dMenuBar->RemovePopup("DAQ24");
	delete dDetMenu4;
	dMenuBar->MapSubwindows();
	dMenuBar->Layout();
}


void n3HeMain::RemoveMonitorTab() {
	if (!TabActive("Monitors"))
		return;
	int tab = GetTabIndex("Monitors");
	if (tab < 0)
		return;

	dTab->RemoveTab(tab);
	dTab->Layout();

	delete dMonCanvas;
	dMonCanvas = NULL;
	delete dMonCnvLayout;
	dMonCnvLayout = NULL;
	delete dMonTabFrame;
	dMonTabFrame = NULL;
	delete dMonTabLayout;
	dMonTabLayout = NULL;

	dMenuFile->UnCheckEntry(M_VIEW_MON_DATA);

	dMenuBar->RemovePopup("Beam Monitors");
	delete dMonMenu;
	dMenuBar->MapSubwindows();
	dMenuBar->Layout();
}

void n3HeMain::RemoveUserTab() {
	if (!TabActive("User Interface"))
		return;
	int tab = GetTabIndex("User Interface");
	if (tab < 0)
		return;

	dTab->RemoveTab(tab);
	dTab->Layout();

	delete dUserCanvas;
	dUserCanvas = NULL;
	delete dUserCnvLayout;
	dUserCnvLayout = NULL;
	delete dUserTabFrame;
	dUserTabFrame = NULL;
	delete dUserTabLayout;
	dUserTabLayout = NULL;
	dMenuFile->UnCheckEntry(M_VIEW_USER);
	dMenuBar->RemovePopup("User Interface");
	delete dUserMenu;
	dMenuBar->MapSubwindows();
	dMenuBar->Layout();
}

void n3HeMain::RemoveSpinFlipperTab() {
	if (!TabActive("Spin Flipper"))
		return;
	int tab = GetTabIndex("Spin Flipper");
	if (tab < 0)
		return;

	dTab->RemoveTab(tab);
	dTab->Layout();

	delete dSFLCanvas;
	dSFLCanvas = NULL;
	delete dSFLCnvLayout;
	dSFLCnvLayout = NULL;
	delete dSFLTabFrame;
	dSFLTabFrame = NULL;
	delete dSFLTabLayout;
	dSFLTabLayout = NULL;

	dMenuFile->UnCheckEntry(M_VIEW_SFL_DATA);

	dMenuBar->RemovePopup("Spin Flipper");
	delete dSFLMenu;
	dMenuBar->MapSubwindows();
	dMenuBar->Layout();
}

void n3HeMain::RemoveLogTab() {
	if (!TabActive("Log Book"))
		return;
	int tab = GetTabIndex("Log Book");
	if (tab < 0)
		return;

	dTab->RemoveTab(tab);
	dTab->Layout();

	if (dLogEdit->GetText()->GetLongestLine() > 0)
		dLogText = new TGText(dLogEdit->GetText());
	else
		dLogText = NULL;
	delete dLogEdit;
	dLogEdit = NULL;
	delete dLogTabFrame;
	dLogTabFrame = NULL;
	delete dLogTabLayout;
	dLogTabLayout = NULL;
	delete dLogEditLayout;
	dLogEditLayout = NULL;

	dMenuFile->UnCheckEntry(M_VIEW_LOG);
}

TCanvas *n3HeMain::SplitCanvas(TRootEmbeddedCanvas *cnv, int r, int c,
		const char* ttip) {
	TCanvas *mc = cnv->GetCanvas();
	if (!mc)
		return NULL;
	mc->Clear();
	mc->Update();
	if (r != 0 && c != 0) {
		mc->Divide(r, c);
		for (int i = 0; i < (int) (r * c); i++) {
			mc->cd(i + 1);
			if (ttip) {
				sprintf(dMiscbuffer, "%s %02d", ttip, i);
				gPad->SetToolTipText(dMiscbuffer, 250);
			}
		}
	}
	return mc;
}

void n3HeMain::LogOpened() {
	SetLogFileOpen (kTrue);
	Bool_t untitled =
			!strlen(dLogEdit->GetText()->GetFileName()) ? kTrue : kFalse;
	if (!untitled)
		SetLogFileName((char*) dLogEdit->GetText()->GetFileName());
}

void n3HeMain::LogClosed() {
	SetLogFileOpen (kFalse);
	SetLogFileName("");
}

void n3HeMain::LogSaved() {
	SetLogFileOpen (kTrue);
	Bool_t untitled =
			!strlen(dLogEdit->GetText()->GetFileName()) ? kTrue : kFalse;
	if (!untitled)
		SetLogFileName((char*) dLogEdit->GetText()->GetFileName());
}

void n3HeMain::LogSavedAs() {
	SetLogFileOpen (kTrue);
	Bool_t untitled =
			!strlen(dLogEdit->GetText()->GetFileName()) ? kTrue : kFalse;
	if (!untitled)
		SetLogFileName((char*) dLogEdit->GetText()->GetFileName());
}

void n3HeMain::PadIsPicked(TPad* selpad, TObject* selected, Int_t event) {
	//printf("Pad %d picked! \n",selpad->GetNumber());
}

// Slot method connected to the ValueSet(Long_t) signal.
// It displays the value set in TGNumberEntry widget.
void n3HeMain::DoSetLabel() {
	int nr;

	nr = fNumber->GetNumberEntry()->GetIntNumber();
	if ((nr <= 0) || (nr != (int(nr))))
		fLabel->SetText("Bad Run number!");
	else {
		fLabel->SetText(Form("%d", nr));
		SetRunNumber(nr);
	}
	// Parent frame Layout() method will redraw the label showing the new value.
	fGframe->Layout();

	return;

}

//Open the entered run#:
void n3HeMain::OpenRun() {
	int nr; //run number
	nr = GetRunNumber();
	//check if the run number exists!
	if ((runNumber == 0) || (runNumber > 200000)) {
		fLabel->SetText("Run# not found!");
		fGframe->Layout();
	} else {

		//Now draw all the plots for this run number
		PlotMainData(PT_GRAPH, nr);
		PlotDetectorData1(PT_GRAPH, DDT_DETECTORS, nr);
		PlotDetectorData2(PT_GRAPH, DDT_DETECTORS, nr);
		PlotDetectorData3(PT_GRAPH, DDT_DETECTORS, nr);
		PlotDetectorData4(PT_GRAPH, DDT_DETECTORS, nr);
		PlotMonitorData(PT_GRAPH, nr);
		PlotSpinFlipperData(PT_GRAPH, DDT_SFLIPPER, nr);
		cout << "Done Drawing Graphs" << endl;
	}
	return;
}

//Open the run after entered run#:
void n3HeMain::OpenNextRun() {
	int nr = GetRunNumber();
	fNumber->SetNumber(nr + 1);
	this->DoSetLabel();
	this->OpenRun();
}

void n3HeMain::PlotMonitorData(ERPlotTypes ptype, Int_t runNumber) {
	TCanvas *mc = NULL;

	if (!TabOpen("Monitors"))
		return;


	mc = SplitCanvas(dMonCanvas, 1, 3, "Monitor");
	if (!mc)
		return;

	TTreeRaw r(runNumber);
	cout << "runNumber " << runNumber << endl;

	for (int i = 1; i <= 4; i++) {
		mc->cd(i);

		if (i != 2 && i != 3) {

			cout << "Drawing Monitor-1" << i << endl;
			r.Draw("d30[][0]:Iteration$");

			gPad->Modified();
			gPad->Update();
		}
		if (i == 2){
		        
		  cout << "Drawing Monitor-4" << endl;
			r.Draw("d30[][2]:Iteration$");

			gPad->Modified();
			gPad->Update();
		}
	}

	if (mc) {
		mc->Modified();
		mc->Update();
	}
	return;
}

void n3HeMain::PlotMainData(ERPlotTypes ptype, Int_t runNumber) {
	TCanvas *mc = NULL;
	gStyle->SetPalette(1);

	if (!TabOpen("Main"))
		return;
	printf("Run number read:%d \n", runNumber);

	TTreeRaw r(runNumber);

	mc = SplitCanvas(dMainCanvas, 2, 3, "Main");
	if (!mc)
		return;

	mc->cd(1);
	//draw the monitor 1  
	cout << "Drawing monitor 1" << endl;
	r.Draw("d30[][0]:Iteration$");

	gPad->Modified();
	gPad->Update();

	mc->cd(2);
	//draw the spin flipper data
	cout << "Drawing spin flipper data" << endl;
	r.Draw("d30[][2]:Iteration$");

	gPad->Modified();
	gPad->Update();

	mc->cd(3);
	//draw DAQ21 channel-0

	cout << "Drawing DAQ21 channel-0" << endl;
	r.Draw("d21[][0]:Iteration$");

	gPad->Modified();
	gPad->Update();

	mc->cd(4);
	//draw DAQ22 channel-0
	cout << "Drawing DAQ22 channel-0" << endl;
	r.Draw("d22[][0]:Iteration$");

	gStyle->SetOptStat("");

	gPad->Modified();
	gPad->Update();

	if (mc) {
		mc->Modified();
		mc->Update();
	}
	mc->cd(5);

	//draw DAQ23 channel-0
	cout << "Drawing DAQ23 channel-0" << endl;
	r.Draw("d23[][0]:Iteration$");

	gPad->Modified();
	gPad->Update();

	if (mc) {
		mc->Modified();
		mc->Update();
	}

	mc->cd(6);
	//draw DAQ24 channel-0
	cout << "Drawing DAQ24 channel-0" << endl;
	r.Draw("d24[][0]:Iteration$");

	gPad->Modified();
	gPad->Update();

	if (mc) {
		mc->Modified();
		mc->Update();
	}
}

void n3HeMain::PlotDetectorData1(ERPlotTypes ptype, ENDataType dtype,
		Int_t runNumber) {
	TCanvas *mc = NULL;

	if (!TabOpen("DAQ21"))
		return;
	TTreeRaw r(runNumber);

	mc = SplitCanvas(dDetCanvas1, 6, 6, "DAQ21");
	if (!mc)
		return;

	//We have 36 channels per DAQ:  
	for (Int_t i = 0; i < 36; i++) {
		mc->cd(i + 1);
		//if(ptype ==  PT_HISTO_1D){
		if (i % 6 == 0)
			cout << endl;
		if (i < 10) {
			cout << "   ";
		} else {
			cout << "  ";
		}
		cout << i;
		cout.flush();

		//plot DAQ21 data
		if(i<18)      //Module 1
		    r.Draw(Form("d21[][%i]:Iteration$", i), "","");
		else          //Module 2
		    r.Draw(Form("d21[][%i]:Iteration$", i+6), "","");

		gPad->Modified();
		gPad->Update();
	}
	cout << endl;

	if (mc) {
		mc->Modified();
		mc->Update();
	}

	return;
}


void n3HeMain::PlotDetectorData2(ERPlotTypes ptype, ENDataType dtype,
		Int_t runNumber) {
	TCanvas *mc = NULL;

	if (!TabOpen("DAQ22"))
		return;
	TTreeRaw r(runNumber);

	mc = SplitCanvas(dDetCanvas2, 6, 6, "DAQ22");
	if (!mc)
		return;

	//We have 36 channels per DAQ:  
	for (Int_t i = 0; i < 36; i++) {
		mc->cd(i + 1);
		//if(ptype ==  PT_HISTO_1D){
		if (i % 6 == 0)
			cout << endl;
		if (i < 10) {
			cout << "   ";
		} else {
			cout << "  ";
		}
		cout << i;
		cout.flush();

		//plot DAQ22 data
		if(i<18)      //Module 1
		    r.Draw(Form("d22[][%i]:Iteration$", i), "","");
		else         //Module 2
		    r.Draw(Form("d22[][%i]:Iteration$", i+6), "","");
		
		gPad->Modified();
		gPad->Update();
	}
	cout << endl;

	if (mc) {
		mc->Modified();
		mc->Update();
	}

	return;
}

void n3HeMain::PlotDetectorData3(ERPlotTypes ptype, ENDataType dtype,
		Int_t runNumber) {
	TCanvas *mc = NULL;

	if (!TabOpen("DAQ23"))
		return;
	TTreeRaw r(runNumber);

	mc = SplitCanvas(dDetCanvas3, 6, 6, "DAQ23");
	if (!mc)
		return;

	//We have 36 channels per DAQ:  
	for (Int_t i = 0; i < 36; i++) {
		mc->cd(i + 1);
		//if(ptype ==  PT_HISTO_1D){
		if (i % 6 == 0)
			cout << endl;
		if (i < 10) {
			cout << "   ";
		} else {
			cout << "  ";
		}
		cout << i;
		cout.flush();

		//plot DAQ23 data
		if(i<18)    //Module 1
		    r.Draw(Form("d23[][%i]:Iteration$", i), "","");
		else       //Module 2
		    r.Draw(Form("d23[][%i]:Iteration$", i+6), "","");
		
		gPad->Modified();
		gPad->Update();
	}
	cout << endl;

	if (mc) {
		mc->Modified();
		mc->Update();
	}

	return;
}


void n3HeMain::PlotDetectorData4(ERPlotTypes ptype, ENDataType dtype,
		Int_t runNumber) {
	TCanvas *mc = NULL;

	if (!TabOpen("DAQ24"))
		return;
	TTreeRaw r(runNumber);

	mc = SplitCanvas(dDetCanvas4, 6, 6, "DAQ24");
	if (!mc)
		return;

	//We have 36 channels per DAQ:  
	for (Int_t i = 0; i < 36; i++) {
		mc->cd(i + 1);
		//if(ptype ==  PT_HISTO_1D){
		if (i % 6 == 0)
			cout << endl;
		if (i < 10) {
			cout << "   ";
		} else {
			cout << "  ";
		}
		cout << i;
		cout.flush();

		//plot DAQ24 data
		if(i<18)
		    r.Draw(Form("d24[][%i]:Iteration$", i), "","");
		else
		    r.Draw(Form("d24[][%i]:Iteration$", i+6), "","");
		
		gPad->Modified();
		gPad->Update();
	}
	cout << endl;

	if (mc) {
		mc->Modified();
		mc->Update();
	}

	return;
}


void n3HeMain::PlotSpinFlipperData(ERPlotTypes ptype, ENDataType dtype,
		Int_t runNumber) {
	TCanvas *mc = NULL;

	if (!TabOpen("Spin Flipper"))
		return;
	TTreeRaw r(runNumber);

	mc = SplitCanvas(dSFLCanvas, 1, 2, "Spin Flipper");
	if (!mc)
		return;
	mc->cd(1);
	cout << "Drawing spin flipper current" << endl;
	r.Draw("d30[][1]:Iteration$");
	gPad->Modified();
	gPad->Update();

	mc->cd(2);
	cout << "Drawing spin flipper voltage" << endl;
	r.Draw("d30[][3]:Iteration$");

	gPad->Modified();
	gPad->Update();


	if (mc) {
		mc->Modified();
		mc->Update();
	}
}

Int_t n3HeMain::GetFilenameFromDialog(char *file, const char *ext,
		ERFileStatus status, Bool_t kNotify, const char *notifytext) {
	if (kNotify && notifytext) {
		int retval;
		new TGMsgBox(fClient->GetRoot(), this, "File Open Operation",
				notifytext, kMBIconQuestion, kMBOk | kMBCancel, &retval);
		if (retval == kMBCancel)
			return PROCESS_FAILED;
	}

	if (!ext || !*ext)
		return PROCESS_FAILED;
	if (!file)
		return PROCESS_FAILED;
	TString fext = ext;
	const char *filetypes[12];
	Int_t index = 0;

	if (fext.Contains("dat")) {
		filetypes[index] = "Data files";
		index++;
		filetypes[index] = "*.dat";
		index++;
	}
	if (fext.Contains("txt")) {
		filetypes[index] = "Data files";
		index++;
		filetypes[index] = "*.txt";
		index++;
	}
	if (fext.Contains("csv")) {
		filetypes[index] = "Data files";
		index++;
		filetypes[index] = "*.csv";
		index++;
	}
	if (fext.Contains("root")) {
		filetypes[index] = "Root files";
		index++;
		filetypes[index] = "*.root";
		index++;
	}
	if (fext.Contains("log")) {
		filetypes[index] = "Log files";
		index++;
		filetypes[index] = "*.log";
		index++;
	}
	filetypes[index] = "All files";
	index++;
	filetypes[index] = "*";
	index++;
	filetypes[index] = 0;
	index++;
	filetypes[index] = 0;
	index++;

	static TString dir(".");
	TGFileInfo fi;

	if (status == FS_OLD) {
		fi.fFileTypes = (const char **) filetypes;
		fi.fIniDir = StrDup(dir);
		new TGFileDialog(fClient->GetRoot(), this, kFDOpen, &fi);
		dir = fi.fIniDir;

		if (!fi.fFilename) {
			return PROCESS_FAILED;
		};
	}
	if (status == FS_NEW) {
		fi.fFileTypes = (const char **) filetypes;
		fi.fIniDir = StrDup(dir);
		new TGFileDialog(fClient->GetRoot(), this, kFDSave, &fi);
		dir = fi.fIniDir;

		if (!fi.fFilename) {
			return PROCESS_FAILED;
		};
	}
	strcpy(file, fi.fFilename);
	return PROCESS_OK;
}

Int_t n3HeMain::Append(char *buffer, Bool_t T_Stamp) {
	int size = strlen(buffer) + 200;
	int lnum = 0;
	int cutoff = 110;    //64;
	char *ptr;
	char *line;
	int index;
	char *tmpbuffer = new char[size];
	TGLongPosition pos;
	pos.fX = 0;
	TGText * cText = NULL;

	if (!tmpbuffer) {
		return LOG_PROCESS_ERROR;
	}
	memset(tmpbuffer, '\0', size);

	if (dLogEdit) {
		cText = new TGText(dLogEdit->GetText());
	} else if (dLogText) {
		cText = dLogText;
	} else {
		dLogText = new TGText();
		cText = dLogText;
	}

	if (!cText)
		return LOG_PROCESS_ERROR;

	ptr = buffer;
	index = 0;
	lnum = 0;
	for (int i = 0; i <= (int) strlen(buffer); i++) {
		if (buffer[i] == '\n' || i - index > cutoff) {
			line = new char[i - index + 1];
			memset(line, '\0', i - index + 1);
			strncpy(line, ptr, i - index);
			if (lnum == 0 && T_Stamp)
				sprintf(tmpbuffer, "%s     %s", GetTime(), line);
			else
				sprintf(tmpbuffer, "             %s", line);
			pos.fY = cText->RowCount();
			cText->InsText(pos, tmpbuffer);
			lnum++;

			delete[] line;
			if (buffer[i] == '\n') {
				index = i + 1;
				ptr = &buffer[i + 1];
			} else {
				index = i;
				ptr = &buffer[i];
			}
		} else if (buffer[i] == '\0') {
			if (lnum == 0 && T_Stamp)
				sprintf(tmpbuffer, "%s     %s", GetTime(), ptr);
			else
				sprintf(tmpbuffer, "             %s", ptr);
// 	  sprintf(tmpbuffer,"             %s",ptr);
			pos.fY = cText->RowCount();
			cText->InsText(pos, tmpbuffer);

		}
	}

	pos.fY = cText->RowCount();
	cText->InsText(pos, "");

	if (dLogEdit) {
		dLogEdit->SetText(cText);
		dLogEdit->Goto(cText->RowCount(),
				cText->GetLineLength((Long_t)(cText->RowCount() - 1)));
	}

	return LOG_PROCESS_OK;
}

void n3HeMain::CloseLogFile() {
	if (TabActive("Log Book") && dLogEdit) {
		SendMessage(dLogEdit, MK_MSG(kC_COMMAND, kCM_MENU),
				TGTextEdit::kM_FILE_CLOSE, 0);
	}
	SetLogFileOpen (kFalse);
	SetLogFileName("");
}

Int_t n3HeMain::OpenLogFile(ERFileStatus status, const char* file) {
	if (IsLogFileOpen())
		CloseLogFile();
	char filename[NAME_STR_MAX];
	if (!file) {
		if (GetFilenameFromDialog(filename, "log", status) == PROCESS_FAILED)
			return PROCESS_FAILED;
	} else
		strcpy(filename, file);

	if (strcmp(".log", strrchr(filename, '.')))
		return PROCESS_FAILED;

	if (!TabActive("Log Book") || !dLogEdit)
		MakeLogTab();
	if (!dLogEdit)
		return PROCESS_FAILED;
	if (!dLogEdit->LoadFile(filename))
		if (!dLogEdit->SaveFile(filename))
			return PROCESS_FAILED;

	SetLogFileOpen (kTrue);
	SetLogFileName(filename);
	return PROCESS_OK;
}

Bool_t n3HeMain::TabActive(const char *str) {
	int nt = dTab->GetNumberOfTabs();
	for (int i = 0; i < nt; i++) {
		TString s = dTab->GetTabTab(i)->GetString();
		if (s == str) {
			return kTrue;
		}
	}
	return kFalse;
}

// This function returns true for the current open tab and false for others
Bool_t n3HeMain::TabOpen(const char *str) {
	if (dTab->GetNumberOfTabs() > 0) {
		int current_tab_index = dTab->GetCurrent();
		TString s = dTab->GetTabTab(current_tab_index)->GetString();
		if (s == str) {
			return kTrue;
		}
	}
	return kFalse;
}

Int_t n3HeMain::GetTabIndex(const char *str) {
	int nt = dTab->GetNumberOfTabs();
	for (int i = 0; i < nt; i++) {
		TString s = dTab->GetTabTab(i)->GetString();
		if (s == str) {
			return i;
		}
	}
	return -1;
}

Int_t n3HeMain::WriteLogData(const char *filename) {
	if (!IsLogFileOpen()) {
		if (OpenLogFile(FS_NEW, filename) != PROCESS_OK)
			return PROCESS_FAILED;
	}
	if (!TabActive("Log Book"))
		return PROCESS_FAILED;
	if (!dLogEdit)
		return PROCESS_FAILED;
	if (!dLogEdit->SaveFile(filename))
		return PROCESS_FAILED;
	return PROCESS_OK;
}

void n3HeMain::OpenBrowser() {
	return;
}

void n3HeMain::CloseWindow() {
	// Got close message for this MainFrame. Terminate the application
	// or returns from the TApplication event loop (depending on the
	// argument specified in TApplication::Run()).

	sprintf(dMiscbuffer, "rm %s", "n3HeD_PID.DAT");
	system (dMiscbuffer);
	//CloseRun();
	gApplication->Terminate(0);

}

Bool_t n3HeMain::ProcessMessage(Long_t msg, Long_t parm1, Long_t parm2) {
	// Handle messages send to the MainFrame object. E.g. all menu button
	// messages.
	Int_t rn;  //the run number
	switch (GET_MSG(msg)) {

	case kC_COMMAND:
		switch (GET_SUBMSG(msg)) {

		case kCM_COMBOBOX: {
			switch (parm1) {
			case M_PATH_SELECT:
				printf("Path# %d selected!", fPathSelect->GetSelected());
				SetSelectedPath (dTOFBINStrings[0]);
				break;
			}
		}
			break;

		case kCM_MENUSELECT:
			break;

		case kCM_MENU:
			switch (parm1) {

			case M_RUN_OPEN:
				OpenBrowser();
				break;

			case M_FILE_EXIT:
				CloseWindow();   // this also terminates theApp
				break;

			case M_FILE_CLOSE:

				SplitCanvas(dMainCanvas, 0, 0, NULL);
				break;

			case M_USER_OPTIONS:
				//WriteUserOptions();
				break;

			case M_VIEW_DET_DATA:
				if (dMenuFile->IsEntryChecked(M_VIEW_DET_DATA)) {
					RemoveDetectorTab1();
				} else {
					MakeDetectorTab1();
				}
				break;

			case M_VIEW_USER:
				if (dMenuFile->IsEntryChecked(M_VIEW_USER)) {
					RemoveUserTab();
				} else {
					MakeUserTab();
				}
				break;

			case M_VIEW_MON_DATA:
				if (dMenuFile->IsEntryChecked(M_VIEW_MON_DATA)) {
					RemoveMonitorTab();
				} else {
					MakeMonitorTab();
				}
				break;

			case M_SET_CONFIG:
				//DoConfigSettings();
				break;

			case M_VIEW_SFL_DATA:
				if (dMenuFile->IsEntryChecked(M_VIEW_SFL_DATA)) {
					RemoveSpinFlipperTab();
				} else {
					MakeSpinFlipperTab();
				}
				break;

			case M_GEN_UPR:
				//GenerateUnpolarizedRatio(2,1);
				break;

			case M_GEN_UPR2:
				//GenerateUnpolarizedRatio(3,1);
				break;

			case M_GEN_UPR3:
				//GenerateUnpolarizedRatio(3,2);
				break;

			case M_GEN_PEDS:
				//StoreRunDataAverage("pedestals");
				break;

			case M_SET_MOD:
				toggle_det_cuts = !toggle_det_cuts;
				if (toggle_det_cuts) { // Plot every 10
					dMenuFile->CheckEntry(M_SET_MOD);
					draw_mod_10 = 10;
					cout << "Switched to modulus 10" << endl;
				} else { // Plot all
					dMenuFile->UnCheckEntry(M_SET_MOD);
					draw_mod_10 = 0;
					cout << "Switched to plot all entries" << endl;
				}
				break;

			case M_GEN_BGRND:
				//StoreRunDataAverage("background");
				break;

			case M_VIEW_LOG:
				if (dMenuFile->IsEntryChecked(M_VIEW_LOG)) {
					RemoveLogTab();
				} else {
					MakeLogTab();
				}
				break;

			case M_VIEW_DET_HIST:
				rn = GetRunNumber();
				PlotDetectorData1(PT_HISTO_1D, DDT_DETECTORS, rn);
				break;

			case M_VIEW_SUM_HIST:
				rn = GetRunNumber();
				PlotDetectorData1(PT_HISTO_1D, DDT_SUM, rn);
				break;

			case M_VIEW_DIFF_HIST:
				rn = GetRunNumber();
				PlotDetectorData1(PT_HISTO_1D, DDT_DIFFERENCE, rn);
				break;

			case M_VIEW_DET_WAVE:
				rn = GetRunNumber();
				PlotDetectorData1(PT_GRAPH, DDT_DETECTORS, rn);
				break;

			case M_VIEW_SUM_WAVE:
				rn = GetRunNumber();
				PlotDetectorData1(PT_GRAPH, DDT_SUM, rn);
				break;

			case M_VIEW_DIFF_WAVE:
				rn = GetRunNumber();
				PlotDetectorData1(PT_GRAPH, DDT_DIFFERENCE, rn);
				break;

			case M_VIEW_MON_HIST:
				rn = GetRunNumber();
				PlotMonitorData(PT_HISTO_1D, rn);
				break;

			case M_VIEW_MON_WAVE:
				rn = GetRunNumber();
				PlotMonitorData(PT_GRAPH, rn);
				break;

			case M_VIEW_SFL_HIST:
				rn = GetRunNumber();
				PlotSpinFlipperData(PT_HISTO_1D, DDT_SFLIPPER, rn);
				break;

			case M_VIEW_SFL_WAVE:
				rn = GetRunNumber();
				PlotSpinFlipperData(PT_GRAPH, DDT_SFLIPPER, rn);
				break;

			case M_HELP_CONTENTS:
				//ViewContents();
				break;

			case M_HELP_ABOUT:
				//ViewAbout();
				break;

			case M_SET_SFL_EFF_PARMS:
				//if(IsSFlipperAllocated())
				//dSFlipper->InitSpinFlipEfficiencyMeasurement();
				break;

			case M_CALC_SFL_EFF:
				//GetAnalysisOptionsFromDialog();
				break;

			default:
				break;
			}

			break;
		}
		break;
	case kC_TEXTENTRY:
		switch (GET_SUBMSG(msg)) {
		case kTE_ENTER:
			if (parm1 == 1) {
				// here copy the string from text buffer to return variable
				const char *string = fCommandBuf->GetString();
				if (strlen(string) > 1) {
					// form temporary file path
					TString pathtmp = Form("%s/ride.%d.log",
							gSystem->TempDirectory(), fPid);
					TString sPrompt =
							((TRint*) gROOT->GetApplication())->GetPrompt();
					FILE *lunout = fopen(pathtmp.Data(), "a+t");
					if (lunout) {
						fputs(Form("%s%s\n", sPrompt.Data(), string), lunout);
						fclose(lunout);
					}
					gSystem->RedirectOutput(pathtmp.Data(), "a");
					// gApplication->SetBit(TApplication::kProcessRemotely);
					gROOT->ProcessLine(string);
					// fComboCmd->ReturnPressed();
					fComboCmd->InsertEntry(string, 0, -1);
					Gl_histadd((char *) string);
					gSystem->RedirectOutput(0);
					fTextView->LoadFile(pathtmp.Data());
					if (fTextView->ReturnLineCount() > 7)
						fTextView->SetVsbPosition(fTextView->ReturnLineCount());
					//CheckRemote(string);
					fCommand->Clear();
				}
			}
			break;

		default:
			break;
		}
		break;

	default:
		break;
	}
	return kTRUE;
}

n3HeMain *gViewMain;

int main(int argc, char **argv) {
	char expl[5000];
	ClineArgs dClArgs;
	int help = 0;

	if (argv[1]) {
		for (int i = 1; i < argc; i++) {
			if (strcmp(argv[i], "-b") == 0) {
			}

			if (strcmp(argv[i], "-t") == 0) {
			}

			if (strcmp(argv[i], "-help") == 0) {
				help = 1;
			}

			if (strcmp(argv[i], "-f") == 0) {
				if (!argv[i + 1] || argv[i + 1][0] == '-') {
					printf("\nMissing value for option -f\n\n");
					return 0;
				}

			}

			if (strcmp(argv[i], "-c") == 0) {
				if (!argv[i + 1] || argv[i + 1][0] == '-') {
					printf("\nMissing value for option -c\n\n");
					return 0;
				}

			}
		}
	} else
		printf("\nRun " "DView -help" " for command line help\n\n");

	if (help) {
		strcpy(expl,
				"\n\nThis program takes the following commandline arguments:\n\n");
		strcat(expl, "1) -b        Read binary format file.\n\n");
		strcat(expl,
				"2) -t        Read ascii text file in row and column format.\n\n");
		strcat(expl, "3) -f        Starting filename:\n\n");
		strcat(expl,
				"             Here one of two file types must be used, based on\n");
		strcat(expl, "             the -b or -t parameters passed .\n");
		strcat(expl, "             For case -b, the program expects a\n");
		strcat(expl,
				"             a binary file with format to be specified\n");
		strcat(expl, "             For case -t, it expects an ascii file \n");
		strcat(expl, "             arranged in rows and columns of data.\n");
		strcat(expl,
				"             For the second case, the columns of interest must\n");
		strcat(expl,
				"             be specified with the -c switch (see below).\n");
		strcat(expl,
				"             Always use the full path for the input files.\n\n");
		strcat(expl,
				"4) -c        Columns. Ex: (-c 23) selects columns 2 and 3.\n\n");
		strcat(expl, "9) -help     Prints this help \n\n");

		printf(expl);
	} else {
		TApplication theApp("DView", &argc, argv);

		if (gROOT->IsBatch()) {
			fprintf(stderr, "%s: cannot run in batch mode\n", argv[0]);
			return 1;
		}

		n3HeMain mainWindow(gClient->GetRoot(), dClArgs, 1000, 800);

		gViewMain = &mainWindow;

		mainWindow.WritePid();
		theApp.Run();
	}

	return 0;
}

void n3HeMain::WritePid() {
	FILE *fp = fopen("n3HeD_PID.DAT", "w");
	if (fp) {
		memset(dMiscbuffer, '\0', sizeof(dMiscbuffer));
		sprintf(dMiscbuffer, "%d\n", (int) getpid());
		printf("pid = %s\n", dMiscbuffer);
		fwrite(dMiscbuffer, 1, strlen(dMiscbuffer), fp);
		fclose(fp);
	}
}

