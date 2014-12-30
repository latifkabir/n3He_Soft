#ifndef n3HeMAIN_H
#define n3HeMAIN_H

#include <string.h>
#include <time.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

#ifndef ROOT_TGFrame
#include "TGFrame.h"
#endif
#ifndef ROOT_TGTextEdit
#include "TGTextEdit.h"
#endif

#include <TGTab.h>
#include <TCanvas.h>
#include <TApplication.h>
#include <TInterpreter.h>
#include <Getline.h>
#include <TRint.h>
#include <TSystem.h>
#include <TGComboBox.h>
#include <TGButton.h>
#include <TGMsgBox.h>
#include <TGFrame.h>
#include <TPad.h>
#include <TGLayout.h>
#include <TString.h>
#include <TGSplitter.h>
#include <TGLabel.h>
#include <TGMenu.h>
#include <TGWindow.h>
#include "TRint.h"
#include <TG3DLine.h>
#include <TObjArray.h>
#include <TRootEmbeddedCanvas.h>
#include <TGraph.h>
#include <TMultiGraph.h>
#include <TGraphErrors.h>
#include <TGTextEntry.h>
#include <TGNumberEntry.h>
#include <TGTextView.h>
#include <TGClient.h>

#include <TGFileDialog.h>

#include <TGFSContainer.h>
#include <RQ_OBJECT.h>
#include <TMath.h>
#include <TRandom3.h>
#include <time.h>

#include "n3HeMainDef.h"

//------------------------------------------

class n3HeMain: public TGMainFrame {

	RQ_OBJECT("n3HeMain");

private:

	Int_t fPid; //current process id 
	Int_t runNumber;
	Int_t draw_mod_10;
	Bool_t dLogFileOpen;
	time_t seconds;
	TRandom3* rgen;

	Bool_t IsLogFileOpen() {
		return dLogFileOpen;
	}
	;

	Bool_t toggle_det_cuts;

	Char_t dTOFBINStrings[100][NAME_STR_MAX];
	Char_t dMiscbuffer[MSG_SIZE_MAX];
	Char_t dLogfilename[NAME_STR_MAX];
	Char_t dPath[NAME_STR_MAX];

	Char_t dDate[NAME_STR_MAX];
	Char_t dTime[NAME_STR_MAX];

	Int_t dSelectedTBin;
	Int_t dMWWidth;
	Int_t dMWHeight;
	Int_t dRunNumber;
	Double_t dTBinWidth;
	Double_t dMPOffset;
	Double_t dSessionStartRunTime;

	//------------------------------  

	TGComboBox *fComboCmd;   // CINT command combobox
	TGTextBuffer *fCommandBuf; // text buffer in use 
	TGTextEntry *fCommand;    // text entry for CINT commands
	TGTextView *fTextView;   // display CINT output
	TString fName;       // name of temp created file
	//-----------------------------------
	TGFileContainer *fContents;  //file navigation container
	TGComboBox *fPathSelect;
	TGCompositeFrame *fF1;
	TGGroupFrame *fGframe;
	TGLabel *fLabel;
	TGNumberEntry *fNumber;
	TGLayoutHints *fL3, *fL1;
	TGHorizontal3DLine *dHorizontal3DLine;
	TGHorizontalFrame *dUtilityFrame;
	TGTextButton *txt1, *txt2, *txt3;

	TGTab *dTab;
	TGLayoutHints *dTabLayout;

	TRootEmbeddedCanvas *dMainCanvas;
	TGHorizontalFrame *dMainTabFrame;
	TGLayoutHints *dMainTabLayout;
	TGLayoutHints *dMainCnvLayout;

	TRootEmbeddedCanvas *dDetCanvas1;
	TGCompositeFrame *dDetCnvFrame1;
	TGHorizontalFrame *dDetTabFrame1;
	TGLayoutHints *dDetTabLayout1;
	TGLayoutHints *dDetCnvLayout1;
	TGPopupMenu *dDetMenu1;

	TRootEmbeddedCanvas *dDetCanvas2;
	TGCompositeFrame *dDetCnvFrame2;
	TGHorizontalFrame *dDetTabFrame2;
	TGLayoutHints *dDetTabLayout2;
	TGLayoutHints *dDetCnvLayout2;
	TGPopupMenu *dDetMenu2;

	TRootEmbeddedCanvas *dDetCanvas3;
	TGCompositeFrame *dDetCnvFrame3;
	TGHorizontalFrame *dDetTabFrame3;
	TGLayoutHints *dDetTabLayout3;
	TGLayoutHints *dDetCnvLayout3;
	TGPopupMenu *dDetMenu3;

	TRootEmbeddedCanvas *dDetCanvas4;
	TGCompositeFrame *dDetCnvFrame4;
	TGHorizontalFrame *dDetTabFrame4;
	TGLayoutHints *dDetTabLayout4;
	TGLayoutHints *dDetCnvLayout4;
	TGPopupMenu *dDetMenu4;


	TRootEmbeddedCanvas *dUserCanvas;
	TGVerticalFrame *dUserTabFrame;
	TGLayoutHints *dUserTabLayout;
	TGLayoutHints *dUserCnvLayout;
	TGPopupMenu *dUserMenu;

	TRootEmbeddedCanvas *dMonCanvas;
	TGCompositeFrame *dMonCnvFrame;
	TGHorizontalFrame *dMonTabFrame;
	TGLayoutHints *dMonTabLayout;
	TGLayoutHints *dMonCnvLayout;
	TGPopupMenu *dMonMenu;

	TRootEmbeddedCanvas *dSFLCanvas;
	TGCompositeFrame *dSFLCnvFrame;
	TGVerticalFrame *dSFLTabFrame;
	TGLayoutHints *dSFLTabLayout;
	TGLayoutHints *dSFLCnvLayout;
	TGPopupMenu *dSFLMenu;

	TGText *dLogText;
	TGTextEdit *dLogEdit;
	TGHorizontalFrame *dLogTabFrame;
	TGLayoutHints *dLogTabLayout;
	TGLayoutHints *dLogEditLayout;

	TGMenuBar *dMenuBar;
	TGPopupMenu *dMenuFile;
	TGPopupMenu *dMenuSettings;
	TGPopupMenu *dMenuTools;
	TGPopupMenu *dMenuHelp;

	TGLayoutHints *dMenuBarLayout;
	TGLayoutHints *dMenuBarItemLayout;
	TGLayoutHints *dMenuBarHelpLayout;

	Int_t Append(char *buffer, Bool_t T_Stamp = kFalse);

	void CloseLogFile();

	//Char_t         *GetCurrentDataDirectory(char *str);

	Int_t GetFilenameFromDialog(char *, const char *, ERFileStatus status =
			FS_OLD, Bool_t kNotify = kFalse, const char *notifytext = NULL);

	Int_t GetTabIndex(const char*);
	Double_t GetSessionStartRunTime() {
		return dSessionStartRunTime;
	}
	;

	void MakeDetectorTab1();
	void MakeDetectorTab2();
	void MakeDetectorTab3();
	void MakeDetectorTab4();
	void MakeUserTab();
	void MakeLogTab();
	void MakeMainTab();
	void MakeMenuLayout();
	//Int_t               MakeMonitors();
	void MakeMonitorTab();
	void MakeReport();
	//Int_t                   MakeSpinFlipper();
	void MakeSpinFlipperTab();
	void MakeUtilityLayout();

	Int_t OpenLogFile(ERFileStatus status = FS_OLD, const char* file = NULL);

	virtual Bool_t ProcessMessage(Long_t msg, Long_t parm1, Long_t);
	void RemoveDetectorTab1();
	void RemoveDetectorTab2();
	void RemoveDetectorTab3();
	void RemoveDetectorTab4();
	void RemoveUserTab();
	void RemoveLogTab();
	void RemoveMonitorTab();
	void RemoveSpinFlipperTab();

	void SetLogFileName(const char *name) {
		strcpy(dLogfilename, name);
	}
	;
	void SetLogFileOpen(Bool_t open = kFalse) {
		dLogFileOpen = open;
	}
	;
	void SetSelectedPath(const char *name) {
		strcpy(dPath, name);
	}
	;

	void SetSessionStartRunTime(Double_t time) {
		dSessionStartRunTime = time;
	}
	;

	TCanvas *SplitCanvas(TRootEmbeddedCanvas *, int, int, const char*);

	Bool_t TabActive(const char *);  //YES
	Bool_t TabOpen(const char *);

	Int_t WriteLogData(const char*);
	//Int_t                 WriteUserOptions();

public:
	n3HeMain(const TGWindow *p, ClineArgs clargs, UInt_t w, UInt_t h);
	virtual ~n3HeMain();
	//----------------------------------

	virtual void CloseWindow();
	void DoSetLabel();
	Char_t *GetDate();

	Double_t GetMPOffset() {
		return dMPOffset;
	}
	;
	Double_t GetTBinWidth() {
		return dTBinWidth;
	}
	;
	Int_t GetRunNumber() {
		return runNumber;
	}
	;
	Char_t *GetTime();

	void LogClosed();
	void LogOpened();
	void LogSaved();
	void LogSavedAs();

	void OpenRun();
	void OpenNextRun();
	void OpenBrowser();
	void PlotDetectorData1(ERPlotTypes type, ENDataType dtype, Int_t);
	void PlotDetectorData2(ERPlotTypes type, ENDataType dtype, Int_t);
	void PlotDetectorData3(ERPlotTypes type, ENDataType dtype, Int_t);
	void PlotDetectorData4(ERPlotTypes type, ENDataType dtype, Int_t);
	void PlotMainData(ERPlotTypes type, Int_t);
	void PlotMonitorData(ERPlotTypes type, Int_t);
	void PlotSpinFlipperData(ERPlotTypes type, ENDataType dtype, Int_t);
	void SetRunNumber(Int_t rn) {
		runNumber = rn;
	}
	;
	void PadIsPicked(TPad* selpad, TObject* selected, Int_t event);

	void WritePid();

	ClassDef(n3HeMain,0);
};

#endif

