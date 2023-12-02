#pattern printing

#!/bin/bash

read -p "Enter any Punctuation : " a

for ((i=1 ; i<=5; i++));
do
    for ((j=1; j<=i; j++));
    do
    echo -n "$a "
    done
    echo 
done 
