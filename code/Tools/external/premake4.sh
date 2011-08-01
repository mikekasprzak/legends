#!/bin/sh

SCRIPT=`readlink -f "$0"`

SCRIPT_DIR=`dirname "$SCRIPT"`
SCRIPT_FILE=`basename "$SCRIPT" .sh`

#echo ">>$SCRIPT"
#echo ">>$SCRIPT_DIR"
#echo ">>$SCRIPT_FILE"

ROOT_NAME="$SCRIPT_DIR"/bin/"$SCRIPT_FILE"

ARCH=`uname -m`
SUBARCH=`uname -i`

if [ "$WINDIR" != "" ]; then
	EXE="$SCRIPT_DIR"/win/"$SCRIPT_FILE".exe
else
#if [ "$SUBARCH" != "unknown" ]; then
#	EXE="nix/$ROOT_NAME"_"$ARCH"_"$SUBARCH"
#	if [ ! -e $EXE ]; then
#		EXE="nix/$ROOT_NAME"."$ARCH"
#	fi
#else
	EXE="$SCRIPT_DIR"/nix/"$SCRIPT_FILE"
#	EXE="$SCRIPT_DIR"/nix/"$SCRIPT_FILE"."$ARCH"
#	EXE="$ROOT_NAME"."$ARCH"
#fi
fi

#echo $EXE
$EXE $@

exit $?
