#!/bin/bash

echo -e "PID\t\tUSER\tRSS\tCOMMAND" > test1.txt

for FILE in $(ls -vd /proc/[1-9]*); do
    if test -f "$FILE/status"; then
        echo $FILE
        cat $FILE/status | grep -w Pid: >> test1.txt
        sed -i 's/Pid:\t//' test1.txt
        tr -t -s-1 test1.txt
        echo -ne "\t\t$(stat -c %U $FILE)\t" >> test1.txt
        cat $FILE/status | grep -w VmRSS: >> test1.txt
        sed -i 's/VmRSS:\t//' test1.txt
        tr -t -s-4 test1.txt
        echo -e "\t$(cat $FILE/cmdline)" >> test1.txt
    fi
done 

cat test1.txt
