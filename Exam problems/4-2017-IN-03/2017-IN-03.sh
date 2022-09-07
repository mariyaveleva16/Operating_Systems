#!/bin/bash
cut -d ":" -f1,5,6 passwd|grep "/home/Inf"|sed "s/,/:/g"|cut -d ":" -f1,2| grep "a$"|cut -c 3-4 |uniq -c| tr -s " "
