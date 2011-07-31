#!/bin/sh
# FileExists.sh - Does a file exist or not?  Echos if it does. 

if [ ! -e "$1" ]; then
	exit 1
fi

echo $1

exit 0
