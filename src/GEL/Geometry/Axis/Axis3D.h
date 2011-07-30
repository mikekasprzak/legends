// - ------------------------------------------------------------------------------------------ - //
// Axis3D //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Geometry_Axis3D_H__
#define __Geometry_Axis3D_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <Math/Real.h>
#include <Math/Vector.h>
#include <Geometry/Rect.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
class Axis3D {
public:
	enum eAxisId {
		_x = 0,
		_y = 1,
		_z = 2
	} AxisId;
	
	Vector3D Point;
public:
	static Axis3D XOrigin;
	static Axis3D YOrigin;
	static Axis3D ZOrigin;
public:
	inline Axis3D() :
		AxisId( _x )
	{
	}
	
	inline Axis3D( const Vector3D& v ) :
		AxisId( _x ),
		Point( v )
	{
	}

	inline Axis3D( const eAxisId& Id, const Vector3D& v ) :
		AxisId( Id ),
		Point( v )
	{
	}
public:
	// Construct via "Axis3D MyAxis = Axis3D::XAxis( pos );" //
	inline static Axis3D XAxis( const Vector3D& v ) {
		return Axis3D( _x, v );
	}

	inline static Axis3D YAxis( const Vector3D& v ) {
		return Axis3D( _y, v );
	}

	inline static Axis3D ZAxis( const Vector3D& v ) {
		return Axis3D( _z, v );
	}

	
public:	
	inline const bool IsX() const {
		return AxisId == _x;
	}
	inline const bool IsY() const {
		return AxisId == _y;
	}
	inline const bool IsZ() const {
		return AxisId == _z;
	}

	inline void SetX() {
		AxisId = _x;
	}
	inline void SetY() {
		AxisId = _y;
	}
	inline void SetZ() {
		AxisId = _z;
	}

public:
	// Test versus a point //
	inline const Real Test( const Vector3D& v ) const {
		// The Wide Axis //
		if ( IsX() ) {
			if ( v.y > Point.y )
				return Real::One;
			else if ( v.y < Point.y )
				return -Real::One;
			else
				return Real::Zero;
		}
		// The Tall Axis //
		else if ( IsY() ) {
			if ( v.x > Point.x )
				return Real::One;
			else if ( v.x < Point.x )
				return -Real::One;
			else
				return Real::Zero;
		}
		// The Long Axis //
		else {
			if ( v.z > Point.z )
				return Real::One;
			else if ( v.z < Point.z )
				return -Real::One;
			else
				return Real::Zero;			
		}
	}
	
	// Finding the closest point //
	inline const Vector3D ClosestPoint( const Vector3D& v ) const {
		// The Wide Axis //
		if ( IsX() ) {
			return Vector3D( v.x, Point.y, v.z );
		}
		// The Tall Axis //
		else if ( IsY() ) {
			return Vector3D( Point.x, v.y, v.z );
		}
		// The Long Axis //
		else {
			return Vector3D( v.x, v.y, Point.z );
		}		
	}

public:
	// Test Versus a RadiusRect - Fastest version (Ref, Ref Ops) //
	inline const Real Test( const RadiusRect3D& Vs ) const {
		// The Wide Axis //
		if ( IsX() ) {
			if ( Vs.Center().y > Point.y + Vs.HalfHeight() )
				return Real::One;
			else if ( Vs.Center().y < Point.y - Vs.HalfHeight() )
				return -Real::One;
			else
				return Real::Zero;
		}
		// The Tall Axis //
		else if ( IsY() ) {
			if ( Vs.Center().x > Point.x + Vs.HalfWidth() )
				return Real::One;
			else if ( Vs.Center().x < Point.x - Vs.HalfWidth() )
				return -Real::One;
			else
				return Real::Zero;
		}
		// The Long Axis //
		else {
			if ( Vs.Center().z > Point.z + Vs.HalfLength() )
				return Real::One;
			else if ( Vs.Center().z < Point.z - Vs.HalfLength() )
				return -Real::One;
			else
				return Real::Zero;
		}
	}

	// Test Versus a Rect - Slower (2, 1 Ops) //
	inline const Real Test( const Rect3D& Vs ) const {
		// The Wide Axis //
		if ( IsX() ) {
			if ( Vs.Center().y > Point.y + Vs.HalfHeight() )
				return Real::One;
			else if ( Vs.Center().y < Point.y - Vs.HalfHeight() )
				return -Real::One;
			else
				return Real::Zero;
		}
		// The Tall Axis //
		else if ( IsY() ) {
			if ( Vs.Center().x > Point.x + Vs.HalfWidth() )
				return Real::One;
			else if ( Vs.Center().x < Point.x - Vs.HalfWidth() )
				return -Real::One;
			else
				return Real::Zero;
		}
		// The Long Axis //
		else {
			if ( Vs.Center().z > Point.z + Vs.HalfLength() )
				return Real::One;
			else if ( Vs.Center().z < Point.z - Vs.HalfLength() )
				return -Real::One;
			else
				return Real::Zero;
		}
	}

	// Test Versus a PairRect - Slowest (3, 2 Ops) //
	inline const Real Test( const PairRect3D& Vs ) const {
		// The Wide Axis //
		if ( IsX() ) {
			if ( Vs.Center().y > Point.y + Vs.HalfHeight() )
				return Real::One;
			else if ( Vs.Center().y < Point.y - Vs.HalfHeight() )
				return -Real::One;
			else
				return Real::Zero;
		}
		// The Tall Axis //
		else if ( IsY() ) {
			if ( Vs.Center().x > Point.x + Vs.HalfWidth() )
				return Real::One;
			else if ( Vs.Center().x < Point.x - Vs.HalfWidth() )
				return -Real::One;
			else
				return Real::Zero;
		}
		// The Long Axis //
		else {
			if ( Vs.Center().z > Point.z + Vs.HalfLength() )
				return Real::One;
			else if ( Vs.Center().z < Point.z - Vs.HalfLength() )
				return -Real::One;
			else
				return Real::Zero;
		}
	}	
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Geometry_Axis3D_H__ //
// - ------------------------------------------------------------------------------------------ - //
