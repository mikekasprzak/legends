// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL2_GRID_SUBGRID2D_CLASS_H__
#define __GEL2_GRID_SUBGRID2D_CLASS_H__
// - ------------------------------------------------------------------------------------------ - //
// SubGrid2D -- A portion of a Grid2D object //
// - ------------------------------------------------------------------------------------------ - //
#include "Grid2D.h"
// - ------------------------------------------------------------------------------------------ - //
template< typename tType >
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
	// Reference Only Version //
	inline SubGrid2D( Grid2D<tType>& _Grid ) :
		x( 0 ),
		y( 0 ),
		w( _Grid.Width() ),
		h( _Grid.Height() ),
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

	// - -------------------------------------------------------------------------------------- - //
	// X2,Y2 are currently exclusive (i.e. are not to be included in the range, just the max) //
	// - -------------------------------------------------------------------------------------- - //
	inline const szt X1() const {
		return x;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const szt Y1() const {
		return y;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const szt X2() const {
		return x+w;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const szt Y2() const {
		return y+h;
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
		// Inner //
		if ( _x < 0 )
			_x = Width() - ((-_x) % Width());
		else
			_x %= Width();
		// Inner //		
		if ( _y < 0 )
			_y = Height() - ((-_y) % Height());
		else
			_y %= Height();
			
		_x = x+_x;
		_y = y+_y;

		// Outer //
		if ( _x < 0 )
			_x = Grid->Width() - ((-_x) % Grid->Width());
		else
			_x %= Grid->Width();
		// Outer //		
		if ( _y < 0 )
			_y = Grid->Height() - ((-_y) % Grid->Height());
		else
			_y %= Grid->Height();

		return _x + (_y * Grid->Width());
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const szt IndexWrapX( int _x, const int _y ) const {
		// Inner //
		if ( _x < 0 )
			_x = Width() - ((-_x) % Width());
		else
			_x %= Width();
			
		_x = x+_x;

		// Outer //
		if ( _x < 0 )
			_x = Grid->Width() - ((-_x) % Grid->Width());
		else
			_x %= Grid->Width();

		return _x + ((y+_y) * Grid->Width());
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const szt IndexWrapY( const int _x, int _y ) const {
		// Inner //		
		if ( _y < 0 )
			_y = Height() - ((-_y) % Height());
		else
			_y %= Height();
			
		_y = y+_y;

		// Outer //		
		if ( _y < 0 )
			_y = Grid->Height() - ((-_y) % Grid->Height());
		else
			_y %= Grid->Height();
						
		return (x+_x) + (_y * Grid->Width());
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

public:
	// - -------------------------------------------------------------------------------------- - //
	inline tType& operator () ( const szt _x, const szt _y ) {
		return Grid->Data[ Index( _x, _y ) ];
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const tType& operator () ( const szt _x, const szt _y ) const {
		return Grid->Data[ Index( _x, _y ) ];
	}
	// - -------------------------------------------------------------------------------------- - //
	inline tType& operator [] ( const szt _Index ) {
		// TODO: Assert out of bounds 
		return Grid->Data[ _Index ];
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const tType& operator [] ( const szt _Index ) const {
		// TODO: Assert out of bounds 
		return Grid->Data[ _Index ];
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Get the position, with axis wrapping //
	inline tType& Wrap( const int _x, const int _y ) {
		return Grid->Data[ IndexWrap( _x, _y ) ];
	}
	inline const tType& Wrap( const int _x, const int _y ) const {
		return Grid->Data[ IndexWrap( _x, _y ) ];
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the position, with axis wrapping //
	inline tType& WrapX( const int _x, const int _y ) {
		return Grid->Data[ IndexWrapX( _x, _y ) ];
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the position, with axis wrapping //
	inline const tType& WrapX( const int _x, const int _y ) const {
		return Grid->Data[ IndexWrapX( _x, _y ) ];
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the position, with axis wrapping //
	inline tType& WrapY( const int _x, const int _y ) {
		return Grid->Data[ IndexWrapY( _x, _y ) ];
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the position, with axis wrapping //
	inline const tType& WrapY( const int _x, const int _y ) const {
		return Grid->Data[ IndexWrapY( _x, _y ) ];
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the position, with next line/first line wrapping //
	inline tType& NextWrap( const int _x, const int _y ) {
		return Grid->Data[ IndexNextWrap( _x, _y ) ];
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the position, with next line/first line wrapping //
	inline const tType& NextWrap( const int _x, const int _y ) const {
		return Grid->Data[ IndexNextWrap( _x, _y ) ];
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the position, aligning to edges //
	inline tType& Saturate( const int _x, const int _y ) {
		return Grid->Data[ IndexSaturate( _x, _y ) ];
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the position, aligning to edges //
	inline const tType& Saturate( const int _x, const int _y ) const {	
		return Grid->Data[ IndexSaturate( _x, _y ) ];
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the position, aligning to edges //
	inline tType& SaturateX( const int _x, const int _y ) {
		return Grid->Data[ IndexSaturateX( _x, _y ) ];
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the position, aligning to edges //
	inline const tType& SaturateX( const int _x, const int _y ) const {	
		return Grid->Data[ IndexSaturateX( _x, _y ) ];
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the position, aligning to edges //
	inline tType& SaturateY( const int _x, const int _y ) {
		return Grid->Data[ IndexSaturateY( _x, _y ) ];
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the position, aligning to edges //
	inline const tType& SaturateY( const int _x, const int _y ) const {	
		return Grid->Data[ IndexSaturateY( _x, _y ) ];
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// These are for converting explicit X and Y values in to ones that fit within grid ranges //
	// - -------------------------------------------------------------------------------------- - //
	// Get the position, aligning to edges //
	inline const int AxisSaturateX( int _x ) const {
		if ( _x >= (int)Width() )
			_x = Width() - 1;
		else if ( _x < 0 )
			_x = 0;
		
		return _x;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the position, aligning to edges //
	inline const int AxisSaturateY( int _y ) const {
		if ( _y >= (int)Height() )
			_y = Height() - 1;
		else if ( _y < 0 )
			_y = 0;
			
		return _y;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const szt AxisWrapX( int _x ) const {
		if ( _x < 0 )
			_x = -_x;
		return (_x % Width());
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const szt AxisWrapY( int _y ) const {
		if ( _y < 0 )
			_y = -_y;
		return (_y % Height());
	}
	// - -------------------------------------------------------------------------------------- - //


	// - -------------------------------------------------------------------------------------- - //
	// Get the position, returning the dead value if over //
	inline const szt DeadIndex( const int _x, const int _y, const szt DeadValue = SZT_MAX ) const {
		if ( _x >= (int)Width() )
			return DeadValue;
		else if ( _x < 0 )
			return DeadValue;
			
		if ( _y >= (int)Height() )
			return DeadValue;
		else if ( _y < 0 )
			return DeadValue;
			
		return Index( _x, _y );
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the position, returning the dead value if over //
	inline const tType& Dead( const int _x, const int _y, const tType& DeadValue = tType() ) const {
		szt DIndex = DeadIndex(_x,_y);
		
		if ( DIndex != SZT_MAX )
			return Grid->Data[ Index( _x, _y ) ];
		else
			return DeadValue;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Given an edge described by OffsetX and OffsetY (Top=(0,1) Left=(1,0) ...), Index along it. //
	inline const int EdgeIndex( const int _Index, const int OffsetX, const int OffsetY ) {
		int _x, _y;
		
		if ( OffsetX < 0 ) {
			_x = Width() - 1;
			_y = _Index;
		}
		else if ( OffsetX > 0 ) {
			_x = 0;
			_y = _Index;
		}
		else if ( OffsetY < 0 ) {
			_x = _Index;
			_y = Height() - 1;
		}
		else  if ( OffsetY > 0 ) {
			_x = _Index;
			_y = 0;
		}
		
		return IndexSaturate(_x,_y);
	}
	// - -------------------------------------------------------------------------------------- - //
	inline tType& Edge( const int _Index, const int OffsetX, const int OffsetY ) {
		return Grid->Data[ EdgeIndex( _Index, OffsetX, OffsetY ) ];
	}
	// - -------------------------------------------------------------------------------------- - //

public:
	// - -------------------------------------------------------------------------------------- - //
	// Exchange two values given their coordinates //
	inline void _Swap( const int x1, const int y1, const int x2, const int y2 ) {
		tType Temp = (*Grid)(x1,y1);
		(*Grid)(x1,y1) = (*Grid)(x2,y2);
		(*Grid)(x2,y2) = Temp;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline void Swap( int x1, int y1, int x2, int y2 ) {
		x1 = AxisSaturateX( x1 );
		y1 = AxisSaturateY( y1 );
		
		x2 = AxisSaturateX( x2 );
		y2 = AxisSaturateY( y2 );
		
		_Swap(x1,y1,x2,y2);
	}
	// - -------------------------------------------------------------------------------------- - //
	// Exchange the passed value with the value at the coordinate, returning the coordinate's value //
	inline const tType _Swap( const int x1, const int y1, const tType& Value ) {
		tType Temp = (*Grid)(x1,y1);
		(*Grid)(x1,y1) = Value;
		
		return Temp;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const tType Swap( int x1, int y1, const tType& Value ) {
		x1 = AxisSaturateX( x1 );
		y1 = AxisSaturateY( y1 );

		return _Swap(x1,y1,Value);
	}
	// - -------------------------------------------------------------------------------------- - //
	// Exchange the passed value with the value at the Index, returning the value at the Index //
	inline const tType Swap( int _Index, const tType& Value ) {
		tType Temp = (*Grid)[_Index];
		(*Grid)[_Index] = Value;
		
		return Temp;
	}
	// - -------------------------------------------------------------------------------------- - //

};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL2_GRID_SUBGRID2D_CLASS_H__ //
// - ------------------------------------------------------------------------------------------ - //
