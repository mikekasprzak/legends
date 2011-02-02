#!/bin/sh
# SVNRoot.sh - Returns the SVN root folder

dirname `svn info | grep -e "URL:" | awk '{print $2}'`
