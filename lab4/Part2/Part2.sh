#!/bin/bash

MAINFILES=""
MODFILES=""
OTHERFILES=""
for FILE in $(find $1 -name "*.c"); do
    if grep -wq "int main" $FILE; then
        MAINFILES="$MAINFILES$FILE:$(cat $FILE | grep printf | wc -l),$(cat $FILE | grep fprintf | wc -l)\n"
    elif grep -wq "init_module" $FILE; then
        MODFILES="$MODILES$FILE:$(grep -n "printk" $FILE | sed -e 's/:.*//' | tr '\n' ',')\n"
    else
        OTHERFILES="#OTHERFILES$FILE\n"
    fi
if test -z $MAINFILES; then
    MAINFILES="No main files"
fi
if test -z $MODFILES; then
    MODFILES="No module files"
fi
if test -z $OTHERFILES; then
    OTHERFILES="No other files"
fi
echo -e "Main Files:\n$MAINFILES Module Files:\n$MODFILES Other Files:\n$OTHERFILES"
