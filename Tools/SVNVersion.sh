#!/bin/bash
# SVNVersion.sh - Returns the SVN Version of a file, otherwise 0

if [ ! -n "$1" ]
then
  echo "Usage: `basename $0` argument1 argument2 etc."
  exit 1
fi  


for arg in "$@"
do
	VAR=$(svn info $arg 2>/dev/null | grep "Last Changed Rev:" | sed s/"Last Changed Rev: "//)

	if [ -n "$VAR" ]
	then
		echo "$VAR"
	else
		echo "0"
	fi
done

exit 0
