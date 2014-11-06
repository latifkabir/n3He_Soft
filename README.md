Software for the n3He Experiment
================================== 
This is the official reporitory for any developed software for the [n3He experiment at SNS][1].
This repository is divided into several sub directories based on the category:
* n3HeDAQ --- Contains software for the n3He DAQ.
* libn3He --- Contains the analysis library for the n3He experiment.
* n3HeMag ---Contains 'driver for FluxGate' in C++ source code 
* n3HeScan --- Software for field and beam scan 
* DAQFirmware --- This directory contain DAQ Firmware related Software update.
* DemoScripts --- Contains demo analysis or other demo scripts necessary for DAQ performance demonstration & testing.

n3HeDAQ
-------
Contains
   * The DAQ control program using command line.
   * The DAQ GUI control program (Under development).

libn3He
-------
Contains
   * TBranchBinary : A Root friendly analysis library.
   * ReadBinary : An independent analysis library

n3HeMag
--------
 Driver for FluxGate in C++ source code. 


n3HeScan
---------
  * field : Software for magnetic field scan
  * beam : Software for beam scan

DAQFormware
----------
This directory contain DAQ Firmware related Software update.

DemoScripts
-----------
Contains analysis or other demo scripts necessary for DAQ performance demonstration & testing.

In any case please read the REAME file in the corresponding section first.

[1]: http://n3he.wikispaces.com
