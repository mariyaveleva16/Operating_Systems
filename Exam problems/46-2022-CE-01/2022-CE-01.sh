#!/bin/bash

if [ $# -ne 3 ];then
	echo "Wrong number of param"
	exit 1
fi

base=base.csv
prefix=prefix.csv

multp=$(cat $prefix|awk -F "," '$2=="'$2'" {print $3}')

suf=$(cat $base|awk -F "," '$2=="'$3'" {print $2}')

brackets=$(cat $base|awk -F "," '$2=="'$3'" {print "("$3" ,"$1")"}')

result=$(echo "$1*$multp"|bc -l)

echo "$result $suf $brackets"
