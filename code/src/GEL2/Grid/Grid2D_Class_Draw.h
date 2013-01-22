// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL2_GRID_GRID2D_CLASS_DRAW_H__
#define __GEL2_GRID_GRID2D_CLASS_DRAW_H__
// - ------------------------------------------------------------------------------------------ - //
// Drawing Code //		
// - ------------------------------------------------------------------------------------------ - //
//DrawRadiusRect
//DrawRadiusFilledRect

// Add a function for generating a mask from a Grid.  I.e. all tiles that match a pattern, or //
//   dont match a pattern.  //
// Perhaps have a distinct MaskGrid type (Grid2D<int>), and functions for generating either //
//   a MaskGrid or a regular Grid copy. //

// Add a function for testing "per pixel collision" style for contacts between two placed //
//   overlapping grids.  This is needed (preferred) for a tetris move verification function. //

// Add a function for shifting the contents of a grid //

// Add equivalent functions for Adjacency searching (GenerateAdjacentDistanceGrid, ...) //
// - ------------------------------------------------------------------------------------------ - //
template< typename tType >
void Grid2D<tType>::_DrawHLine( const int x, const int y, const int _w, const tType& Value ) {
	for ( szt idx = x; idx < x+_w; idx++ ) {
		operator()(idx,y) = Value;
	}
}
// - ------------------------------------------------------------------------------------------ - //
template< typename tType >
void Grid2D<tType>::DrawHLine( int x, const int y, int _w, const tType& Value ) {
	if ( y < 0 )
		return;
	else if ( y >= Height() )
		return;
		
	if ( x < 0 ) {
		_w += x;
		x = 0;
	}		
	else if ( x >= Width() )
		return;
	
	if ( _w < 1 )
		return;
	else if ( x+_w >= Width() )
		_w = Width()-x;
	
	_DrawHLine( x, y, _w, Value );
}
// - ------------------------------------------------------------------------------------------ - //
template< typename tType >
void Grid2D<tType>::_DrawVLine( const int x, const int y, const int _h, const tType& Value ) {
	for ( szt idx = y; idx < y+_h; idx++ ) {
		operator()(x,idx) = Value;
	}
}
// - ------------------------------------------------------------------------------------------ - //
template< typename tType >
void Grid2D<tType>::DrawVLine( const int x, int y, int _h, const tType& Value ) {
	if ( x < 0 )
		return;
	else if ( x >= Width() )
		return;
		
	if ( y < 0 ) {
		_h += y;
		y = 0;
	}		
	else if ( y >= Height() )
		return;

	if ( _h < 1 )
		return;
	else if ( y+_h >= Height() )
		_h = Height()-y;
	
	_DrawVLine( x, y, _h, Value );
}
// - ------------------------------------------------------------------------------------------ - //
template< typename tType >
void Grid2D<tType>::DrawRect( const int x, const int y, const int _w, const int _h, const tType& Value ) {
	DrawHLine( x, y, _w, Value );
	DrawHLine( x, y-1+_h, _w, Value );

	DrawVLine( x, y+1, _h-2, Value );
	DrawVLine( x-1+_w, y+1, _h-2, Value );
}
// - ------------------------------------------------------------------------------------------ - //
template< typename tType >
void Grid2D<tType>::DrawRectFill( int x, int y, int _w, int _h, const tType& Value ) {
	if ( x < 0 ) {
		_w += x;
		x = 0;
	}
	else if ( x >= Width() )
		return;
		
	if ( y < 0 ) {
		_h += y;
		y = 0;
	}		
	else if ( y >= Height() )
		return;

	if ( _w < 1 )
		return;
	else if ( x+_w >= Width() )
		_w = Width()-x;
	
	if ( _h < 1 )
		return;
	else if ( y+_h >= Height() )
		_h = Height()-y;

	for ( szt idx = y; idx < y+_h; idx++ ) {
		_DrawHLine( x, idx, _w, Value );
	}
}
// - ------------------------------------------------------------------------------------------ - //
template< typename tType >
void Grid2D<tType>::DrawLine( int x1, int y1, int x2, int y2, const tType& Value ) {
	int xDiff = x2-x1;
	int yDiff = y2-y1;
	
	int SignX = 1;
	int SignY = 1;
	int xDiffABS = xDiff;
	int yDiffABS = yDiff;
	
	// Figure out the sign of xDiff //
	if ( xDiff < 0 ) {
		SignX = -1;
		xDiffABS = -xDiff;
	}

	// Figure out the sign of yDiff //
	if ( yDiff < 0 ) {
		SignY = -1;
		yDiffABS = -yDiff;
	}
	
	// Wider than Tall //
	if ( xDiffABS >= yDiffABS ) {
		// Swap if X is backwards //
		if ( x1 > x2 ) {
			int Temp = x2;
			x2 = x1;
			x1 = Temp;
			Temp = y2;
			y2 = y1;
			y1 = Temp;
			
			xDiff = -xDiff;
		}
		
		float Slope = 0;
		if ( xDiffABS != 0 ) {
			Slope = (float)yDiff / (float)xDiff;
			Slope *= SignX;
		}
		
		int StartX = 0;
		if ( x1 < 0 )
			StartX = -x1;
		else if ( x1 > Width() )
			return;

		int EndX = xDiff+1;
		if ( x2 < 0 )
			return;
		else if ( x2 > Width() )
			EndX = (xDiff) - (x2-Width());
		
		for ( szt idx = StartX; idx < EndX; idx++ ) {
			operator()( x1 + idx, y1 + round(Slope*(float)(idx)) ) = Value;
		}
	}
	// Taller than Wide //
	else {
		// Swap if Y is backwards //
		if ( y1 > y2 ) {
			int Temp = x2;
			x2 = x1;
			x1 = Temp;
			Temp = y2;
			y2 = y1;
			y1 = Temp;
			
			yDiff = -yDiff;
		}

		float Slope = 0;
		if ( yDiffABS != 0 ) {
			Slope = (float)xDiff / (float)yDiff;
			Slope *= SignY;
		}

		int StartY = 0;
		if ( y1 < 0 )
			StartY = -y1;
		else if ( y1 > Height() )
			return;

		int EndY = yDiff+1;
		if ( y2 < 0 )
			return;
		else if ( y2 > Height() )
			EndY = (yDiff) - (y2-Height());
	
		for ( szt idx = StartY; idx < EndY; idx++ ) {
			operator()( x1 + round(Slope*(float)(idx)), y1 + idx ) = Value;
		}			
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL2_GRID_GRID2D_CLASS_DRAW_H__ //
// - ------------------------------------------------------------------------------------------ - //
