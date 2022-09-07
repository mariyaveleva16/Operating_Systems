#!/bin/bash

if [ $# -ne 2 ];then
	exit 1
fi

if [ ! -d $1 ];then
	exit 2
fi

if [ ! -d $2 ];then
	exit 3
fi

file=$(mktemp)
find $1 -type f \( ! -iname "*.swp" \)>>$file
while read line;do
dirs=$(echo "$line"|cut -d "/" -f2-|awk -F "/" '{$NF=""}1' OFS='/')
mkdir -p $2/$dirs && mv $line $_
done < $file

rm $file
