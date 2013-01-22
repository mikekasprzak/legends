// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL2_GRID_GRID2D_CLASS_ADJACENCY_H__
#define __GEL2_GRID_GRID2D_CLASS_ADJACENCY_H__
// - ------------------------------------------------------------------------------------------ - //
// Generate a grid of values for how far away each found value is from the start //
template< typename tType >
const Grid2D<int> Grid2D<tType>::GenerateAdjacentXAdjacencyGrid( int x, int y, const tType& Value ) const {
	Grid2D<int> NewGrid( Width(), Height() );
	
	x = AxisSaturateX( x );
	y = AxisSaturateY( y );
	
	if ( operator()( x, y ) != Value )
		return NewGrid;
	
	NewGrid( x, y ) = 1;
	
	{
		szt Distance = 1;
		for ( int _x = x; _x-- > 0; ) {
			if ( operator()( _x, y ) == Value ) {
				Distance++;
				
				NewGrid( _x, y ) = Distance;
			}
			else
				break;
		}
	}

	{
		szt Distance = 1;
		for ( int _x = x; ++_x < Width(); ) {
			if ( operator()( _x, y ) == Value ) {
				Distance++;
				
				NewGrid( _x, y ) = Distance;
			}
			else
				break;
		}
	}
	
	return NewGrid;
}
// - -------------------------------------------------------------------------------------- - //
// Generate a grid of values for how far away each found value is from the start //
template< typename tType >
const Grid2D<int> Grid2D<tType>::GenerateAdjacentYAdjacencyGrid( int x, int y, const tType& Value ) const {
	Grid2D<int> NewGrid( Width(), Height() );
	
	x = AxisSaturateX( x );
	y = AxisSaturateY( y );
	
	if ( operator()( x, y ) != Value )
		return NewGrid;
	
	NewGrid( x, y ) = 1;
	
	{
		szt Distance = 1;
		for ( int _y = y; _y-- > 0; ) {
			if ( operator()( x, _y ) == Value ) {
				Distance++;
				
				NewGrid( x, _y ) = Distance;
			}
			else
				break;
		}
	}

	{
		szt Distance = 1;
		for ( int _y = y; ++_y < Height(); ) {
			if ( operator()( x, _y ) == Value ) {
				Distance++;
				
				NewGrid( x, _y ) = Distance;
			}
			else
				break;
		}
	}
	
	return NewGrid;
}
// - -------------------------------------------------------------------------------------- - //
template< typename tType >
const Grid2D<int> Grid2D<tType>::GenerateAdjacentXAdjacencyGrid( const int x, const int y ) const {
	return GenerateAdjacentXAdjacencyGrid( x, y, Saturate( x, y ) );
}
// - -------------------------------------------------------------------------------------- - //
template< typename tType >
const Grid2D<int> Grid2D<tType>::GenerateAdjacentYAdjacencyGrid( const int x, const int y ) const {
	return GenerateAdjacentYAdjacencyGrid( x, y, Saturate( x, y ) );
}
// - -------------------------------------------------------------------------------------- - //

// - -------------------------------------------------------------------------------------- - //
// In the case of rows and columns, an Adjacency Grid is exactly the same as a Distance Grid //
// - -------------------------------------------------------------------------------------- - //
template< typename tType >
const Grid2D<int> Grid2D<tType>::GenerateAdjacentXDistanceGrid( const int x, const int y, const tType& Value ) const {
	return GenerateAdjacentXAdjacencyGrid( x, y, Value );
}
// - -------------------------------------------------------------------------------------- - //
template< typename tType >
const Grid2D<int> Grid2D<tType>::GenerateAdjacentYDistanceGrid( const int x, const int y, const tType& Value ) const {
	return GenerateAdjacentYAdjacencyGrid( x, y, Value );
}
// - -------------------------------------------------------------------------------------- - //
template< typename tType >
const Grid2D<int> Grid2D<tType>::GenerateAdjacentXDistanceGrid( const int x, const int y ) const {
	return GenerateAdjacentXAdjacencyGrid( x, y );
}
// - -------------------------------------------------------------------------------------- - //
template< typename tType >
const Grid2D<int> Grid2D<tType>::GenerateAdjacentYDistanceGrid( const int x, const int y ) const {
	return GenerateAdjacentYAdjacencyGrid( x, y );
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL2_GRID_GRID2D_CLASS_ADJACENCY_H__ //
// - ------------------------------------------------------------------------------------------ - //
