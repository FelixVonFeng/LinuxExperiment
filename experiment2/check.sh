#!/bin/bash
NAME=$1
if [ "$NAME" = "" ]
then 
	echo "usage:prog name"
	exit
fi
for user in $(cut -d : -f 1 /etc/passwd)
do
	if [ "$user" = "$NAME" ]
	then
		echo found $NAME in /etc/passwd
		break
	fi
done

if [ "$user" != "$NAME" ]
then
	echo user $NAME is not in system
fi
