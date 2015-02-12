#!/bin/bash

PingDAQ()
{
    IP=192.168.0.$1
    ping -c 1 $IP &> /dev/null
    STSTUS=$?
    if [ $STSTUS -eq 0 ]
    then
	echo "DAQ $1 is Active. --OK"
    else
	echo "DAQ $1 is NOT Active. Enter the Cave and Reboot it manually. --PROBLEM"
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
    STSTUS=$?
    if [ $STSTUS -eq 0 ]
    then
	echo "The configuration for DAQ $1 is as expected. --OK"
    else
	echo "PROBLEM with DAQ $1 Configuration Detected. --PROBLEM"
    fi

}

RebootDAQ()
{
    echo "Now rebooting the DAQ"
    ssh root@128.165.131.1 'PATH=$PATH:/usr/local/bin/ 
    reboot'
    echo "Sleeping for 60 sec for reboot time"
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
echo "Close the window to quit."

sleep 600
