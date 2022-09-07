#!/bin/bash

if [ $# -ne 2 ];then
	echo "Wr p"
	exit 1
fi

if [ ! -d $1 ];then 
	echo "Not d"
	exit 2
fi

if [ -e $2 ];then
	echo "$2 exists"
	exit 3
fi


files=$(mktemp)
files2=$(mktemp)
albums=$(mktemp)
titles=$(mktemp)
data=$(mktemp)

find $1 -name '*.jpg' -printf "%P \n"| tr -s " "|sed 's/)/(/g'|sort>> $files
find $1 -name '*.jpg' -printf "%P:%Ty-%Tm-%Td\n"| tr -s " "|sort>> $files2

while read line
do
	isAlbum=$(echo "$line"|egrep "\(" |wc -l)
	if [ $isAlbum -eq 1 ];then
		echo "$(echo $line|awk -F "(" '{print $(NF-1)}')"|tr -s " ">> $albums
	else 
		echo "misc" >> $albums
	fi

done < $files

while read line
do
	echo "$line"|cut -d ":" -f1|sed -e 's/([^()]*)//g'|tr -s " "|sed 's/ \././g'| sed 's/^ //g' >> $titles
	echo "$line"|cut -d ":" -f2 >> $data
	#shaSum=$(sha256 $line)
	#cp $line DST/$shaSum.jpg
	#
done <$files2

cat $albums
cat $titles
cat $data
rm $albums
rm $files
rm $files2
rm $titles
rm $data
