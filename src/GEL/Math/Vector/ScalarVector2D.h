// - ------------------------------------------------------------------------------------------ - //
// ScalarVector2D //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Geometry_ScalarVector2D_H__
#define __Geometry_ScalarVector2D_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <External/boost/operators.hpp>

#include "Vector2D.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Utility class for reinterpreting a Vector as a scalar, so multiplication works differently //
// - ------------------------------------------------------------------------------------------ - //
class ScalarVector2D: public Vector2D,
	boost::multipliable2<ScalarVector2D, Vector2D>
{
public:
	inline ScalarVector2D() {
	}
	
	inline ScalarVector2D( const Real& _x, const Real& _y ) :
		Vector2D( _x, _y )
	{
	}
	
public:
	inline const Vector2D& operator *= ( const Vector2D& _Vs ) {
		x *= _Vs.x;
		y *= _Vs.y;
		return (const Vector2D&)*this;
	}
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Geometry_ScalarVector2D_H__ //
// - ------------------------------------------------------------------------------------------ - //
