#!/bin/sh

SCRIPT=`readlink -f "$0"`

SCRIPT_DIR=`dirname "$SCRIPT"`
SCRIPT_FILE=`basename "$SCRIPT" .sh`

ROOT_NAME="$SCRIPT_DIR"/bin/"$SCRIPT_FILE"

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
echo $EXE
$EXE $@

exit $?
