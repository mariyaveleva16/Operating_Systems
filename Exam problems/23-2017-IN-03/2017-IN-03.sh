#!/bin/bash

timesF=$(mktemp);
cut -d ":" -f6 /etc/passwd|while read line;do
find $line -mindepth 1 -maxdepth 1 -type f -printf "%T@ %p\n"|sort -n|tail -n 1 >>$timesF 2>/dev/null
done

cat $timesF|sort -n|tail -n 1| awk -F "/" '{print $(NF-1)" "$(NF)}'

rm $timesF
