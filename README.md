Software for the n3He Experiment
================================== 
This is the official reporitory for any developed software for the [n3He experiment at SNS][1].
This repository is divided into several sub directories based on the category:
* n3HeDAQ v1.3 [(download)][2] --- Contains software for the n3He DAQ Control.
* Library v1.3 [(download)][3] --- Contains the analysis library for the n3He experiment.
* n3HeDataBrowser v1.2 [(download)][4] --- The GUI for online analysis.GUI to browse the data for each run easily.
* n3HeMag v1.0 [(download)][5] ---Contains 'driver for FluxGate' in C++ source code 
* n3HeScan v1.0 [(download)][6] --- Software for field and beam scan 
* DAQFirmware v1.0 [(download)][7] --- This directory contain DAQ Firmware related Software update.
* DemoScripts v1.0 [(download)][8] --- Contains demo analysis or other demo scripts necessary for DAQ performance demonstration & testing.
* ReadRS232 v1.0 [(download)][9] -- GUI for monitoring magnetic field and Temperature on a ncurses window through RS232.
* Watchdog  v1.0 [(download)][10]-- Program for 24/7 DAQ status and other critical parameters watchdog.
* Diagnosis v1.2 [(download)][11] --- The DAQ's healthcare companion Baymax with automated diagnosis and healing capability. 
* Manual v1.5 --- DAQ Operational Manual [(download)][12] and n3He Analysis Startup Guide [(download)][13]
* Analysis Contributors' Repo --- Source code repository by the n3He analysis contributors (check end of this page).


[Release Notes][14]

Please continue reading to know details of each section.
The download links will download the last release for each category. For the most recent changes or to participate in the development you might want to download/clone the entire project from the right.   
Alternatively, to clone using a terminal use, from Github repo :`` git clone https://github.com/latifkabir/n3He_Soft.git `` 
Or from ASU repo : `` git clone n3he@alarcondaq.la.asu.edu:/mnt/sharedSource/N3HE.git ``   
In any case please read the README file in the corresponding section first.  

n3HeDAQ v1.2 [(download)][2]
------------------------
Contains
   * The DAQ control program using command line.
   * The DAQ GUI control program.

* n3HeDAQ GUI Control Program Screenshot:
![](https://raw.githubusercontent.com/latifkabir/n3He_Soft/master/n3HeDAQ/n3HeDAQ_demo.png "n3HeDAQ GUI Control Program")

* n3HeDAQ Control Program in commandline Screenshot:
![](https://raw.githubusercontent.com/latifkabir/n3He_Soft/master/n3HeDAQ/n3HeDAQ_commandline.png "n3HeDAQ Control Program in commandline")


Library v1.2 [(download)][3]
------------------------
Contains
   * libn3He : Root friendly Library for the n3He Experiment.
   * TBranchBinary : A prototype example Root friendly analysis library.
   * ReadBinary : An independent analysis library.
   

n3HeDataBrowser v1.0 [(download)][4]
-------------------------------
   * The GUI for Online analysis. GUI to browse the data for each run easily.

![](https://raw.githubusercontent.com/latifkabir/n3He_Soft/master/n3HeDataBrowser/n3HeData/demo_n3HeDataBrowser.png "n3He Data Browser")


n3HeMag v1.0 [(download)][5]
-------------------------
 Driver for FluxGate in C++ source code. 


n3HeScan v1.0 [(download)][6]
--------------------------
  * field : Software for magnetic field scan
  * beam : Software for beam scan

DAQFirmware v1.0 [(download)][7]
----------------------------
This directory contains DAQ Firmware related Software update.

DemoScripts v1.0 [(download)][8]
----------------------------
Contains analysis or other demo scripts necessary for DAQ performance demonstration & testing.

ReadRS232 v1.0 [(download)][9]
---------
GUI for monitoring magnetic field and Temperature on a ncurses window through RS232.

![](https://raw.githubusercontent.com/latifkabir/n3He_Soft/master/ReadRS232/Mag&Temp/magTemp.png "Field & Temperature Display")

Watchdog v1.0 [(download)][10]
----------
Program for 24/7 DAQ status and other critical parameters watchdog. Capable to send text alert and restart the DAQ program automatically.

Diagnosis v1.0 [(download)][11]
----------
The DAQ's healthcare companion Baymax with automated diagnosis and healing capability. 

Manual v1.0 
------------
DAQ Operational Manual [(download)][12] and n3He Analysis Startup Guide [(download)][13]


Analysis Contributors' Repo 
----------------------------
Following are source code repositories by the n3He analysis contributors :

Kabir's Analysis (ROOT based) Repo :

Kabir's personal n3He Analysis Tools based on ROOT can be found [here][16]

MTSU Analysis (Python based) Repo :

Middle Tennessee State University contributors (Led by Rob), starting from scratch, developed a pristine Python based analysis library.
It can be cloned using (assuming you have access to basestar):
``git clone basestar:~mahurin/n3he_rootpy.git``
 


report bug to: latifulkabir@uky.edu

Last Updated on 2/04/16

-Latiful Kabir

[1]: http://n3he.wikispaces.com
[2]:http://raw.githubusercontent.com/latifkabir/n3HeReleases/master/n3HeDAQ.zip 
[3]:http://raw.githubusercontent.com/latifkabir/n3HeReleases/master/Library.zip
[4]:http://raw.githubusercontent.com/latifkabir/n3HeReleases/master/n3HeDataBrowser.zip
[5]:http://raw.githubusercontent.com/latifkabir/n3HeReleases/master/n3HeMag.zip
[6]:http://raw.githubusercontent.com/latifkabir/n3HeReleases/master/n3HeScan.zip
[7]:http://raw.githubusercontent.com/latifkabir/n3HeReleases/master/DAQFirmware.zip
[8]:http://raw.githubusercontent.com/latifkabir/n3HeReleases/master/DemoScripts.zip
[9]:http://raw.githubusercontent.com/latifkabir/n3HeReleases/master/ReadRS232.zip
[10]:http://raw.githubusercontent.com/latifkabir/n3HeReleases/master/Watchdog.zip
[11]:http://raw.githubusercontent.com/latifkabir/n3HeReleases/master/Diagnosis.zip
[12]:https://github.com/latifkabir/n3He_Soft/raw/master/Manual/DAQManual.pdf
[13]:https://github.com/latifkabir/n3He_Soft/raw/master/Manual/AnalysisGuide.pdf
[14]:http://raw.githubusercontent.com/latifkabir/n3HeReleases/master/ReleaseNotes
[15]:https://raw.githubusercontent.com/latifkabir/n3He_Soft/master/n3HeDAQ/n3HeDAQ_commandline.png
[16]:https://github.com/latifkabir/n3HeAnalysisTool

	 
