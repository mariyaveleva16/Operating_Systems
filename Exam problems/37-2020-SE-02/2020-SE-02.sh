#!/bin/bash

if [ $# -ne 1 ];then
	echo "wr p"
	exit 1
fi

if [ ! -f $1 ];then
	echo "$1 not exist"
	exit 2
fi
sites=$(mktemp)
cat $1|cut -d " " -f2|sort|uniq -c|tr -s " "|sort -nr -t " " -k2,2|head -n 3|cut -d " " -f3 >> $sites
users=$(mktemp)
while read site
do
	all=$(cat $1| awk -F " " '$2=="'$site'" {print $0}'|wc -l)
	w2=$(cat $1| awk -F " " '$2=="'$site'" && $8=="HTTP/2.0" {print $0}'|wc -l)
	non=$(($all-$w2))
	cat $1| awk -F " " '$2=="'$site'" && $9>302 {print $1}' >> $users 
	echo "$site HTTP/2.0: $w2 non-HTTP/2.0: $non"

done < $sites

cat $users|sort|uniq -c|tr -s " "| sort -nr -t " " -k2,2|head -n 5

rm $users
rm $sites
