#!/bin/sh

DEFINES="-DMONGOOSE_NO_WIN32_INIT -DCURL_STATICLIB"
INCLUDES="-I /usr/local/include -I /usr/local/ssl/include -I ../GEL/ -I ../External/"
FILES="main.cpp NetGet.cpp GELGeoData.cpp ../GEL/Debug/Log.cpp ../External/cJSON/cJSON.c ../External/Mongoose/mongoose.c"
LIBS="`curl-config --static-libs` -L /usr/local/ssl/lib -lcrypto"

# If $WINDIR is NOT set #
if [ -z "$WINDIR" ]; then
	LIBS="$LIBS -ldl"
fi  

g++ $DEFINES $INCLUDES $FILES -o SatServ.exe $LIBS
