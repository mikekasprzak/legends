#!/bin/sh

# "--std=c++11" is only supported in GCC 4.7+. Solution, use c++0x #
# "--std=c++0x" causes failures with _fileno and other legacy macros. Solution: Use gnu++0x #

# -fmudflap -- Pointer protection. Like an integrated valgrind. Currently unavailable in MinGW :(

# -Wdouble-promotion -- float's becoming double
# -Wfloat-equal -- Warn about equality tests done for floats, since they are unsafe
# -Wshadow -- Warn about variable name re-use.
# -Wlogical-op -- Warn about cases where you should be using | instead of ||, and vice versa.
# -Winline -- Warn if inline is impossible
# -Wundef -- Warns about other #if checks to undefined macros (i.e. #if LOG_LEVEL > 1)
# -Wcast-qual -- Warn about going from const to non-const in a cast
# -Wconversion -- Warn about explicit type conversion (double to float to int) without a cast
# -Wpadded -- Warn whenever a type is padded
# -Wuseless-cast -- Warn about pointless casts. GCC 4.8+ only.
# -Wmissing-braces -- arrays of types need more {}'s. Typically ignored in C++, but not C.
# -Wmissing-include-dirs -- Complains when an -I neglects points to a non existing path ?

# -Wzero-as-null-pointer-constant -- 

# -fstrict-aliasing enables strict aliasing, but with -Wno-strict-aliasing you wont get warned about potential dangeous aliases #

# All Flags that aren't warnings #
FLAGS="$FLAGS --std=gnu++0x -fstrict-aliasing"
# Warnings not included with -Wall and -Wextra #
FLAGS="$FLAGS -Wshadow -Wlogical-op -Wmissing-braces -Wmissing-include-dirs"
#-Wdouble-promotion -Wfloat-equal 

# -Wall and -Wextra, with warnings I will not fix removed #
FLAGS="$FLAGS -Wall -Wno-unknown-pragmas -Wextra -Wno-ignored-qualifiers"
# Additional Warnings from -Wall and -Wextra I would like to remove, but still want to know about #
FLAGS="$FLAGS -Wno-strict-aliasing -Wno-missing-field-initializers -Wno-unused-parameter -Wno-unused-but-set-parameter"
# Verbose Warnings #
#FLAGS="$FLAGS -Winline -Wundef -Wcast-qual -Wconversion -Wpadded"

# Release Mode Flags #
#FLAGS="$FLAGS -Dndebug -O2 -funsafe-loop-optimizations -Wunsafe-loop-optimizations "

# Debug Mode Flags -- GCC 4.8 is getting -Og, an ideal optimization level for debugging #
FLAGS="$FLAGS -Ddebug -O0 -g -gstabs3 -fstack-protector"

# Defines (with -D) #
DEFINES="-DCURL_STATICLIB -DSVN_VERSION=`../../Tools/SVNVersion.sh .` -DUSES_WGL -DUSES_OPENGL2 -DUSES_SDL2"
INCLUDES=" -I . -I /usr/local/include -I /usr/local/ssl/include -I ../GEL/ -I ../External/ -I ../External/ENet/include -I ../ServerSatellite/"
CFILES="../ServerSatellite/Util/*.c ../External/cJSON/*.c ../External/Mongoose/*.c"
CPPFILES="*.cpp ../ServerSatellite/Net/*.cpp ../ServerSatellite/Sat/*.cpp"
CPPFILES="$CPPFILES Input/*.cpp MainClient/*.cpp Screen/*.cpp System/*.cpp"
CPPFILES="$CPPFILES ../External/TinyThread/*.cpp ../GEL/Debug/*.cpp ../GEL/Timer/*.cpp ../GEL/System/*.cpp ../GEL/Math/*.cpp ../GEL/Math/Vector/*.cpp ../GEL/Math/Matrix/*.cpp ../ServerSatellite/NetAdapter/*.cpp"
LIBS="-L /usr/local/ssl/lib -lcrypto -L /usr/local/lib -lenet -lwinmm `sdl2-config --static-libs` -lopengl32"

SYSTEM=`uname`

# Linux sh doesn't support ==, so use = #

# If $WINDIR is NOT set #
if [ -n "$WINDIR" ]; then
	DEFINES="$DEFINES -DUSES_WINDOWS -DUSES_MINGW -DUSES_XINPUT"
	INCLUDES="$INCLUDES -I ../External/XInput/include"
	LIBS="$LIBS ../External/XInput/lib/XInput.lib `curl-config --static-libs` -lIphlpapi -lPsapi -static"
elif [ "$SYSTEM" = "FreeBSD" ]; then
	DEFINES="$DEFINES -DUSES_UNIX"
	LIBS="$LIBS `curl-config --libs` -lpthread"
else
	DEFINES="$DEFINES -DUSES_UNIX"
	LIBS="$LIBS `curl-config --libs` -ldl"
fi  

#gcc -c $DEFINES $INCLUDES $CFILES -o SatServ.o $FLAGS
g++ $DEFINES $INCLUDES $CPPFILES $CFILES -o SatGame.exe $LIBS $FLAGS
