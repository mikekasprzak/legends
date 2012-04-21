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
	
	//void gelDrawFillRect( float x, float y, float w, float h );
// - ------------------------------------------------------------------------------------------ - //
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_GRAPHICS_2D_H__
// - ------------------------------------------------------------------------------------------ - //
