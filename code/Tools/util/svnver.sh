#!/bin/bash

echo "extern const char SVN_REVISION[];"
echo const char SVN_REVISION[] = \"`svn info | grep -e "Revision:" | awk '{print $2}'`\"\;
