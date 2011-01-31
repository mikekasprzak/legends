
SetFont 2
SetAlign Center Center

// Sound Options -------------------- //
Text
String "Sound: On"
String "Sound: Off"

Element Text
Pos 0 32
Value 0
Range 0 1


// Start Game ----------------------- //
Text
String "Start Game"

Element Text
Pos 0 64

// Stort Game ----------------------- //
Text
String "Stort Game"

Element Text
Pos 0 64
AddView 128 48

// Graphic -------------------------- //
Graphic 256 256
SetImage "/Screen/Logo"
Shape 0 0 256 128

Element Graphic
Pos 0 -64

// Graphic -------------------------- //
Graphic 256 256
SetImage "/Screen/Logo"
Shape 0 0 256 128

Element Graphic
Pos 0 -64
