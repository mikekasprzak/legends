#!/bin/bash
# Zenity.sh - Wrapper for Zenity.  If not installed, ignore.

command=zenity

command_exists () {
	type "$1" &> /dev/null ;
}

if command_exists $command
then
	$command $@
	exit $?
else
	echo "Warning: $command not found, ignoring..." 1>&2
fi
exit 0
