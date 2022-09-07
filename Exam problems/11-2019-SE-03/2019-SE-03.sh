#!/bin/bash
inod=$(find /home/velin -type f -printf "%C@ %p %i\n"|sort -n -t " " -k1 |tail -n 1|cut -d " " -f3)

find /home/velin -type f -printf "%i %p\n"|grep "$inod"|cut -d " " -f2|awk -F "/" '{print NF-1}'|sort -nr|tail -n 1
