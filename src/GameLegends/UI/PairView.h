// - ------------------------------------------------------------------------------------------ - //
#ifndef __PairView_H__
#define __PairView_H__
// - ------------------------------------------------------------------------------------------ - //
// Views are a type of regioning structure, for breaking up a screen. //
// PairView does it with integer pairs of points. //
// - ------------------------------------------------------------------------------------------ - //
// Implement a PairView in a separate .cpp file as an array of int's.  Extern it there as one.  //
//   But in your real code, extern it as a PairView and gain all whole bunch of extras. //
//
// Views should be ordered top to bottom in such a way that the last region is the one you want //
//   returned.  This means a parent view would appear higher up on a list than it's children. //
//   Only 2 levels of heiarchy.  Parents and children.  If not important, don't stack views and //
//   any region searching function will return a useful value. //
//   If you actually want heiarchy, create a separate PairView and some association scheme.  That //
//   could mean just nested "if" blocks, but a complex type could work too. //
// - ------------------------------------------------------------------------------------------ - //
#ifdef _MSC_VER
#pragma warning (disable : 4200) // Zero sized array member //
#endif // _MSC_VER
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// TODO: Move this to a C based integer collision detection library //
inline const bool Test_IntegerPoint_Vs_IntegerPairRect( const int x, const int y, const int x1, const int y1, const int x2, const int y2 ) {
	// Inclusive of x1y1, exclusive of x2y2 //
	// ??? Should it be inclusive of both (for pairs, but not shapes) ??? //
	if ( x >= x1 )
		if ( x < x2 )
			if ( y >= y1 )
				return y < y2;
	return false;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
struct PairView {
	int Count;
	int Region[];
	
public:
	// Standard Type Compatibility //
	inline const int Size() const {
		return Count;
	}
	
	// Accessor functions //
	inline const int& X1( const int Index ) const {
		return Region[ (Index << 2) + 0];
	}
	inline const int& Y1( const int Index ) const {
		return Region[ (Index << 2) + 1];
	}
	inline const int& X2( const int Index ) const {
		return Region[ (Index << 2) + 2];
	}
	inline const int& Y2( const int Index ) const {
		return Region[ (Index << 2) + 3];
	}
	
	inline const int* operator [] ( const int Index ) {
		return &Region[ Index << 2 ];
	}
	
	
public:
	// A pair of functions for getting the dimensions of a region //
	inline const int GetWidth( const int Index ) const {
		return X2(Index) - X1(Index);
	}
	inline const int GetHeight( const int Index ) const {
		return Y2(Index) - Y1(Index);
	}
	
	// A pair of functions for getting the half dimensions of a region //
	inline const int GetHalfWidth( const int Index ) const {
		return (X2(Index) - X1(Index)) >> 1;
	}
	inline const int GetHalfHeight( const int Index ) const {
		return (Y2(Index) - Y1(Index)) >> 1;
	}

	// A pair of functions for getting the center point of a region //
	inline const int GetCenterX( const int Index ) const {
		return X1(Index) + GetHalfWidth(Index);
	}
	inline const int GetCenterY( const int Index ) const {
		return Y1(Index) + GetHalfHeight(Index);
	}
	
		
public: 
	inline const bool TestRegion( const int Index, const int x, const int y ) const {
		return Test_IntegerPoint_Vs_IntegerPairRect( 
			x, y, 
			X1(Index), Y1(Index),
			X2(Index), Y2(Index)
			);
	}
	
	inline const int GetRegion( const int x, const int y ) const {
		// Return the last region the point is found in //
		for ( int idx = Count; idx--; ) {
			if ( TestRegion( idx, x, y ) )
				return idx;
		}
		
		// Point never found in a region //
		return -1;
	}
	
	inline const int GetParentRegion( const int x, const int y ) const {
		// Return the first region the point is found in //
		for ( int idx = 0; idx < Count; idx++ ) {
			if ( TestRegion( idx, x, y ) )
				return idx;
		}
		
		// Point never found in a region //
		return -1;
	}

};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __PairView_H__ //
// - ------------------------------------------------------------------------------------------ - //
