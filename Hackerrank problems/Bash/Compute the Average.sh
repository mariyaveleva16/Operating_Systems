read N
a=0
sum=0

while [ $a -lt $N ] 
do
    read c
    sum=$((sum+c))
    a=$((a+1))
done

echo "$sum/$N"|bc -l |xargs printf "%.3f"
