#!/usr/bin/bash
# 2 - to find largest of the three

echo "Enter the three numbers : "
read a
read b
read c

if ((a>b))
then
    if ((a>c))
    then
        echo "$a is the largest"
    else
        echo "$c is the largest"
    fi
else
    if ((b>c))
    then
        echo "$b is the largest"
    else
        echo "$c is the largest"
    fi
fi