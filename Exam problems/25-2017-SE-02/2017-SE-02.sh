#!/bin/bash

if [ $# -ne 3 ];then
	echo "Wrong n of p";
	exit 1;
fi

if [ ! -d $1 ];then
	echo "$1 not a directory";
	exit 1;
fi

if [ "$1" != "src" ];then
	echo "$1 should be src"
	exit 1;
fi

if [ ! -d $2 ];then
	echo "$2 in not a directory";
	exit 1;
fi

if [ "$2" != "dst" ];then
	echo "$2 should be dst";
	exit 1;
fi

dstFiles=$(find $2 -mindepth 1|wc -l)

if [ $dstFiles -ne 0 ];then
	echo "dst has files"
	exit 1
fi

for line in $(find $1 -name "*$3*")
do 
	dirs=$(echo "$line"|cut -d "/" -f2-|awk -F "/" '{$NF=""}1' OFS='/')
	mkdir -p $2/$dirs && mv $line $_
done
