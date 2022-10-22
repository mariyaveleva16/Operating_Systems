a=$(</dev/stdin)
echo "$a"|uniq -c -i|sed 's/^ *//'
