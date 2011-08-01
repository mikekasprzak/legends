#!/bin/sh

if [ "$WINDIR" != "" ]; then
	ARGS=vs2008
else
	ARGS=xcode4
fi

if [ "$1" != "" ]; then
	ARGS=$@
fi

../../Tools/External/premake4.sh --file=msvc-proj.lua $ARGS

exit $?
