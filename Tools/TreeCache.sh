#!/bin/sh
# TreeCache.sh - Frontend for TreeTool that caches contents to a file, returning immediately

THISFILE=$0
TREETOOL=`dirname $THISFILE`/TreeTool.sh

CACHEFILE=$1
shift

function update_file() {
	$TREETOOL $@>$CACHEFILE
}

if [ ! -e "$CACHEFILE" ]; then
	mkdir -p `dirname $CACHEFILE`
	update_file $@
	cat $CACHEFILE
	exit 0
fi

cat $CACHEFILE
update_file $@ &

exit 0
