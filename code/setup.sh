#!/bin/sh
# setup.sh - Generate several useful files reqested of the build system

echo "Generating project settings..."
echo ""

DEFAULTDIR=Tools/default

if [ ! -n "$1" ]
then
	echo "USAGE: `basename $0` GameProjectName"
	echo ""
	echo "* Project not specified, using default..."
	echo ""
	
	PROJECT=`cat $DEFAULTDIR/.project`
else
	PROJECT=$1
fi  

echo "Project Name:    $PROJECT"
echo "$PROJECT" >.project
if [ "$WINDIR" != "" ]; then
	attrib +h .project
fi

REPOS=`Tools/SVNRoot.sh`

echo "Repository Root: $REPOS"
echo "$REPOS" >.repos
if [ "$WINDIR" != "" ]; then
	attrib +h .repos
fi

echo "Done."
exit 0
