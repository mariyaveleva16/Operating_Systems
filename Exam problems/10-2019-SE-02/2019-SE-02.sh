#!/bin/bash

grep "$(find $(awk -F ":" '{if($6~"/home/students/s62*") print $0}' /etc/passwd|cut -d ":" -f6) -mindepth 1 -maxdeph 1 -newerct "2021-02-08" !-newerct "2022-05-15")" /etc/passwd|cut -d "," -f1|cut -d ":" -f1,5|cut -c 2-|sed 's/:/\t/' 
