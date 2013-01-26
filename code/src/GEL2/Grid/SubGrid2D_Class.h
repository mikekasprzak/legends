// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL2_GRID_SUBGRID2D_CLASS_H__
#define __GEL2_GRID_SUBGRID2D_CLASS_H__
// - ------------------------------------------------------------------------------------------ - //
// SubGrid2D -- A portion of a Grid2D object //
// - ------------------------------------------------------------------------------------------ - //
#include "Grid2D.h"
// - ------------------------------------------------------------------------------------------ - //
template< typename tType = int >
class SubGrid2D {
public:
	// - -------------------------------------------------------------------------------------- - //	
	szt x, y;		// Base X and Y coordinates //
	szt w, h;		// Dimensions //
	Grid2D<tType>* Grid;
	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	inline SubGrid2D() :
		x( 0 ),
		y( 0 ),
		w( 0 ),
		h( 0 ),
		Grid( 0 )
	{
	}
	// - -------------------------------------------------------------------------------------- - //
	// As Pointer Version (also the no grid but dimensions only init version) //
	inline SubGrid2D( const szt _x, const szt _y, const szt _w, const szt _h, Grid2D<tType>* const _Grid = 0 ) :
		x( _x ),
		y( _y ),
		w( _w ),
		h( _h ),
		Grid( _Grid )
	{
	}
	// - -------------------------------------------------------------------------------------- - //
	// Reference Version (extract the pointer) //
	inline SubGrid2D( const szt _x, const szt _y, const szt _w, const szt _h, Grid2D<tType>& _Grid ) :
		x( _x ),
		y( _y ),
		w( _w ),
		h( _h ),
		Grid( &_Grid )
	{
	}
	// - -------------------------------------------------------------------------------------- - //
	// Destructor, do nothing (since we're a reference anyway) //
	inline ~SubGrid2D() {
	}
	// - -------------------------------------------------------------------------------------- - //

public:
	// - -------------------------------------------------------------------------------------- - //
	inline const szt Width() const {
		return w;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const szt Height() const {
		return h;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const szt HalfWidth() const {
		return w >> 1;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const szt HalfHeight() const {
		return h >> 1;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const szt Size() const {
		return w * h;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const szt SizeOf() const {
		return Size() * sizeof(tType);
	}
	// - -------------------------------------------------------------------------------------- - //

public:
	// - -------------------------------------------------------------------------------------- - //
	const tType* operator *() const {
		return Grid->Data;
	}
	// - -------------------------------------------------------------------------------------- - //
	tType* operator *() {
		return Grid->Data;
	}
	// - -------------------------------------------------------------------------------------- - //

public:
	// - -------------------------------------------------------------------------------------- - //
	// Index Generating functions.  Return a valid index for [] operator. //
	// - -------------------------------------------------------------------------------------- - //
	inline const szt Index( const int _x, const int _y ) const {
		// TODO: Assert out of bounds 
		return (x+_x) + ((y+_y) * Grid->Width());
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const szt IndexWrap( int _x, int _y ) const {
		if ( _x < 0 )
			_x = -_x;
		if ( _y < 0 )
			_y = -_y;
		return ((x+(_x % Width())) % Grid->Width()) + (((y+(_y % Height())) % Grid->Width()) * Grid->Width());
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const szt IndexWrapX( int _x, const int _y ) const {
		if ( _x < 0 )
			_x = -_x;
		return ((x+(_x % Width())) % Grid->Width()) + ((y+_y) * Grid->Width());
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const szt IndexWrapY( const int _x, int _y ) const {
		if ( _y < 0 )
			_y = -_y;
		return (x+_x) + (((y+(_y % Height())) % Grid->Width()) * Grid->Width());
	}
	// - -------------------------------------------------------------------------------------- - //
	// Wraps linearly to the next line, but around to the top //
	inline const szt IndexNextWrap( const int _x, const int _y ) const {
		return abs(Index(_x,_y)) % Grid->Size();
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the position, aligning to edges //
	inline const szt IndexSaturate( int _x, int _y ) const {
		if ( _x >= Width() )
			_x = Width() - 1;
		else if ( _x < 0 )
			_x = 0;
			
		if ( _y >= Height() )
			_y = Height() - 1;
		else if ( _y < 0 )
			_y = 0;
			
		return Index( _x, _y );
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the position, aligning to edges //
	inline const szt IndexSaturateX( int _x, int _y ) const {
		if ( _x >= Width() )
			_x = Width() - 1;
		else if ( _x < 0 )
			_x = 0;
			
		return Index( _x, _y );
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the position, aligning to edges //
	inline const szt IndexSaturateY( int _x, int _y ) const {
		if ( _y >= Height() )
			_y = Height() - 1;
		else if ( _y < 0 )
			_y = 0;
			
		return Index( _x, _y );
	}
	// - -------------------------------------------------------------------------------------- - //

};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL2_GRID_SUBGRID2D_CLASS_H__ //
// - ------------------------------------------------------------------------------------------ - //
