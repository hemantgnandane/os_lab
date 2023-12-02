
#!/bin/bash

echo "Enter a key"
read key
case "$key" in
[a-z]) echo "$key is a lower case alphabet.";;
[A-Z]) echo "$key is an upper case alphabet.";;
[0-9]) echo "$key is a number.";;
*) echo "$key is a punctuation";;

esac