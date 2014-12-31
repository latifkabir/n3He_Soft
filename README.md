Software for the n3He Experiment
================================== 
This is the official reporitory for any developed software for the [n3He experiment at SNS][1].
This repository is divided into several sub directories based on the category:
* n3HeDAQ[(download)][2] --- Contains software for the n3He DAQ Control.
* Library[(download)][3] --- Contains the analysis library for the n3He experiment.
* n3HeDataBrowser[(download)][4] --- The GUI for Online analysis. GUI to browse the data for each run easily.
* n3HeMag[(download)][5] ---Contains 'driver for FluxGate' in C++ source code 
* n3HeScan[(download)][6] --- Software for field and beam scan 
* DAQFirmware[(download)][7] --- This directory contain DAQ Firmware related Software update.
* DemoScripts[(download)][8] --- Contains demo analysis or other demo scripts necessary for DAQ performance demonstration & testing.

Please read below to know what's inside each category.
The above download link will download the last release for each category. For the most recent changes or to participate in the development 
you might want to download/clone the entire project from the left. 
In any case please read the README file in the corresponding section first.

n3HeDAQ
-------
Contains
   * The DAQ control program using command line.
   * The DAQ GUI control program.

![](https://raw.githubusercontent.com/latifkabir/n3He_Soft/master/n3HeDAQ/n3HeDAQ_demo.png "n3HeDAQ Control Program")


Library
-------
Contains
   * libn3He : Root friendly Library for the n3He Experiment.
   * TBranchBinary : A prototype example Root friendly analysis library.
   * ReadBinary : An independent analysis library.
   

n3HeDataBrowser
----------------
   * The GUI for Online analysis. GUI to browse the data for each run easily.

![](https://raw.githubusercontent.com/latifkabir/n3He_Soft/master/n3HeDataBrowser/n3HeData/demo_n3HeDataBrowser.png "n3He Data Browser")


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


Last Updated on 12/30/14

-Latiful Kabir

[1]: http://n3he.wikispaces.com
[2]:http://raw.githubusercontent.com/latifkabir/n3HeReleases/master/n3HeDAQ.zip 
[3]:http://raw.githubusercontent.com/latifkabir/n3HeReleases/master/Library.zip
[4]:http://raw.githubusercontent.com/latifkabir/n3HeReleases/master/n3HeDataBrowser.zip
[5]:http://raw.githubusercontent.com/latifkabir/n3HeReleases/master/n3HeMag.zip
[6]:http://raw.githubusercontent.com/latifkabir/n3HeReleases/master/n3HeScan.zip
[7]:http://raw.githubusercontent.com/latifkabir/n3HeReleases/master/DAQFirmware.zip
[8]:http://raw.githubusercontent.com/latifkabir/n3HeReleases/master/DemoScripts.zip

