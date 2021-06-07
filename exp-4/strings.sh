# echo "Enter the names:"

# for ((i=0;i<3;i++))
# do
#     read names
#     echo $names
# done | sort

# reading command line args

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
    fi
done
echo "$a $b $c"