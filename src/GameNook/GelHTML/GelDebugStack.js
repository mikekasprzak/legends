
// - -------------------------------------------------------------------------------------------------------------- - //
var DBGE_Text = 				1;
var DBGE_Rect = 				2;
var DBGE_RectFill = 			3;
var DBGE_Circle = 				4;
var DBGE_CircleFill = 			5;
var DBGE_Square = 				6;
var DBGE_SquareFill = 			7;
var DBGE_Diamond = 				8;
var DBGE_DiamondFill = 			9;
var DBGE_Cross = 				10;
var DBGE_X = 					11;

var DBGE_TriangleShape = 		16;
var DBGE_TriangleShapeFill = 	17;
var DBGE_QuadShape = 			18;
var DBGE_QuadShapeFill = 		19;

var DBGE_WedgeTopLeft = 		24;
var DBGE_WedgeTopLeftFill = 	25;
var DBGE_WedgeBottomLeft = 		26;
var DBGE_WedgeBottomLeftFill = 	27;
var DBGE_WedgeTopRight = 		28;
var DBGE_WedgeTopRightFill = 	29;
var DBGE_WedgeBottomRight = 	30;
var DBGE_WedgeBottomRightFill =	31;
// - -------------------------------------------------------------------------------------------------------------- - //


// - -------------------------------------------------------------------------------------------------------------- - //
function cDebugElements() {
	this.Current = 0;
	this.Data = [];
}
// - -------------------------------------------------------------------------------------------------------------- - //
cDebugElements.prototype.Add = function( _Type ) {
	this.Current = this.Data.length;
	this.Data.push( { Type: _Type, LifeTime: 1 } );
}
// - -------------------------------------------------------------------------------------------------------------- - //
cDebugElements.prototype.SetColor = function( r, g, b, a ) {
	if ( typeof a === 'undefined' ) {
		this.Data[this.Current].Color = "rgb(" + r + "," + g + "," + b + ")";
	}
	else {
		this.Data[this.Current].Color = "rgba(" + r + "," + g + "," + b + "," + (a / 255) + ")";
	}	
}
// - -------------------------------------------------------------------------------------------------------------- - //
cDebugElements.prototype.SetColorString = function( str ) {
	this.Data[this.Current].Color = str;
}
// - -------------------------------------------------------------------------------------------------------------- - //
cDebugElements.prototype.SetArgs = function( _args ) {
	this.Data[this.Current].Args = _args;
}
// - -------------------------------------------------------------------------------------------------------------- - //
cDebugElements.prototype.SetLifeTime = function( _Life ) {
	this.Data[this.Current].LifeTime = _Life;
}
// - -------------------------------------------------------------------------------------------------------------- - //


// - -------------------------------------------------------------------------------------------------------------- - //
cDebugElements.prototype.Step = function() {
	for ( var idx = 0; idx < this.Data.length; idx++ ) {
		if ( --this.Data[idx].LifeTime == 0 ) {
			this.Data.splice( idx, 1 );			
			idx--;
		}
	}
}
// - -------------------------------------------------------------------------------------------------------------- - //
cDebugElements.prototype.Draw = function() {
	for ( var idx = 0; idx < this.Data.length; idx++ ) {
		ctx.fillStyle = this.Data[idx].Color;
		ctx.strokeStyle = this.Data[idx].Color;
		
		switch ( this.Data[idx].Type ) {
			case 0:
				// Unknown //
				break;
			case DBGE_Text:
				gelDrawTextCenter( this.Data[idx].Args[3], this.Data[idx].Args[0], this.Data[idx].Args[1], this.Data[idx].Args[2], "Commodore" );
				break;
			case DBGE_Rect:
				gelDrawRect( this.Data[idx].Args[0], this.Data[idx].Args[1], this.Data[idx].Args[2], this.Data[idx].Args[3] );
				break;
			case DBGE_RectFill:
				gelDrawRectFill( this.Data[idx].Args[0], this.Data[idx].Args[1], this.Data[idx].Args[2], this.Data[idx].Args[3] );
				break;
			case DBGE_Circle:
				gelDrawCircle( this.Data[idx].Args[0], this.Data[idx].Args[1], this.Data[idx].Args[2] );
				break;
			case DBGE_CircleFill:
				gelDrawCircleFill( this.Data[idx].Args[0], this.Data[idx].Args[1], this.Data[idx].Args[2] );
				break;
			case DBGE_Square:
				gelDrawSquare( this.Data[idx].Args[0], this.Data[idx].Args[1], this.Data[idx].Args[2] );
				break;
			case DBGE_SquareFill:
				gelDrawSquareFill( this.Data[idx].Args[0], this.Data[idx].Args[1], this.Data[idx].Args[2] );
				break;
			case DBGE_Diamond:
				gelDrawDiamond( this.Data[idx].Args[0], this.Data[idx].Args[1], this.Data[idx].Args[2] );
				break;
			case DBGE_DiamondFill:
				gelDrawDiamondFill( this.Data[idx].Args[0], this.Data[idx].Args[1], this.Data[idx].Args[2] );
				break;
			case DBGE_Cross:
				gelDrawCross( this.Data[idx].Args[0], this.Data[idx].Args[1], this.Data[idx].Args[2] );
				break;
			case DBGE_X:
				gelDrawX( this.Data[idx].Args[0], this.Data[idx].Args[1], this.Data[idx].Args[2] );
				break;
			case DBGE_TriangleShape:
				gelDrawTriangleShape( this.Data[idx].Args[0], this.Data[idx].Args[1], this.Data[idx].Args[2], this.Data[idx].Args[3], this.Data[idx].Args[4], this.Data[idx].Args[5] );
				break;
			case DBGE_TriangleShapeFill:
				gelDrawTriangleShapeFill( this.Data[idx].Args[0], this.Data[idx].Args[1], this.Data[idx].Args[2], this.Data[idx].Args[3], this.Data[idx].Args[4], this.Data[idx].Args[5] );
				break;
			case DBGE_QuadShape:
				gelDrawQuadShape( this.Data[idx].Args[0], this.Data[idx].Args[1], this.Data[idx].Args[2], this.Data[idx].Args[3], this.Data[idx].Args[4], this.Data[idx].Args[5], this.Data[idx].Args[6], this.Data[idx].Args[7] );
				break;
			case DBGE_QuadShapeFill:
				gelDrawQuadShapeFill( this.Data[idx].Args[0], this.Data[idx].Args[1], this.Data[idx].Args[2], this.Data[idx].Args[3], this.Data[idx].Args[4], this.Data[idx].Args[5], this.Data[idx].Args[6], this.Data[idx].Args[7] );
				break;
			case DBGE_WedgeTopLeft:
				gelDrawWedgeTopLeft( this.Data[idx].Args[0], this.Data[idx].Args[1], this.Data[idx].Args[2], this.Data[idx].Args[3] );
				break;
			case DBGE_WedgeTopLeftFill:
				gelDrawWedgeTopLeftFill( this.Data[idx].Args[0], this.Data[idx].Args[1], this.Data[idx].Args[2], this.Data[idx].Args[3] );
				break;
			case DBGE_WedgeBottomLeft:
				gelDrawWedgeBottomLeft( this.Data[idx].Args[0], this.Data[idx].Args[1], this.Data[idx].Args[2], this.Data[idx].Args[3] );
				break;
			case DBGE_WedgeBottomLeftFill:
				gelDrawWedgeBottomLeftFill( this.Data[idx].Args[0], this.Data[idx].Args[1], this.Data[idx].Args[2], this.Data[idx].Args[3] );
				break;
			case DBGE_WedgeTopRight:
				gelDrawWedgeTopRight( this.Data[idx].Args[0], this.Data[idx].Args[1], this.Data[idx].Args[2], this.Data[idx].Args[3] );
				break;
			case DBGE_WedgeTopRightFill:
				gelDrawWedgeTopRightFill( this.Data[idx].Args[0], this.Data[idx].Args[1], this.Data[idx].Args[2], this.Data[idx].Args[3] );
				break;
			case DBGE_WedgeBottomRight:
				gelDrawWedgeBottomRight( this.Data[idx].Args[0], this.Data[idx].Args[1], this.Data[idx].Args[2], this.Data[idx].Args[3] );
				break;
			case DBGE_WedgeBottomRightFill:
				gelDrawWedgeBottomRightFill( this.Data[idx].Args[0], this.Data[idx].Args[1], this.Data[idx].Args[2], this.Data[idx].Args[3] );
				break;
		};
	}	
}
// - -------------------------------------------------------------------------------------------------------------- - //
