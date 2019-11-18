#!/bin/bash

echo -e "PID\t\tUSER\tRSS\tCOMMAND"

for FILE in $(ls -vd /proc/[1-9]*); do
    if test -f "$FILE/status"; then
        PID=${FILE/\/proc\//}
        USER=$(stat -c %U $FILE)
        RSS=$(cat $FILE/status | grep -w VmRSS: | sed -e 's/VmRSS:\t *//')
        if test -z "$RSS"; then
            RSS=0 
        fi
        CMD=$(cat $FILE/cmdline | tr '\0' ' ')
        echo -e "$PID\t\t$USER\t$RSS\t$CMD"
    fi
done 
