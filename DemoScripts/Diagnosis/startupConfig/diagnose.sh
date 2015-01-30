#!/bin/bash

echo "Starting the Diagnostic ... ..."
echo "Time:"
date
a=1
while [ $a -ne 250 ]  
do
    echo "=====Loop number $a ======"

    echo "Now rebooting the DAQ"
    ssh root@128.165.131.1 'PATH=$PATH:/usr/local/bin/ 
    reboot'
    echo "Sleeping for 60 sec for reboot time"
    sleep 60
    echo "Reading Current Config"
    ./GetConfig.sh > CurrentConfig

    file1="CurrentConfig"
    file2="ExpectedConfig"

    echo "Now Comparing two configs"
    diff $file1 $file2 &> /dev/null
    STSTUS=$?
    if [ $STSTUS -eq 0 ]
    then
	echo "They are same"
    else
	echo "They are different"
	date
	break
    fi
    a=`expr $a + 1`

    echo "Sleeping for 180 sec ... ..."
    sleep 180
done

