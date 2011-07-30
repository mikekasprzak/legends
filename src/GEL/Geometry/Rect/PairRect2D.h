// - ------------------------------------------------------------------------------------------ - //
// PairRect2D //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Geometry_PairRect2D_H__
#define __Geometry_PairRect2D_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <Math/Real.h>
#include <Math/Vector.h>
// - ------------------------------------------------------------------------------------------ - //

class PairRect2D : 
	boost::additive<PairRect2D,
	boost::arithmetic2<PairRect2D, Vector2D
	> >
{
public:
	// - -------------------------------------------------------------------------------------- - //
	// A typedef for the current rect type, that way, similar code can be cut+paste easier //
	typedef PairRect2D RectType;
	typedef Vector2D VectorType;
	// - -------------------------------------------------------------------------------------- - //
	VectorType _P1;
	VectorType _P2;
	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	PairRect2D() {
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Normal Creation (RectXD style (x,y,w,h)) //
	// - -------------------------------------------------------------------------------------- - //
	inline PairRect2D( const Real& _x, const Real& _y, const Real& _w, const Real& _h ) :
		_P1( _x, _y ),
		_P2( _x + _w, _y + _h )
	{
	}
	// - -------------------------------------------------------------------------------------- - //
	inline PairRect2D( const VectorType& _Vec1, const VectorType& _Vec2 ) :
		_P1( _Vec1 ),
		_P2( _Vec1 + _Vec2 )
	{
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Pair Creation (P1, P2) //
	// - -------------------------------------------------------------------------------------- - //
	inline PairRect2D( const bool&, const VectorType& _Vec1, const VectorType& _Vec2 ) :
		_P1( _Vec1.x.Min( _Vec2.x ), _Vec1.y.Min( _Vec2.y ) ),
		_P2( _Vec1.x.Max( _Vec2.x ), _Vec1.y.Max( _Vec2.y ) )
	{
	}
	// - -------------------------------------------------------------------------------------- - //
	inline PairRect2D( const bool&, const bool&, const VectorType& _Vec1, const VectorType& _Vec2 ) :
		_P1( _Vec1 ),
		_P2( _Vec2 )
	{
	}
	// - -------------------------------------------------------------------------------------- - //


	// - -------------------------------------------------------------------------------------- - //
	// Radius Creation (Center, HalfShape) //
	// - -------------------------------------------------------------------------------------- - //
	inline PairRect2D( const bool&, const bool&, const bool&, const VectorType& _VecCenter, const VectorType& _VecShape ) :
		_P1( _VecCenter - _VecShape ),
		_P2( _VecCenter + _VecShape )
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
	inline const VectorType& P1() const {
		return _P1;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const VectorType& P2() const {
		return _P2;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	inline const VectorType Center() const {
		return P1() + HalfShape();
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	inline const Real Width() const {
		return P2().x - P1().x;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real HalfWidth() const {
		return Width() * Real::Half;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real Height() const {
		return P2().y - P1().y;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real HalfHeight() const {
		return Height() * Real::Half;
	}
	// - -------------------------------------------------------------------------------------- - //
	
	// - -------------------------------------------------------------------------------------- - //
	inline const VectorType Shape() const {
		return P2() - P1();
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
	// Test for intersection between rectangles //
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
		*this = Pair( P1().Max( Vs.P1() ), P2().Min( Vs.P2() ) );

		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Rectangle Union //
	inline const RectType& operator += ( const RectType& Vs ) {
		*this = Pair( P1().Min( Vs.P1() ), P2().Max( Vs.P2() ) );

		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
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
	// Contract a rectangle (like how a selection contract or expand works in PSP/Photoshop) //
	inline const RectType Contract( const Real& Value ) {
		RectType NewRect = *this;
		
		Vector2D Deformation( Value, Value );
		Deformation.x.Minimize( NewRect.HalfShape().x );
		Deformation.y.Minimize( NewRect.HalfShape().y );
		
		NewRect._P1 += Deformation;
		NewRect._P2 -= Deformation;
		
		return NewRect;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Expand a rectangle (like how a selection contract or expand works in PSP/Photoshop) //
	inline const RectType Expand( const Real& Value ) {
		RectType NewRect = *this;
		
		NewRect._P1 -= Vector2D( Value, Value );
		NewRect._P2 += Vector2D( Value, Value );
		
		return NewRect;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const void IncludePoint( const Vector2D& Point ) {
		if ( Point.x < _P1.x )
			_P1.x = Point.x;
		if ( Point.x > _P2.x )
			_P2.x = Point.x;

		if ( Point.y < _P1.y )
			_P1.y = Point.y;
		if ( Point.y > _P2.y )
			_P2.y = Point.y;
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
	inline const class ShapeRect2D ToShapeRect() const;
	inline const class RadiusRect2D ToRadiusRect() const;
	inline const PairRect2D& ToPairRect() const {
		return *this;
	}
};

// - ------------------------------------------------------------------------------------------ - //
#endif // __Geometry_PairRect2D_H__ //
// - ------------------------------------------------------------------------------------------ - //
