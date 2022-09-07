#!/bin/bash

FOOprN=$(ps -e -o user|grep "^s855366"|wc -l)
users=$(mktemp)
ps -e -o user|sort|uniq -c|tr -s " "|sed 's/^ //g'>$users
awk -F " " '$1>'$FOOprN' {print $2}' $users

time=$(ps -e -o times|tail -n +2|awk 'BEGIN{c=0; time}{c++; time+=$1}; END {if (c>0) print time/c; else print "0"}')
echo "Sum of procesess time=$time seconds"

ps -e -o user,pid,times|grep "^s855366"|awk '$3>'$time' {print $2}'|while read pr; do
	echo "Kill proces with PID=$pr"
done 
rm $users
