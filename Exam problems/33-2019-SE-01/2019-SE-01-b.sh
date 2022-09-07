#!/bin/bash

numbers=$(mktemp)
positive=$(mktemp)
numSums=$(mktemp)
while read line
do 
	egrep -x '\-?[[:digit:]]*' >> $numbers
done

while read line
do
	echo "$( echo $line|cut -d "-" -f2)" >> $positive
done < $numbers

while read line
do
	num=$(echo "$line")
	sum=0
	while [ $num -gt 0 ]
	do
		mod=$(($num % 10 ))
		num=$(($num / 10 ))
		sum=$(( $sum + $mod )) 
	done
	echo "$line $sum" >> $numSums
done < $positive

biggestSum=$(cat $numSums|sort -t " " -k2,2n|tail -n 1|cut -d " " -f1)
egrep '\-?'$biggest'' $numbers|sort -n |head -n 1
rm $numbers
rm $positive
rm $numSums
