#!/bin/sh
# setup.sh - Generate several useful files reqested of the build system

DEFAULTDIR=Tools/default
CONFIGDIR=Config

echo "usage: `basename $0` [GameProjectName] [target_makefile] [target_sku]"
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


# Target SKU Makefile #
if [ ! -n "$3" ]; then
	if [ -e "$CONFIGDIR/.sku" ]; then
		SKU=`cat $CONFIGDIR/.sku | awk '{print $1}'`
	else
		SKU="Sku/""$PROJECT""`cat $DEFAULTDIR/default.sku`"
	fi

	while true; do
		echo -n "Target SKU [$SKU]: "
		read answer
		if [ "$answer" != "" ]; then
			if [ -e "$answer" ]; then
				SKU="$answer"
				break
			elif [ -e "Sku/$PROJECT$answer" ]; then
				SKU="Sku/$PROJECT/$answer"
				break
			else
				echo "Error! $answer and Sku/$PROJECT/$answer not found!"
				#exit -1
			fi
		else
			break
		fi
	done
else
	if [ -e "$3" ]; then
		SKU="$3"
	elif [ -e "Sku/$PROJECT$3" ]; then
		SKU="Sku/$PROJECT$3"
	else
		echo "Error! $3 not found!"
		exit -1
	fi
fi

echo "Target SKU: $SKU"
rm -f $CONFIGDIR/.sku
echo "$SKU">$CONFIGDIR/.sku
if [ "$WINDIR" != "" ]; then
	attrib +h $CONFIGDIR/.sku
fi


# SVN Root Directory #
REPOS=`Tools/SVNRoot.sh`

echo "Repository Root: $REPOS"
rm -f $CONFIGDIR/.repos
echo "$REPOS" >$CONFIGDIR/.repos
if [ "$WINDIR" != "" ]; then
	attrib +h $CONFIGDIR/.repos
fi


# End #
echo "Done."
exit 0
