#!/bin/bash


if [ "$#" -ne 2 ]
then
#	echo "no args"
	exit 1
fi
if [ ! -d "$1" ]
then
#	echo "no dir"
	exit 1
fi
filesdir="$1"
searchstr="$2"
#echo "printallarfs $1 $2"
X=$( find $filesdir -type f | wc -l )
Y=$( grep -r $searchstr $filesdir |wc -l )
echo "The number of files are $X and the number of matching lines are $Y"
exit 0
