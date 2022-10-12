#!/bin/bash

FOOpr=$(ps -e -o user|grep "^s855366"|wc -l)
users=$(mktemp)
ps -e -o user|sort|uniq -c|tr -s " "|sed 's/^ //g'>$users
awk -F " " '$1>'$FOOpr' {print $2}' $users
time=$(ps -e -o time|tail -n +2|awk -F ":" '{sum=$1*360+$2*60+$3}; END {print sum}')
rm $users
