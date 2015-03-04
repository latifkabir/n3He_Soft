#!/bin/bash

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
    GetConfig $1 > /home/daq/DAQDiagnosis/CurrentConfig

    file1="/home/daq/DAQDiagnosis/CurrentConfig"
    file2="/home/daq/DAQDiagnosis/ExpectedClean"
    file3="/home/daq/DAQDiagnosis/ExpectedDirty"

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
    echo "Sleeping for 60 sec for reboot time... ..."
    sleep 60
    
}

echo "Starting the DAQ Diagnosis ... ..."
echo "Time:"
date
echo "                           "

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
    echo "                           "
    echo "Please Fix the above issues and then run the diagnosis again."
else
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

	echo "                           "
	echo "Finished the diagnosis !!"
	echo "Close the window or press ctrl+C to quit."
    }
fi
sleep 600
