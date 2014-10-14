#include<iostream>
#include<unistd.h>
#include"Daq.h"
#include"Constants.h"

using namespace std;

int DaqConfig(char *argv2)
// int main(int argc,char *argv[])
{
    string change_config[]={"on","off"};
    string config;

    Daq daq(DAQ21_IP,DAQ_PORT2,DAQ21,RUN_LENGTH);
    if(!daq.CheckStatus())
    {
	//if(argc>1)
	{
	    if(argv2==change_config[0])
	    {
		config="do4_3 1";
		cout<<"Trigger Enabled"<<endl;
		daq.WriteToSocket(config.c_str());
	    }
	    else if(argv2==change_config[1])
	    {
		config="do4_3 0";
		cout<<"Trigger Disabled"<<endl;
		daq.WriteToSocket(config.c_str());
	    }
	}
	// cout<<"Enter DAQ configuration change: "<<endl;
	// cin>>change_config;
        //Suggested Use
	// daq.WriteToSocket("nacc=1,1");
	// daq.WriteToSocket("do4_0 1");
	// daq.WriteToSocket("set.site 1 rgm=1,0,1");
	// daq.WriteToSocket("set.site 1 hi_res_mode=1");
    }
    return(0);
}

// int main()
// {
//     for(int i=0;i<100;i++)
//     {
// 	DaqConfig("on");
// 	sleep(3);
// 	DaqConfig("off");
// 	sleep(3);
//     }
//     return(0);
// }
