#!/bin/sh
# setup.sh - Generate several useful files reqested of the build system

echo "Generating project settings..."
echo ""

DEFAULTDIR=Tools/default

if [ ! -n "$1" ]
then
	PROJECT=`cat $DEFAULTDIR/.project`
	echo "USAGE: `basename $0` GameProjectName"
	echo ""
	echo "* Project not specified, using default..."
	echo ""
else
	PROJECT=$1
fi  

echo "Project Name:    $PROJECT"
echo "$PROJECT" >.project

REPOS=`Tools/SVNRoot.sh`

echo "Repository Root: $REPOS"
echo "$REPOS" >.repos

echo "Done."
exit 0
