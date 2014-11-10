//The program to Show Help Session
//Author: Latiful Kabir
//Date:08.15.14
//Version:1.0

#include<iostream>
#include"Help.h"

using namespace std;

//Default instruction
void DefaultIns()
{
    cout<<"\n\t\t ===================================================================";
    cout<<"\n\t\t ||          Welcome to n3He DAQ Control Program v1.0             ||";
    cout<<"\n\t\t ===================================================================";
    cout<<"\n               \t\t     report bug to: latifulkabir@uky.edu";
    cout<<"\n";
    cout<<"\n";
    cout<<"          \t\t If you already know how to use then just go ahead           "<<endl;
    cout<<"              \t\t Otherwise from terminal do: n3he help                    "<<endl;
    cout<<"\n";
}

//The title 
void Title()
{
    cout<<"\n\t\t ===================================================================";
    cout<<"\n\t\t ||          Welcome to n3He DAQ Control Program v1.0             ||";
    cout<<"\n\t\t ===================================================================";
    cout<<"\n               \t\t       report bug to: latifulkabir@uky.edu";
    cout<<"\n";
    cout<<"\n";
}

//The help session
void Instruction()
{
    
    cout<<"\n\t\t ===================================================================";
    cout<<"\n\t\t ||          Welcome to n3He DAQ Control Program v1.0             ||";
    cout<<"\n\t\t ===================================================================";
    cout<<"\n                     \t\t      The Help Session";
    cout<<"\n               \t\t     report bug to: latifulkabir@uky.edu";
    cout<<"\n";
    cout<<"\n\t\t From the terminal do the following:";
    cout<<"\n ";
    cout<<"\n\t\t n3he start :";
    cout<<"\n  \t\t This will start the data taking process for all the DAQ modules for the";
    cout<<"\n  \t\t default run length continuously.";
    cout<<"\n";
    cout<<"\n\t\t n3he start LENGTH RUN : ";
    cout<<"\n  \t\t Where, LENGTH = The length of each run, RUN= the number of runs to be taken,";
    cout<<"\n  \t\t in Megabyte. ";
    cout<<"\n  \t\t Note RUN and LENGTH must be integer.";
    cout<<"\n  \t\t This will take only 'RUN' number of runs of length 'LENGTH' Megabyte each for";
    cout<<"\n  \t\t all the DAQ modules.";
    cout<<"\n";
    cout<<"\n";
    cout<<"\n\t\t n3he daq MODULE :";
    cout<<"\n  \t\t Where, MODULE= The DAQ module you want to run. It acn be either 21,23,24,30.";
    cout<<"\n  \t\t This will take data only for the DAQ module number 'MODULE' in continuous mode";
    cout<<"\n  \t\t for the default run length.";
    cout<<"\n  \t\t If the module number is not specified it will take data only for module 21 by";
    cout<<"\n  \t\t default.";
    cout<<"\n";
    cout<<"\n\t\t n3he daq MODULE LENGTH RUN :";
    cout<<"\n  \t\t Where, RUN= the number of runs to be taken, \n\t\t        LENGTH = The length of each run in Megabyte.";
    cout<<"\n         \t\tMODULE= The DAQ module you want to run. It can be either 21,23,24,30.";
    cout<<"\n";
    cout<<"\n  \t\t This will take data only for the DAQ module number 'MODULE' for 'RUN' number of ";
    cout<<"\n  \t\t runs of length 'LENGTH' Megabyte each.";
    cout<<"\n  \t\t If MODULE, RUN and LENGTH are not specified the default values are, MODULE=21,";
    cout<<"\n  \t\t RUN=continuous runs and       ";
    cout<<"\n  \t\t LENGTH = default run length.       ";
    cout<<"\n";
    cout<<"\n\t\t n3he config :";
    cout<<"\n  \t\t This will display the current configuration (Sample rate,Averaging, Hi Resolution";
    cout<<"\n   \t\t mode etc.) for all the DAQ module.";
    cout<<"\n   ";
    cout<<"\n";
    cout<<"\n\t\t n3he help : ";
    cout<<"\n   \t\t This will bring this help session. ";
    cout<<"\n";
    cout<<"\n \t\tTo quit the program while in continuous data taking mode :";
    cout<<"\n  \t\t -- Anytime press ctrl+C";
    cout<<"\n  \t\t -- The DAQ will finish the current run first defore it quits."<<endl;

}


void Config()
{

    cout<<"\t\tThis option is yet to be implemented"<<endl;
}
