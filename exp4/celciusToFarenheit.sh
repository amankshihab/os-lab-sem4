# read -p "Enter degree celsius temperature: " celsius
# fahrenheit=`echo "scale=4; $celsius*1.8 + 32" | bc`
# echo "$celsius degree celsius is equal to $fahrenheit degree fahrenheit"

# echo "Enter the temparature in celcius:"
# read celcius

# fahrenheit = `echo "$celcius*1.8 + 32" | bc`

# echo $fahrenheit

echo "Enter temp in celcius:"
read celcius

echo "$celcius*1.8 + 32" | bc