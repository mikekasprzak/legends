#!/bin/sh

#export CC='~/Code/emscripten/emcc'

mkdir -p obj output

echo "// Begin PreJS.txt //">obj/PreJS.txt
cat GelHTML/GelUtil.js>>obj/PreJS.txt
cat GelHTML/GelGraphics2D.js>>obj/PreJS.txt

~/Code/emscripten/emcc -D NOT_GCC -I ../GEL -O2 -s EXPORTED_FUNCTIONS='["__Z6NewGenv", "_main"]' Main.cpp ../GEL/Math/Real.cpp ../GEL/Math/Vector/Vector3D.cpp --pre-js obj/PreJS.txt -o output/Sugar.js 

rm a.out
