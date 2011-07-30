// - ------------------------------------------------------------------------------------------ - //
// ShapeRect2D //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Geometry_ShapeRect2D_H__
#define __Geometry_ShapeRect2D_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <Math/Real.h>
#include <Math/Vector.h>
// - ------------------------------------------------------------------------------------------ - //

class ShapeRect2D : 
	boost::additive<ShapeRect2D,
	boost::arithmetic2<ShapeRect2D, Vector2D
	> >
{
public:
	// - -------------------------------------------------------------------------------------- - //
	// A typedef for the current rect type, that way, similar code can be cut+paste easier //
	typedef ShapeRect2D RectType;
	typedef Vector2D VectorType;
	// - -------------------------------------------------------------------------------------- - //
	VectorType _P1;
	VectorType _Shape;
	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	inline ShapeRect2D() {
	}
	// - -------------------------------------------------------------------------------------- - //
	
	// - -------------------------------------------------------------------------------------- - //
	// Normal Creation (RectXD style (x,y,w,h)) //
	// - -------------------------------------------------------------------------------------- - //
	inline ShapeRect2D( const Real& _x, const Real& _y, const Real& _w, const Real& _h ) :
		_P1( _x, _y ),
		_Shape( _w, _h )
	{
	}
	// - -------------------------------------------------------------------------------------- - //
	inline ShapeRect2D( const VectorType& _Vec1, const VectorType& _Vec2 ) :
		_P1( _Vec1 ),
		_Shape( _Vec2 )
	{
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Pair Creation (P1, P2) //
	// - -------------------------------------------------------------------------------------- - //
	inline ShapeRect2D( const bool&, const VectorType& _Vec1, const VectorType& _Vec2 ) :
		_P1( _Vec1.x.Min( _Vec2.x ), _Vec1.y.Min( _Vec2.y ) ),
		_Shape( (_Vec2.x - _Vec1.x).Abs(), (_Vec2.y - _Vec1.y).Abs() )
	{
	}
	// - -------------------------------------------------------------------------------------- - //
	inline ShapeRect2D( const bool&, const bool&, const VectorType& _Vec1, const VectorType& _Vec2 ) :
		_P1( _Vec1 ),
		_Shape( _Vec2 - _Vec1 )
	{
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Radius Creation (Center, HalfShape) //
	// - -------------------------------------------------------------------------------------- - //
	inline ShapeRect2D( const bool&, const bool&, const bool&, const VectorType& _VecCenter, const VectorType& _VecShape ) :
		_P1( _VecCenter - _VecShape ),
		_Shape( _VecShape + _VecShape )
	{
	}
	// - -------------------------------------------------------------------------------------- - //

public:
	// - -------------------------------------------------------------------------------------- - //
	// Creation as a Pair //
	// - -------------------------------------------------------------------------------------- - //
	inline static const RectType Pair( const Real& _x1, const Real& _y1, const Real& _x2, const Real& _y2 ) {
		return RectType( true, VectorType( _x1, _y1 ), VectorType( _x2, _y2 ) );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline static const RectType Pair( const VectorType& _Vec1, const VectorType& _Vec2 ) {
		return RectType( true, _Vec1, _Vec2 );
	}
	// - -------------------------------------------------------------------------------------- - //
	// Optimized Pair Creation (both points must be in the correct space, no min/max'ing done) //
	// - -------------------------------------------------------------------------------------- - //
	inline static const RectType _Pair( const VectorType& _Vec1, const VectorType& _Vec2 ) {
		return RectType( true, true, _Vec1, _Vec2 );
	}
	// - -------------------------------------------------------------------------------------- - //	

	// - -------------------------------------------------------------------------------------- - //
	// Creation as a Radius //
	// - -------------------------------------------------------------------------------------- - //
	inline static const RectType Radius( const Real& _x1, const Real& _y1, const Real& _x2, const Real& _y2 ) {
		return RectType( true, true, true, VectorType( _x1, _y1 ), VectorType( _x2, _y2 ) );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline static const RectType Radius( const VectorType& _Vec1, const VectorType& _Vec2 ) {
		return RectType( true, true, true, _Vec1, _Vec2 );
	}
	// - -------------------------------------------------------------------------------------- - //

public:
	// - -------------------------------------------------------------------------------------- - //
	inline const VectorType P1() const {
		return _P1;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const VectorType P2() const {
		return _P1 + _Shape;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	inline const VectorType Center() const {
		return P1() + HalfShape();
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	inline const Real& Width() const {
		return _Shape.x;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real HalfWidth() const {
		return Width() * Real::Half;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real& Height() const {
		return _Shape.y;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real HalfHeight() const {
		return Height() * Real::Half;
	}
	// - -------------------------------------------------------------------------------------- - //	

	// - -------------------------------------------------------------------------------------- - //
	inline const VectorType Shape() const {
		return _Shape;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const VectorType HalfShape() const {
		return Shape() * Real::Half;
	}
	// - -------------------------------------------------------------------------------------- - //
public:	
	// - -------------------------------------------------------------------------------------- - //
	inline const Real Area() const {
		return Width() * Height();
	}
	// - -------------------------------------------------------------------------------------- - //

public:	
	// - -------------------------------------------------------------------------------------- - //
	// Test for intersection between Rectangles //
	inline const bool operator == ( const RectType& Vs ) const;
	// - -------------------------------------------------------------------------------------- - //
	inline const bool operator != ( const RectType& Vs ) const {
		return !(*this == Vs);
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const bool operator == ( const VectorType& Vs ) const;
	// - -------------------------------------------------------------------------------------- - //
	// Rectangle Difference //
	inline const RectType& operator -= ( const RectType& Vs ) {
		*this = _Pair(
			Vector2D( P1().x.Max( Vs.P1().x ), P1().y.Max( Vs.P1().y ) ),
			Vector2D( P2().x.Min( Vs.P2().x ), P2().y.Min( Vs.P2().y ) )
			);

		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Rectangle Union //
	inline const RectType& operator += ( const RectType& Vs ) {
		*this = _Pair(
			Vector2D( P1().x.Min( Vs.P1().x ), P1().y.Min( Vs.P1().y ) ),
			Vector2D( P2().x.Max( Vs.P2().x ), P2().y.Max( Vs.P2().y ) )
			);

		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Given a point, find the closest point on the Rectangle //
	inline const VectorType ClosestPoint( const VectorType& v ) const {
		VectorType Point;
	
		if ( v.x < P1().x )
			Point.x = P1().x;
		else if ( v.x > P2().x )
			Point.x = P2().x;
		else
			Point.x = v.x;
	
		if ( v.y < P1().y )
			Point.y = P1().y;
		else if ( v.y > P2().y )
			Point.y = P2().y;
		else
			Point.y = v.y;
	
		return Point;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Given a point, find the nearest point on edge of the Rectangle //
	inline const VectorType NearestEdgePoint( const VectorType& v ) const {
		VectorType Point;
		
		// Construct a vector with the closest X edge and Y edge //
		if ( (P1().x - v.x).Abs() < (P2().x - v.x).Abs() )
			Point.x = P1().x;
		else
			Point.x = P2().x;
		
		if ( (P1().y - v.y).Abs() < (P2().y - v.y).Abs() )
			Point.y = P1().y;
		else
			Point.y = P2().y;
		
		// Return a vector with 
		if ( (Point.x - v.x).Abs() < (Point.y - v.y).Abs() )
			return VectorType( Point.x, v.y );
		else
			return VectorType( v.x, Point.y );
	}	
	
	// - -------------------------------------------------------------------------------------- - //
	// Contract a rectangle (like how a selection contract or expand works in PSP/Photoshop) //
	inline const RectType Contract( const Real& Value ) {
		RectType NewRect = *this;
		
		Vector2D Deformation( Value + Value, Value + Value );
		Deformation.x.Minimize( NewRect._Shape.x );
		Deformation.y.Minimize( NewRect._Shape.y );
		
		NewRect._P1 += Deformation * Real::Half;
		NewRect._Shape -= Deformation;
		
		return NewRect;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Expand a rectangle (like how a selection contract or expand works in PSP/Photoshop) //
	inline const RectType Expand( const Real& Value ) {
		RectType NewRect = *this;
		
		NewRect._P1 -= Vector2D( Value, Value );
		NewRect._Shape += Vector2D( Value, Value );
		NewRect._Shape += Vector2D( Value, Value );
		
		return NewRect;
	}
	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	// Adding vectors to offset the position of a rectangle //
	inline const RectType& operator += ( const VectorType& Vs ) {
		*this = Pair( P1() + Vs, P2() + Vs );
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Subtracting vectors to offset the position of a rectangle //
	inline const RectType& operator -= ( const VectorType& Vs ) {
		*this = Pair( P1() - Vs, P2() - Vs );
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
public:
	inline const class Rect2D ToRect() const;
	inline const class RadiusRect2D ToRadiusRect() const;
	inline const class PairRect2D ToPairRect() const;
	inline const ShapeRect2D& ToShapeRect() const {
		return *this;
	}
};

// - ------------------------------------------------------------------------------------------ - //
#endif // __Geometry_ShapeRect2D_H__ //
// - ------------------------------------------------------------------------------------------ - //
