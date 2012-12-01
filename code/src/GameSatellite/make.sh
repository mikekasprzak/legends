#!/bin/sh

# "--std=c++11" is only supported in GCC 4.7+. Solution, use c++0x #
# "--std=c++0x" causes failures with _fileno and other legacy macros. Solution: Use gnu++0x #

# -Wunused-variable -- unused variables
# -Wmissing-braces -- arrays of types need more {}'s
# -Wdouble-promotion -- float's becoming double
# -Wformat -- printf formatting warnings
# -Wsign-compare -- signed vs unsigned checks. Notably, ENUM's are signed.

FLAGS="-O2 --std=gnu++0x -fstrict-aliasing -Wunused-variable -Wmissing-braces -Wdouble-promotion -Wformat"
#FLAGS="$FLAGS -Wsign-compare"
#FLAGS="$FLAGS -Wall -Wextra"
DEFINES="-DCURL_STATICLIB"
INCLUDES="-I /usr/local/include -I /usr/local/ssl/include -I ../GEL/ -I ../External/ -I ../External/ENet/include -I ../ServerSatellite/ -I ."
CFILES="../ServerSatellite/Util/*.c ../External/cJSON/*.c ../External/Mongoose/*.c"
CPPFILES="*.cpp ../ServerSatellite/Net/*.cpp ../ServerSatellite/Sat/*.cpp ../External/TinyThread/*.cpp ../GEL/Debug/*.cpp ../GEL/Timer/*.cpp ../GEL/System/*.cpp ../GEL/Math/*.cpp ../GEL/Math/Vector/*.cpp ../GEL/Math/Matrix/*.cpp ../ServerSatellite/NetAdapter/*.cpp"
LIBS="-L /usr/local/ssl/lib -lcrypto -L /usr/local/lib -lenet -lwinmm `sdl2-config --static-libs` -lopengl32"

SYSTEM=`uname`

# Linux sh doesn't support ==, so use = #

# If $WINDIR is NOT set #
if [ -n "$WINDIR" ]; then
	DEFINES="$DEFINES -DUSES_WINDOWS -DUSES_XINPUT"
	INCLUDES="$INCLUDES -I ../External/XInput/include"
	LIBS="$LIBS ../External/XInput/lib/XInput.lib `curl-config --static-libs` -lIphlpapi -static"
elif [ "$SYSTEM" = "FreeBSD" ]; then
	DEFINES="$DEFINES -DUSES_UNIX"
	LIBS="$LIBS `curl-config --libs` -lpthread"
else
	DEFINES="$DEFINES -DUSES_UNIX"
	LIBS="$LIBS `curl-config --libs` -ldl"
fi  

#gcc -c $DEFINES $INCLUDES $CFILES -o SatServ.o $FLAGS
g++ $DEFINES $INCLUDES $CPPFILES $CFILES -o SatGame.exe $LIBS $FLAGS
