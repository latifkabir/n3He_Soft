#!/bin/bash

ps -e | grep -w 'magTemp' >> /dev/null
STATUS=$?

if [ $STATUS == 0 ]
then
    echo "                    "
    echo "                    "
    echo "                    "
    echo "                    "
    echo "                Seems like magTemp program is already running."
    echo "                Running multiple of them at the same time is prohibited by its programmer."
    echo "                Please close the other one if you really need to start a fresh one."
    echo "                Note there are multiple workspaces on this computer.    "
    echo "                    "
    sleep 600
else
    /home/daq/ReadRS232/Mag\&Temp/bin/magTemp
fi
