#!/bin/bash
declare -i score
echo "please input score"
read score
while [ "$score" != -1 ]
do
	score="$score"/10
	case $score in
		9)
			echo "very good"
			;;
		8)
			echo "good"
			;;
		7)		
			echo "no good"
			;;
		6) 
			echo "no bad"
			;;
		*) 	
			echo "bad"
	esac
	echo "please input next score"
	read score
done
	echo "script exiting ..."		




