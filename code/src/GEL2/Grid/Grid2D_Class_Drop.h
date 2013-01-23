// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL2_GRID_GRID2D_CLASS_DROP_H__
#define __GEL2_GRID_GRID2D_CLASS_DROP_H__
// - ------------------------------------------------------------------------------------------ - //
// Logical Functions for games that play on a grid and have some sort of gravity (i.e. Smiles) //
// NOTE: Any mentions of OffsetX and OffsetY define an edge. (+0,+1) is downward gravity.
// - ------------------------------------------------------------------------------------------ - //
//CanDrop( x, y, offx, offy, TestValue )
//CanRockfordDrop( ... )

//GenerateDropGrid( offx, offy, TestValue )
//GenerateRockfordDropGrid( offx, offy, TestValue) // 1, 2, 3, where 2 is down and others diagonals //

// NOTE: Standard dropping can move in large chunks safely, but rockford drops should move //
//   individual tiles only. The reasoning for this is because with a single drop step, blocks //
//   that are above can move in to place to cause the rockford drop logic to push a tile that //
//   would by default come out the left to the right.  Otherwise, it'll fill up the left side //
//   first, then the right side.  Lame.  //
// - -------------------------------------------------------------------------------------- - //
template< typename tType >
const int Grid2D<tType>::CanDrop( int x, int y, const int OffsetX, const int OffsetY, const tType& Value ) const {
	// Clip the incoming co-ordinates //
	x = AxisSaturateX( x );
	y = AxisSaturateY( y );
	
	// Bail if the tile is already empty //
	if ( operator()(x,y) == Value )
		return 0;
	
	// Generate and clip offset co-ordinate //
	int DownOffsetX = AxisSaturateX( x + OffsetX );
	int DownOffsetY = AxisSaturateY( y + OffsetY );
		
	// If the offset tile is our test value, then we can drop //
	return operator()( DownOffsetX, DownOffsetY ) == Value;
}
// - -------------------------------------------------------------------------------------- - //
template< typename tType >
const int Grid2D<tType>::CanRockfordDrop( int x, int y, const int OffsetX, const int OffsetY, const tType& Value ) const {
	// Clip the incoming co-ordinates //
	x = AxisSaturateX( x );
	y = AxisSaturateY( y );
	
	// Bail if the tile is already empty //
	if ( operator()(x,y) == Value )
		return 0;
	
	// Generate and clip the immediate offset co-ordinate //
	int DownOffsetX = AxisSaturateX( x + OffsetX );
	int DownOffsetY = AxisSaturateY( y + OffsetY );
	
	// Bail if we happened to clip ourselves to the same position (i.e. on a limit) //
	if ( (DownOffsetX == x) && (DownOffsetY == y) )
		return 0;

	// Test below //
	if ( operator()( DownOffsetX, DownOffsetY ) == Value )
		return 2;

		
	// Test to the left //
	if ( Saturate( x - OffsetY, y + OffsetX ) == Value ) {
		int DownX = AxisSaturateX( DownOffsetX - OffsetY );
		int DownY = AxisSaturateY( DownOffsetY + OffsetX );

		// Test below the left //
		if ( operator()( DownX, DownY ) == Value ) {
			return 1;
		}
	}
	
	// Test to the right //
	if ( Saturate( x + OffsetY, y - OffsetX ) == Value ) {
		int DownX = AxisSaturateX( DownOffsetX + OffsetY );
		int DownY = AxisSaturateY( DownOffsetY - OffsetX );

		// Test below the right //
		if ( operator()( DownX, DownY ) == Value ) {
			return 3;
		}
	}

	// No drops available //
	return 0;
}
// - -------------------------------------------------------------------------------------- - //

// - -------------------------------------------------------------------------------------- - //
template< typename tType >
const int Grid2D<tType>::CalcDropDistance( int x, int y, int OffsetX, int OffsetY, const tType& Value ) const {
	// TODO: Assert the Offsets.  There should always be a 1 and a 0 or a -1 and a 0. //
	
	// Clip the incoming co-ordinates //
	x = AxisSaturateX( x );
	y = AxisSaturateY( y );
	
	// Bail if the tile is already empty //
//		if ( operator()(x,y) == Value )
//			return 0;
		
	int DropDistance = 0;
	
	{
		// The offsets determine our sweeping order, so these are our sweeping order control //
		int StartX, StartY;
		int EndX, EndY;
		int IncrementX, IncrementY;
		
		// X axis change //
		if ( OffsetX > 0 ) {
			StartX = x + OffsetX;
			EndX = Width();
			IncrementX = 1;
		}
		else if ( OffsetX < 0 ) {
			StartX = x + OffsetX;
			EndX = -1;
			IncrementX = -1;
		}
		else {
			StartX = x;
			EndX = x + 1;
			IncrementX = 1;
		}
		
		// Y axis change //
		if ( OffsetY > 0 ) {
			StartY = y + OffsetY;
			EndY = Height();
			IncrementY = 1;
		}
		else if ( OffsetY < 0 ) {
			StartY = y + OffsetY;
			EndY = -1;
			IncrementY = -1;
		}
		else {
			StartY = y;
			EndY = y + 1;
			IncrementY = 1;
		}

		// Step through 			
		for ( int _x = StartX; _x != EndX; _x += IncrementX ) {
			for ( int _y = StartY; _y != EndY; _y += IncrementY ) {
				// If the offset tile is our test value, then we can drop //
				if ( operator()( _x, _y ) == Value ) {
					DropDistance++;
				}
				else {
					// Rather than double break, I'm just going to return //
					return DropDistance;
				}
			}
		}	
	}
	
	// If we hit an end boundery, the drop distance is finished //
	return DropDistance;
}
// - -------------------------------------------------------------------------------------- - //

// - -------------------------------------------------------------------------------------- - //
// Return a grid of all tiles that are allowed to drop //
template< typename tType >
const Grid2D<int> Grid2D<tType>::GenerateDropGrid( const int OffsetX, const int OffsetY, const tType& Value ) const {
	// Our drop grid //
	Grid2D<int> DropGrid( Width(), Height() );
	
	for ( int x = 0; x < Width(); x++ ) {
		for ( int y = 0; y < Height(); y++ ) {
			DropGrid( x, y ) = CanDrop( x, y, OffsetX, OffsetY, Value );
		}
	}
	
	// Return the Drop Grid //
	return DropGrid;
}
// - -------------------------------------------------------------------------------------- - //
// Return a grid of all tiles that are allowed to rockford drop //
template< typename tType >
const Grid2D<int> Grid2D<tType>::GenerateRockfordDropGrid( const int OffsetX, const int OffsetY, const tType& Value ) const {
	// Our drop grid //
	Grid2D<int> DropGrid( Width(), Height() );
	
	for ( int x = 0; x < Width(); x++ ) {
		for ( int y = 0; y < Height(); y++ ) {
			DropGrid( x, y ) = CanRockfordDrop( x, y, OffsetX, OffsetY, Value );
		}
	}
	
	// Return the Drop Grid //
	return DropGrid;
}
// - -------------------------------------------------------------------------------------- - //

// - -------------------------------------------------------------------------------------- - //
// Return a grid of all distances a tile can drop //
template< typename tType >
const Grid2D<int> Grid2D<tType>::GenerateDropDistanceGrid( const int OffsetX, const int OffsetY, const tType& Value ) const {
	// Our drop grid //
	Grid2D<int> DropGrid( Width(), Height() );
	
	for ( int x = 0; x < Width(); x++ ) {
		for ( int y = 0; y < Height(); y++ ) {
			if ( operator()( x, y ) == 0 ) {
				DropGrid( x, y ) = 0;
			}
			else {
				DropGrid( x, y ) = CalcDropDistance( x, y, OffsetX, OffsetY, Value );
			}
		}
	}
	
	// Return the Drop Grid //
	return DropGrid;
}
// - -------------------------------------------------------------------------------------- - //

// - -------------------------------------------------------------------------------------- - //
template< typename tType>
void Grid2D<tType>::ApplyDrop( const int x, const int y, const int OffsetX, const int OffsetY ) {
	Swap( x, y, x + OffsetX, y + OffsetY );
}
// - -------------------------------------------------------------------------------------- - //
template< typename tType>
void Grid2D<tType>::ApplyDropDistance( const int x, const int y, const int Distance, const int OffsetX, const int OffsetY ) {
	Swap( x, y, x + (OffsetX*Distance), y + (OffsetY*Distance) );	
}
// - -------------------------------------------------------------------------------------- - //
template< typename tType>
void Grid2D<tType>::ApplyRockfordDrop( const int x, const int y, const int DropType, const int OffsetX, const int OffsetY ) {
	// Left Drop //
	if ( DropType == 1 ) {
		int DownOffsetX = AxisSaturateX( x + OffsetX );
		int DownOffsetY = AxisSaturateY( y + OffsetY );

		Swap( x, y, DownOffsetX - OffsetY, DownOffsetY + OffsetX );
	}
	// Down Drop //
	else if ( DropType == 2 ) {
		Swap( x, y, x + OffsetX, y + OffsetY );
	}
	// Right Drop //
	else if ( DropType == 3 ) {
		int DownOffsetX = AxisSaturateX( x + OffsetX );
		int DownOffsetY = AxisSaturateY( y + OffsetY );

		Swap( x, y, DownOffsetX + OffsetY, DownOffsetY - OffsetX );			
	}
}
// - -------------------------------------------------------------------------------------- - //


// - -------------------------------------------------------------------------------------- - //
// NOTE: Applying a Drop or DropDistance Grid would be fine, but appling a RockfordDrop Grid //
//   wouldn't work, since rockford logic allows 2 tiles to overlap once solving. //
// - -------------------------------------------------------------------------------------- - //
template< typename tType>
void Grid2D<tType>::Drop( const int OffsetX, const int OffsetY ) {
	// TODO: Assert the Offsets.  There should always be a 1 and a 0 or a -1 and a 0. //

	// The offsets determine our sweeping order, so these are our sweeping order control //
	int StartX, StartY;
	int EndX, EndY;
	int IncrementX, IncrementY;
	
	// X axis change //
	if ( OffsetX <= 0 ) {
		StartX = 0;
		EndX = Width();
		IncrementX = 1;
	}
	else {
		StartX = Width() - 1;
		EndX = -1;
		IncrementX = -1;
	}
	
	// Y axis change //
	if ( OffsetY <= 0 ) {
		StartY = 0;
		EndY = Height();
		IncrementY = 1;
	}
	else 
	{
		StartY = Height() - 1;
		EndY = -1;
		IncrementY = -1;
	}
	
	// Depending on the offset, x or y should be the inner increment //
	if ( OffsetY == 0 ) {
		// Step through the Grid //
		for ( int x = StartX; x != EndX; x += IncrementX ) {
			for ( int y = StartY; y != EndY; y += IncrementY ) {
				if ( CanDrop( x, y, OffsetX, OffsetY ) )
					ApplyDrop( x, y, OffsetX, OffsetY );
			}
		}
	}
	else {
		// Step through the Grid //
		for ( int y = StartY; y != EndY; y += IncrementY ) {
			for ( int x = StartX; x != EndX; x += IncrementX ) {
				if ( CanDrop( x, y, OffsetX, OffsetY ) )
					ApplyDrop( x, y, OffsetX, OffsetY );
			}
		}
	}
}
// - -------------------------------------------------------------------------------------- - //

// - -------------------------------------------------------------------------------------- - //
template< typename tType>
void Grid2D<tType>::DoDropDistance( const int OffsetX, const int OffsetY ) {
	// TODO: Assert the Offsets.  There should always be a 1 and a 0 or a -1 and a 0. //

	// The offsets determine our sweeping order, so these are our sweeping order control //
	int StartX, StartY;
	int EndX, EndY;
	int IncrementX, IncrementY;
	
	// X axis change //
	if ( OffsetX <= 0 ) {
		StartX = 0;
		EndX = Width();
		IncrementX = 1;
	}
	else {
		StartX = Width() - 1;
		EndX = -1;
		IncrementX = -1;
	}
	
	// Y axis change //
	if ( OffsetY <= 0 ) {
		StartY = 0;
		EndY = Height();
		IncrementY = 1;
	}
	else 
	{
		StartY = Height() - 1;
		EndY = -1;
		IncrementY = -1;
	}
	
	// Depending on the offset, x or y should be the inner increment //
	if ( OffsetY == 0 ) {
		// Step through the Grid //
		for ( int x = StartX; x != EndX; x += IncrementX ) {
			for ( int y = StartY; y != EndY; y += IncrementY ) {
				if ( int Distance = CalcDropDistance( x, y, OffsetX, OffsetY ) )
					ApplyDropDistance( x, y, Distance, OffsetX, OffsetY );
			}
		}
	}
	else {
		// Step through the Grid //
		for ( int y = StartY; y != EndY; y += IncrementY ) {
			for ( int x = StartX; x != EndX; x += IncrementX ) {
				if ( int Distance = CalcDropDistance( x, y, OffsetX, OffsetY ) )
					ApplyDropDistance( x, y, Distance, OffsetX, OffsetY );
			}
		}
	}
}
// - -------------------------------------------------------------------------------------- - //

// - -------------------------------------------------------------------------------------- - //
template< typename tType>
void Grid2D<tType>::RockfordDrop( const int OffsetX, const int OffsetY ) {
	// TODO: Assert the Offsets.  There should always be a 1 and a 0 or a -1 and a 0. //

	// The offsets determine our sweeping order, so these are our sweeping order control //
	int StartX, StartY;
	int EndX, EndY;
	int IncrementX, IncrementY;
	
	// X axis change //
	if ( OffsetX <= 0 ) {
		StartX = 0;
		EndX = Width();
		IncrementX = 1;
	}
	else {
		StartX = Width() - 1;
		EndX = -1;
		IncrementX = -1;
	}
	
	// Y axis change //
	if ( OffsetY <= 0 ) {
		StartY = 0;
		EndY = Height();
		IncrementY = 1;
	}
	else 
	{
		StartY = Height() - 1;
		EndY = -1;
		IncrementY = -1;
	}
	
	// Depending on the offset, x or y should be the inner increment //
	if ( OffsetY == 0 ) {
		// Step through the Grid //
		for ( int x = StartX; x != EndX; x += IncrementX ) {
			for ( int y = StartY; y != EndY; y += IncrementY ) {
				if ( int DropType = CanRockfordDrop( x, y, OffsetX, OffsetY ) )
					ApplyRockfordDrop( x, y, DropType, OffsetX, OffsetY );
			}
		}
	}
	else
	{
		// Step through the Grid //
		for ( int y = StartY; y != EndY; y += IncrementY ) {
			for ( int x = StartX; x != EndX; x += IncrementX ) {
				if ( int DropType = CanRockfordDrop( x, y, OffsetX, OffsetY ) )
					ApplyRockfordDrop( x, y, DropType, OffsetX, OffsetY );
			}
		}
	}
}
// - -------------------------------------------------------------------------------------- - //


// - -------------------------------------------------------------------------------------- - //
template< typename tType>
const bool Grid2D<tType>::CanISet( const int x, const int y, const tType Value ) const {
	return Saturate(x,y) == Value;
}
// - -------------------------------------------------------------------------------------- - //
template< typename tType>
const bool Grid2D<tType>::CanIDrop( const int _Index, const int OffsetX, const int OffsetY ) const {
	// Place "Value" in the side described by "OffsetX" and "OffsetY", in the "Index" of that //
	//   Row/Column //

	int x, y;
	
	if ( OffsetX < 0 ) {
		x = Width() - 1;
		y = _Index;
	}
	else if ( OffsetX > 0 ) {
		x = 0;
		y = _Index;
	}
	else if ( OffsetY < 0 ) {
		x = _Index;
		y = Height() - 1;
	}
	else  if ( OffsetY > 0 ) {
		x = _Index;
		y = 0;
	}
	
	return CanISet(x,y);
}
// - -------------------------------------------------------------------------------------- - //
template< typename tType >
bool Grid2D<tType>::AddDrop( const int _Index, const int OffsetX, const int OffsetY, const tType& Value ) {
	// Place "Value" in the side described by "OffsetX" and "OffsetY", in the "Index" of that //
	//   Row/Column //

	int x, y;
	
	if ( OffsetX < 0 ) {
		x = Width() - 1;
		y = _Index;
	}
	else if ( OffsetX > 0 ) {
		x = 0;
		y = _Index;
	}
	else if ( OffsetY < 0 ) {
		x = _Index;
		y = Height() - 1;
	}
	else  if ( OffsetY > 0 ) {
		x = _Index;
		y = 0;
	}
	
	if ( CanISet(x,y) ) {
		Swap( x, y, Value );
		return true;
	}

	return false;
}
// - -------------------------------------------------------------------------------------- - //
template< typename tType >
bool Grid2D<tType>::AddDropDistance( const int _Index, const int OffsetX, const int OffsetY, const tType& Value ) {
	// Place "Value" in the side described by "OffsetX" and "OffsetY", in the "Index" of that //
	//   Row/Column //

	int x, y;
	
	if ( OffsetX < 0 ) {
		x = Width() - 1;
		y = AxisSaturateY(_Index);
	}
	else if ( OffsetX > 0 ) {
		x = 0;
		y = AxisSaturateY(_Index);
	}
	else if ( OffsetY < 0 ) {
		x = AxisSaturateX(_Index);
		y = Height() - 1;
	}
	else  if ( OffsetY > 0 ) {
		x = AxisSaturateX(_Index);
		y = 0;
	}
	
	if ( CanISet( x, y ) ) {
		Swap( x, y, Value );
		if ( int Distance = CalcDropDistance( x, y, OffsetX, OffsetY ) ) {
			ApplyDropDistance( x, y, Distance, OffsetX, OffsetY );
		}
		return true;
	}

	return false;
}
// - -------------------------------------------------------------------------------------- - //
template< typename tType >
bool Grid2D<tType>::AddRockfordDrop( const int _Index, const int OffsetX, const int OffsetY, const tType& Value ) {
	// TODO: The fall part will technically pick the wrong way on the bottom and right //
	
	// Desired Tile //
	if ( !AddDrop( _Index, OffsetX, OffsetY, Value ) ) {
		// Tile to the Left //
		if ( !AddDrop( _Index-1, OffsetX, OffsetY, Value ) ) {
			// Tile to the Right //
			return AddDrop( _Index-1, OffsetX, OffsetY, Value );
		}
	}
	return true;
}
// - -------------------------------------------------------------------------------------- - //
template< typename tType>
const int Grid2D<tType>::EdgeDistanceIndex( const int _Index, const int OffsetX, const int OffsetY ) {
	// Place "Value" in the side described by "OffsetX" and "OffsetY", in the "Index" of that //
	//   Row/Column //

	int x, y;
	
	if ( OffsetX < 0 ) {
		x = Width() - 1;
		y = AxisSaturateY(_Index);
	}
	else if ( OffsetX > 0 ) {
		x = 0;
		y = AxisSaturateY(_Index);
	}
	else if ( OffsetY < 0 ) {
		x = AxisSaturateX(_Index);
		y = Height() - 1;
	}
	else  if ( OffsetY > 0 ) {
		x = AxisSaturateX(_Index);
		y = 0;
	}
	
	int Distance = CalcDropDistance( x, y, OffsetX, OffsetY );
	
	return IndexSaturate(x + (OffsetX*Distance), y + (OffsetY*Distance));
}
// - -------------------------------------------------------------------------------------- - //
template< typename tType>
tType& Grid2D<tType>::EdgeDistance( const int _Index, const int OffsetX, const int OffsetY ) {
	return Data[ EdgeDistanceIndex( _Index, OffsetX, OffsetY ) ];
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL2_GRID_GRID2D_CLASS_DROP_H__ //
// - ------------------------------------------------------------------------------------------ - //
