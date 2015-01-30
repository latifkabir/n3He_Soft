#!/bin/bash

echo "Starting the Diagnostics .."
echo "Time:"
time
a=1
while [ $a -ne 250 ]  
do

    ssh root@192.168.0.$MODULE 'PATH=$PATH:/usr/local/bin/ 
    reboot'
    sleep 1
    ./GetConfig.sh > CurrentConfig


    file1="CurrentConfig"
    file2="ExpectedConfig"
    diff $file1 $file2 &> /dev/null
    STSTUS=$?
    echo "Loop number $a"
    if [ $STSTUS -eq 0 ]
    then
	echo "They are same"
    else
	echo "They are different"
	time
	break
    fi
    a=`expr $a + 1`
    sleep 600
done



# Exit status for diff
#     0     No differences were found. 
#     1     Differences were found.
#    >1     An error occurred.

# Just google 'diff unix man page'
