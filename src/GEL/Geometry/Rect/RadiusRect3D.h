// - ------------------------------------------------------------------------------------------ - //
// RadiusRect3D //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Geometry_RadiusRect3D_H__
#define __Geometry_RadiusRect3D_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <Math/Real.h>
#include <Math/Vector.h>
// - ------------------------------------------------------------------------------------------ - //

class RadiusRect3D : 
	boost::additive<RadiusRect3D,
	boost::arithmetic2<RadiusRect3D, Vector3D
	> >
{
public:
	// - -------------------------------------------------------------------------------------- - //
	// A typedef for the current rect type, that way, similar code can be cut+paste easier //
	typedef RadiusRect3D RectType;
	typedef Vector3D VectorType;
	// - -------------------------------------------------------------------------------------- - //
	VectorType _Center;
	VectorType _HalfShape;
	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	inline RadiusRect3D() {
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Normal Creation (RectXD style (x,y,w,h)) //
	// - -------------------------------------------------------------------------------------- - //
	inline RadiusRect3D( const Real& _x, const Real& _y, const Real& _z, const Real& _w, const Real& _h, const Real& _l ) :
		_Center( _x + (_w * Real::Half), _y + (_h * Real::Half), _z + (_l * Real::Half) ),
		_HalfShape( _w * Real::Half, _h * Real::Half, _l * Real::Half )
	{
	}
	// - -------------------------------------------------------------------------------------- - //
	inline RadiusRect3D( const VectorType& _Vec1, const VectorType& _Vec2 ) :
		_Center( _Vec1 + (_Vec2 * Real::Half) ),
		_HalfShape( _Vec2 * Real::Half )
	{
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Pair Creation (P1, P2) //
	// - -------------------------------------------------------------------------------------- - //
	inline RadiusRect3D( const bool&, const VectorType& _Vec1, const VectorType& _Vec2 ) :
		_Center( 
			(_Vec1.x.Min( _Vec2.x )) + ((_Vec2.x - _Vec1.x).Abs() * Real::Half),
			(_Vec1.y.Min( _Vec2.y )) + ((_Vec2.y - _Vec1.y).Abs() * Real::Half),
			(_Vec1.z.Min( _Vec2.z )) + ((_Vec2.z - _Vec1.z).Abs() * Real::Half)
			),
		_HalfShape( 
			(_Vec2.x - _Vec1.x).Abs() * Real::Half,
			(_Vec2.y - _Vec1.y).Abs() * Real::Half,
			(_Vec2.z - _Vec1.z).Abs() * Real::Half
			)
	{
	}
	// - -------------------------------------------------------------------------------------- - //
	inline RadiusRect3D( const bool&, const bool&, const VectorType& _Vec1, const VectorType& _Vec2 ) :
		_Center( _Vec1 + ((_Vec2 - _Vec1) * Real::Half) ),
		_HalfShape( (_Vec2 - _Vec1) * Real::Half )
	{
	}
	// - -------------------------------------------------------------------------------------- - //


	// - -------------------------------------------------------------------------------------- - //
	// Radius Creation (Center, HalfShape) //
	// - -------------------------------------------------------------------------------------- - //
	inline RadiusRect3D( const bool&, const bool&, const bool&, const VectorType& _VecCenter, const VectorType& _VecShape ) :
		_Center( _VecCenter ),
		_HalfShape( _VecShape )
	{
	}
	// - -------------------------------------------------------------------------------------- - //

public:
	// - -------------------------------------------------------------------------------------- - //
	// Creation as a Pair //
	// - -------------------------------------------------------------------------------------- - //
	inline static const RectType Pair( const Real& _x1, const Real& _y1, const Real& _z1, const Real& _x2, const Real& _y2, const Real& _z2 ) {
		return RectType( true, VectorType( _x1, _y1, _z1 ), VectorType( _x2, _y2, _z2 ) );
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
	inline static const RectType Radius( const Real& _x1, const Real& _y1, const Real& _z1, const Real& _x2, const Real& _y2, const Real& _z2 ) {
		return RectType( true, true, true, VectorType( _x1, _y1, _z1 ), VectorType( _x2, _y2, _z2 ) );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline static const RectType Radius( const VectorType& _Vec1, const VectorType& _Vec2 ) {
		return RectType( true, true, true, _Vec1, _Vec2 );
	}
	// - -------------------------------------------------------------------------------------- - //

public:
	// - -------------------------------------------------------------------------------------- - //
	inline const VectorType P1() const {
		return _Center - _HalfShape;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const VectorType P2() const {
		return _Center + _HalfShape;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	inline const VectorType& Center() const {
		return _Center;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	inline const Real Width() const {
		return _HalfShape.x + _HalfShape.x;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real& HalfWidth() const {
		return _HalfShape.x;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real Height() const {
		return _HalfShape.y + _HalfShape.y;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real& HalfHeight() const {
		return _HalfShape.y;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real Length() const {
		return _HalfShape.z + _HalfShape.z;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real& HalfLength() const {
		return _HalfShape.z;
	}
	// - -------------------------------------------------------------------------------------- - //	

	// - -------------------------------------------------------------------------------------- - //
	inline const VectorType Shape() const {
		return _HalfShape + _HalfShape;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const VectorType& HalfShape() const {
		return _HalfShape;
	}
	// - -------------------------------------------------------------------------------------- - //
public:	
	// - -------------------------------------------------------------------------------------- - //
	inline const Real Volume() const {
		return Width() * Height() * Length();
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

		if ( v.z < P1().z )
			Point.z = P1().z;
		else if ( v.z > P2().z )
			Point.z = P2().z;
		else
			Point.z = v.z;
		
		return Point;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Contract a rectangle (like how a selection contract or expand works in PSP/Photoshop) //
	inline const RectType Contract( const Real& Value ) {
		RectType NewRect = *this;
		
		NewRect._HalfShape -= Vector3D( Value, Value, Value );
		
		NewRect._HalfShape.x.Minimize( Real::Zero );
		NewRect._HalfShape.y.Minimize( Real::Zero );
		NewRect._HalfShape.z.Minimize( Real::Zero );
		
		return NewRect;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Expand a rectangle (like how a selection contract or expand works in PSP/Photoshop) //
	inline const RectType Expand( const Real& Value ) {
		RectType NewRect = *this;
		
		NewRect._HalfShape += Vector3D( Value, Value, Value );
		
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
	inline const class Rect3D ToRect() const;
	inline const class ShapeRect3D ToShapeRect() const;
	inline const class PairRect3D ToPairRect() const;
	inline const RadiusRect3D& ToRadiusRect() const {
		return *this;
	}
};

// - ------------------------------------------------------------------------------------------ - //
#endif // __Geometry_RadiusRect3D_H__ //
// - ------------------------------------------------------------------------------------------ - //
