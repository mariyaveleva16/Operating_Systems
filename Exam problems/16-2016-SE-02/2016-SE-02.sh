#!/bin/bash

if [ "$#" -ne 1 ];then 
	echo "Wrong number ot param";
	exit 1;
fi
num=$1;
re='^[0-9]+$';
if [[ ! $1 =~ $re ]];then
	echo "Not a number";
	exit 1;
fi

if [[ $(id -u) -eq 0 ]];then
	echo "Not root";
	exit 1;
fi

ps -e --no-header -o user,rss,pid | sort -r -n | awk '{
	if($1==prev){
		sum+=$2;
		biggest=$3;
	}
	else{
		printf prev" : "sum"\n"
		if ( biggest>'$num'){
			printf "and we must kill process with pid "biggest"\n"
	}
	
	sum=$2;
	prev=$1;
	biggest=$3;
	}
   
}'
