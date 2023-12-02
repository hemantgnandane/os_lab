#!/bin/bash

read -p 'Enter a : ' a
read -p 'Enter b : ' b

if(( $a==$b ))
then
	echo a is equal to b.
else
    if(( $a!=$b ))
    then
	    echo a is not equal to b.
    else
    	echo a is equal to b.
    fi

    if(( $a<$b ))
    then
        echo a is less than b.
    fi

    if(( $a>$b ))
    then
        echo a is greater than b.
    fi
fi



