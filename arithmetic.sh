#!/bin/bash
echo "Enter two number"
read n1 n2
result=$(expr $n1+$n2 | bc)
#res=$[$n1+$n2]
#echo $res
echo "$result"
#ress=$(expr $n1 + $n2)
#echo $ress
