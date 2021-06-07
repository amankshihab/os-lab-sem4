while ((1))
do
echo "Options:"
echo "1. Addition"
echo "2. Subraction"
echo "3. Multiplication"
echo "4. Division"
echo "5. Modulus"
echo "6. Exit"
echo "Enter your choice : "
read option

echo "Enter the numbers : "
read a
read b

if ((option==1))
then
    echo "$a+$b" | bc
elif ((option==2))
then
    echo "$a-$b" | bc
elif ((option==3))
then
    echo "$a*$b" | bc
elif ((option==4))
then
    echo "$a/$b" | bc
elif ((option==5))
then
    echo "$a%$b" | bc
else
    exit 0
fi
done