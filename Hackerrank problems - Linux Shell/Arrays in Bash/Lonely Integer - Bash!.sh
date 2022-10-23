read n
read a
arr=($a)

echo "${arr[@]}"| tr " " "\n"|sort|uniq -c| sed 's/^ *//g'|awk '{if($1==1) print $2}'
