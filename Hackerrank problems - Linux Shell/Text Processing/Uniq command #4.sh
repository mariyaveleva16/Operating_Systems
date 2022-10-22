a=$(</dev/stdin)

echo "$a"|uniq -c|sed 's/ *//'|awk -F " " '{if ($1==1) print}'|cut -d " " -f2-
