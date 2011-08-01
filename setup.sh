#!/bin/sh
# setup.sh - Generate several useful files reqested of the build system
#
# TODO: Make the SKU complain if the directory doesn't contain the project

DEFAULTDIR=Tools/default
CONFIGDIR=Config

echo "usage: `basename $0` [GameProjectName] [target_sku] [target_makefile]"
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

	while true; do
		echo -n "Project Name [$PROJECT]: "
		read answer
		if [ "$answer" != "" ]; then
			if [ -e "SKU/$answer" ]; then
				PROJECT="$answer"
				break
			else
				echo "Error! $answer not found!"
				#exit -1
			fi		
		else
			break
		fi
	done
else
	if [ -e "SKU/$1" ]; then
		PROJECT=$1
	else
		echo "Error! $1 not found!"
		exit -1
	fi

fi  

echo "Project Name:    $PROJECT"
rm -f $CONFIGDIR/.project
echo "$PROJECT" >$CONFIGDIR/.project
if [ "$WINDIR" != "" ]; then
	attrib +h $CONFIGDIR/.project
fi


# Target SKU Makefile #
if [ ! -n "$2" ]; then
	if [ -e "$CONFIGDIR/.sku" ]; then
		SKU=`cat $CONFIGDIR/.sku | awk '{print $1}'`
	elif [ -e "SKU/$PROJECT/.default" ]; then
		SKU=`cat SKU/$PROJECT/.default | awk '{print $1}'`
	else
		SKU="SKU/$PROJECT/`cat $DEFAULTDIR/default.sku`"
	fi

	while true; do
		echo -n "Target SKU [$SKU]: "
		read answer
		if [ "$answer" != "" ]; then
			if [ -e "$answer" ]; then
				SKU="$answer"
				break
			elif [ -e "SKU/$PROJECT/$answer" ]; then
				SKU="SKU/$PROJECT/$answer"
				break
			else
				echo "Error! $answer and SKU/$PROJECT/$answer not found!"
				#exit -1
			fi
		else
			break
		fi
	done
else
	if [ -e "$2" ]; then
		SKU="$2"
	elif [ -e "SKU/$PROJECT/$2" ]; then
		SKU="SKU/$PROJECT/$2"
	else
		echo "Error! $2 and SKU/$PROJECT/$answer not found!"
		exit -1
	fi
fi

echo "Target SKU: $SKU"
rm -f $CONFIGDIR/.sku
echo "$SKU">$CONFIGDIR/.sku
if [ "$WINDIR" != "" ]; then
	attrib +h $CONFIGDIR/.sku
fi


# Target Makefile #
if [ ! -n "$3" ]; then
	if [ -e "$CONFIGDIR/.target" ]; then
		TARGET=`cat $CONFIGDIR/.target | awk '{print $1}'`
	elif [ -e "SKU/$PROJECT/.target" ]; then
		TARGET=`cat SKU/$PROJECT/.target | awk '{print $1}'`
	else
		if [ "$WINDIR" != "" ]; then
			TARGET="`cat $DEFAULTDIR/windows.target`"
		else
			TARGET="`cat $DEFAULTDIR/linux.target`"
		fi
	fi
	
	while true; do
		echo -n "Target Makefile [$TARGET]: "
		read answer
		if [ "$answer" != "" ]; then
			if [ -e "$answer" ]; then
				TARGET="$answer"
				break
			else
				echo "Error! $answer not found!"
				#exit -1
			fi
		else
			break
		fi
	done
else
	if [ -e "$3" ]; then
		TARGET="$3"
	else
		echo "Error! $3 not found!"
		exit -1
	fi
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


# End #
echo "Done."
exit 0
