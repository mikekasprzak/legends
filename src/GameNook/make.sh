#!/bin/sh

#export CC='~/Code/emscripten/emcc'
export CC='/d/Build/em2/emcc'

mkdir -p obj output

echo "// Begin PreJS.txt //">obj/PreJS.txt
cat GelHTML/GelUtil.js>>obj/PreJS.txt
cat GelHTML/GelMath.js>>obj/PreJS.txt
cat GelHTML/GelGeometry.js>>obj/PreJS.txt
cat GelHTML/GelGraphics2D.js>>obj/PreJS.txt
cat GelHTML/GelAudioDummy.js>>obj/PreJS.txt
#cat GelHTML/GelAudio.js>>obj/PreJS.txt
cat Main.js>>obj/PreJS.txt
cat Load.js>>obj/PreJS.txt


#$CC -D NOT_GCC -I ../GEL -O2 -s EXPORTED_FUNCTIONS='["__Z6NewGenv", "_main"]' Main.cpp ../GEL/Math/Real.cpp ../GEL/Math/Vector/Vector3D.cpp --pre-js obj/PreJS.txt -o output/Sugar.js 

$CC -D NOT_GCC -D EMSCRIPTEN -D USES_UNIX_DIR -I ../GEL -I ../External/cJSON -O0 src/Main.cpp ../GEL/Math/Real.cpp ../GEL/Debug/LogEmscripten.cpp ../GEL/Math/Vector/Vector3D.cpp ../External/cJSON/cJSON.c --pre-js obj/PreJS.txt --embed-file Content/MapData.json -o output/nook.js 

#rm a.out
