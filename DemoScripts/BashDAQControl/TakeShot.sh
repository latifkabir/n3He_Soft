#!/bin/sh
max=${1:-1000}
uut=127.0.0.1
length={$2:-10000}
for shot in $(seq 1 $max)
do
    nc $uut 4210 | dd bs=512 count=10000 of=shot$(printf "%03d" $shot);
    sleep 5;
done



#=> creates 1000 files shotNNN each approx 5120000 bytes
#(ie many events/shots)

