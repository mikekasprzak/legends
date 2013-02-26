// - ------------------------------------------------------------------------------------------ - //
// XYZSet //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Geometry_XYZSet_H__
#define __Geometry_XYZSet_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template <class T>
class XYZSet {
public:
	T x, y, z;

public:
	XYZSet() {
	}
	
	XYZSet( T _x, T _y, T _z ) :
		x( _x ),
		y( _y ),
		z( _z )
	{
	}
	
	// - -------------------------------------------------------------------------------------- - //
	inline bool operator == ( const XYZSet& _Vs ) const {
		if ( (x == _Vs.x) )
			if ( (y == _Vs.y) )
				return (z == _Vs.z);
		return false;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline T& operator [] ( const int Index ) {
		return *((&x)+Index);
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const T& operator [] ( const int Index ) const {
		return *((&x)+Index);
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Swizzles //
	// - -------------------------------------------------------------------------------------- - //
#define SWIZZLE_ABC( _A, _B, _C ) \
	inline const XYZSet<T> _A ## _B ## _C () const { return XYZSet(_A,_B,_C); }

	SWIZZLE_ABC( x,x,x );
	SWIZZLE_ABC( x,x,y );
	SWIZZLE_ABC( x,x,z );
	SWIZZLE_ABC( x,y,x );
	SWIZZLE_ABC( x,y,y );
	SWIZZLE_ABC( x,y,z );
	SWIZZLE_ABC( x,z,x );
	SWIZZLE_ABC( x,z,y );
	SWIZZLE_ABC( x,z,z );

	SWIZZLE_ABC( y,x,x );
	SWIZZLE_ABC( y,x,y );
	SWIZZLE_ABC( y,x,z );
	SWIZZLE_ABC( y,y,x );
	SWIZZLE_ABC( y,y,y );
	SWIZZLE_ABC( y,y,z );
	SWIZZLE_ABC( y,z,x );
	SWIZZLE_ABC( y,z,y );
	SWIZZLE_ABC( y,z,z );

	SWIZZLE_ABC( z,x,x );
	SWIZZLE_ABC( z,x,y );
	SWIZZLE_ABC( z,x,z );
	SWIZZLE_ABC( z,y,x );
	SWIZZLE_ABC( z,y,y );
	SWIZZLE_ABC( z,y,z );
	SWIZZLE_ABC( z,z,x );
	SWIZZLE_ABC( z,z,y );
	SWIZZLE_ABC( z,z,z );

#undef SWIZZLE_ABC
	// - -------------------------------------------------------------------------------------- - //
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Geometry_XYZSet_H__ //
// - ------------------------------------------------------------------------------------------ - //
