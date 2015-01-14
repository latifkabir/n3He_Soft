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
    cout<<"\n ====================================================================";
    cout<<"\n ||   Welcome to n3He Magnetic Field Reading  Program v1.0         ||";
    cout<<"\n ====================================================================";
    cout<<"\n                report bug to: latifulkabir@uky.edu";
    cout<<"\n";
    cout<<"\n";
    cout<<"           If you already know how to use then just go ahead           "<<endl;
    cout<<"               Otherwise from terminal do: mag help                    "<<endl;
    cout<<"\n";
}

//The title 
void Title()
{
    cout<<"\n =====================================================================";
    cout<<"\n ||     Welcome to n3He Magnetic Field Reading Program v1.0         ||";
    cout<<"\n =====================================================================";
    cout<<"\n                report bug to: latifulkabir@uky.edu";
    cout<<"\n";
    cout<<"\n";
}

//The help session
void Instruction()
{
    
    cout<<"\n =======================================================================";
    cout<<"\n ||  Welcome to n3He Magnetic Field Reading Program Program v1.0      ||";
    cout<<"\n =======================================================================";
    cout<<"\n                      The Help Session";
    cout<<"\n                report bug to: latifulkabir@uky.edu";
    cout<<"\n";
    cout<<"\n From the terminal do the following:";
    cout<<"\n ";
    cout<<"\n mag single :";
    cout<<"\n   This will take a sigle reading for the magnetic field";
    cout<<"\n   After the single run press 'c' followed by Enter to ";
    cout<<"\n   take another shot.";
    cout<<"\n";
    cout<<"\n mag scan : ";
    cout<<"\n   This will read field cotinuosly at an intervel 4 or 5 sec";
    cout<<"\n";
    cout<<"\n n3he help : ";
    cout<<"\n   This will bring this help session. ";
    cout<<"\n";
    cout<<"\n To quit the program while in continuous data taking mode :";
    cout<<"\n   -- Anytime press ctrl+C";
    cout<<"\n   -- It will finish the current run first defore it quits."<<endl;

}
