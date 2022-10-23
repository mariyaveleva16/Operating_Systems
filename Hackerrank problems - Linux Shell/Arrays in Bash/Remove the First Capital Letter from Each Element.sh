# https://tldp.org/LDP/abs/html/arrays.html

arr=()

while read i;do
    arr+=("$i")
done </dev/stdin

echo ${arr[@]/[A-Z]/.}
