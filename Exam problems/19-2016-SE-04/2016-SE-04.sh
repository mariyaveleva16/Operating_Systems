#!/bin/bash

if [ $# -ne 2 ];then
	echo "Wrong param"
	exit 1
fi

if [ ! -f $1 ];then
	echo "file $1 doesn't exsit"
	exit 1
fi

if [ ! -f $2 ];then
	echo "file $2 doesn't exist"
	exit 1
fi

lines1=$(grep "$1" $1|wc -l)
lines2=$(grep "$2" $2|wc -l)

if [ $lines1 -gt $lines2 ];then
	file="$1"
else 
	file="$2"
fi 

cut -d '-' -f2- $file|cut -d " " -f2-|sort>$file.songs
