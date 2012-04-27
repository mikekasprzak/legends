#!/bin/sh

#export CC='~/Code/emscripten/emcc'
export CC='/d/Build/em2/emcc'

#export CFLAGS='-O0 --closure 0'
export CFLAGS='-O2 --closure 0'
export DEFINES='-D NOT_GCC -D EMSCRIPTEN -D USES_UNIX_DIR'
export INCLUDES='-I ../GEL -I ../External/cJSON'
export FILES='src/Main.cpp ../GEL/Math/Real.cpp ../GEL/Debug/LogEmscripten.cpp ../GEL/Math/Vector/Vector3D.cpp ../External/cJSON/cJSON.c'

mkdir -p obj output

echo "// Begin PreJS.txt //">obj/PreJS.txt
#cat external/buzz.js>>obj/PreJS.txt
#cat external/soundmanager2-nodebug-jsmin.js>>obj/PreJS.txt
#cat GelHTML/GelAudio.js>>obj/PreJS.txt
#cat GelHTML/GelAudioBuzz.js>>obj/PreJS.txt
cat GelHTML/GelAudioDummy.js>>obj/PreJS.txt

#echo "var ContentMapData = ">>obj/PreJS.txt
#cat Content/MapData.json>>obj/PreJS.txt
#echo ";">>obj/PreJS.txt

cat GelHTML/GelUtil.js>>obj/PreJS.txt
cat GelHTML/GelMath.js>>obj/PreJS.txt
cat GelHTML/GelGeometry.js>>obj/PreJS.txt
cat GelHTML/GelGraphics2D.js>>obj/PreJS.txt
cat Main.js>>obj/PreJS.txt
cat Load.js>>obj/PreJS.txt


#$CC -D NOT_GCC -I ../GEL -O2 -s EXPORTED_FUNCTIONS='["__Z6NewGenv", "_main"]' Main.cpp ../GEL/Math/Real.cpp ../GEL/Math/Vector/Vector3D.cpp --pre-js obj/PreJS.txt -o output/Sugar.js 

$CC $DEFINES $INCLUDES $CFLAGS $FILES --pre-js obj/PreJS.txt -o output/nook.emcc.js 

java -jar bin/compiler.jar --compilation_level WHITESPACE_ONLY --js output/nook.emcc.js 2>output/nook.emcc.js.txt>output/nook.js
#java -jar bin/compiler.jar --compilation_level SIMPLE_OPTIMIZATIONS --js output/nook.emcc.js 2>output/nook.emcc.js.txt>output/nook.js
#cp output/nook.emcc.js output/nook.js
#java -jar bin/compiler.jar --compilation_level SIMPLE_OPTIMIZATIONS --js Content/MapData.json.js >Content/MapData.json.js2

#--embed-file Content/MapData.json
# --js-library external/soundmanager2-nodebug-jsmin.js

#rm a.out
