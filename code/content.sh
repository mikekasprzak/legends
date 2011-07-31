#!/bin/sh
# content.sh - Frontend script for checking-out, updating, and committing content

# TODO: verify that the repository is correct, in case of branches ? 
# TODO: inside checkin, catch and forward "-m" message argument (or all options) to svn


DEFAULTDIR=Tools/default
CONFIGDIR=Config

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
	echo "  checkout (co) - \"Art/4444 Sound/WAV Music/OGG Tools\" or \"all\" for everything"
	echo "  update (up)"
	echo "  checkin (ci) - message"
#	echo "  update (up) - no args, or explicit repository by name"
#	echo "  checkin (ci) - no args, or explicit repository by name"
}

if [ ! -n "$1" ]; then
	usage
	exit 1
elif (([ "$1" = "checkout" ] || [ "$1" = "co" ])); then
	shift 1

	if [ ! -n "$1" ]; then
		echo "Checkout (defaults):"
		if [ -e "$CONFIGDIR/.content" ]; then
			FILES="`cat $CONFIGDIR/.content`"
		else	
			FILES="`cat $DEFAULTDIR/.content`"
		fi
	else
		echo "Checkout:"
		FILES="$@"
		
		# Delete ".content" if a specific checkout command was issued
		rm -f $CONFIGDIR/.content
		OVERWRITE=true
	fi
	
	for arg in $FILES
	do
		if [ "$arg" = "all" ]; then
			for arg2 in `svn list $REPOS/content/$PROJECT/`
			do
				echo "+ $REPOS/content/$PROJECT/$arg2"
				echo "- Content/$arg2"
				svn co $REPOS/content/$PROJECT/$arg2 Content/$arg2
				if [ "$OVERWRITE" = "true" ]; then
					echo "$arg2">>$CONFIGDIR/.content
				fi
			done
		elif [ "$arg" = "Tools" ]; then
			echo "+ $REPOS/content/$arg"
			echo "- Content/$arg"
			svn co $REPOS/content/$arg Content/$arg
			if [ "$OVERWRITE" = "true" ]; then
				echo "$arg">>$CONFIGDIR/.content
			fi
		else
			echo "+ $REPOS/content/$PROJECT/$arg"
			echo "- Content/$arg"
			svn co $REPOS/content/$PROJECT/$arg Content/$arg
			if [ "$OVERWRITE" = "true" ]; then
				echo "$arg">>$CONFIGDIR/.content
			fi
		fi
	done
	
	# If on Windows, set the content file to hidden #
	if [ "$WINDIR" != "" ]; then
		if [ "$OVERWRITE" = "true" ]; then
			attrib +h $CONFIGDIR/.content
		fi
	fi
elif (([ "$1" = "update" ] || [ "$1" = "up" ])); then
	shift 1

#	if [ ! -n "$1" ]; then
#		echo "Update (defaults):"
#		if [ -e "$CONFIGDIR/.content" ]; then
#			FILES="`cat $CONFIGDIR/.content`"
#		else	
#			FILES="`cat $DEFAULTDIR/.content`"
#		fi
#	else
#		echo "Update:"
#		FILES="$@"
#	fi

	echo "Update:"
	if [ -e "$CONFIGDIR/.content" ]; then
		FILES="`cat $CONFIGDIR/.content`"
	else	
		FILES="`cat $DEFAULTDIR/.content`"
	fi
	
	for arg in $FILES
	do
		echo "Content/$arg"
		svn update Content/$arg
	done
	
elif (([ "$1" = "commit" ] || [ "$1" = "checkin" ] || [ "$1" = "ci" ])); then
	shift 1
	
#	if [ ! -n "$1" ]; then
#		echo "Commit (defaults):"
#		if [ -e "$CONFIGDIR/.content" ]; then
#			FILES="`cat $CONFIGDIR/.content`"
#		else	
#			FILES="`cat $DEFAULTDIR/.content`"
#		fi
#	else
#		echo "Commit:"
#		FILES="$@"
#	fi

#	for arg in $FILES
#	do
#		echo "Content/$arg"
#		svn ci Content/$arg --message ""
#	done


	if [ ! -n "$1" ]; then
		echo "ERROR: No commit message specified"
		usage
		exit 1
	fi

	echo "Commit:"
	if [ -e "$CONFIGDIR/.content" ]; then
		FILES="`cat $CONFIGDIR/.content`"
	else	
		FILES="`cat $DEFAULTDIR/.content`"
	fi
	
	for arg in $FILES
	do
		echo "Content/$arg"
		svn ci Content/$arg --message "$*"
	done
else
	echo "ERROR: Unknown Command \"$1\""
	usage
	exit 1
fi

exit 0
