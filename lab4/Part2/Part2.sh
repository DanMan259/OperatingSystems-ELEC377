#!/bin/bash

MAINFILES=""
MODFILES=""
OTHERFILES=""
for FILE in $(find $1 -type f -name "*.c"); do
    FILE=`readlink -f $FILE`
    if grep -wq "[i,n,t,v,o,i,d]* main" $FILE; then
        MAINFILES="$MAINFILES$FILE:$(cat $FILE | grep -w printf | wc -l),$(cat $FILE | grep -w fprintf | wc -l)\n"
    elif grep -wq "init_module" $FILE; then
        MODFILES="$MODFILES$FILE:$(grep -wn "printk" $FILE | sed -e 's/:.*//' | tr '\n' ',' | sed -e 's/,$//')\n"
    else
        OTHERFILES="$OTHERFILES$FILE\n"
    fi
done
if test -z $MAINFILES; then
    MAINFILES="No main files\n"
fi
if test -z $MODFILES; then
    MODFILES="No module files\n"
fi
if test -z $OTHERFILES; then
    OTHERFILES="No other files\n"
fi
echo -e "Main Files:\n"$MAINFILES"\nModule Files:\n"$MODFILES"\nOther Files:\n$OTHERFILES"
