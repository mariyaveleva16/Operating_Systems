#!/bin/bash
reg='^[0-9]+$';
if [[ $# -lt 1 ]];then
	echo "Less then 1 param";
	exit 1;
elif [[ ! -d $1 ]];then
	echo "Not a diractory";
	exit 1;
elif [[ ! $# -eq 2 ]];then 
	find -L $1 -type l;
	exit 0;
elif [[ ! $2 =~ $reg ]];then
	echo "Not number";
	exit 1;	
fi

find $1 -printf "%n %f\n"|awk '$1>='$2' {print $2}'
