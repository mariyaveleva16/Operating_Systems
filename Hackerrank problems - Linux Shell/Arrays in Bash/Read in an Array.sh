arr=()
while read i; do
  arr+=("$i")
done </dev/stdin

echo ${arr[@]}
