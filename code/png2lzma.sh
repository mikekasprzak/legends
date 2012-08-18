#!/bin/sh
# png2lzma.sh - convert images to proper pvr files

APPNAME=`basename $0`

usage () {
	echo "usage: $APPNAME infile outfile"
}

if [ ! -n "$2" ]; then
	usage
	exit 1
fi

if [ ! -e "$1" ]; then
	echo "File \"$1\" does not exist"
	exit 1
fi

TEMP=`mktemp`

Content/Tools/PowerVR/PVRTexTool.exe -m -premultalpha -yflip0 -f OGL8888 -i $1 -o $TEMP.pvr
Tools/external/lzma.exe e $TEMP.pvr $2
rm $TEMP.pvr

exit 0
