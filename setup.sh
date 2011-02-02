#!/bin/sh
# setup.sh - Generate several useful files reqested of the build system

DEFAULTDIR=Tools/default

echo "usage: `basename $0` [GameProjectName] [target_makefile]"
echo ""

if [ -e ".project" ]; then
	echo "Warning! File \".project\" exists!"
	echo -n "Overwrite [y/N]? "
	read answer
	if [ "$answer" != "y" ] && [ "$answer" != "Y" ] && [ "$answer" != "yes" ]; then
		echo "Exiting..."
		exit 1
	fi
fi

echo "Generating project settings..."
echo ""

if [ ! -n "$1" ]; then
	if [ -e ".project" ]; then
		PROJECT=`cat .project`
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
rm -f .project
echo "$PROJECT" >.project
if [ "$WINDIR" != "" ]; then
	attrib +h .project
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


# SVN Root Directory #
REPOS=`Tools/SVNRoot.sh`

echo "Repository Root: $REPOS"
rm -f .repos
echo "$REPOS" >.repos
if [ "$WINDIR" != "" ]; then
	attrib +h .repos
fi

# End #
echo "Done."
exit 0
