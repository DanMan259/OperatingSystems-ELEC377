#!/bin/bash

# print banner to console
echo -e "PID\tUSER\tRSS\tCOMMAND"

# only loop through files in proc directory that consist of digits only
for FILE in $(ls -vd /proc/[1-9]*); do
    # if process has a 'status' directory in it
    if test -f "$FILE/status"; then
        # get PID for proc
        PID=${FILE/\/proc\//}
        # get user using the stat command
        USER=$(stat -c %U $FILE)
        # get RSS value and remove 'VmRSS' and 'kB'
        RSS=$(grep -w VmRSS: $FILE/status | sed -e 's/VmRSS:\t *//'| sed -e 's/ [kK]B//')
        # check if RSS is empty
        if test -z "$RSS"; then
            RSS=0 
        fi
        # get command from 'cmdline' in proc
        CMD=$(cat $FILE/cmdline | tr '\0' ' ')
        if test -z "$CMD"; then
            CMD = "[$(grep 'Name' $FILE/'status' | sed -e 's/.*\t *//')]"
        fi
        echo -e "$PID\t$USER\t$RSS\t$CMD"
    fi
done 
