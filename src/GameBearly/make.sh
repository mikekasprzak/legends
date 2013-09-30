#!/bin/sh

#export CC='~/Code/emscripten/emcc'
export CC='emcc'

#export CFLAGS='-O0'
export CFLAGS='-O2'
export DEFINES='-D NOT_GCC -D EMSCRIPTEN -D USES_UNIX_DIR'
export INCLUDES='-I ../GEL -I ../External/cJSON'
export FILES='src/Main.cpp ../GEL/Math/Real.cpp ../GEL/Debug/LogEmscripten.cpp ../GEL/Math/Vector/Vector3D.cpp ../External/cJSON/cJSON.c'

export TARGET='game'

mkdir -p obj output

echo "// Begin PreJS.js //">obj/PreJS.js
echo "// Begin PostJS.js //">obj/PostJS.js

cat external/buzz.js>>obj/PreJS.js
#cat external/soundmanager2-nodebug-jsmin.js>>obj/PreJS.js

#cat GelHTML/GelAudio.js>>obj/PreJS.js
cat GelHTML/GelAudioBuzz.js>>obj/PostJS.js
#cat GelHTML/GelAudioDummy.js>>obj/PreJS.js

#echo "var ContentMapData = ">>obj/PreJS.js
#cat Content/MapData.json>>obj/PreJS.js
#echo ";">>obj/PreJS.js

cat GelHTML/GelUtil.js>>obj/PostJS.js
cat GelHTML/GelMath.js>>obj/PostJS.js
cat GelHTML/GelGeometry.js>>obj/PostJS.js
cat GelHTML/GelGraphics2D.js>>obj/PostJS.js
cat Main.js>>obj/PostJS.js
cat Load.js>>obj/PostJS.js


#$CC -D NOT_GCC -I ../GEL -O2 -s EXPORTED_FUNCTIONS='["__Z6NewGenv", "_main"]' Main.cpp ../GEL/Math/Real.cpp ../GEL/Math/Vector/Vector3D.cpp --pre-js obj/PreJS.js -o output/Sugar.js 

$CC $DEFINES $INCLUDES $CFLAGS $FILES -s EXPORTED_FUNCTIONS='["__Z8GameInitv","__Z8GameStepv","__Z8GameDrawv","__Z9GameInputffii","__Z14GameDrawPausedv"]' --pre-js obj/PreJS.js --post-js obj/PostJS.js -o output/$TARGET.emcc.js 

#java -jar ../GameNook/bin/compiler.jar --compilation_level WHITESPACE_ONLY --js output/$TARGET.emcc.js 2>output/$TARGET.emcc.js.txt>output/$TARGET.js
#java -jar bin/compiler.jar --compilation_level SIMPLE_OPTIMIZATIONS --js output/$TARGET.emcc.js 2>output/$TARGET.emcc.js.txt>output/$TARGET.js
cp output/$TARGET.emcc.js output/$TARGET.js
#java -jar bin/compiler.jar --compilation_level SIMPLE_OPTIMIZATIONS --js Content/WorldMap.json.js >Content/WorldMap.json.js2

