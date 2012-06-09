// - -------------------------------------------------------------------------------------------------------------- - //
// GelGraphics2D - 2D HTML5 Canvas Drawing Code //
// - -------------------------------------------------------------------------------------------------------------- - //
//"use strict";
// - -------------------------------------------------------------------------------------------------------------- - //
function _gelGraphicsInit( width, height ) {
	Log( "Original Canvas Size: " + Module.canvas.width + ", " + Module.canvas.height );

    try {
		Module.ctx = Module.canvas.getContext("2d");
		if ( !Module.ctx )
			throw 'ERROR: Could not get context!';
			
		Module.canvas.style.backgroundColor = "black";

	    Module.canvas.width = width;
	    Module.canvas.height = height;
    } catch (e) {
		Module.print('ERROR: Canvas not available!');
    }	

	Log( "New Canvas Size: " + Module.canvas.width + ", " + Module.canvas.height );
}
// - -------------------------------------------------------------------------------------------------------------- - //
function _gelGraphicsExit() {	
}
// - -------------------------------------------------------------------------------------------------------------- - //

// - -------------------------------------------------------------------------------------------------------------- - //
function _gelCenterImage( img, x, y ) {
	Module.ctx.drawImage( img, x-(img.width >> 1), y-(img.height >> 1) );
}
// - -------------------------------------------------------------------------------------------------------------- - //
function _gelCenterImage( img, x, y, scale_x, scale_y ) {
	Module.ctx.drawImage( img, x-((img.width * scale_x) >> 1), y-((img.height * scale_y) >> 1), img.width * scale_x, img.height * scale_y );
}
// - -------------------------------------------------------------------------------------------------------------- - //

// - -------------------------------------------------------------------------------------------------------------- - //
function gelDrawTextCenter( _Text, _x, _y, _Size, _Font ) {
	Module.ctx.font = "" + _Size + "px " + _Font;
	Module.ctx.textAlign = "left";
	Module.ctx.textBaseline = "top";
	
	// Hack: The C64 font I was using wouldn't perfectly Text Align center, so I manually center //
	var TextWidth = Math.floor( Module.ctx.measureText(_Text).width ) >> 1;
	var TextHeight = Math.floor( _Size ) >> 1;

	Module.ctx.fillText( _Text, Math.floor(_x - TextWidth), Math.floor(_y - TextHeight) );
}
// - -------------------------------------------------------------------------------------------------------------- - //
function _gelDrawTextCenter( _Text, _x, _y, _Size, _Font ) {
	gelDrawTextCenter( Pointer_stringify(_Text), _x, _y, _Size, Pointer_stringify(_Font) );
}
// - -------------------------------------------------------------------------------------------------------------- - //
function gelDrawTextLeft( _Text, _x, _y, _Size, _Font ) {
	Module.ctx.font = "" + _Size + "px " + _Font;
	Module.ctx.textAlign = "left";
	Module.ctx.textBaseline = "top";
	
	// Hack: The C64 font I was using wouldn't perfectly Text Align center, so I manually center //
//	var TextWidth = Math.floor( Module.ctx.measureText(_Text).width ) >> 1;
	var TextHeight = Math.floor( _Size ) >> 1;

	Module.ctx.fillText( _Text, Math.floor(_x), Math.floor(_y - TextHeight) );
}
// - -------------------------------------------------------------------------------------------------------------- - //
function _gelDrawTextLeft( _Text, _x, _y, _Size, _Font ) {
	gelDrawTextLeft( Pointer_stringify(_Text), _x, _y, _Size, Pointer_stringify(_Font) );
}
// - -------------------------------------------------------------------------------------------------------------- - //
function gelDrawTextRight( _Text, _x, _y, _Size, _Font ) {
	Module.ctx.font = "" + _Size + "px " + _Font;
	Module.ctx.textAlign = "left";
	Module.ctx.textBaseline = "top";
	
	// Hack: The C64 font I was using wouldn't perfectly Text Align center, so I manually center //
	var TextWidth = Math.floor( Module.ctx.measureText(_Text).width );
	var TextHeight = Math.floor( _Size ) >> 1;

	Module.ctx.fillText( _Text, Math.floor(_x - TextWidth), Math.floor(_y - TextHeight) );
}
// - -------------------------------------------------------------------------------------------------------------- - //
function _gelDrawTextRight( _Text, _x, _y, _Size, _Font ) {
	gelDrawTextRight( Pointer_stringify(_Text), _x, _y, _Size, Pointer_stringify(_Font) );
}
// - -------------------------------------------------------------------------------------------------------------- - //

// - -------------------------------------------------------------------------------------------------------------- - //
function _gelSetColor( r, g, b, a ) {
//	Log( typeof a );
	if ( typeof a === 'undefined' ) {
		Module.ctx.fillStyle = "rgb(" + r + "," + g + "," + b + ")";
		Module.ctx.strokeStyle = Module.ctx.fillStyle;
	}
	else {
		Module.ctx.fillStyle = "rgba(" + r + "," + g + "," + b + "," + (a / 255) + ")";
		Module.ctx.strokeStyle = Module.ctx.fillStyle;
	}
}
// - -------------------------------------------------------------------------------------------------------------- - //
function _gelSetColorString( str ) {
	Module.ctx.fillStyle = str;
	Module.ctx.strokeStyle = str;
}
// - -------------------------------------------------------------------------------------------------------------- - //

// - -------------------------------------------------------------------------------------------------------------- - //
function _gelDrawRectFill( x, y, w, h ) {
	Module.ctx.fillRect( x, y, w, h );
}
// - -------------------------------------------------------------------------------------------------------------- - //
function _gelDrawPixelThinRect( x, y, w, h ) {
	Module.ctx.fillRect( x, y, w, 1 );
	Module.ctx.fillRect( x+1, y+h-1, w-1, 1 );
	Module.ctx.fillRect( x, y+1, 1, h-1 );
	Module.ctx.fillRect( x+w-1, y+1, 1, h-2 );
}
// - -------------------------------------------------------------------------------------------------------------- - //
function _gelDrawRect( x, y, w, h ) {
	Module.ctx.strokeRect( x, y, w, h );
}
// - -------------------------------------------------------------------------------------------------------------- - //
function _gelClearRect( x, y, w, h ) {
	Module.ctx.clearRect( x, y, w, h );
}
// - -------------------------------------------------------------------------------------------------------------- - //

// - -------------------------------------------------------------------------------------------------------------- - //
function _gelDrawTriangleShape( x1, y1, x2, y2, x3, y3 ) {
	Module.ctx.beginPath();
	Module.ctx.moveTo( x1, y1 );

	Module.ctx.lineTo( x2, y2 );
	Module.ctx.lineTo( x3, y3 );
	Module.ctx.lineTo( x1, y1 );

	Module.ctx.closePath();
	Module.ctx.stroke();
}
// - -------------------------------------------------------------------------------------------------------------- - //
function _gelDrawTriangleShapeFill( x1, y1, x2, y2, x3, y3 ) {
	Module.ctx.beginPath();
	Module.ctx.moveTo( x1, y1 );

	Module.ctx.lineTo( x2, y2 );
	Module.ctx.lineTo( x3, y3 );
	Module.ctx.lineTo( x1, y1 );

	Module.ctx.closePath();
	Module.ctx.fill();
}
// - -------------------------------------------------------------------------------------------------------------- - //
function _gelDrawQuadShape( x1, y1, x2, y2, x3, y3, x4, y4 ) {
	Module.ctx.beginPath();
	Module.ctx.moveTo( x1, y1 );

	Module.ctx.lineTo( x2, y2 );
	Module.ctx.lineTo( x3, y3 );
	Module.ctx.lineTo( x4, y4 );
	Module.ctx.lineTo( x1, y1 );

	Module.ctx.closePath();
	Module.ctx.stroke();
}
// - -------------------------------------------------------------------------------------------------------------- - //
function _gelDrawQuadShapeFill( x1, y1, x2, y2, x3, y3, x4, y4 ) {
	Module.ctx.beginPath();
	Module.ctx.moveTo( x1, y1 );

	Module.ctx.lineTo( x2, y2 );
	Module.ctx.lineTo( x3, y3 );
	Module.ctx.lineTo( x4, y4 );
	Module.ctx.lineTo( x1, y1 );

	Module.ctx.closePath();
	Module.ctx.fill();
}
// - -------------------------------------------------------------------------------------------------------------- - //

// - -------------------------------------------------------------------------------------------------------------- - //
function _gelDrawWedgeBottomRight( x1, y1, w, h ) {
	var x2 = x1+w;
	var y2 = y1+h;
	_gelDrawTriangleShape( x2,y1, x2,y2, x1,y2 );
}
// - -------------------------------------------------------------------------------------------------------------- - //
function _gelDrawWedgeBottomLeft( x1, y1, w, h ) {
	var x2 = x1+w;
	var y2 = y1+h;
	_gelDrawTriangleShape( x1,y1, x2,y2, x1,y2 );
}
// - -------------------------------------------------------------------------------------------------------------- - //
function _gelDrawWedgeTopRight( x1, y1, w, h ) {
	var x2 = x1+w;
	var y2 = y1+h;
	_gelDrawTriangleShape( x1,y1, x2,y1, x2,y2 );
}
// - -------------------------------------------------------------------------------------------------------------- - //
function _gelDrawWedgeTopLeft( x1, y1, w, h ) {
	var x2 = x1+w;
	var y2 = y1+h;
	_gelDrawTriangleShape( x1,y1, x2,y1, x1,y2 );
}
// - -------------------------------------------------------------------------------------------------------------- - //
function _gelDrawWedgeBottomRightFill( x1, y1, w, h ) {
	var x2 = x1+w;
	var y2 = y1+h;
	_gelDrawTriangleShapeFill( x2,y1, x2,y2, x1,y2 );
}
// - -------------------------------------------------------------------------------------------------------------- - //
function _gelDrawWedgeBottomLeftFill( x1, y1, w, h ) {
	var x2 = x1+w;
	var y2 = y1+h;
	_gelDrawTriangleShapeFill( x1,y1, x2,y2, x1,y2 );
}
// - -------------------------------------------------------------------------------------------------------------- - //
function _gelDrawWedgeTopRightFill( x1, y1, w, h ) {
	var x2 = x1+w;
	var y2 = y1+h;
	_gelDrawTriangleShapeFill( x1,y1, x2,y1, x2,y2 );
}
// - -------------------------------------------------------------------------------------------------------------- - //
function _gelDrawWedgeTopLeftFill( x1, y1, w, h ) {
	var x2 = x1+w;
	var y2 = y1+h;
	_gelDrawTriangleShapeFill( x1,y1, x2,y1, x1,y2 );
}
// - -------------------------------------------------------------------------------------------------------------- - //

// - -------------------------------------------------------------------------------------------------------------- - //
function _gelDrawCircleFill( x, y, Radius ) {
	Module.ctx.beginPath();
	Module.ctx.arc( x, y, Radius, 0, Math.PI*2, true); 
	Module.ctx.closePath();
	Module.ctx.fill();	
}
// - -------------------------------------------------------------------------------------------------------------- - //
function _gelDrawCircle( x, y, Radius ) {
	Module.ctx.beginPath();
	Module.ctx.arc( x, y, Radius, 0, Math.PI*2, true); 
	Module.ctx.closePath();
	Module.ctx.stroke();
}
// - -------------------------------------------------------------------------------------------------------------- - //
function _gelDrawSquareFill( x, y, Radius ) {
	Module.ctx.fillRect( x-Radius, y-Radius, Radius+Radius, Radius+Radius );
}
// - -------------------------------------------------------------------------------------------------------------- - //
function _gelDrawSquare( x, y, Radius ) {
	Module.ctx.strokeRect( x-Radius, y-Radius, Radius+Radius, Radius+Radius );
}
// - -------------------------------------------------------------------------------------------------------------- - //
function _gelDrawPixelThinSquare( x, y, Radius ) {
	_gelDrawPixelThinRect( x-Radius, y-Radius, Radius+Radius, Radius+Radius );
}
// - -------------------------------------------------------------------------------------------------------------- - //
function _gelDrawDiamondFill( x, y, Radius ) {
	Module.ctx.beginPath();
	Module.ctx.moveTo( x-Radius, y );

	Module.ctx.lineTo( x, y-Radius );
	Module.ctx.lineTo( x+Radius, y );
	Module.ctx.lineTo( x, y+Radius );
	Module.ctx.lineTo( x-Radius, y );
	
	Module.ctx.closePath();
	Module.ctx.fill();	
}
// - -------------------------------------------------------------------------------------------------------------- - //
function _gelDrawDiamond( x, y, Radius ) {
	Module.ctx.beginPath();
	Module.ctx.moveTo( x-Radius, y );

	Module.ctx.lineTo( x, y-Radius );
	Module.ctx.lineTo( x+Radius, y );
	Module.ctx.lineTo( x, y+Radius );
	Module.ctx.lineTo( x-Radius, y );

	Module.ctx.closePath();
	Module.ctx.stroke();
}
// - -------------------------------------------------------------------------------------------------------------- - //
function _gelDrawCross( x, y, Radius ) {
	Module.ctx.beginPath();

	Module.ctx.moveTo( x-Radius, y );
	Module.ctx.lineTo( x+Radius, y );

	Module.ctx.moveTo( x, y-Radius );
	Module.ctx.lineTo( x, y+Radius );

	Module.ctx.closePath();
	Module.ctx.stroke();
}
// - -------------------------------------------------------------------------------------------------------------- - //
function _gelDrawX( x, y, Radius ) {
	Module.ctx.beginPath();

	Module.ctx.moveTo( x-Radius, y-Radius );
	Module.ctx.lineTo( x+Radius, y+Radius );

	Module.ctx.moveTo( x+Radius, y-Radius );
	Module.ctx.lineTo( x-Radius, y+Radius );

	Module.ctx.closePath();
	Module.ctx.stroke();
}
// - -------------------------------------------------------------------------------------------------------------- - //

// - -------------------------------------------------------------------------------------------------------------- - //
function _gelDrawLine( x1, y1, x2, y2 ) {
	Module.ctx.beginPath();

	Module.ctx.moveTo( x1, y1 );
	Module.ctx.lineTo( x2, y2 );

	Module.ctx.closePath();
	Module.ctx.stroke();
}
// - -------------------------------------------------------------------------------------------------------------- - //
function _gelDrawText( _x, _y, _Text ) {
	var _Size = 16;
	var _Font = "Commodore";
	
	Module.ctx.font = "" + _Size + "px " + _Font;
	Module.ctx.textAlign = "left";
	Module.ctx.textBaseline = "top";

	// Hack: The C64 font I was using wouldn't perfectly Text Align center, so I manually center //
	var TextWidth = Math.floor( Module.ctx.measureText(_Text).width ) >> 1;
	var TextHeight = Math.floor( _Size ) >> 1;

	Module.ctx.fillText( Pointer_stringify(_Text), Math.floor(_x - TextWidth), Math.floor(_y - TextHeight) );
}
// - -------------------------------------------------------------------------------------------------------------- - //

// - -------------------------------------------------------------------------------------------------------------- - //
var ImageData = new Array();
var CurrentImage;
// - -------------------------------------------------------------------------------------------------------------- - //
function _gelLoadImage( FileName ) {
	var NewImage = new Image;
//	ImageData.Data.onload = function() {
//		_super.CellW = _super.Data.width / _XCells;
//		_super.CellH = _super.Data.height / _YCells;
//	};
	NewImage.src = Pointer_stringify(FileName);//allocate(intArrayFromString(FileName), 'i8', ALLOC_STACK);//FileName;
	
	var Index = ImageData.length;
	ImageData.push( NewImage );
	return Index;
}
// - -------------------------------------------------------------------------------------------------------------- - //
function _gelBindImage( ImageId ) {
	CurrentImage = ImageData[ ImageId ];
}
// - -------------------------------------------------------------------------------------------------------------- - //
function _gelDrawImage( sx, sy ) {
	Module.ctx.drawImage( CurrentImage, sx, sy );
}
// - -------------------------------------------------------------------------------------------------------------- - //
function _gelDrawImageCrop( sx, sy, sw, sh, dx, dy ) {
	Module.ctx.drawImage( CurrentImage, sx, sy, sw, sh, dx, dy, sw, sh );
}
// - -------------------------------------------------------------------------------------------------------------- - //


// - -------------------------------------------------------------------------------------------------------------- - //
function _gelLoadTileset( FileName, w, h ) {
	var NewImage = new Image;
	NewImage.src = Pointer_stringify(FileName);
	
	NewImage.Tileset = true;
	NewImage.TileWidth = w;
	NewImage.TileHeight = h;
	
	NewImage.onload = function() {
		NewImage.WidthInTiles = NewImage.width / w;
		NewImage.HeightInTiles = NewImage.height / h;
	};
	
	var Index = ImageData.length;
	ImageData.push( NewImage );
	return Index;
}
// - -------------------------------------------------------------------------------------------------------------- - //
function _gelBindTileset( ImageId ) {
	CurrentImage = ImageData[ ImageId ];
}
// - -------------------------------------------------------------------------------------------------------------- - //
function _gelDrawTile( Tile, dx, dy ) {
	Module.ctx.drawImage( 
		CurrentImage, 
		Math.floor( Tile % CurrentImage.WidthInTiles ) * CurrentImage.TileWidth, Math.floor( Tile / CurrentImage.WidthInTiles ) * CurrentImage.TileHeight,
		CurrentImage.TileWidth, CurrentImage.TileHeight, 
		dx, dy,
		CurrentImage.TileWidth, CurrentImage.TileHeight 
		);
}
// - -------------------------------------------------------------------------------------------------------------- - //
function _gelDrawTileCentered( Tile, dx, dy ) {
	Module.ctx.drawImage( 
		CurrentImage, 
		Math.floor( Tile % CurrentImage.WidthInTiles ) * CurrentImage.TileWidth, Math.floor( Tile / CurrentImage.WidthInTiles ) * CurrentImage.TileHeight,
		CurrentImage.TileWidth, CurrentImage.TileHeight, 
		dx - (CurrentImage.TileWidth>>1), dy - (CurrentImage.TileHeight>>1),
		CurrentImage.TileWidth, CurrentImage.TileHeight 
		);
}
// - -------------------------------------------------------------------------------------------------------------- - //
function _gelDrawTileBaseline( Tile, dx, dy ) {
	Module.ctx.drawImage( 
		CurrentImage, 
		Math.floor( Tile % CurrentImage.WidthInTiles ) * CurrentImage.TileWidth, Math.floor( Tile / CurrentImage.WidthInTiles ) * CurrentImage.TileHeight,
		CurrentImage.TileWidth, CurrentImage.TileHeight, 
		dx - (CurrentImage.TileWidth>>1), dy - (CurrentImage.TileHeight),
		CurrentImage.TileWidth, CurrentImage.TileHeight 
		);
}
// - -------------------------------------------------------------------------------------------------------------- - //
function _gelDrawTileFlipX( Tile, dx, dy ) {
	Module.ctx.scale(-1, 1);
	_gelDrawTile( Tile, -dx-CurrentImage.TileWidth, dy );
	Module.ctx.scale(-1, 1);
}
// - -------------------------------------------------------------------------------------------------------------- - //
function _gelDrawTileFlipY( Tile, dx, dy ) {
	Module.ctx.scale(1, -1);
	_gelDrawTile( Tile, dx, -dy-CurrentImage.TileHeight );
	Module.ctx.scale(1, -1);
}
// - -------------------------------------------------------------------------------------------------------------- - //
function _gelDrawTileFlipXY( Tile, dx, dy ) {
	Module.ctx.scale(-1, -1);
	_gelDrawTile( Tile, -dx-CurrentImage.TileWidth, -dy-CurrentImage.TileHeight );
	Module.ctx.scale(-1, -1);
}
// - -------------------------------------------------------------------------------------------------------------- - //


function _gelDrawTiles( DataPtr, MapWidth, MapHeight, StartX, StartY, EndX, EndY, TileMod, OffsetX, OffsetY ) {
	var Width = MapWidth * 2;
//	OffsetX = Math.floor( OffsetX );
//	OffsetY = Math.floor( OffsetY );

	var dx;
	var dy;
	
	for ( var _y = StartY; _y < EndY; _y++ ) {
		for ( var _x = StartX; _x < EndX; _x++ ) {
			//int Tile = (*MapLayer->Data[Layer])(_x, _y);
			var Tile = HEAP16[ (DataPtr + (Width*_y) + _x + _x) >> 1 ];//getValue( DataPtr + (Width*_y) + _x + _x, 'i16' );
			if ( Tile > 0 ) {
				Tile += TileMod;
				dx = ((_x - StartX) * CurrentImage.TileWidth) - OffsetX;
				dy = ((_y - StartY) * CurrentImage.TileHeight) - OffsetY;
				
				Module.ctx.drawImage( 
					CurrentImage, 
					Math.floor( Tile % CurrentImage.WidthInTiles ) * CurrentImage.TileWidth, Math.floor( Tile / CurrentImage.WidthInTiles ) * CurrentImage.TileHeight,
//					(Tile & 0x3F) << 3, (Tile >> 6) << 3,
					CurrentImage.TileWidth, CurrentImage.TileHeight, 
					dx, dy,
					CurrentImage.TileWidth, CurrentImage.TileHeight 
					);
			}
		}
	}	
}