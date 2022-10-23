arr=()
while read i; do
  arr+=("$i")
done </dev/stdin

echo ${arr[@]:3:5}
