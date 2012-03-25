#!/bin/sh

#export CC='~/Code/emscripten/emcc'

cat GelHTML/GelUtil.js>PreJS.txt
cat GelHTML/GelGraphics2D.js>>PreJS.txt

~/Code/emscripten/emcc -O2 Main.cpp --pre-js PreJS.txt -o Sugar.js 

