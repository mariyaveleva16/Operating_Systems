#!/bin/bash
i=1
while [ $i -le $# ]
do 
	file=$(echo "${@:$i:1}")
	isSOA=$(head -n 1 $file| awk '($3=="IN" && $4=="SOA")||($2=="IN" && $3=="SOA") {print $0}'|wc -l)
	if [ $isSOA -ne 1 ];then
		echo "File $file doesn't have SOA type on it's first line"
	else
		isMultiline=$(head -n 1 $file| grep "("|wc -l)

		if [ $isMultiline -eq 1 ];then #mnogoredov
			serial=$(head -n 2 $file|tail -n 1|cut -d ";" -f1|tr "\t" " "| tr -s " "|sed 's/^ //g'|sed 's/ $//g')
		else
			serial=$(head -n 1 $file| awk '{print $(NF-4)}')
		fi

		data=$(echo "$serial"| cut -c 1-8)
		today=$(date +"%Y%m%d")

		if [ $data -lt $today ];then
			sed -i 's/'$serial'/'$today'00/' $file
		elif [ $data -eq $today ];then
			newSerial=$(echo "$(($serial+1))")
			sed -i 's/'$serial'/'$newSerial'/' $file
		else 
			echo "The day in file $file is in the future :D"
		fi
	fi
	i=$((i+1))
done
