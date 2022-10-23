arr=()
while read i; do
  arr+=("$i")
done </dev/stdin

for i in ${!arr[@]}; do
    if [[ $i -le 7 && $i -ge 3 ]];then
        echo -n "${arr[$i]} "
    fi
done
