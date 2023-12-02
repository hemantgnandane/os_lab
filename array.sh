#!/bin/bash

declare -a my_array

echo "Enter elements for the array (Ctrl+D to stop): "

while IFS= read -r element; 
do
    my_array+=("$element")
done

echo "Elements in the array:"
for element in "${my_array[@]}"; 
do
    echo -n "$element "
done
