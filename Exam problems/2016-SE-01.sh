echo Броят на търсените редове е $(cat 2016-SE-01.txt|gerp [02468]|grep -v [a-w]|wc -l)
