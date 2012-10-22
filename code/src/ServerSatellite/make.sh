#!/bin/sh

g++ -DMONGOOSE_NO_WIN32_INIT -DCURL_STATICLIB -I /usr/local/include -I /usr/local/ssl/include -I ../GEL/ -I ../External/ main.cpp NetGet.cpp GELGeoData.cpp ../External/cJSON/cJSON.c ../External/Mongoose/mongoose.c -o SatServ.exe `curl-config --static-libs` -L /usr/local/ssl/lib -lcrypto
