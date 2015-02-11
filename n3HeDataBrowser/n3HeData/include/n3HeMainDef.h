///////////////////////////////////////////////////////////////////////////////
//n3He Experiment Data Visualization and Analysis
//
//Version 2.01
//
//Definitions file, containing all common constants
///////////////////////////////////////////////////////////////////////////////

#ifndef n3HeMAINDEF_H
#define n3HeMAINDEF_H

/* #define n3He_DEBUG */

#ifndef Pi
#define Pi                    3.14159265359
#endif

#define NUM_MON 3 //the number of monitors

enum ERFileTypes {
	FT_TEXT = 300,                     //File is ASCII text
	FT_BINARY,                               //FIle is binary
	FT_ROWCOLUMN,                            //File is ASCII text arranged
											 //in rows and columns
	FT_ROOT,                                 //File is a ROOT object file
											 //(*.root)
	FT_MATHCAD
};

enum ERFileModes {
	FM_READ = 500,                     //File is opened for reading
	FM_WRITE,                                //FIle is opened for writing
	FM_UPDATE                                //File is opened for updating
};

enum ERRDCMessageTypes {
	kC_CONT_OBJECT = 700,
	kCM_CONT_MSG,
	M_CONT_CLOSED,
	M_CONT_LOGTXTTS,
	M_CONT_ERROR_MSG
};

#ifndef kTrue
#define kTrue                 1
#endif
#ifndef kFalse
#define kFalse                0
#endif

#ifndef NAME_STR_MAX
#define NAME_STR_MAX          200          //Maximum file name length
#endif

enum ERPlotTypes {
	PT_HISTO_1D = 900,     //Make a 1D histogram from the data
	PT_HISTO_2D,                 //Make a 2D histogram from the data
	PT_HISTO_3D,                 //Make a 3D histogram from the data
	PT_GRAPH,                    //Make a 1D graph from the data
	PT_GRAPH_ER,                 //Make a 1D graph with errorbars from the data
	PT_GRAPH_ASYMER,             //Make a 1D graph with asymetric errorbars 
								 //from the data
	PT_MULTIGRAPH                //Make a 1D multigraph from the data
};

enum RDWCommandId {

	M_PLOT_SAVEPS = 1100,
	M_PLOT_SAVERT,
	M_PLOT_SAVESETUP,
	M_PLOT_FITSETUP,
	M_PLOT_ATTR,
	M_PLOT_ADD,
	M_PLOT_CLOSE,
	M_PLOT_PRINT,
	M_PLOT_OPEN,
	M_PLOT_ADDLEGEND,
	M_PLOT_WRITEMISC,
	M_PLOT_READMISC,
	M_PLOT_INTEG,
	M_PLOT_DIVIDE,
	M_PLOT_SCALE,
	M_PLOT_NORM,
	M_PLOT_VIEWROOTOBJ,
	M_PLOT_EDITOR,

	M_DTWIND_CLOSED,
	M_DTWIND_LOGTXTTS,
	M_DTWIND_ERROR_MSG
};

#define TARGET "Cl"

#ifndef MSG_QUEUE_MAX
#define MSG_QUEUE_MAX         10           //Maximum entries per message
#endif                                     //queue
#ifndef MSG_SIZE_MAX
#define MSG_SIZE_MAX          1000         //Maximum size of each message
#endif
#ifndef NAME_STR_MAX
#define NAME_STR_MAX          200          //Maximum file name length
#endif

//Define the allowed time difference between corresponding macropulses from
//the 3 VME crates
//Also Define the same for consecutive macro pulses in the same VME file
//**************************************************************************
#define VME_TIME_DIFF_MAX                 1000 //In microseconds
#define PULSE_TIME_DIFF_MAX              60000 //In microseconds
#define PULSE_TIME_DIFF_MIN              40000 //In microseconds
//**************************************************************************

#define ANL_MAX_OBJ_CNT                  10000 //Maximum number of obj used in 
//Analysis
#define ADC_CONV_FACTOR                 3276.8 //ADC sample unit conversion factor
//(counts per Volt)
#define AMPL_NOISE                     1.9e-14 //amps per sqrt(Hz) from amplifier
#define MAIN_GAIN                         50e6 //First amp stage gain (Ohms)
#define SAMPL_FAC                          0.6 //from bessel filtering (see lab book)
#define SAMPL_BW                          4200 //Bandwidth (Hz) set by the Sum-Diff Amps 
#define DAQ_SDFAC                            1 //Summing and Differencing
//noise enhancement factor
#define COSMIC_DEP_MEV                      85 //Energy deposited in a detector
//by a single cosmic traversing
//the entire detector length (MeV)
#define e_CHARGE                1.60217733e-19 //electron charge in Coulombs
#define v_LIGHT                 2.99792458e8   //speed of light in m/s
#define n_MASS                  939.56533e6    //neutron mass in eV/c^2             
#ifndef kTrue
#define kTrue                             1
#endif
#ifndef kFalse
#define kFalse                            0
#endif

#ifndef MP_SAMPLE_WINDOW
#define MP_SAMPLE_WINDOW               40.0   //Size of the sampling window in ms 
#endif

#define N_AVOG                    6.0221367e23

#define FIGFILEMAX                 50 //Maximum number of figures per log file
#define ERR_RET_VAL                400000000 

#define DATA_CONFIG            "n3HeData.conf"
#define DATA_DIR               "/data07"

#define QUEUE_GRPUFLOW_ERROR   "ERROR: Trying to read beyond end of file.\n"
#define FILE_RANGE_ERROR       "ERROR: Invalid macro pulse range selected.\n"
#define ANL_ALLOC_ERROR        "ERROR: Unable to allocate memory for analysis\n"
#define ANL_BINNING_ERROR      "ERROR: Unable to auto establish binning of histos\n"

//Error Messages
#ifndef PROCESS_OK
#define PROCESS_OK                            1013
#endif
#ifndef PROCESS_FAILED
#define PROCESS_FAILED                        1014
#endif
#define PROCESS_CANCELED                      1015
#define MEMORY_ALLOC_ERROR                    1016
#ifndef LOG_PROCESS_ERROR
#define LOG_PROCESS_ERROR                     1017
#endif
#ifndef LOG_PROCESS_OK
#define LOG_PROCESS_OK                        1018
#endif

#define kC_PR_DIALOG                   1500
#define kCM_PR_MSG                      150
#define kC_PLO_DIALOG                  1060
#define kCM_PLO_MSG                     106
#define kC_MATH_DIALOG                 1400
#define kCM_MATH_MSG                    140
#define kC_ANL_ENT_DIALOG              1100
#define kCM_ANL_ENT_MSG                 110

enum CommandIdentifiers {

	M_HP_LOGTXTTS,
	M_HP_LOGTXTNS,
	M_HP_CLOSED,
	M_DC_LOGTXTTS,
	M_DC_LOGTXTNS,
	M_DC_CLOSED,
	M_HS_LOGTXTTS,
	M_HS_LOGTXTNS,
	M_HS_CLOSED,
	M_PL_LOGTXTTS,
	M_PL_LOGTXTNS,
	M_PLO_CLOSED,
	M_MATH_LOGTXTTS,
	M_MATH_LOGTXTNS,
	M_MATH_ERROR_MSG,

	M_HPE_LOGTXTTS,
	M_HPE_LOGTXTNS,
	M_HPE_CLOSED,
	M_HSE_LOGTXTTS,
	M_HSE_LOGTXTNS,
	M_HSE_CLOSED,
	M_PLE_LOGTXTTS,
	M_PLE_LOGTXTNS,
	M_PLE_CLOSED,
	M_CALC_SFL_EFF,
	M_SET_SFL_EFF_PARMS,

	M_ANLE_CLOSE,
	M_ANLE_CLOSED,
	M_TOF_DEFAULTS,
	M_PR_SEQ,
	M_PR_RUN,
	M_PR_CLOSED,
	M_PR_CLOSE,
	M_PR_STOP,
	M_PR_PAUSE,
	M_PR_RESUME,

	M_CSDE_CLOSE,
	M_CSDE_CLOSED,

	M_PATH_SELECT,
	M_RUN_OPEN,
	M_FILE_SAVE,
	M_FILE_SAVEAS,
	M_FILE_PRINT,
	M_FILE_PRINTSETUP,
	M_FILE_EXIT,
	M_FILE_CLOSE,
	M_FILE_ANALYZE,
	M_FILE_NOISESTAT,
	M_FILE_ASYMSTAT,

	M_USER_OPTIONS,
	M_VIEW_BROWSER,
	M_VIEW_CHP,
	M_VIEW_DET_DATA,
	M_VIEW_DET_HIST,
	M_VIEW_DET_WAVE,
	M_VIEW_SUM_HIST,
	M_VIEW_SUM_WAVE,
	M_VIEW_DIFF_HIST,
	M_VIEW_DIFF_WAVE,
	M_VIEW_LOG,
	M_VIEW_MON_DATA,
	M_VIEW_MON_HIST,
	M_VIEW_MON_WAVE,
	M_VIEW_SFL_DATA,
	M_VIEW_SFL_HIST,
	M_VIEW_SFL_WAVE,
	M_VIEW_TUN_HIST,
	M_VIEW_USER,

	M_SET_CONFIG,
	M_SET_MOD,
	M_RESET_GEOM_VIEW,
	M_CALC_DETCROSS,
	M_VIEW_GEOMETRY,
	M_ANL_ASYM,
	M_GEN_PEDS,
	M_GEN_BGRND,
	M_GEN_UPR,
	M_GEN_UPR2,
	M_GEN_UPR3,

	M_PLOT_DET_DATA,
	M_PLOT_DIF_DATA,
	M_PLOT_SUM_DATA,
	M_HIST_DET_DATA,
	M_HIST_DIF_DATA,
	M_HIST_SUM_DATA,
	M_COMB_PH_DATA,
	M_ANL_OUTPUT,

	M_HISTO_SAVE,
	M_HISTO_SAVESETUP,

	M_HISTO_CLOSE,
	M_HISTO_ENTRY_SET,
	M_HISTO_ENTRY_CANCEL,

	M_HISTOPLOT_SAVE,
	M_HISTOPLOT_SAVESETUP,

	M_HISTOPLOT_CLOSE,
	M_HISTOPLOT_ENTRY_SET,
	M_HISTOPLOT_ENTRY_CANCEL,

	M_ANALYZE_CLOSE,
	M_ANALYZE_ENTRY_SET,
	M_ANALYZE_ENTRY_CANCEL,
	M_SETTING_ENTRY_SET,
	M_SETTING_ENTRY_CANCEL,
	M_ANALYZE_ALL_MPS,
	M_AUTO_BIN,
	M_SUB_PED,
	M_SUB_BGR,

	M_DATAVIEW_ENTRY_SET,
	M_DATAVIEW_ENTRY_CANCEL,

	M_FIT_CLOSE,
	M_FIT_ENTRY_SET,
	M_FIT_ENTRY_CANCEL,
	M_FIT_FULLRANGE,
	M_FIT_SELFUNC,
	M_FITE_CLOSE,
	M_FITE_CLOSED,

	M_HELP_CONTENTS,
	M_HELP_SEARCH,
	M_HELP_ABOUT,

	VId1,
	HId1,
	VId2,
	HId2,

	VSId1,
	HSId1,
	VSId2,
	HSId2,
	ColorSel
};

enum ENDetOrientation {
	DOR_UP, DOR_DOWN, DOR_LEFT, DOR_RIGHT,
};

enum ENDetOpMode {
	DOM_DATA, DOM_SIM,
};

enum ERFileStatus {
	FS_NEW, FS_OLD,
};

enum ENDataType {
	DDT_DETECTORS,
	DDT_DIFFERENCE,
	DDT_SUM,
	DDT_MONITOR,
	DDT_MONITOR_RATIO,
	DDT_SFLIPPER,
	DDT_SFLIPPER_VOLT,
	DDT_SFLIPPER_CURR,
	DDT_SFLEFFIC,
};

enum ENMsgType {
	MT_START, MT_END, MT_HALT,
};

enum ENAnalysisType {
	AT_CALCNOISESTAT,
	AT_CALCNOISEASYM,
	AT_CALCUDASYM,
	AT_CALCLRASYM,
	AT_CALCRAWASYM,
	AT_CALCCOSMICSTAT,
	AT_CALCCOSMICGAIN,
	AT_CALCCOSMICDIST,
	AT_CALCCNTSTATS,
	AT_DATARAWGEN,
	AT_CALCPEDFLUC,
	AT_DETGAINASYM,
	AT_MISC,
	AT_NONE,
};

struct AnalyzeOptions {

	int kSilentMode;
	int kWriteData;
	int kUDAsym;
	int kLRAsym;
	int kRawAsym;
	int kNseAsym;
	int kDetElecNoise;
	int kDetGainCosmics;
	int kPedFluc;
	int kCntStats;
	int kRFSFEff;
	int NumRuns;
	int BinStart;
	int BinStop;
	int kSubPeds;
	int kSubBackgr;
	int kRunFile;
	int kPedFile;
	double CosmicLevDef;
	double GammaEnergy;
	char Runs[MSG_SIZE_MAX];
	char dRunListFile[MSG_SIZE_MAX];
	char dPedListFile[MSG_SIZE_MAX];
	char dProjectName[MSG_SIZE_MAX];
	char dEffXvals[MSG_SIZE_MAX];
};

struct DefaultSettings {

	int KeepTOFOffset;
	int KeepChopCutStart;
	int KeepChopCutStop;
	int KeepPedWindStart;
	int KeepPedWindStop;
	double TOFOffset;     //from T0 in ms
	double ChopCutStart;  //from TOFOffset in ms
	double PedWindStart;  //from TOFOffset in ms
	double PedWindStop;	//from TOFOffset in ms

};

struct ClineArgs {

	int bckgr;
	int mute;
	ENAnalysisType mode;
	AnalyzeOptions opts;
	char file[1000];

};

struct DataViewOptions {

	int VME3;
	int sum;
	int diff;
	int det;
	int pattern;
};

const double DetGainStageTwo[48] = { 2.67,/* 2.15 */2.39, 2.21, 2.37,/* 2.21 */
		2.45, 2.10, 2.05,/* 2.21 */2.45, 1.74, 1.78,/* 2.21 */2.45, 1.78, 2.05,/* 2.80 */
		3.11, 2.32, 2.26,/* 1.78 */1.98, 2.00, 2.10,/* 1.69 */1.88, 2.26, 2.05,/* 2.43 */
		2.70, 2.15, 1.78,/* 2.26 */2.51, 1.65, 1.74,/* 1.69 */1.88, 1.91, 2.10,/* 2.00 */
		2.22, 2.26, 1.91,/* 2.43 */2.70, 1.65, 2.05,/* 2.80 */3.11, 2.55, 2.26,/* 2.00 */
		2.22, 2.21, 2.10,/* 2.55 */2.83, 2.32, 2.05,/* 2.00 */2.22, 1.91, };

const double DetEfficiency[48] = { 1462.8, 1415.0, 1279.1, 1354.0, 1358.1,
		1370.6, 1133.8, 1462.2, 1233.1, 1242.2, 1347.7, 1138.2, 1353.6, 1478.2,
		1391.7, 1066.7, 1121.1, 1276.7, 1016.2, 1313.0, 1249.2, 1383.3, 1471.5,
		1306.2, 1094.6, 1252.3, 1036.2, 1119.7, 1245.5, 1286.1, 1323.1, 1374.8,
		1434.4, 1147.0, 1476.4, 1141.2, 1385.6, 1510.0, 1447.4, 1362.8, 1264.5,
		1284.1, 1234.7, 1463.1, 1004.8, 1432.0, 1188.2, 1280.4, };

const int SpinState[16] = { 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, };

/* struct  TofGFactor { */
/*   Double_t CosNum[100]; */
/*   Double_t CosDen[100]; */
/*   Double_t AvgCos[100]; */
/*   Double_t RayCnt[100]; */
/* }; */

const double AlDistAttenuation[100] = { 0.032, 0.033, 0.035, 0.036, 0.037,
		0.037, 0.037, 0.037, 0.037, 0.038, 0.039, 0.039, 0.040, 0.050, 0.050,
		0.050, 0.050, 0.050, 0.051, 0.052, 0.053, 0.053, 0.053, 0.053, 0.053,
		0.054, 0.054, 0.055, 0.055, 0.056, 0.056, 0.056, 0.056, 0.057, 0.058,
		0.058, 0.058, 0.059, 0.059, 0.059, 0.059, 0.060, 0.060, 0.060, 0.060,
		0.061, 0.061, 0.061, 0.062, 0.062, 0.062, 0.063, 0.063, 0.063, 0.063,
		0.063, 0.064, 0.064, 0.064, 0.065, 0.066, 0.066, 0.066, 0.066, 0.067,
		0.067, 0.068, 0.068, 0.068, 0.070, 0.070, 0.070, 0.071, 0.072, 0.072,
		0.073, 0.073, 0.073, 0.073, 0.074, 0.075, 0.075, 0.076, 0.077, 0.077,
		0.078, 0.078, 0.079, 0.079, 0.079, 0.080, 0.080, 0.081, 0.081, 0.082,
		0.082, 0.082, 0.083, 0.083, 0.083, };

const double ClDistAttenuation[100] = { 1.642e-01, 2.579e-01, 3.054e-01,
		3.478e-01, 3.824e-01, 4.201e-01, 4.574e-01, 4.909e-01, 5.260e-01,
		5.685e-01, 6.056e-01, 6.343e-01, 6.686e-01, 7.021e-01, 7.402e-01,
		7.750e-01, 8.104e-01, 8.390e-01, 8.697e-01, 9.034e-01, 9.361e-01,
		9.640e-01, 9.991e-01, 1.039e+00, 1.069e+00, 1.102e+00, 1.143e+00,
		1.167e+00, 1.217e+00, 1.247e+00, 1.280e+00, 1.316e+00, 1.353e+00,
		1.398e+00, 1.444e+00, 1.493e+00, 1.493e+00, 1.551e+00, 1.551e+00,
		1.617e+00, 1.658e+00, 1.689e+00, 1.722e+00, 1.760e+00, 1.795e+00,
		1.837e+00, 1.872e+00, 1.906e+00, 1.941e+00, 1.972e+00, 2.015e+00,
		2.046e+00, 2.075e+00, 2.104e+00, 2.141e+00, 2.177e+00, 2.213e+00,
		2.257e+00, 2.277e+00, 2.323e+00, 2.349e+00, 2.402e+00, 2.429e+00,
		2.454e+00, 2.483e+00, 2.546e+00, 2.576e+00, 2.609e+00, 2.643e+00,
		2.678e+00, 2.719e+00, 2.719e+00, 2.762e+00, 2.802e+00, 2.844e+00,
		2.885e+00, 2.885e+00, 2.935e+00, 2.988e+00, 2.988e+00, 3.043e+00,
		3.043e+00, 3.108e+00, 3.170e+00, 3.170e+00, 3.235e+00, 3.235e+00,
		3.311e+00, 3.311e+00, 3.311e+00, 3.385e+00, 3.385e+00, 3.473e+00,
		3.473e+00, 3.566e+00, 3.566e+00, 3.566e+00, 3.659e+00, 3.659e+00,
		3.659e+00, };

const double ClDepolFac[40] = { 0.9722, 0.9618, 0.9534, 0.9476, 0.9412, 0.9360,
		0.9317, 0.9276, 0.9247, 0.9197, 0.9173, 0.9144, 0.9111, 0.9089, 0.9057,
		0.9038, 0.9014, 0.8995, 0.8967, 0.8946, 0.8929, 0.8901, 0.8889, 0.8870,
		0.8860, 0.8840, 0.8832, 0.8820, 0.8795, 0.8778, 0.8769, 0.8754, 0.8740,
		0.8725, 0.8717, 0.8703, 0.8693, 0.8683, 0.8683, 0.865, };

const double H2DepolFac[40] = { 0.9722, 0.9618, 0.9534, 0.9476, 0.9412, 0.9360,
		0.9317, 0.9276, 0.9247, 0.9197, 0.9173, 0.9144, 0.9111, 0.9089, 0.9057,
		0.9038, 0.9014, 0.8995, 0.8967, 0.8946, 0.8929, 0.8901, 0.8889, 0.8870,
		0.8860, 0.8840, 0.8832, 0.8820, 0.8795, 0.8778, 0.8769, 0.8754, 0.8740,
		0.8725, 0.8717, 0.8703, 0.8693, 0.8683, 0.8683, 0.865, };

#endif
