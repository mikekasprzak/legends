
print("Hello World!\n");
print("AHOY!!\n");

local Sugar = "Moister";

// Illegal //
//Sugar[0] = 'N';

print( Sugar + "\n" );

if ( Sugar[0] == 'M' )
	print( "Emm\n" );
else
	print( "Not Emm\n" );

// - ------------------------------------------------------------------------------------------ - //
class BasicShaft {
	Digging = 0;	// Can dig, but no skill of any merit //
	Piercing = 1;
	Blunting = 2;
	Blunt = true;
};

class BasicDebris {
	Scatter = true;
};
// - ------------------------------------------------------------------------------------------ - //
	
// - ------------------------------------------------------------------------------------------ - //
class Stick extends BasicShaft {
	Name = "Stick";
	Shaft = 2;
	MadeOf = ["Woodchip", "Woodchip"];
};

class Bone extends BasicShaft {
	Name = "Bone";
	Shaft = 4;
	MadeOf = ["Bonechip", "Bonechip"];
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
class Woodchip extends BasicDebris {
	Name = "Woodchip";
};
class Bonechip extends BasicDebris {
	Name = "Bonechip";
};
// - ------------------------------------------------------------------------------------------ - //
class RoughStone {
	Name = "Rough Stone";
	Sharpening = true;
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
class SharpenedStick extends Stick {
	Name = "Sharpened Stick";
	Blunt = false;

	constructor() {
		// Sharpened form has improved piercing and all other attributes //
		Piercing = base.Piercing + 2;
	}
};
// - ------------------------------------------------------------------------------------------ - //
class SharpenedBone extends Bone {
	Name = "Sharpened Bone";
	Blunt = false;
	
	constructor() {
		// Sharpened form has improved piercing and all other attributes //
		Piercing = base.Piercing + 2;
	}
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
function Recipe_SharpenedShaft( InputSharpener, InputShaft ) {
	if ( "Sharpening" in InputSharpener ) {
		if ( "Shaft" in InputShaft ) {
			if ( InputShaft.Blunt ) {
				// Can produce this recipe //
				return true;
			}
		}
	}
	
	// Can not produce this recipe //
	return false;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
class IgnoreList {
	constructor() { };
	MadeOf = null;
};
// - ------------------------------------------------------------------------------------------ - //

//local Object = Bone();
//local Object = Stick();
//local Object = Woodchip();
//local Object = SharpenedStick();

// Dynamically generate the object by name //
local ObRoot = "Bone";
local ObName = "return Sharpened" + ObRoot + "();"
local ObFunc = compilestring( ObName );

// Instance the object //
local Object = ObFunc();

print( "Object is a \"" + Object.tostring() + "\"\n" );

if ( "Shaft" in Object ) {
	print( "Object has shaft " + Object.Shaft + "\n" );
}
else {
	print( "Object is no shaft!\n" );
}

if ( Object instanceof BasicShaft ) {
	print( "Object is a BasicShaft\n" );
}
else if ( Object instanceof BasicDebris ) {
	print( "Object is BasicDebris\n" );
}
else {
	print( "Object is of unknown base\n" );
}

if ( Recipe_SharpenedShaft( Woodchip(), Bone() ) ) {
	print("Yes\n");
}
else {
	print("No\n");
}

if ( Recipe_SharpenedShaft( RoughStone(), Stick() ) ) {
	print("Yes\n");
}
else {
	print("No\n");
}

if ( Recipe_SharpenedShaft( RoughStone(), SharpenedStick() ) ) {
	print("Yes\n");
}
else {
	print("No\n");
}

print( Object.Name + " is made of:\n" );
foreach( idx,var in Object.MadeOf ) {
	print( idx + ": " + var + "\n" );
}
print( "\n" );

print( Object.Name + " has properties:\n" );
foreach( idx,var in Object.getclass() ) {
	if ( idx in IgnoreList )
		continue;
	
	print( idx + ": " + var + "\n" );
}
print( "\n" );
