Software for the n3He Experiment
================================== 
This is the official reporitory for any developed software for the [n3He experiment at SNS][1].
This repository is divided into several sub directories based on the category:
* n3HeDAQ --- Contains software for the n3He DAQ.
* Library --- Contains the analysis library for the n3He experiment.
* n3HeDataBrowser --- The GUI for Online analysis. GUI to browse the data for each run easily.
* n3HeMag ---Contains 'driver for FluxGate' in C++ source code 
* n3HeScan --- Software for field and beam scan 
* DAQFirmware --- This directory contain DAQ Firmware related Software update.
* DemoScripts --- Contains demo analysis or other demo scripts necessary for DAQ performance demonstration & testing.

n3HeDAQ
-------
Contains
   * The DAQ control program using command line.
   * The DAQ GUI control program.

Library
-------
Contains
   * libn3He : Root friendly Library for the n3He Experiment.
   * TBranchBinary : A prototype Root friendly analysis library.
   * ReadBinary : An independent analysis library.
   

n3HeDataBrowser
----------------
   * The GUI for Online analysis. GUI to browse the data for each run easily.

n3HeMag
--------
 Driver for FluxGate in C++ source code. 


n3HeScan
---------
  * field : Software for magnetic field scan
  * beam : Software for beam scan

DAQFirmware
----------
This directory contains DAQ Firmware related Software update.

DemoScripts
-----------
Contains analysis or other demo scripts necessary for DAQ performance demonstration & testing.

In any case please read the REAME file in the corresponding section first.

Last Updated on 12/30/14

-Latiful Kabir

[1]: http://n3he.wikispaces.com
