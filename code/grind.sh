#!/bin/sh
# grind.sh - Valgrind the currently built game

CONFIGDIR=Config
OUTPUTDIR=output

# Are we running Windows? #
if [ "$WINDIR" != "" ]; then
	SYSTEM_SUFFIX=
	EXT=exe
else
	SYSTEM_SUFFIX=_`uname -s`
	EXT=`uname -m`
fi


if [ ! -e "$CONFIGDIR/.project" ]; then
	echo "ERROR: File \".project\" does not exist!  Please run \"setup.sh\" to generate."
	exit 1
fi

if [ ! -e "$CONFIGDIR/.sku" ]; then
	echo "ERROR: File \".sku\" does not exist!  Please run \"setup.sh\" to generate."
	exit 1
fi

if [ ! -e "$CONFIGDIR/.target$SYSTEM_SUFFIX" ]; then
	echo "ERROR: File \".target$SYSTEM_SUFFIX\" does not exist!  Please run \"setup.sh\" to generate."
	exit 1
fi

PROJECT=`cat $CONFIGDIR/.project`
if [ "$WINDIR" != "" ]; then
	EXT=exe
else
	EXT=`uname -m`
fi

SKU=`cat $CONFIGDIR/.sku`
SKU_NAME=`basename $SKU`

TARGET=`cat $CONFIGDIR/.target$SYSTEM_SUFFIX`
TARGET_NAME=`basename $TARGET`

TARGET_DIR=$OUTPUTDIR/$SKU_NAME-$TARGET_NAME

valgrind --leak-check=yes --track-origins=yes $@ ./$TARGET_DIR/$PROJECT.$EXT -DIR ./ -SAVE $TARGET_DIR/
