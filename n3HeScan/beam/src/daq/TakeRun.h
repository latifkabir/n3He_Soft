//Header for the program to take the data
//Author: Latiful Kabir
//Date:08.15.14
//Version:1.0


// Read last run number and generate run number for current run
void RunList();
//Rename all the data files (just taken) adding the run number
void Rename(int run,int module);
//Routine to run a single DAQ module only
void RunSingle(int module=21,int runlength=100000000,int runNumber=0);
//Running all the DAQ module
void RunAll (int runlength=100000000,int runNumber=0);
