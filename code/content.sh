#!/bin/sh
# content.sh - Frontend script for checking-out, updating, and committing content

if [ ! -e ".project" ]; then
	echo "ERROR: File \".project\" does not exist!  Please run \"setup.sh\" to generate."
	exit 1
fi

if [ ! -e ".repos" ]; then
	echo "ERROR: File \".repos\" does not exist!  Please run \"setup.sh\" to generate."
	exit 1
fi

APPNAME=`basename $0`
PROJECT=`cat .project`
REPOS=`cat .repos`

# TODO: verify that the repository is correct, in case of branches ? 

usage () {
	echo "usage: $APPNAME <subcommand> [args]"
	echo ""
	echo "Available subcommands:"
	echo "  checkout (co) - \"Art/4444 Sound/WAV Music/OGG Tools\" or \"all\""
	echo "  update (up) - no args for all, or explicit repository by name"
	echo "  commit (ci) - no args for all, or explicit repository by name"
}

if [ ! -n "$1" ]; then
	usage
	exit 1
elif [ "$1" == "checkout" ] || [ "$1" == "co" ]; then
	shift 1

	if [ ! -n "$1" ]; then
		echo "Checkout (defaults):"
		if [ -e ".content" ]; then
			FILES="`cat .content`"
		else	
			FILES="`cat Tools/default/.content`"
		fi
	else
		echo "Checkout:"
		FILES="$@"
		
		# Delete ".content" if a specific checkout command was issued
		rm -f .content
		OVERWRITE=true
	fi
	
	for arg in $FILES
	do
		if [ "$arg" == "all" ]; then
			for arg2 in `svn list $REPOS/content/$PROJECT/`
			do
				echo "+ $REPOS/content/$PROJECT/$arg2"
				echo "- Content/$arg2"
				svn co $REPOS/content/$PROJECT/$arg2 Content/$arg2
				if [ "$OVERWRITE" == "true" ]; then
					echo "$arg2">>.content
				fi
			done
		elif [ "$arg" == "Tools" ]; then
			echo "+ $REPOS/content/$arg"
			echo "- Content/$arg"
			svn co $REPOS/content/$arg Content/$arg
			if [ "$OVERWRITE" == "true" ]; then
				echo "$arg">>.content
			fi
		else
			echo "+ $REPOS/content/$PROJECT/$arg"
			echo "- Content/$arg"
			svn co $REPOS/content/$PROJECT/$arg Content/$arg
			if [ "$OVERWRITE" == "true" ]; then
				echo "$arg">>.content
			fi
		fi
	done
	
	# If on Windows, set the content file to hidden #
	if [ "$WINDIR" != "" ]; then
		if [ "$OVERWRITE" == "true" ]; then
			attrib +h .content
		fi
	fi
elif [ "$1" == "update" ] || [ "$1" == "up" ]; then
	shift 1

	if [ ! -n "$1" ]; then
		echo "Update (defaults):"
		if [ -e ".content" ]; then
			FILES="`cat .content`"
		else	
			FILES="`cat Tools/default/.content`"
		fi
	else
		echo "Update:"
		FILES="$@"
	fi
	
	for arg in $FILES
	do
		echo "Content/$arg"
		svn update Content/$arg
	done
	
elif [ "$1" == "commit" ] || [ "$1" == "ci" ]; then
	shift 1
	
	# TODO: catch and forward "-m" message argument, or all options to svn

	if [ ! -n "$1" ]; then
		echo "Commit (defaults):"
		if [ -e ".content" ]; then
			FILES="`cat .content`"
		else	
			FILES="`cat Tools/default/.content`"
		fi
	else
		echo "Commit:"
		FILES="$@"
	fi
	
	for arg in $FILES
	do
		echo "Content/$arg"
		svn ci Content/$arg
	done
else
	echo "ERROR: Unknown Command \"$1\""
	usage
	exit 1
fi  

exit 0
