read -p "Enter a symbol: " a 
for((i=0;i<5;i++))
do
    for((j=0;j<i;j++))
    do
        echo -n "$a"
    done
    echo
done