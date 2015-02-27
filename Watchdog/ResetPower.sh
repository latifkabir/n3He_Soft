#!/bin/bash
wget http://admin:12345678@192.168.0.100/SetPower.cmd?P60=0  #Turn off Outlet:1
wget http://admin:12345678@192.168.0.100/SetPower.cmd?P60=1  #Turn on Outlet:1
