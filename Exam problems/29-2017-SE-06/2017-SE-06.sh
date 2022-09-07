#!/bin/bash

if [ $(id -un) != "s62445" ];then
	echo "Wr user"
	exit 1
fi

match=$(mktemp)
while read line
do 
	dires=$(echo "$line"|cut -d ":" -f6)
	user=$(echo "$line"|cut -d ":" -f1)
	if [ ! -d $echo "$dires" ];then
		echo "$user" >> $match
	else
		dirOwner=$(stat "${dires}" --printf "%u\n")
		curUser=$(id -u $user)
		if [ "$dirOwner" != "$curUser" ];then
			echo "$user" >> $match
		fi
		perm=$(stat "${dires}" --printf "%A\n")
		if [ $(echo $perm|cut -c 3) != "w" ];then
			echo "$user" >> $match
		fi
	fi
done < /etc/passwd
cat $match

rootRss=$(ps -e --no-header -o user,pid,rss|awk '$1=="root" {print $0}'|awk -F " " 'BEGIN{t=0}{t+=$3}; END {print t}')
echo  "$rootRss"

while read line
do 
	userRss="$(ps -e --no-header -o user,rss|grep "$line"|awk 'BEGIN{r=0}{r+=$2}; END {print r}')"
	if [ $userRss -gt $rootRss ];then
		echo "$(ps -e --no-header -o user,pid|grep "$line"|awk '{print $NF}')"
	fi
done <$match
rm $match
