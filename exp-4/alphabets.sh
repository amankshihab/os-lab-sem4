# echo "Enter the alphabets:"

# for ((i=0;i<3;i++))
# do
#     read alphabets
#     echo $alphabets
# done | sort

a=$1
b=$2
c=$3

for ((i=0;i<3;i++))
do 
    if [[ $a>$b ]]
    then
        if [[ $a>$c ]]
        then
            temp=$a
            a=$c
            c=$temp
        else
            temp=$a
            a=$b
            b=$temp
        fi
    else
        if [[ $b>$c ]]
        then
            temp=$b
            b=$c
            c=$temp
        fi
    fi
done

echo " Sorted : $a $b $c"