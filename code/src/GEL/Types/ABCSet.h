// - ------------------------------------------------------------------------------------------ - //
// ABCSet //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Geometry_ABCSet_H__
#define __Geometry_ABCSet_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template <class T>
class ABCSet {
public:
	T a, b, c;

public:
	ABCSet() {
	}
	
	ABCSet( T _a, T _b, T _c ) :
		a( _a ),
		b( _b ),
		c( _c )
	{
	}
	
	// - -------------------------------------------------------------------------------------- - //
	inline bool operator == ( const ABCSet& _Vs ) const {
		if ( (a == _Vs.a) )
			if ( (b == _Vs.b) )
				return (c == _Vs.c);
		return false;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline T& operator [] ( const int Index ) {
		return *((&a)+Index);
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const T& operator [] ( const int Index ) const {
		return *((&a)+Index);
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Swizzles //
	// - -------------------------------------------------------------------------------------- - //
#define SWIZZLE_ABC( _A, _B, _C ) \
	inline const ABCSet<T> _A ## _B ## _C () const { return ABCSet(_A,_B,_C); }

	SWIZZLE_ABC( a,a,a );
	SWIZZLE_ABC( a,a,b );
	SWIZZLE_ABC( a,a,c );
	SWIZZLE_ABC( a,b,a );
	SWIZZLE_ABC( a,b,b );
	SWIZZLE_ABC( a,b,c );
	SWIZZLE_ABC( a,c,a );
	SWIZZLE_ABC( a,c,b );
	SWIZZLE_ABC( a,c,c );

	SWIZZLE_ABC( b,a,a );
	SWIZZLE_ABC( b,a,b );
	SWIZZLE_ABC( b,a,c );
	SWIZZLE_ABC( b,b,a );
	SWIZZLE_ABC( b,b,b );
	SWIZZLE_ABC( b,b,c );
	SWIZZLE_ABC( b,c,a );
	SWIZZLE_ABC( b,c,b );
	SWIZZLE_ABC( b,c,c );

	SWIZZLE_ABC( c,a,a );
	SWIZZLE_ABC( c,a,b );
	SWIZZLE_ABC( c,a,c );
	SWIZZLE_ABC( c,b,a );
	SWIZZLE_ABC( c,b,b );
	SWIZZLE_ABC( c,b,c );
	SWIZZLE_ABC( c,c,a );
	SWIZZLE_ABC( c,c,b );
	SWIZZLE_ABC( c,c,c );

#undef SWIZZLE_ABC
	// - -------------------------------------------------------------------------------------- - //
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Geometry_ABCSet_H__ //
// - ------------------------------------------------------------------------------------------ - //
