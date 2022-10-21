while read a
do
echo $a|tr "()" "[]"
done <"${1:-/dev/stdin}"
