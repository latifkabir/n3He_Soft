//Header for the program to take the data
//Author: Latiful Kabir
//Date:08.15.14
//Version:1.0

#include"Constants.h"

// Read last run number and generate run number for current run
void RunList();
//Rename all the data files (just taken) adding the run number
void Rename(int run,int module);
//Routine to run a single DAQ module only
void RunSingle(int module=MODULE,int runlength=RUN_LENGTH,int runNumber=RUN_NUMBER);
//Running all the DAQ module
void RunAll (int runlength=RUN_LENGTH,int runNumber=RUN_NUMBER);
