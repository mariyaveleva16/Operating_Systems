#!/bin/bash

if [ $# -ne 2 ];then
	echo "Wrong"
	exit 1
fi

if [ ! -d $1 ];then
	echo "Not dir"
	exit 1
fi

find $1 -mindepth 1 -maxdepth 1 -type f|egrep "$1/vmlinuz-[[:digit:]]+\.[[:digit:]]+\.[[:digit:]]+-$2"|sort -V|tail -n 1
