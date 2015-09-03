#!/bin/bash

if [ $# == 0 ]
then
    echo "Please enter run ranges as the arguments"
    exit
fi

RUN=$1

if [ $# == 1 ]
then
    LAST=$1
elif [ $# == 2 ]
then
    LAST=$2
else
    echo "Please enter run two ranges as the arguments"
    exit
fi


while [ $RUN -le $LAST ]
do
    ssh basestar "test -e /mnt/idata05/summary/run-${RUN}.root"
    STATUS=$?
    if [ $STATUS == 0 ]
    then
	scp -p basestar:/mnt/idata05/summary/run-${RUN}.root .
    else
	echo "The file run-${RUN}.root does NOT exist"
    fi
    RUN=`expr $RUN + 1`
done
