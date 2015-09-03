#!/bin/bash

RUN=$1
LAST=$2
while [ $RUN -le $LAST ]
do
    if [ -f /home/daq/DATA/run-${RUN}data-21 ] && if [ -f /home/daq/DATA/run-${RUN}data-22 ] && if [ -f /home/daq/DATA/run-${RUN}data-23 ] && if [ -f /home/daq/DATA/run-${RUN}data-24 ] && if [ -f /home/daq/DATA/run-${RUN}data-30 ]
    then
	scp -p /home/daq/DATA/run-${RUN}data-{21,22,23,24,30} basestar:/mnt/idata01/data/.
    fi
    RUN=`expr $RUN + 1`
done
