// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_GRAPHICS_2D_H__
#define __GEL_GRAPHICS_2D_H__
// - ------------------------------------------------------------------------------------------ - //
extern "C" {
// - ------------------------------------------------------------------------------------------ - //	
	void gelGraphicsInit( int Width, int Height );
	void gelGraphicsExit();
	
	void gelSetColor( int r, int g, int b, int a );
	void gelDrawCircle( float x, float y, float Radius );
	void gelDrawCircleFill( float x, float y, float Radius );

	void gelDrawLine( float x1, float y1, float x2, float y2 );
	void gelDrawText( float x, float y, const char* Text );

	void gelDrawTextCenter( const char* Text, float x, float y, int SizePx, const char* Font );
	void gelDrawTextLeft( const char* Text, float x, float y, int SizePx, const char* Font );
	void gelDrawTextRight( const char* Text, float x, float y, int SizePx, const char* Font );
	
	void gelDrawRect( float x, float y, float w, float h );
	void gelDrawRectFill( float x, float y, float w, float h );
	
	//void gelDrawFillRect( float x, float y, float w, float h );
	
	int gelLoadImage( const char* FileName );
	void gelBindImage( int ImageId );
	void gelDrawImage( float x, float y );
	void gelDrawImageCrop( float sx, float sy, float sw, float sh, float dx, float dy );

	int gelLoadTileset( const char* FileName, int w, int h );
	void gelBindTileset( int ImageId );
	void gelDrawTile( int Tile, float x, float y );
	void gelDrawTileFlipX( int Tile, float x, float y );
	void gelDrawTileFlipY( int Tile, float x, float y );
	void gelDrawTileFlipXY( int Tile, float x, float y );
	
	void gelDrawTileCentered( int Tile, float x, float y );
	void gelDrawTileBaseline( int Tile, float x, float y );
	
	void gelDrawTiles( 
		const short* DataPtr, 
		int MapWidth, int MapHeight, 
		int StartX, int StartY, 
		int EndX, int EndY, 
		int TileMod, 
		int OffsetX, int OffsetY
		);
		
// - ------------------------------------------------------------------------------------------ - //
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_GRAPHICS_2D_H__
// - ------------------------------------------------------------------------------------------ - //
