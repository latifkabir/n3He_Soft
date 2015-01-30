#!/bin/bash

MODULE=$1
echo "====================================="
echo "The current config for DAQ Module: $MODULE"
echo "====================================="
echo "                    "
echo "Printing Config in the order of :1.rgm 2.rtm_translen 3. hi_res_mode 4.nacc 5.bank_mask 6.clk 7.clkdiv 8.trg "
echo "                    "
ssh root@128.165.131.1 'PATH=$PATH:/usr/local/bin/ 
get.site 1 <<EOF
rgm
rtm_translen
hi_res_mode
nacc
bank_mask
clk
clkdiv
trg
EOF
'
