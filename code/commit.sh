#!/bin/sh
# commit.sh - Frontend script for committing all repositories

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

if [ ! -e "$CONFIGDIR/.content" ]; then
	echo "ERROR: File \".content\" does not exist!  Please run \"content.sh co\" to generate."
	exit 1
fi

if [ ! -e "$CONFIGDIR/.sku" ]; then
	echo "ERROR: File \".sku\" does not exist!  Please run \"sku.sh co\" to generate."
	exit 1
fi

./content.sh update
./content.sh commit "$*"

./sku.sh update
./sku.sh commit "$*"

svn update
svn commit --message "$*"

./content.sh update
./sku.sh update
svn update
