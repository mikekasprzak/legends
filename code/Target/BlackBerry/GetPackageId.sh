#!/bin/sh

if [ ! -n "$1" ]; then
	echo "Usage: $0 TOKEN_FILE_NAME.bar"
	exit 1
elif [ ! -e "$1" ]; then
	echo "Error! $1 doesn't exist!"
	exit 1
fi

echo "`unzip -p $1 META-INF/MANIFEST.MF | grep "Package-Id:" | sed s/"Package-Id: "//`"

exit 0
