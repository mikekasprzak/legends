#!/bin/sh
# maketool.sh - Simple Shell Script that compiles a tool for the current platform #

SCRIPT=`readlink -f "$0"`

SCRIPT_DIR=`dirname "$SCRIPT"`
SCRIPT_BASE=`basename "$SCRIPT" .sh`
SCRIPT_FILE=`basename "$SCRIPT"`

if [ "$1" == "" ]; then
	echo "USAGE: $SCRIPT_FILE ToolName"
	exit 1
fi

ROOT_NAME=../bin/"$1"

ARCH=`uname -m`
SUBARCH=`uname -i`

if [ "$WINDIR" != "" ]; then
	EXE="$ROOT_NAME".exe
else
if [ "$SUBARCH" != "unknown" ]; then
	EXE="$ROOT_NAME"_"$ARCH"_"$SUBARCH"
else
	EXE="$ROOT_NAME"_"$ARCH"
fi
fi

# src, GEL and gel, since some file systems don't support upper case dirs #
INCLUDES="-I../../src -I../../src/GEL -I../../src/gel"

g++ $INCLUDES "$1"/"$1".cpp -O3 -o "$EXE"

exit $?
