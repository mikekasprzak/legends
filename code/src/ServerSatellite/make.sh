#!/bin/sh

# "--std=c++11" is only supported in GCC 4.7+. Solution, use c++0x #
# "--std=c++0x" causes failures with _fileno and other legacy macros. Solution: Use gnu++0x #

FLAGS="--std=gnu++0x"
DEFINES="-DMONGOOSE_NO_WIN32_INIT -DCURL_STATICLIB -DUSES_CURSES"
INCLUDES="-I /usr/local/include -I /usr/local/ssl/include -I ../GEL/ -I ../External/ -I ../External/ENet/include -I ."
CFILES="Util/*.c ../External/cJSON/*.c ../External/Mongoose/*.c"
CPPFILES="*.cpp Net/*.cpp Sat/*.cpp Text/*.cpp ../External/TinyThread/*.cpp ../GEL/Debug/Log*.cpp ../GEL/Timer/*.cpp ../GEL/Math/*.cpp ../GEL/Math/Vector/*.cpp ../GEL/Math/Matrix/*.cpp NetAdapter/*.cpp"
LIBS="-L /usr/local/ssl/lib -lcrypto -L /usr/local/lib"

# apt-get install ncurses-dev

SYSTEM=`uname`

# Ubuntu's sh doesn't support "==", so use "=" #

# If $WINDIR is NOT set #
if [ -n "$WINDIR" ]; then
	DEFINES="$DEFINES"
	INCLUDES="$INCLUDES -I ../External/PDCurses/include"
	LIBS="$LIBS -lenet -lwinmm ../External/PDCurses/pdcurses.lib `curl-config --static-libs` -lIphlpapi -static"
elif [ "$SYSTEM" = "FreeBSD" ]; then
	INCLUDES="$INCLUDES"
	DEFINES="$DEFINES -DUSES_UNIX_TIMER"
	LIBS="$LIBS `curl-config --libs` -lpthread -lncurses /usr/local/lib/libenet.a"
	FLAGS="$FLAGS -Wl,-rpath,$ORIGIN"
else
	INCLUDES="$INCLUDES"
	DEFINES="$DEFINES -DUSES_UNIX_TIMER"
	LIBS="$LIBS `curl-config --libs` -ldl -lncurses /usr/local/lib/libenet.a"
	FLAGS="$FLAGS -Wl,-rpath,$ORIGIN"
fi  

g++ $DEFINES $INCLUDES $CPPFILES $CFILES -o SatServ.exe $LIBS $FLAGS
