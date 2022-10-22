a=$(</dev/stdin)

echo "$a"|uniq -c|sed 's/^ *//' 
