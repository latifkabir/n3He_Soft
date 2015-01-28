#!/bin/bash

MODULE=$1
echo "====================================="
echo "The current config for DAQ Module: $MODULE"
echo "====================================="
echo "                    "
echo "Setting Config in the order of :1.rgm 2.rtm_translen 3. hi_res_mode 4.nacc 5.SIG:sample_count:FREQ 6.bank_mask 7.clk 8.clkdiv 9.trg "
echo "                    "
ssh root@192.168.0.$MODULE 'PATH=$PATH:/usr/local/bin/ 
set.site 1 <<EOF
rgm 1,0,1
rtm_translen 830
hi_res_mode 1
nacc 16,16
bank_mask ABC
clk 1,1,0
clkdiv 1
trg 1,1,1
EOF
'
