#!/bin/bash
# EchoEach.sh - Echo's each argument on a separate line

if [ ! -n "$1" ]
then
  echo "Usage: `basename $0` argument1 argument2 etc."
  exit 1
fi  


for arg in "$@"
do
	echo "$arg"
done

exit 0
