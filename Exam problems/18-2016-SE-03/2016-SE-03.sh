#!/bin/bash

if [ $# -ne 2 ];then
	echo "Wrong nuber of param."
	exit 1;
fi

reg='^[0-9]+$';

if [[ ! $1 =~ $reg ]] || [[ ! $2 =~ $reg ]];then
	echo "$1 and $2 should be numbers";
	exit 1;
fi
mkdir a;
mkdir b;
mkdir c;
files=$(mktemp)
find ./ -mindepth 1 -maxdepth 1 -type f|cut -c 3->>$files;

while read line;
do 
	nmLines=$(cat $line|wc -l);
	if [ $nmLines -lt $1 ];then
		mv ./$line a/$line
	elif [ $nmLines -lt $2 ];then
		mv ./$line b/$line 
	else 
		mv ./$line c/$line
	fi
done<$files
rm $files
