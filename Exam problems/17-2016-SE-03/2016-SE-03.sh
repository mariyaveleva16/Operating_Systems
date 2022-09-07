#!/bin/bash

if [ $# -ne 0 ];then
	echo "Wrong number of arg."
	exit 1
fi

if [ $(id -u) -eq 0 ];then
	echo "Must be root";
fi
result=$(mktemp);
while read line; do
	homedir=$(echo $line| cut -d ":" -f6);
	user=$(echo $line|cut -d ":" -f1);
	#echo "$user :$homedir";
	if [ ! -d $homedir ];then 
		echo $user>>$result;
	else 
		perm=$(stat "${homedir}" --printf "%A\n");
		dirowner=$(stat "${homedir}" --printf "%u\n");
		curUser=$(id -u $user);
		dirgroup=$(stat "${homedir}" --printf "%g\n");
		group=$(mktemp);
		hasperm=0;
		id -G $user|tr ' ' "\n" >>$group
		
		if [ "$dirowner" == "$curUser" ];then
			if [ $(echo $perm|cut -c 3) != 'w' ];then
				echo $user>>$result;
			else 
			   hasperm=1;
			fi	   
		elif [ $(cat $group| grep "$dirgroup"|wc -l) -gt 0 ];then
			if [ $(echo $perm|cut -c 6) != 'w' ];then
				echo $user>>$result;
			else
				hasperm=1;
			fi
		elif [ $hasperm -eq 0 ] && [ "$(echo $perm|cut -c 9)" != 'w' ];then
			echo $user>>$result;		   	
		fi
		rm $group
	fi
done</etc/passwd

cat $result
rm $result
