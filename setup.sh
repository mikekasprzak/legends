#!/bin/sh
# setup.sh - Generate several useful files reqested of the build system

DEFAULTDIR=Tools/default
CONFIGDIR=Config
CUSTOMDIR=Custom

echo "usage: `basename $0` [GameProjectName] [target_makefile]"
echo ""

if [ -e "$CONFIGDIR/.project" ]; then
	echo "Warning! File \".project\" exists!"
	echo -n "Overwrite [type \"yes\"]? "
	read answer
	if [ "$answer" != "yes" ]; then
		echo "Exiting..."
		exit 1
	fi
fi

echo "Generating project settings..."
echo ""

if [ ! -n "$1" ]; then
	if [ -e "$CONFIGDIR/.project" ]; then
		PROJECT=`cat $CONFIGDIR/.project`
	elif [ -e "$CUSTOMDIR/.project" ]; then
		PROJECT=`cat $CUSTOMDIR/.project`
	else
		PROJECT=`cat $DEFAULTDIR/.project`
	fi
	echo -n "Project Name [$PROJECT]: "
	read answer
	if [ "$answer" != "" ]; then
		PROJECT="$answer"
	fi
else
	PROJECT=$1
fi  

echo "Project Name:    $PROJECT"
rm -f $CONFIGDIR/.project
echo "$PROJECT" >$CONFIGDIR/.project
if [ "$WINDIR" != "" ]; then
	attrib +h $CONFIGDIR/.project
fi


# Target Makefile #
if [ ! -n "$2" ]; then
	if [ -e "$CONFIGDIR/.target" ]; then
		TARGET=`cat $CONFIGDIR/.target | awk '{print $1}'`
	else
		if [ "$WINDIR" != "" ]; then
			TARGET="`cat $DEFAULTDIR/windows.target`"
		else
			TARGET="`cat $DEFAULTDIR/linux.target`"
		fi
	fi
	
	echo -n "Target Makefile [$TARGET]: "
	read answer
	if [ "$answer" != "" ]; then
		TARGET="$answer"
	fi
else
	TARGET="$2"
fi

echo "Target Makefile: $TARGET"
rm -f $CONFIGDIR/.target
echo "$TARGET">$CONFIGDIR/.target
if [ "$WINDIR" != "" ]; then
	attrib +h $CONFIGDIR/.target
fi


# SVN Root Directory #
REPOS=`Tools/SVNRoot.sh`

echo "Repository Root: $REPOS"
rm -f $CONFIGDIR/.repos
echo "$REPOS" >$CONFIGDIR/.repos
if [ "$WINDIR" != "" ]; then
	attrib +h $CONFIGDIR/.repos
fi


# Checkout some custom stuffs #
./sku.sh co

# End #
echo "Done."
exit 0
