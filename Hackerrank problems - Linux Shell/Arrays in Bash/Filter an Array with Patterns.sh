arr=()
while read i; do
  arr+=("$i")
done </dev/stdin

declare -a pattern=( ${arr[@]/*a*/} )
echo ${pattern[@]
