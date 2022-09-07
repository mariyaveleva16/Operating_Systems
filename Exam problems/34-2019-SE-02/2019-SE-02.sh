#!/bin/bash

if [ "$1" == "-n" ];then
	files=$(($#-2))
	N=$2
	
else 
	files=$#
	N=10
	i=1
fi
i=1
summary=$(mktemp)
while (($i <= $files))
do
	if [ "$1" == "-n" ];then
		file=$(echo "${@:$i+2:1}")
	else
		file=$(echo "${@:$i:1}")
	fi
	while read line
	do
		time=$(echo "$line"|cut -d " " -f1,2)
		data=$(echo "$line"|cut -d " " -f3-)
		echo "$time $file $data" >> $summary
	done < $file
	i=$((i+1))
done

cat $summary|sort -n|head -n $N
rm $summary
