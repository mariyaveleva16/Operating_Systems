#!/bin/bash

if [ $(id -un) != "s62445" ];then
	echo "Not root"
	exit 1
fi
ps -e --no-header -o user,rss,pid | sort |awk 'BEGIN{U=""; R=$2; i=0}{
	if (U!=$1){
		print "user:" $1 " rss: " R " count: " C 
		if ( C > 0 && biggest >R/C) print "kill process with pid  " pid
		U=$1;
		R=$2;
		C=1;
		biggest=R;
		pid=$3;
	}
	else{
		R+=$2;
		C++;
		biggest=R;
		pid=$3;
	}
		
}'
