#!/bin/sh
# debug.sh - Debug the currently built game

CONFIGDIR=Config
OUTPUTDIR=output


if [ ! -e "$CONFIGDIR/.project" ]; then
	echo "ERROR: File \".project\" does not exist!  Please run \"setup.sh\" to generate."
	exit 1
fi

if [ ! -e "$CONFIGDIR/.sku" ]; then
	echo "ERROR: File \".sku\" does not exist!  Please run \"setup.sh\" to generate."
	exit 1
fi

if [ ! -e "$CONFIGDIR/.target" ]; then
	echo "ERROR: File \".target\" does not exist!  Please run \"setup.sh\" to generate."
	exit 1
fi

PROJECT=`cat $CONFIGDIR/.project`
EXT=exe

SKU=`cat $CONFIGDIR/.sku`
SKU_NAME=`basename $SKU`

TARGET=`cat $CONFIGDIR/.target`
TARGET_NAME=`basename $TARGET`

TARGET_DIR=$OUTPUTDIR/$SKU_NAME-$TARGET_NAME

gdb --args ./$TARGET_DIR/$PROJECT.$EXT -DIR ./ -SAVE $TARGET_DIR/
