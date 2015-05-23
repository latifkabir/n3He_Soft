//Program for periodic run transfer to basestar.
//Author: Latiful Kabir
//Date:03/03/15

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "constants.h"
using namespace std;


//--------------Transfer the run to basestar------------------
int TransferData(int rnumber,int last_trans)
{
    int start_run=last_trans+1;  //next run after last run transferred sucessfully.
    int stop_run;
    time_t start,end;
    double tDiff;

    if(rnumber < start_run+2) 
	stop_run=rnumber;   // Current run ready for transfer.
    else
	stop_run=start_run+2;
    int sleep_time=450;
    // if(stop_run > start_run-1)
    // 	sleep_time=(450 - 150*(stop_run+1-start_run));
    

    int strlen=200;
    char *command=new char[strlen];
    snprintf(command,strlen,TRANS_COMMAND,start_run,stop_run+1);

    int isConnected=system(PING_COMMAND);

    if((stop_run > (start_run-1)) && isConnected==0 )
    {
	cout<<"\n\t\tNow attempting to transfer the data files to basestar ..."<<endl;

	time(&start);
	int tstatus=system(command);
	time(&end);
	tDiff=difftime(end,start);
	sleep_time=(sleep_time - (int)tDiff);
	if(sleep_time<0)
	    sleep_time=0;
 
	if(!tstatus)  //0 tstatus means successfully transferred
	{	
	    if(stop_run==start_run)
		cout<<"\n\t\tAll data files for run number "<<stop_run<<" transferred to basestar successfully"<<endl;
	    else
		cout<<"\n\t\tAll data files for run numbers "<<start_run<<" to "<<stop_run<<" transferred to basestar successfully"<<endl;
            //Update last transferred run
	    ofstream last_transf(LAST_TRANS_TXT);
	    if(last_transf)
	    {
		last_transf<<stop_run;
		last_transf.close();
	    }
	    cout<<"\n\t\tNow waiting for next run ... ..."<<endl;
	    sleep(sleep_time);    	//wait till current run finishes
	}
	else
	{
	    time(&start);
	    cout<<"\n\t\tThe first attenpt to send data files to basestar failed.Will initiate the second attempt shortly ... .."<<endl;
	    sleep(100);
	    cout<<"\n\t\tSecond attempt to transfer data to basestar ..."<<endl;

	    tstatus=system(command);
	    time(&end);
	    tDiff=difftime(end,start);
	    sleep_time=(sleep_time - (int)tDiff);
	    if(sleep_time<0)
		sleep_time=0;

	    if(!tstatus)
	    {
		if(stop_run==start_run)
		    cout<<"\n\t\tAll data files for run number "<<stop_run<<" transferred to basestar successfully"<<endl;
		else
		    cout<<"\n\t\tAll data files for run numbers "<<start_run<<" to "<<stop_run<<"transferred to basestar successfully"<<endl;
		
                //Update last transferred run
		ofstream last_transf(LAST_TRANS_TXT);
		if(last_transf)
		{
		    last_transf<<stop_run;
		    last_transf.close();
		}

		cout<<"\n\t\tNow waiting for next run ... ..."<<endl;
		sleep(sleep_time);
	    }
	    else
	    {
		if(stop_run==start_run)
		    cout<<"\n\t\tBoth attempts to transfer run "<<stop_run<<" data failed."<<endl;
		else
		    cout<<"\n\t\tBoth attempts to transfer run: "<<start_run<<" to "<<stop_run<<" data files failed."<<endl;	       
   
		cout<<"\n\t\tNow waiting for next run ... ..."<<endl;
		sleep(sleep_time);
	    }
	}
    }
    else
    {
	cout<<"\n\t\tNo valid run number for transfer activity or No internet connection"<<endl;
	cout<<"\n\t\tNow waiting for next run ... ..."<<endl;
	sleep(sleep_time);
    }

    delete[] command;
}
