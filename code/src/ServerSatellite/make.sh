#!/bin/sh

g++ -DCURL_STATICLIB -I /usr/local/include -I ../GEL/ -I ../External/ main.cpp ../External/cJSON/cJSON.c -o SatServ.exe `curl-config --static-libs`
