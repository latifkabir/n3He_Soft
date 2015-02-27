#!/bin/bash

RUN=$1
LAST=$2
while [ $RUN -ne $LAST ]
do
    if [ -f /home/daq/DATA/run-${RUN}data-21 ]
    then
	scp -p /home/daq/DATA/run-${RUN}data-{21,22,23,24,30} basestar:/mnt/idata01/data/.
    fi
    #sleep 4200
    RUN=`expr $RUN + 1`
done
