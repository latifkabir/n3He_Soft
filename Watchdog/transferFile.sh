#!/bin/bash

START=$1
STOP=$2

echo "$START"
echo "$STOP"

scp -p ~/Downloads/Library.zip basestar:~/Videos/.


# START=$1
# STOP=$2
# while [ $START -ne $STOP ]
# do
#     if[ -f /home/daq/DATA/run-${START}data-21 ]
#     then
# 	scp -p /home/daq/DATA/run-${START}data-{21,22,23,24,30} basestar:/mnt/idata01/data/.
#     fi
#     START=`expr $START + 1`
# done
