# 7 - average of n numbers

echo "Enter 'n':"
read n

for ((i=1;i<=n;i++))
do
    echo "Enter number $i:"
    read number
    ((sum+=number))
done

((avg=sum/n))

echo "The average is $avg"