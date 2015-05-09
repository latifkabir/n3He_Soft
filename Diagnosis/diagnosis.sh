#!/bin/bash

# Filename: diagnosis.sh
# Description: The DAQ's healthcare companion Baymax 
# Author: Latiful Kabir < siplukabir@gmail.com >
# Created: Sat Mar 28 15:53:47 2015 (-0400)
# URL: latifkabir.github.io



if [ $# == 1 ]
then 
    AUTO=$1
else
    AUTO='no'
fi

SR_ATTEMPT=0
RP_ATTEMPT=0
SUCCESS_A=0
SUCCESS_B=0
CHECK_FS=0
LOOP=0
FROZEN=0

file1=/home/daq/Diagnosis/CurrentConfig
file2=/home/daq/Diagnosis/ExpectedClean
file3=/home/daq/Diagnosis/ExpectedDirty
file4=/home/daq/Diagnosis/power_reset

dfile1=/home/daq/DATA/data-21
dfile2=/home/daq/DATA/data-22
dfile3=/home/daq/DATA/data-23
dfile4=/home/daq/DATA/data-24
dfile5=/home/daq/DATA/data-30

CheckStatus()
{
    echo "Checking if all files are in place ..."
    if [ -e $file1 ] && [ -e $file2 ] && [ -e $file3 ] && [ -e $file4 ]
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
	echo "               "
	echo "DAQ $1 is NOT Active. Power Reboot it using browser or terminal. --PROBLEM"
	echo "             "
	LIVE[$INDEX1]=0
    fi
}

GetConfig()
{
    ssh -o ConnectTimeout=10 root@192.168.0.$1 'PATH=$PATH:/usr/local/bin/ 
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
    TIMED_OUT=$?

    if [ $TIMED_OUT -eq 0 ]
    then
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
	    echo "                   "
	    echo "PROBLEM with DAQ $1 Configuration Detected. --PROBLEM"
	    echo "                    "
	    echo "Following is the corrupted config for DAQ $1"
	    echo "---------------------------------------------------"
	    cat $file1
	    echo "---------------------------------------------------"
	    MIS[$INDEX2]=0
	fi
    else
	LIVE[$INDEX2]=0
	FROZEN=1
    fi
}

RebootDAQ()
{
    echo "Now rebooting the DAQ $1"
    ssh -o ConnectTimeout=10 root@192.168.0.$1 'PATH=$PATH:/usr/local/bin/ 
    reboot'
}

ResetPower()
{
    if [ ${LIVE[0]} == 0 ]
    then
	/home/daq/Diagnosis/power_reset 21
    fi

    if [ ${LIVE[1]} == 0 ]
    then
	/home/daq/Diagnosis/power_reset 22
    fi

    if [ ${LIVE[2]} == 0 ]
    then
	/home/daq/Diagnosis/power_reset 23
    fi

    if [ ${LIVE[3]} == 0 ]
    then
	/home/daq/Diagnosis/power_reset 24
    fi

    if [ ${LIVE[4]} == 0 ]
    then
	/home/daq/Diagnosis/power_reset 30
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
}

SolveFrozenActivity()
{
    if [ ${LIVE[0]} == 0 ] || [ ${LIVE[1]} == 0 ] || [ ${LIVE[2]} == 0 ] || [ ${LIVE[3]} == 0 ] || [ ${LIVE[4]} == 0 ]
    then
	ACTIVITY=0
	echo "              "
	echo "PROBLEM detected. Seems like I am capable to handle it."
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
	    RP_ATTEMPT=`expr $RP_ATTEMPT + 1` 
	else
	    echo "                           "
	    echo "Please Fix the above issues yourself and then run the diagnosis again."
	    SUCCESS_A=1 
	    SUCCESS_B=1 
	fi 
    else
	ACTIVITY=1
	SUCCESS_A=1
    fi  
    LOOP=`expr $LOOP + 1` 
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
	echo "               "
	echo "PROBLEM detected. Seems like I am capable to handle it."
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
	    SR_ATTEMPT=`expr $SR_ATTEMPT + 1` 
	else
	    echo "                           "
	    echo "Please Fix the above issues yourself and then run the diagnosis again."
	    SUCCESS_B=1
	fi
    elif [ $FROZEN -eq 1 ]
    then
	SolveFrozenActivity
    else
	SUCCESS_B=1
	CHECK_FS=1
    fi    
    LOOP=`expr $LOOP + 1` 
}

CheckFileSize()
{
    if [ -e $dfile1 ] && [ -e $dfile2 ] && [ -e $dfile3 ] && [ -e $dfile4 ] && [ -e $dfile5 ]
    then
	echo "                                      "
	echo "Now Checking file size consistancy ..."
	echo "                                      "
	SIZE21=$(ls -l $dfile1 | awk '{print $5}')
	echo "DAQ21 data file size: $SIZE21 Bytes" 
	SIZE22=$(ls -l $dfile2 | awk '{print $5}')
	echo "DAQ22 data file size: $SIZE22 Bytes" 
	SIZE23=$(ls -l $dfile3 | awk '{print $5}')
	echo "DAQ23 data file size: $SIZE23 Bytes" 
	SIZE24=$(ls -l $dfile4 | awk '{print $5}')
	echo "DAQ24 data file size: $SIZE24 Bytes" 
	SIZE30=$(ls -l $dfile5 | awk '{print $5}')
	echo "DAQ30 data file size: $SIZE30 Bytes" 

	SIZE=0

	if [ $SIZE21 -gt $SIZE22 ]
	then
	    SIZE=$SIZE21
	else
	    SIZE=$SIZE22
	fi     

	if [ $SIZE23 -gt $SIZE ]
	then
	    SIZE=$SIZE23
	fi     

	if [ $SIZE24 -gt $SIZE ]
	then
	    SIZE=$SIZE24
	fi     

	if [ $SIZE -gt 5000000 ]
	then
	    SIZED=$(echo "($SIZE*5.41666666667)/1" | bc)
	    SIZEC=`expr $SIZED - 5000000`
	    SIZER=`expr $SIZE - 5000000`

	    if [ $SIZER -gt $SIZE21 ]
	    then
		echo "             "
		echo "Unexpected file size. Problem with DAQ 21. ---PROBLEM"
		MIS[0]=0
	    fi
	    
	    if [ $SIZER -gt $SIZE22 ]
	    then
		echo "             "
		echo "Unexpected file size. Problem with DAQ 22. ---PROBLEM"
		MIS[1]=0
	    fi
	    
	    if [ $SIZER -gt $SIZE23 ]
	    then
		echo "             "
		echo "Unexpected file size. Problem with DAQ 23. ---PROBLEM"
		MIS[2]=0
	    fi     

	    if [ $SIZER -gt $SIZE24 ]
	    then
		echo "             "
		echo "Unexpected file size. Problem with DAQ 24. ---PROBLEM"
		MIS[3]=0
	    fi   

	    if [ $SIZEC -gt $SIZE30 ] && [ $SIZE30 -ne 0 ]
	    then
		echo "             "
		echo "Unexpected file size. Problem with DAQ 30. ---PROBLEM"
		MIS[4]=0
	    fi     

	    if [ ${MIS[0]} == 0 ] || [ ${MIS[1]} == 0 ] || [ ${MIS[2]} == 0 ] || [ ${MIS[3]} == 0 ] || [ ${MIS[4]} == 0 ]
	    then
		echo "               "
		echo "PROBLEM detected."
		echo "Discard this PROBLEM if you just rebooted this DAQ & have not resumed data taking process."
		echo "Otherwise seems like I am capable to handle it.               "
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
		    SR_ATTEMPT=`expr $SR_ATTEMPT + 1` 
		else
		    echo "                           "
		    echo "Please Fix the above issues yourself and then run the diagnosis again."
		    SUCCESS_B=1
		fi
	    else
		echo "               "
		echo "The data file sizes make sense. --OK"
		SUCCESS_B=1
	    fi
	else
	    SUCCESS_B=1
	fi
    else
	SUCCESS_B=1    
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
    SolveFrozenActivity
    if [ $ACTIVITY == 1 ]
    then
	DiagnoseConfig
	if [ $CHECK_FS == 1 ]
	then
	    SUCCESS_B=0
	    if [ $attempt == 1 ]
	    then 
		CheckFileSize
	    fi
	fi
    fi

    if [ $SR_ATTEMPT -gt 0 ] || [ $RP_ATTEMPT -gt 0 ]
    then
	echo "                                "
	echo "Checking the Activity and Configuration after the fixes..."
	DiagnoseActivity
	SolveFrozenActivity
	if [ $ACTIVITY == 1 ]
	then
	    DiagnoseConfig
	fi
	if [ $SUCCESS_A == 1 ] && [ $SUCCESS_B == 1 ]
	then
	    break
	fi
    fi

    if [ $SUCCESS_A == 1 ] && [ $SUCCESS_B == 1 ]
    then
	break
    fi
done

if [ $LOOP -ge 3 ]
then
    if [ $SUCCESS_A == 1 ] && [ $SUCCESS_B == 1 ]
    then
	echo "           "
	echo "Successfully fixed the issues!!!. The DAQ is ready to resume data taking process."
	if [ $AUTO == 'auto' ]
	then
	    echo "Terminating the frozen DAQ Program ..."
	    PID=$(ps -e | grep -w 'n3he' | awk '{print $1}')
	    if [ $PID > 0 ]
	    then
		kill $PID
	    fi
	    sleep 5
	    echo "Initializing alternative data taking program on it's own ..."
	    /home/daq/Watchdog/bin/textAlert.sh "Initiated alternative automated n3He data taking process"
	    /home/daq/n3HeDAQ/bin/n3he start
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
