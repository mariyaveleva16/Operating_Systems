#!/bin/bash

if [ $# -ne 2 ];then
	echo "Wr p"
	exit 1
fi

if [ ! -d $2 ];then
	echo "$2 not dir"
	exit 2
fi

if [ $(find $2|wc -l) -eq 1 ];then
	echo "$2 is empty"
	exit 3
fi

touch $1

echo "hostname,phy,vlans,hosts,failover,VPN-3DES-AES,peers,VLAN Trunk Ports,license,SN,key" >$1

find $2 -type f -name '*\.log'|while read file;do
	count=1
	l=$(mktemp)
	while read line
	do
		if [ $count -ne 9 ] && [ $count -ne 1 ];then
			echo "$(echo $line|tr -s " "|cut -d ":" -f2|sed 's/^ //g')">>$l
		else 
			if [ $count -eq 9 ];then 
				echo "$(echo $line|tr -s " "|cut -d " " -f5- | awk -F " " '{$NF=""}1')">>$l
			fi
		fi
		count=$((count+1))
	done < $file
	cat $l| tr "\n" ','|sed 's/^,//g'|sed 's/,$//g'|sed 's/ ,/,/g'>> $1
	echo "">> $1
	rm $l
done
