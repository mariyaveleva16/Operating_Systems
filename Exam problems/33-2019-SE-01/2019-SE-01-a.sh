#!/bin/bash

numbers=$(mktemp)
positive=$(mktemp)
while read line
do 
	egrep -x '\-?[[:digit:]]+' >> $numbers
done

while read line
do
	echo "$( echo $line|cut -d "-" -f2)" >> $positive
done < $numbers

biggest=$(cat $positive|sort -n|tail -n 1)
echo "Numbers"
cat $numers
grep "$biggest" $numbers
rm $numbers
rm $positive
