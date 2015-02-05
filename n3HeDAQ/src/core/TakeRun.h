//Header for the program to take the data in command line mode
//Author: Latiful Kabir
//Date:08.15.14
//Version:1.0

#include"Constants.h"

// Read last run number and generate run number for current run
void RunList(bool gui_mode);
//Rename all the data files (just taken) adding the run number
int Rename(int run,int module,bool gui_mode);
//Enable or Disable the trigger
int Sync(bool status,bool gui_mode);
//Routine to run a single DAQ module only
void RunSingle(int module=MODULE,int runlength=RUN_LENGTH,int runNumber=RUN_NUMBER);
//Running all the DAQ module
void RunAll (int runlength=RUN_LENGTH,int runNumber=RUN_NUMBER);
//Handle Ctrl+C Signal
void signalHandler( int signum );
//Process Dirty DAQ data from previous run while taking current run
int ProcessDirty(int count);
