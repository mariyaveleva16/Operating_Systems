#!/bin/bash

if [ $# -lt 1 ];then
	echo "At least one arg"
	exit 1
fi

if [ $# -gt 2 ];then
	echo "Max 2 arg"
	exit 1
fi

if [ ! -d $1 ];then
	echo "$1 not dir"
	exit 1
fi

broken=$(mktemp)
find -L $1 -type l >$broken

allS=$(mktemp)
find $1 -type l > $allS

while read line
do	
	isLine=$(grep "$line" $broken|wc -l)
	if [ $isLine -eq 0 ];then
		link=$(echo "$line"|awk -F "/" '{print $NF}')
		if [ $# -eq 2 ];then
			echo "$link -> $(readlink $line)" >> $2
		else 
			echo "$link -> $(readlink $line)"
		fi
	fi
	
done < $allS
if [ $# -eq 2 ];then
	cat $broken|wc -l >> $2
else 
	echo "$(cat $broken|wc -l)"
fi
rm $allS
rm $broken
