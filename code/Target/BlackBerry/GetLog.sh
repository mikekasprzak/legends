#!/bin/sh

usage () {
	echo "Usage: $0 AppName.bar {IP_ADDRESS} {SSH_KEY}"
}

if [ ! -n "$1" ]; then
	usage
	exit 1
elif [ ! -n "$2" ]; then
	usage
	exit 1
elif [ ! -n "$3" ]; then
	usage
	exit 1
elif [ ! -e "$1" ]; then
	echo "Error! $1 doesn't exist!"
	exit 1
fi

PACKAGE_NAME=`unzip -p $1 META-INF/MANIFEST.MF | grep "Package-Name:" | sed s/"Package-Name: "//`
PACKAGE_ID=`unzip -p $1 META-INF/MANIFEST.MF | grep "Package-Id:" | sed s/"Package-Id: "//`

ACTION="cat /accounts/1000/appdata/$PACKAGE_NAME.$PACKAGE_ID/logs/log"

echo "** Connecting to $2 (this can take a while)... **"

ssh devuser@$2 -i $3 "$ACTION"

exit 0
