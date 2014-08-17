//The program to Show Help Session
//Author: Latiful Kabir
//Date:08.15.14
//Version:1.0


#include"Help.h"

using namespace std;

//Default instruction
void DefaultIns()
{
    cout<<"\n ===================================================================";
    cout<<"\n ||          Welcome to n3He DAQ Control Program v1.0             ||";
    cout<<"\n ===================================================================";
    cout<<"\n                report bug to: latifulkabir@uky.edu";
    cout<<"\n";
    cout<<"\n";
    cout<<"           If you already know how to use then just go ahead           "<<endl;
    cout<<"               Otherwise from terminal do: n3he help                    "<<endl;
    cout<<"\n";
}

//The title 
void Title()
{
    cout<<"\n ===================================================================";
    cout<<"\n ||          Welcome to n3He DAQ Control Program v1.0             ||";
    cout<<"\n ===================================================================";
    cout<<"\n                report bug to: latifulkabir@uky.edu";
    cout<<"\n";
    cout<<"\n";
}

//The help session
void Instruction()
{
    
    cout<<"\n ===================================================================";
    cout<<"\n ||          Welcome to n3He DAQ Control Program v1.0             ||";
    cout<<"\n ===================================================================";
    cout<<"\n                      The Help Session";
    cout<<"\n                report bug to: latifulkabir@uky.edu";
    cout<<"\n";
    cout<<"\n From the terminal do the following:";
    cout<<"\n ";
    cout<<"\n n3he start :";
    cout<<"\n   This will start the data taking process for all the DAQ modules for the";
    cout<<"\n   default run length continuously.";
    cout<<"\n";
    cout<<"\n n3he start LENGTH RUN : ";
    cout<<"\n   Where, LENGTH = The length of each run, RUN= the number of runs to be taken,";
    cout<<"\n   in Megabyte. ";
    cout<<"\n   Note RUN and LENGTH must be integer.";
    cout<<"\n   This will take only 'RUN' number of runs of length 'LENGTH' Megabyte each for";
    cout<<"\n   all the DAQ modules.";
    cout<<"\n";
    cout<<"\n";
    cout<<"\n n3he daq MODULE :";
    cout<<"\n   Where, MODULE= The DAQ module you want to run. It acn be either 21,23,24,30.";
    cout<<"\n   This will take data only for the DAQ module number 'MODULE' in continuous mode";
    cout<<"\n   for the default run length.";
    cout<<"\n   If the module number is not specified it will take data only for module 21 by";
    cout<<"\n   default.";
    cout<<"\n";
    cout<<"\n n3he daq MODULE LENGTH RUN :";
    cout<<"\n   Where, RUN= the number of runs to be taken, LENGTH = The length of each run in";
    cout<<"\n          MODULE= The DAQ module you want to run. It can be either 21,23,24,30.";
    cout<<"\n          Megabyte.";
    cout<<"\n   This will take data only for the DAQ module number 'MODULE' for 'RUN' number of ";
    cout<<"\n   runs of length 'LENGTH' Megabyte each.";
    cout<<"\n   If MODULE, RUN and LENGTH are not specified the default values are, MODULE=21,";
    cout<<"\n   RUN=continuous runs and       ";
    cout<<"\n   LENGTH = default run length.       ";
    cout<<"\n";
    cout<<"\n n3he config :";
    cout<<"\n   This will display the current configuration (Sample rate,Averaging, Hi Resolution";
    cout<<"\n    mode etc.) for all the DAQ module.";
    cout<<"\n   ";
    cout<<"\n";
    cout<<"\n n3he help : ";
    cout<<"\n    This will bring this help session. ";
    cout<<"\n";
    cout<<"\n To quit the program while in continuous data taking mode :";
    cout<<"\n   -- At first let the current run finish.";
    cout<<"\n   -- When the run finishes and it sleeps a while, press Ctrl+C to quit the program."<<endl;

}


void Config()
{

    cout<<"This option is yet to be implemented"<<endl;
}
