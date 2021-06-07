while ((1))
do
echo "Options:"
echo "1. Area of circle"
echo "2. Circumference of circle"
echo "3. Area of rectangle"
echo "4. Area of square"
echo "5. Exit"
echo "Enter your choice : "
read option

if ((option==1))
then
    echo "Enter the radius : "
    read radius
    
    echo "$radius*3.14"|bc

elif ((option==2))
then
    echo "Enter the radius : "
    read radius
    
    echo "$radius*3.14*$radius"|bc
elif ((option==3))
then 
    echo "Enter the length : "
    read length
    
    echo "Enter the breadth : "
    read breadth

    echo "$length*$breadth"|bc
elif ((option==4))
then
    echo "Enter the edge length : "
    read edge

    echo "$edge*$edge."|bc
else
    exit 0
fi
done