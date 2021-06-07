# 5 - operations on files

DIR="/home/amanks/S4-Lab/os-lab/exp-4/bash"

if [[ -d "$DIR" ]]
then
    echo "Directory exists"
else
    echo "Creating directory"
    mkdir bash
    echo "Directory created"
fi

ls