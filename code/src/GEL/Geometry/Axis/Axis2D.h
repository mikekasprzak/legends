// - ------------------------------------------------------------------------------------------ - //
// Axis2D //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Geometry_Axis2D_H__
#define __Geometry_Axis2D_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <Math/Real.h>
#include <Math/Vector.h>
#include <Geometry/Rect.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
class Axis2D {
public:
	enum eAxisId {
		_x = 0,
		_y = 1
	} AxisId;
	
	Vector2D Point;
public:
	static Axis2D XOrigin;
	static Axis2D YOrigin;
public:
	Axis2D() :
		AxisId( _x )
	{
	}
	
	Axis2D( const Vector2D& v ) :
		AxisId( _x ),
		Point( v )
	{
	}

	Axis2D( const eAxisId& Id, const Vector2D& v ) :
		AxisId( Id ),
		Point( v )
	{
	}
public:
	// Construct via "Axis2D MyAxis = Axis2D::XAxis( pos );" //
	static Axis2D XAxis( const Vector2D& v ) {
		return Axis2D( _x, v );
	}

	static Axis2D YAxis( const Vector2D& v ) {
		return Axis2D( _y, v );
	}

	
public:	
	inline const bool IsX() const {
		return AxisId == _x;
	}
	inline const bool IsY() const {
		return AxisId == _y;
	}

	inline void SetX() {
		AxisId = _x;
	}
	inline void SetY() {
		AxisId = _y;
	}

public:
	// Test versus a point //
	inline const Real Test( const Vector2D& v ) const {
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
		else {
			if ( v.x > Point.x )
				return Real::One;
			else if ( v.x < Point.x )
				return -Real::One;
			else
				return Real::Zero;
		}
	}
	
	// Finding the closest point //
	inline const Vector2D ClosestPoint( const Vector2D& v ) const {
		// The Wide Axis //
		if ( IsX() ) {
			return Vector2D( v.x, Point.y );
		}
		// The Tall Axis //
		else {
			return Vector2D( Point.x, v.y );
		}
	}

public:
	// Test Versus a RadiusRect - Fastest version (Ref, Ref Ops) //
	inline const Real Test( const RadiusRect2D& Vs ) const {
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
		else {
			if ( Vs.Center().x > Point.x + Vs.HalfWidth() )
				return Real::One;
			else if ( Vs.Center().x < Point.x - Vs.HalfWidth() )
				return -Real::One;
			else
				return Real::Zero;
		}
	}

	// Test Versus a Rect - Slower (2, 1 Ops) //
	inline const Real Test( const Rect2D& Vs ) const {
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
		else {
			if ( Vs.Center().x > Point.x + Vs.HalfWidth() )
				return Real::One;
			else if ( Vs.Center().x < Point.x - Vs.HalfWidth() )
				return -Real::One;
			else
				return Real::Zero;
		}
	}

	// Test Versus a PairRect - Slowest (3, 2 Ops) //
	inline const Real Test( const PairRect2D& Vs ) const {
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
		else {
			if ( Vs.Center().x > Point.x + Vs.HalfWidth() )
				return Real::One;
			else if ( Vs.Center().x < Point.x - Vs.HalfWidth() )
				return -Real::One;
			else
				return Real::Zero;
		}
	}	
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Geometry_Axis2D_H__ //
// - ------------------------------------------------------------------------------------------ - //
