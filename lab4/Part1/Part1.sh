#!/bin/bash


echo "PID\t\tUSER\t\tRSS\t\tCOMMAND"

for FILE in $(ls -vd /proc/[1-9]*); do
	echo $FILE
done
