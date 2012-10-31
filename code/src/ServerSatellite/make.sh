#!/bin/sh

DEFINES="-DMONGOOSE_NO_WIN32_INIT -DCURL_STATICLIB"
INCLUDES="-I /usr/local/include -I /usr/local/ssl/include -I ../GEL/ -I ../External/"
FILES="main.cpp NetGet.cpp GELGeoData.cpp ../GEL/Debug/Log.cpp ../External/cJSON/cJSON.c ../External/Mongoose/mongoose.c NetAdapter/NetAdapter_*.cpp"
LIBS="-L /usr/local/ssl/lib -lcrypto"

SYSTEM=`uname`

# If $WINDIR is NOT set #
if [ -n "$WINDIR" ]; then
	LIBS="$LIBS `curl-config --static-libs` -lIphlpapi -static"
elif [ "$SYSTEM" == "FreeBSD" ]; then
	LIBS="$LIBS `curl-config --libs` -lpthread"
else
	LIBS="$LIBS `curl-config --libs` -ldl"
fi  

g++ $DEFINES $INCLUDES $FILES -o SatServ.exe $LIBS
