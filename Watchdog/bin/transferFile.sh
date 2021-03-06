#!/bin/bash

RUN=$1
LAST=$2
while [ $RUN -ne $LAST ]
do
    if [ -f /home/daq/DATA/run-${RUN}data-21 ] && [ -f /home/daq/DATA/run-${RUN}data-22 ] && [ -f /home/daq/DATA/run-${RUN}data-23 ] && [ -f /home/daq/DATA/run-${RUN}data-24 ] && [ -f /home/daq/DATA/run-${RUN}data-30 ]
    then
	scp -p /home/daq/DATA/run-${RUN}data-{21,22,23,24,30} basestar:/mnt/idata02/data/.
    else
	echo "FAILED to transfer run:${RUN}  . Files does NOT exist."
	echo "run:${RUN} " >> /home/daq/Watchdog/bin/failedRuns.txt
    fi
    RUN=`expr $RUN + 1`
done
