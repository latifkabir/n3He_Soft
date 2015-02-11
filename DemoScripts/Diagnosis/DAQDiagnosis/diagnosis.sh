#!/bin/bash

PingDAQ()
{
    IP=192.168.0.$1
    ping -c 1 $IP &> /dev/null
    STSTUS=$?
    if [ $STSTUS -eq 0 ]
    then
	echo "Found DAQ $1 is Active. --OK"
    else
	echo "DAQ $1 is NOT Active. Enter the Cave and Reboot it manually. --PROBLEM"
    fi
}

GetConfig()
{
    ssh root@192.168.0.$1 'PATH=$PATH:/usr/local/bin/ 
get.site 1 <<EOF
rgm
rtm_translen
hi_res_mode
nacc
bank_mask
clk
clkdiv
trg
EOF
'
}

CheckConfig()
{
    echo "Reading Current Config"
    GetConfig $1 > CurrentConfig

    file1="CurrentConfig"
    file2="ExpectedConfig"

    echo "Now Comparing two configs"
    diff $file1 $file2 &> /dev/null
    STSTUS=$?
    if [ $STSTUS -eq 0 ]
    then
	echo "The configuration for DAQ $1 is OK"
    else
	echo "PROBLEM with DAQ $1 Configuration Detected.--PROBLEM"
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

echo "Finished the diagnosis !!"
