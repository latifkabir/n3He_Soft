#!/bin/bash

MODULE=$1
echo "====================================="
echo "The current config for DAQ Module: $MODULE"
echo "====================================="
echo "                    "

ssh root@192.168.0.$MODULE 'PATH=$PATH:/usr/local/bin/ 
echo "Running mode:"
get.site 1 rgm
echo "          "

echo "Hi Res mode:"
get.site 1 hi_res_mode
echo "          "

echo "Averaging and decimation:"
get.site 1 nacc
echo "          "

echo "Event length: "
get.site 1 rtm_translen
echo "           "

echo "Sample/Event Rate: "
get.site 1 SIG:sample_count:FREQ
echo "           "

echo "Bank Mask: "
get.site 1 bank_mask
echo "           "

echo "Clock: "
get.site 1 clk
echo "           "

echo "Clock Division:"
get.site 1 clkdiv'
