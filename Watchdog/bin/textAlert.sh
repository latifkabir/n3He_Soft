#!/bin/bash
TXT=$1
echo "                $TXT"
ssh basestar "echo $TXT | mutt number1@domain1,number2@domain2,number3@domain3,number4@domain4"
