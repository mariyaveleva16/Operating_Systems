#!/bin/bash

if [ $# -ne 2 ]; then
	exit 1;
fi

if [ ! -f $1 ]; then
	exit 2;
fi

if [ -f $2 ]; then
	echo""
#	exit 3
fi

#touch $2;
from=$1;
to=$2;

cat $from | sort -t',' -k2 -k1,1n | while read line; do
	columns=$(echo $line | cut -d',' -f2-)
	if [ "$columns" != "$prev" ]; then
		echo "$line" >> $to;
		prev="$columns"	
	fi

done
