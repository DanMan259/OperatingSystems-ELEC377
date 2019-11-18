#!/bin/bash

# initialize variables
MAINFILES=""
MODFILES=""
OTHERFILES=""

# loop through files ending with '.c' extention using '-name' flag
for FILE in $(find $1 -type f -name "*.c"); do
    FILE=`readlink -f $FILE`
    # search for main method (can be void or int)
    if grep -wq "[i,n,t,v,o,i,d]* main" $FILE; then
        # add directory path, # of printf, # of fprintf to MAINFILES using cat pipe grep
        MAINFILES="$MAINFILES$FILE:$(cat $FILE | grep -w printf | wc -l),$(cat $FILE | grep -w fprintf | wc -l)\n"
    elif grep -wq "init_module" $FILE; then
        # add directory path, line # of all printk to MODFILES using grep pipe sed
        MODFILES="$MODFILES$FILE:$(grep -wn "printk" $FILE | sed -e 's/:.*//' | tr '\n' ',' | sed -e 's/,$//')\n"
    else
        # add directory path to OTHERFILES
        OTHERFILES="$OTHERFILES$FILE\n"
    fi
done

# fallback procedures, print 'No File' if no files are found for a source file type
if test -z $MAINFILES; then
    MAINFILES="No main files\n"
fi
if test -z $MODFILES; then
    MODFILES="No module files\n"
fi
if test -z $OTHERFILES; then
    OTHERFILES="No other files\n"
fi

# final print statement
echo -e "Main Files:\n"$MAINFILES"\nModule Files:\n"$MODFILES"\nOther Files:\n$OTHERFILES"
