#!/bin/bash
cosm=$(tail -n +2 spacex.txt|sort -t "|" -k2|cut -d "|" -f2,3|uniq -c| tr -s " "|sort -n|grep "Failure"|tail -n 1|cut -d " " -f3|cut -d "|" -f1)

grep "$cosm" spacex.txt|sort -n|head -n 1|cut -d "|" -f3,4| sed 's/|/:/g'
