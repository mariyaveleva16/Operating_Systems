#!/bin/bash

if [ "$#" -ne 1 ]; then
	echo "Wrong numer of parameters.\n";
	exit 1;
fi

if [ ! -d "$1" ];then
	echo "Not directory.\n";
	exit 1;
fi

find -L $1 -type l
