#!/bin/sh
# sku.sh - Script for changing the active SKU (sub-project of an active .target)

#DEFAULTDIR=Tools/default
CONFIGDIR=Config
CUSTOMDIR=Custom

if [ ! -e "$CONFIGDIR/.project" ]; then
	echo "ERROR: File \".project\" does not exist!  Please run \"setup.sh\" to generate."
	exit 1
fi

if [ ! -e "$CONFIGDIR/.repos" ]; then
	echo "ERROR: File \".repos\" does not exist!  Please run \"setup.sh\" to generate."
	exit 1
fi

APPNAME=`basename $0`
PROJECT=`cat $CONFIGDIR/.project`
REPOS=`cat $CONFIGDIR/.repos`

usage () {
	echo "usage: $APPNAME <subcommand> [args]"
	echo ""
	echo "Available subcommands:"
	echo "  checkout (co) - no args, or specify a SKU file to use"
	echo "  update (up)"
	echo "  checkin (ci) - message"
	echo "  set - no args (use default), or specify a SKU file to use"
}

if [ ! -n "$1" ]; then
	usage
	exit 1
elif (([ "$1" = "checkout" ] || [ "$1" = "co" ])); then
	shift 1

	echo "$REPOS/custom/$PROJECT..."

	# Confirm that the current .project and custom .project match
	if [ -e "$CUSTOMDIR/.project" ]; then
		if [ "`cat $CUSTOMDIR/.project`" != $PROJECT ]; then
			echo "ERROR: Custom .project and current .project do not match!"
			echo "  Remove \"Custom\" folder and try again."
			exit 1
		fi
	fi
	
	svn co $REPOS/custom/$PROJECT $CUSTOMDIR

	# Remove the old .sku file	
	rm -f $CONFIGDIR/.sku

	if [ -n "$1" ]; then
		echo $1>$CONFIGDIR/.sku
		if [ "$WINDIR" != "" ]; then
			attrib +h $CONFIGDIR/.sku
		fi
	elif [ -e "$CUSTOMDIR/.default" ]; then
		# If project has a .default file, make that the current SKU #
		cat $CUSTOMDIR/.default>$CONFIGDIR/.sku
		if [ "$WINDIR" != "" ]; then
			attrib +h $CONFIGDIR/.sku
		fi		
	fi
elif (([ "$1" = "update" ] || [ "$1" = "up" ])); then
	shift 1

	svn up $CUSTOMDIR
elif (([ "$1" = "commit" ] || [ "$1" = "checkin" ] || [ "$1" = "ci" ])); then
	shift 1

	if [ ! -n "$1" ]; then
		echo "ERROR: No commit message specified"
		usage
		exit 1
	fi

	svn ci $CUSTOMDIR --message "$*"
elif [ "$1" = "set" ]; then
	# Remove the old .sku file	
	rm -f $CONFIGDIR/.sku

	if [ -n "$1" ]; then
		echo $1>$CONFIGDIR/.sku
		if [ "$WINDIR" != "" ]; then
			attrib +h $CONFIGDIR/.sku
		fi		
	elif [ -e "$CUSTOMDIR/.default" ]; then
		# If project has a .default file, make that the current SKU #
		cat $CUSTOMDIR/.default>$CONFIGDIR/.sku
		if [ "$WINDIR" != "" ]; then
			attrib +h $CONFIGDIR/.sku
		fi		
	fi
else
	echo "ERROR: Unknown Command \"$1\""
	usage
	exit 1
fi  

exit 0
