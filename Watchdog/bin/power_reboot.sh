#!/usr/bin/expect

spawn telnet 192.168.0.100
expect "Login:"
send "admin=12345678\r"
expect "Username and password is ok!"
send "setpower=[lindex $argv 0]\r"
send "exit\r"
interact
