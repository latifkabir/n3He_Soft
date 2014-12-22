TBranchBinary
=============

TBranchBinary is a new class developed by Christopher Crawford (now prof of Physics at Univ of Kentucky)

   * Allows one to interpret binary files as ntuples without actually reading them into an ntuple.
   * Gives access to all features of TTree.
   * Access to any ROOT classes.

This library is used extensively in the data analysis for [NPDGamma][1] experiment and [n3He][2] experiment at SNS. 

What's included
---------------

This directory directory contains TBranchBinary library with make file, sample data file and sample analysis.
The included files are:
 * In Library: The TBranchBinary library with make file.
 * In Analysis: A macro to plot the data (data_plot.C)
 * In Data: A small data file produced by our ADC (with sinusoidal(1volt, 60 Hz) applied on channel-1, ADC running at 10KHz sample rate ) (file name "000")
 * In Sample_output: Some output files how you will see if you can run the macro (data_plot.C) successfully.

Prerequisite
------------

You must have ROOT installed and configured in order to use this library.

Steps to be followed
--------------------

* To Compile:
From terminal , go to the extracted TBranchBinary Library directory where you have "makefile"
Then from terminal type"make"
This will create addition files(Dic and .o files) in */Library/src/libN3HE/ and the libN3HE.so file in */Library/lib .
Then libN3HE.so is the shared object file that will serve as your library.


* To load the library source the bin/thisN3HE.sh file before doing analysis 
(i.e. run `. /path/to/N3HE/bin/thisN3HE.sh`).  
It's convenient to put this source command into your ~/.bash_profile or ~/.bashrc file:

 
```
if [ -f /path/to/N3HE/bin/thisN3HE.sh ]; then 
        . /path/to/N3HE/bin/thisN3HE.sh
 fi 
```

In that case it would not matter which directory you are doing your analysis, You are free do the analysis from any directory as the library is loaded in the terminal itself.

* From a new terminal go to the analysis directory("TBranchBinary/Analysis").and issue the command:

 `root data_plot.C  -l`

* Three windows will pop-up giving the plot of the data in 000 file.
  1. One windows giving histogram plotted manually (i.e. filling histogram for each data point)
  2. One window giving the same histogram but this time using Ntuple/TTree .
  3. Another window giving 1D Ntuple plot of the data
  4. The terminal will also print the values for channel one of the ADC.

[1]:http://battlestar.phys.utk.edu/wiki/index.php/Main_Page
[2]:http://n3he.wikispaces.com

