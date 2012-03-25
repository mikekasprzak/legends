#!/bin/sh

#export CC='~/Code/emscripten/emcc'

mkdir -p obj output

echo "// Begin PreJS.txt //">obj/PreJS.txt
cat GelHTML/GelUtil.js>>obj/PreJS.txt
cat GelHTML/GelGraphics2D.js>>obj/PreJS.txt

~/Code/emscripten/emcc -O2 Main.cpp --pre-js obj/PreJS.txt -o output/Sugar.js 

