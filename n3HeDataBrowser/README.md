      ======================================================================================================
                                    Data Browser for the n3He Experiment
      ======================================================================================================
1. bin directory: contains just binary files(obtained after doing make) named n3HeData.

2. libn3He directory: Contains all the library required for running the Data check GUI and Target GUI.

3. To produce a new binary file named "n3HeData", go to n3HeData directory, open makefile and change LIB_INCLUDE and GLIBS to
appropriate location for you and then do "make". It will produce "n3HeData" binary file in the same dirctory. 

4. Now before you run this binary do the following:
Open */libn3He/bin/thisn3He.sh and define "n3HeROOT" path variable to the location where "libn3He" is located.
for example: n3HeROOT=/home/siplu/libn3He/

5. Now include command in your .bashrc file to run thisn3He.sh file each time you open the terminal. i.e. include the fillowing lines:
```if [ -f $HOME/libn3He/bin/thisn3He.sh ]; then
	. $HOME/libn3He/bin/thisn3He.sh
fi```

Or, if you want to do it for the current session only, you can just copy and paste the lines in "thisn3He.sh" file in 
your terminal.

6. Before you do 'make' do: "make clean" in the same directory. 

7. You need to change the Data file directory from TTRaw in libn3He to appropriate directory. You need to clean and make a fresh binary files after you make any changes.

8. Now run the binary file"n3HeData" by doing "./n3HeData" from your recently compiled verson in */n3He_DAQ_GUI/n3HeData/ or using already previously compiled one from */n3He_DAQ_GUI/bin/ .

9. In order to get the data for checking, you need to run it from Basestar. Or Change the path for data file in TTreeRaw source code.

                                                                                  Last Updated on 12/25/14
                                                                                 -Latiful Kabir
