
// - -------------------------------------------------------------------------------------------------------------- - //
function isMobileSafari() {
    return navigator.userAgent.match(/(iPod|iPhone|iPad)/) && navigator.userAgent.match(/AppleWebKit/)
}
// - -------------------------------------------------------------------------------------------------------------- - //
function isMobile() {
	return 'createTouch' in document;
}
// - -------------------------------------------------------------------------------------------------------------- - //

// - -------------------------------------------------------------------------------------------------------------- - //
function Log( val ) {
	if ( isMobile() ) {
//		setTimeout( function() { document.getElementById("HTMLLog").innerHTML += val + "<br />"; }, 50 );
	}
	else {
		console.log( val );
	}
}
// - -------------------------------------------------------------------------------------------------------------- - //

// - -------------------------------------------------------------------------------------------------------------- - //
function NextPowerOfTwo( v ) {
	// http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2 //
	v--;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	v++;
	
	return v;
}
// - -------------------------------------------------------------------------------------------------------------- - //

// - -------------------------------------------------------------------------------------------------------------- - //
// http://my.opera.com/GreyWyvern/blog/show.dml/1725165 //
Object.prototype.clone = function() {
	var newObj = (this instanceof Array) ? [] : {};
	for (i in this) {
		if (i == 'clone') continue;
		if (this[i] && typeof this[i] == "object") {
			newObj[i] = this[i].clone();
		} 
		else 
			newObj[i] = this[i]
	} 
	return newObj;
};
// - -------------------------------------------------------------------------------------------------------------- - //

// - -------------------------------------------------------------------------------------------------------------- - //
// http://24ways.org/2005/dont-be-eval //
function evalRequest( url, MyFunc ) {
	Log( "EV..." );
	var xmlhttp = new XMLHttpRequest();
	xmlhttp.onreadystatechange = function() {
		if (xmlhttp.readyState==4 && xmlhttp.status==200) {
			Log( "** " + xmlhttp.responseText + " ** " );
			eval(xmlhttp.responseText);
			Generate();
			if ( MyFunc ) {
				Log( "Has Function..." );
				MyFunc();
			}
		}
	}
	Log( "EVO..." );
	xmlhttp.open( "GET", url, false );
	xmlhttp.send(null);
	Log( "EVS..." );
}
// - -------------------------------------------------------------------------------------------------------------- - //

// - -------------------------------------------------------------------------------------------------------------- - //
function RGB( r, g, b ) {
	return "rgb(" + r + "," + g + "," + b + ")";
}
// - -------------------------------------------------------------------------------------------------------------- - //
function RGBA( r, g, b, a ) {
	return "rgba(" + r + "," + g + "," + b + "," + (Alpha/255) + ")";
}
// - -------------------------------------------------------------------------------------------------------------- - //
function ColorString( r, g, b, Alpha ) {
	if ( typeof Alpha === 'undefined' ) {
		return "rgb(" + r + "," + g + "," + b + ")";
	}
	else {
		return "rgba(" + r + "," + g + "," + b + "," + (Alpha/255) + ")";
	}
}
// - -------------------------------------------------------------------------------------------------------------- - //

// - -------------------------------------------------------------------------------------------------------------- - //
function C64F_BLACK( Alpha ) { return ColorString( 0, 0, 0, Alpha ); }
function C64F_WHITE( Alpha ) { return ColorString( 255, 255, 255, Alpha ); }
function C64F_RED( Alpha ) { return ColorString( 160, 71, 57, Alpha ); }
function C64F_CYAN( Alpha ) { return ColorString( 105, 194, 203, Alpha ); }
function C64F_PURPLE( Alpha ) { return ColorString( 169, 30, 168, Alpha ); }
function C64F_GREEN( Alpha ) { return ColorString( 70, 187, 84, Alpha ); }
function C64F_BLUE( Alpha ) { return ColorString( 96, 0, 162, Alpha ); }
function C64F_YELLOW( Alpha ) { return ColorString( 192, 227, 120, Alpha ); }

function C64F_ORANGE( Alpha ) { return ColorString( 159, 106, 38, Alpha ); }
function C64F_BROWN( Alpha ) { return ColorString( 105, 90, 0, Alpha ); }
function C64F_LIGHT_RED( Alpha ) { return ColorString( 203, 121, 109, Alpha ); }
function C64F_DARK_GRAY( Alpha ) { return ColorString( 98, 98, 98, Alpha ); }
function C64F_MEDIUM_GRAY( Alpha ) { return ColorString( 137, 137, 137, Alpha ); }
function C64F_LIGHT_GREEN( Alpha ) { return ColorString( 138, 243, 148, Alpha ); }
function C64F_LIGHT_BLUE( Alpha ) { return ColorString( 149, 95, 211, Alpha ); }
function C64F_LIGHT_GRAY( Alpha ) { return ColorString( 173, 173, 173, Alpha ); }
// - -------------------------------------------------------------------------------------------------------------- - //
var RGB_BLACK		=	RGB(0,0,0);
var RGB_GREY		=	RGB(127,127,127);
var RGB_WHITE		=	RGB(255,255,255);

var RGB_RED			=	RGB(255,0,0);
var RGB_GREEN		=	RGB(0,255,0);
var RGB_BLUE		=	RGB(0,0,255);

var RGB_MAGENTA		=	RGB(255,0,255);
var RGB_YELLOW		=	RGB(255,255,0);
var RGB_CYAN		=	RGB(0,255,255);

var RGB_ORANGE		=	RGB(255,127,0);
var RGB_PINK		=	RGB(255,0,127);
var RGB_PURPLE		=	RGB(127,0,255);
var RGB_PUKE		=	RGB(127,255,0);
var RGB_MINT		=	RGB(0,255,127);
var RGB_SKY			=	RGB(0,127,255);

var RGB_DEFAULT		=	RGB_WHITE;
// - -------------------------------------------------------------------------------------------------------------- - //
function RGBF_BLACK		(Alpha) { return ColorString(0,0,0,Alpha); }
function RGBF_GREY		(Alpha) { return ColorString(127,127,127,Alpha); }
function RGBF_WHITE		(Alpha) { return ColorString(255,255,255,Alpha); }

function RGBF_RED		(Alpha) { return ColorString(255,0,0,Alpha); }
function RGBF_GREEN		(Alpha) { return ColorString(0,255,0,Alpha); }
function RGBF_BLUE		(Alpha) { return ColorString(0,0,255,Alpha); }

function RGBF_MAGENTA	(Alpha) { return ColorString(255,0,255,Alpha); }
function RGBF_YELLOW	(Alpha) { return ColorString(255,255,0,Alpha); }
function RGBF_CYAN		(Alpha) { return ColorString(0,255,255,Alpha); }

function RGBF_ORANGE	(Alpha) { return ColorString(255,127,0,Alpha); }
function RGBF_PINK		(Alpha) { return ColorString(255,0,127,Alpha); }
function RGBF_PURPLE	(Alpha) { return ColorString(127,0,255,Alpha); }
function RGBF_PUKE		(Alpha) { return ColorString(127,255,0,Alpha); }
function RGBF_MINT		(Alpha) { return ColorString(0,255,127,Alpha); }
function RGBF_SKY		(Alpha) { return ColorString(0,127,255,Alpha); }
// - -------------------------------------------------------------------------------------------------------------- - //
