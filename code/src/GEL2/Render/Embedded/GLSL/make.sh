#!/bin/sh

for file in *.json ; do
	../../../../../Tools/bin/Text2C.exe $file Output/$file.c "" "_json"
done

for file in *.glsl ; do
	../../../../../Tools/bin/Text2C.exe $file Output/$file.c "" "_glsl"
done

exit 0
