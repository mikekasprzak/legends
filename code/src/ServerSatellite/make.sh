#!/bin/sh

# "--std=c++11" is only supported in GCC 4.7+. Solution, use c++0x #
# "--std=c++0x" causes failures with _fileno and other legacy macros. Solution: Use gnu++0x #

FLAGS="--std=gnu++0x"
DEFINES="-DMONGOOSE_NO_WIN32_INIT -DCURL_STATICLIB"
INCLUDES="-I /usr/local/include -I /usr/local/ssl/include -I ../GEL/ -I ../External/ -I ../External/PDCurses/include -I ../External/ENet/include -I ."
CFILES="Util/*.c ../External/cJSON/*.c ../External/Mongoose/*.c"
CPPFILES="*.cpp Net/*.cpp Sat/*.cpp Text/*.cpp ../External/TinyThread/*.cpp ../GEL/Debug/*.cpp ../GEL/Timer/*.cpp ../GEL/Math/*.cpp ../GEL/Math/Vector/*.cpp ../GEL/Math/Matrix/*.cpp NetAdapter/*.cpp"
LIBS="-L /usr/local/ssl/lib -lcrypto -L /usr/local/lib -lenet -lwinmm"

SYSTEM=`uname`

# Linux sh doesn't support ==, so use = #

# If $WINDIR is NOT set #
if [ -n "$WINDIR" ]; then
	LIBS="$LIBS ../External/PDCurses/pdcurses.lib `curl-config --static-libs` -lIphlpapi -static"
elif [ "$SYSTEM" = "FreeBSD" ]; then
	LIBS="$LIBS `curl-config --libs` -lpthread"
else
	LIBS="$LIBS `curl-config --libs` -ldl"
fi  

g++ $DEFINES $INCLUDES $CPPFILES $CFILES -o SatServ.exe $LIBS $FLAGS
