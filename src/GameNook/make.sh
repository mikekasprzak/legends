#!/bin/sh

export CC='emcc'

#export CFLAGS='-O0'
export CFLAGS='-O2'
export DEFINES='-D NOT_GCC -D EMSCRIPTEN -D USES_UNIX_DIR'
export INCLUDES='-I ../GEL -I ../External/cJSON'
export FILES='src/Main.cpp ../GEL/Math/Real.cpp ../GEL/Debug/LogEmscripten.cpp ../GEL/Math/Vector/Vector3D.cpp ../External/cJSON/cJSON.c'

mkdir -p obj output

echo "// Begin PreJS.txt //">obj/PreJS.txt
cat external/buzz.js>>obj/PreJS.txt
#cat external/soundmanager2-nodebug-jsmin.js>>obj/PreJS.txt

echo "// Begin PostJS.txt //">obj/PostJS.txt
#cat GelHTML/GelAudio.js>>obj/PostJS.txt
cat GelHTML/GelAudioBuzz.js>>obj/PostJS.txt
#cat GelHTML/GelAudioDummy.js>>obj/PostJS.txt

#echo "var ContentMapData = ">>obj/PostJS.txt
#cat Content/MapData.json>>obj/PostJS.txt
#echo ";">>obj/PostJS.txt

cat GelHTML/GelUtil.js>>obj/PostJS.txt
cat GelHTML/GelMath.js>>obj/PostJS.txt
cat GelHTML/GelGeometry.js>>obj/PostJS.txt
cat GelHTML/GelGraphics2D.js>>obj/PostJS.txt
cat Main.js>>obj/PostJS.txt
cat Load.js>>obj/PostJS.txt


#$CC -D NOT_GCC -I ../GEL -O2 -s EXPORTED_FUNCTIONS='["__Z6NewGenv", "_main"]' Main.cpp ../GEL/Math/Real.cpp ../GEL/Math/Vector/Vector3D.cpp --pre-js obj/PreJS.txt --post-js obj/PostJS.txt -o output/Sugar.js 

$CC $DEFINES $INCLUDES $CFLAGS $FILES -s EXPORTED_FUNCTIONS='["__Z8GameInitv","__Z8GameStepv","__Z8GameDrawv","__Z9GameInputffii","__Z14GameDrawPausedv"]' --pre-js obj/PreJS.txt --post-js obj/PostJS.txt -o output/nook.emcc.js 

#java -jar bin/compiler.jar --compilation_level WHITESPACE_ONLY --js output/nook.emcc.js 2>output/nook.emcc.js.txt>output/nook.js
#java -jar bin/compiler.jar --compilation_level SIMPLE_OPTIMIZATIONS --js output/nook.emcc.js 2>output/nook.emcc.js.txt>output/nook.js
cp output/nook.emcc.js output/nook.js
#java -jar bin/compiler.jar --compilation_level SIMPLE_OPTIMIZATIONS --js Content/MapData.json.js >Content/MapData.json.js2

#--embed-file Content/MapData.json
# --js-library external/soundmanager2-nodebug-jsmin.js

#rm a.out
