#!/bin/sh
# SVNRoot.sh - Returns the SVN root folder (assuming "Legends" style file layout)

dirname `svn info | grep -e "URL:" | awk '{print $2}'`
