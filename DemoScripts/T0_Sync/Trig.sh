#!/bin/bash

ssh root@192.168.0.30 'PATH=$PATH:/usr/local/bin/ 
echo "Trigger:"
a=10
while [ $a -ge 10 ]
do
 get.site 0 do4_3
done
'  
