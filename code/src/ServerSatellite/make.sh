#!/bin/sh

g++ -I /usr/local/include -I ../GEL/ -I ../External/ main.cpp ../External/cJSON/cJSON.c -o SatServ.exe `curl-config --libs`
