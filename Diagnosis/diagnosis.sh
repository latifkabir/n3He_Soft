#!/bin/bash

if [ $# == 1 ]
then 
    AUTO=$1
else
    AUTO='no'
fi
SR_ATTEMPT=-1
RP_ATTEMPT=-1
SUCCESS=0
file1=/home/daq/Diagnosis/CurrentConfig
file2=/home/daq/Diagnosis/ExpectedClean
file3=/home/daq/Diagnosis/ExpectedDirty

CheckStatus()
{
    echo "Checking if all files are in place ..."
    if [ -f $file1 ] && [ -f $file2 ] && [ -f $file3 ]
    then
	echo "Found all files are in place"
    else
	{
	    echo "Could NOT locate all required files"
	    exit
	}
    fi
}

PingDAQ()
{
    if [ $1 -eq 21 ]
    then
	INDEX1=0
    elif [ $1 -eq 22 ]
    then
	INDEX1=1
    elif [ $1 -eq 23 ]
    then
	INDEX1=2
    elif [ $1 -eq 24 ]
    then
	INDEX1=3
    elif [ $1 -eq 30 ]
    then
	INDEX1=4
    fi
    IP=192.168.0.$1
    ping -c 1 $IP &> /dev/null
    STSTUS1=$?
    if [ $STSTUS1 -eq 0 ]
    then
	echo "DAQ $1 is Active. --OK"
	LIVE[$INDEX1]=1
    else
	echo "DAQ $1 is NOT Active. Power Reboot it using browser or terminal. --PROBLEM"
	LIVE[$INDEX1]=0
    fi
}

GetConfig()
{
    ssh root@192.168.0.$1 'PATH=$PATH:/usr/local/bin/ 
cat /etc/acq400/1/rgm
cat /etc/acq400/1/rtm_translen
cat /etc/acq400/1/hi_res_mode
cat /etc/acq400/1/nacc
cat /etc/acq400/1/bank_mask
cat /etc/acq400/1/clk
cat /etc/acq400/1/clkdiv
cat /etc/acq400/1/trg
'
}

CheckConfig()
{

    if [ $1 -eq 21 ]
    then
	INDEX2=0
    elif [ $1 -eq 22 ]
    then
	INDEX2=1
    elif [ $1 -eq 23 ]
    then
	INDEX2=2
    elif [ $1 -eq 24 ]
    then
	INDEX2=3
    elif [ $1 -eq 30 ]
    then
	INDEX2=4
    fi

    echo "Reading Current Config"
    GetConfig $1 > /home/daq/Diagnosis/CurrentConfig

    echo "Now Comparing two configs"
    if [ $1 -eq 30 ]
    then
	diff $file1 $file3 &> /dev/null
    else
	diff $file1 $file2 &> /dev/null
    fi
    STSTUS2=$?
    if [ $STSTUS2 -eq 0 ]
    then
	echo "The configuration for DAQ $1 is as expected. --OK"
	MIS[$INDEX2]=1
    else
	echo "PROBLEM with DAQ $1 Configuration Detected. --PROBLEM"
	echo "Following is the corrupted config for DAQ $1"
	echo "---------------------------------------------------"
	cat $file1
	echo "---------------------------------------------------"
	MIS[$INDEX2]=0
    fi

}

RebootDAQ()
{
    echo "Now rebooting the DAQ"
    ssh root@192.168.0.$1 'PATH=$PATH:/usr/local/bin/ 
    reboot'
}

ResetPower()
{
    if [ ${LIVE[0]} == 0 ]
    then
	power_reset 21
    fi

    if [ ${LIVE[1]} == 0 ]
    then
	power_reset 22
    fi

    if [ ${LIVE[2]} == 0 ]
    then
	power_reset 23
    fi

    if [ ${LIVE[3]} == 0 ]
    then
	power_reset 24
    fi

    if [ ${LIVE[4]} == 0 ]
    then
	power_reset 30
    fi

    echo "Please wait 60 sec more to allow the DAQ to boot up properly... ..."
    sleep 60
}

SoftReboot()
{
    if [ ${MIS[0]} == 0 ]
    then
	RebootDAQ 21
    fi

    if [ ${MIS[1]} == 0 ]
    then
	RebootDAQ 22
    fi

    if [ ${MIS[2]} == 0 ]
    then
	RebootDAQ 23
    fi

    if [ ${MIS[3]} == 0 ]
    then
	RebootDAQ 24
    fi

    if [ ${MIS[4]} == 0 ]
    then
	RebootDAQ 30
    fi    
    echo "Sleeping for 60 sec for reboot time... ..."
    sleep 60    
}


DiagnoseActivity()
{
    for DAQ in 21 22 23 24 30  
    do
	echo "                           "
	echo "Checking if DAQ $DAQ is Active ..."
	echo "Please wait ... ..."
	echo "                           "
	PingDAQ $DAQ
    done

    if [ ${LIVE[0]} == 0 ] || [ ${LIVE[1]} == 0 ] || [ ${LIVE[2]} == 0 ] || [ ${LIVE[3]} == 0 ] || [ ${LIVE[4]} == 0 ]
    then
	ACTIVITY=0
	echo "              "
	echo "Problem detected. Seems like I am capable to handle it."
	echo "              "
	if [ $AUTO == 'auto' ]
	then
	    INPUT='y'
	else
	    echo "If you want me to fix the issue press enter 'y', Otherwise enter 'n'"
	    read INPUT
	fi

	if [ $INPUT == 'y' ]
	then
	    ResetPower
	    RP_ATTEMPT=1
	else
	    echo "                           "
	    echo "Please Fix the above issues yourself and then run the diagnosis again."
	    RP_ATTEMPT=0
	    SUCCESS=1 
	fi 
    else
	ACTIVITY=1
	RP_ATTEMPT=0 
    fi  
}

DiagnoseConfig()
{
    echo "                           "
    echo "Now testing if there is any configuration mismatch ..."
    echo "                           "

    for DAQ in 21 22 23 24 30  
    do
	echo "                           "
	echo "Checking if there is any config mismatch for DAQ $DAQ"
	echo "                           "
	CheckConfig $DAQ
    done

    if [ ${MIS[0]} == 0 ] || [ ${MIS[1]} == 0 ] || [ ${MIS[2]} == 0 ] || [ ${MIS[3]} == 0 ] || [ ${MIS[4]} == 0 ]
    then
	echo "Problem detected. Seems like I am capable to handle it."
	echo "               "
	if [ $AUTO == 'auto' ]
	then
	    INPUT='y'
	else
	    echo "If you want me to fix the issue press enter 'y', Otherwise enter 'n'"
	    read INPUT
	fi

	if [ $INPUT == 'y' ]
	then
	    SoftReboot
	    SR_ATTEMPT=1
	else
	    echo "                           "
	    echo "Please Fix the above issues yourself and then run the diagnosis again."
	    SR_ATTEMPT=0
	    SUCCESS=1
	fi
    else
	SR_ATTEMPT=0
	SUCCESS=1
    fi    
}

echo "--------------------------------------------------------"
echo "|     Welcome to DAQ's Healthcare Companion Baymax     |"
echo "|     report issues or bug to:latifulkabir@uky.edu     |"
echo "--------------------------------------------------------"
CheckStatus
echo "Starting the DAQ Diagnosis ... ..."
echo "Time:"
date
echo "                           "
for attempt in 1 2 3
do
    DiagnoseActivity
    if [ $ACTIVITY == 1 ]
    then
	DiagnoseConfig
    fi

    if [ $SR_ATTEMPT == 1 ] || [ $RP_ATTEMPT == 1 ]
    then
	echo "Checking the Activity and Configuration after the fixes..."
	DiagnoseActivity
	if [ $ACTIVITY == 1 ]
	then
	    DiagnoseConfig
	fi
    fi

    if [ $SUCCESS == 1 ]
    then
	break
    fi
done

if [ $SR_ATTEMPT == 1 ] || [ $RP_ATTEMPT == 1 ]
then
    if [ $SUCCESS == 1 ]
    then
	echo "           "
	echo "Successfully fixed the issues!!!. The DAQ is ready to resume data taking process."
	if [ $AUTO == 'auto' ]
	then
	    echo "Initializing alternative data taking program own it's own ..."
	    n3he start
	fi
    else
	echo "Sorry, Unable to fix the issue :) ."
    fi
else
    echo "                           "
    echo "Finished the diagnosis !!"
    echo "Close the window or press ctrl+C to quit."
fi
sleep 600
