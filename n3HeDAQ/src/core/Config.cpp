#include<iostream>
#include"Config.h"
#include"Daq.h"
using namespace std;

int DaqConfig()
// int main(void)
{
    string change_config;

    Daq daq("192.168.0.23","4221",23,10e6);
    if(!daq.CheckStatus())
    {
	cout<<"Enter DAQ configuration change: "<<endl;
	cin>>change_config;
        daq.WriteToSocket(change_config.c_str());
        //Suggested Use
	// daq.WriteToSocket("nacc=1,1");
	// daq.WriteToSocket("do4_0 1");
	// daq.WriteToSocket("set.site 1 rgm=1,0,1");
	// daq.WriteToSocket("set.site 1 hi_res_mode=1");
    }
    return(0);
}
