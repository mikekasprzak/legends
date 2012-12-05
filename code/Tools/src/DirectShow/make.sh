#!/bin/sh

# "--std=c++11" is only supported in GCC 4.7+. Solution, use c++0x #
# "--std=c++0x" causes failures with _fileno and other legacy macros. Solution: Use gnu++0x #

FLAGS="--std=gnu++0x"
DEFINES=""
INCLUDES="-I /usr/local/include "
CFILES=""
CPPFILES="main.cpp"
LIBS="-L /usr/local/lib -lStrmiids -lole32"

# -lole32 is COM
# -lStrmiids is DirectShow (WTF)

SYSTEM=`uname`

# Ubuntu's sh doesn't support "==", so use "=" #

# If $WINDIR is NOT set #
if [ -n "$WINDIR" ]; then
	DEFINES="$DEFINES"
	INCLUDES="$INCLUDES"
	LIBS="$LIBS -static"
elif [ "$SYSTEM" = "FreeBSD" ]; then
	echo "hey"
else
	echo "uh"
fi  

g++ $DEFINES $INCLUDES $CPPFILES $CFILES -o DShower.exe $LIBS $FLAGS
