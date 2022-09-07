#!/bin/bash

if [ $# -ne 1 ];then
	echo "Wrong par"
	exit 
fi

if [ ! -f $1 ];then
	echo "$1 not exist"
	exit 1
fi
output=$(mktemp)
cut -d " " -f4- $1|sort>$output
i=1;
while read line
do echo "$i. $line"
	i=$((i+1))
done<$output

rm $output
