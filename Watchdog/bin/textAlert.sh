#!/bin/bash
TXT=$1
echo "                $TXT"
ssh basestar "echo $TXT | mutt -s \"Subject Here\" number1@domain1,-b number2@domain2,-b number3@domain3, -b number4@domain4"
gnome-terminal --geometry=110x50+0+0 -t "Alert" -e "/home/daq/Watchdog/bin/screenAlert"
