#!/bin/bash

isProgRunning()
{
    ps -a | grep 'n3he'
    STATUS=$?
    STATUS >> watchdogParam.txt

    # If n3he is running then STATUS is 0 (exit Success) , if not running the STATUS is 1
}
