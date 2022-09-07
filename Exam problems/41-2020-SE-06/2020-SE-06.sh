#!/bin/bash

if [ $# -ne 3 ];then
	echo "Wr p"
	exit 1
fi

if [ ! -f $1 ];then
   	echo "$1 not file"
	exit 2  
fi

reg='^[a-zA-Z0-9_]+$'
key=$2
value=$3

if [[ ! "$key" =~ $reg ]];then
	echo "$2 wr format"
	exit 3
fi

if [[ ! "$value" =~ $reg ]];then
	echo "$3 wr format"
	exit 4
fi

data=$(date)
user=$(whoami)

isThere=$(cat $1|tr -s " "| sed 's/ = /=/g'|grep "^$key="|wc -l)

if [ $isThere -eq 1 ];then
	cat $1|tr -s " "| sed 's/ = /=/g'| grep "^$key="|sed -i -e 's/^/#/'| sed 's/$/ # added at /'
	
else 
	echo "$key = $value # added at $data by $user" >> $1
fi
