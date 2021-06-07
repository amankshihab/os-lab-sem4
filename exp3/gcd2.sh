a=$1
b=$2

while ((b!=0))
do
	((c=b))
	((b=a%b))
	((a=c))
done

echo $a
