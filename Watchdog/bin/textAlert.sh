#!/bin/bash
TXT=$1
echo "                $TXT"
ssh basestar "echo $TXT | mutt -s \"Subject Here\" number1@domain1,-b number2@domain2,-b number3@domain3, -b number4@domain4"

HOUR=$(date "+%k")
if [ $HOUR -lt 8 ]
then
	echo "                  Sent Text Alert"
else
	gnome-terminal --geometry=165x30+0+0 -t "Alert" -e "/home/daq/Watchdog/bin/screenAlert"
fi
