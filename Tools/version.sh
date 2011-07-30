#!/bin/sh

echo "extern const int BuildVersion;"
echo "const int BuildVersion = `svn info 2>/dev/null | grep "Last Changed Rev:" | sed s/"Last Changed Rev: "//`;"

exit 0
