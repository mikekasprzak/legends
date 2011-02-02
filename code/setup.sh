#!/bin/sh
# setup.sh - Generate several useful files reqested of the build system

DEFAULTDIR=Tools/default

if [ ! -n "$1" ]; then
	echo "USAGE: `basename $0` [GameProjectName] [target_makefile]"
	echo ""
	echo "* Project not specified, using defaults..."
	echo ""
	
	PROJECT=`cat $DEFAULTDIR/.project`
else
	PROJECT=$1
fi  

if [ -e ".project" ]; then
	echo "Warning! File \".project\" exists! Overwrite? y/n [n]"
	read answer
	if [ "$answer" != "y" ]; then
		exit 1
	fi
fi

echo "Generating project settings..."
echo ""

echo "Project Name:    $PROJECT"
rm -f .project
echo "$PROJECT" >.project
if [ "$WINDIR" != "" ]; then
	attrib +h .project
fi


# SVN Root Directory #
REPOS=`Tools/SVNRoot.sh`

echo "Repository Root: $REPOS"
rm -f .repos
echo "$REPOS" >.repos
if [ "$WINDIR" != "" ]; then
	attrib +h .repos
fi


# Target Makefile #
if [ ! -n "$2" ]; then
	if [ "$WINDIR" != "" ]; then
		TARGET="winsdl_makefile"
	else
		TARGET="Target/nixsdl_makefile"
	fi
else
	TARGET="$2"
fi

echo "Target Makefile: $TARGET"
rm -f .target
echo "-include $TARGET">.target
if [ "$WINDIR" != "" ]; then
	attrib +h .target
fi

# End #
echo "Done."
exit 0
