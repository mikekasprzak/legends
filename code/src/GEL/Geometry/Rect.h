// - ------------------------------------------------------------------------------------------ - //
// Rect //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Geometry_Rect_H__
#define __Geometry_Rect_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include "Rect/Rect2D.h"
#include "Rect/ShapeRect2D.h"
#include "Rect/RadiusRect2D.h"
#include "Rect/PairRect2D.h"

#include "Rect/Rect3D.h"
#include "Rect/ShapeRect3D.h"
#include "Rect/RadiusRect3D.h"
#include "Rect/PairRect3D.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// ShapeRect vs. ShapeRect //
const bool ShapeRect2D::operator == ( const ShapeRect2D& Vs ) const {
	PairRect2D r( P1(), Shape() + Vs.Shape() );
	Vector2D v( Vs.P2() );
	
	if ( v.x >= r.P1().x )
		if ( v.x < r.P2().x )
			if ( v.y >= r.P1().y )
				return ( v.y < r.P2().y );
	return false;
}
// - ------------------------------------------------------------------------------------------ - //
// RadiusRect vs. RadiusRect //
const bool RadiusRect2D::operator == ( const RadiusRect2D& Vs ) const {
	PairRect2D r( P1(), Shape() + Vs.Shape() );
	Vector2D v( Vs.P2() );
	
	if ( v.x >= r.P1().x )
		if ( v.x < r.P2().x )
			if ( v.y >= r.P1().y )
				return ( v.y < r.P2().y );
	return false;
}
// - ------------------------------------------------------------------------------------------ - //
// PairRect vs. PairRect //
const bool PairRect2D::operator == ( const PairRect2D& Vs ) const {
	PairRect2D r( P1(), Shape() + Vs.Shape() );
	Vector2D v( Vs.P2() );
	
	if ( v.x >= r.P1().x )
		if ( v.x < r.P2().x )
			if ( v.y >= r.P1().y )
				return ( v.y < r.P2().y );
	return false;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// ShapeRect vs. Vector //
const bool ShapeRect2D::operator == ( const Vector2D& Vs ) const {
	if ( Vs.x >= P1().x )
		if ( Vs.x < P2().x )
			if ( Vs.y >= P1().y )
				return ( Vs.y < P2().y );
	return false;
}
// - ------------------------------------------------------------------------------------------ - //
inline const bool operator == ( const Vector2D& a, const ShapeRect2D& b ) {
	return b == a;
}
// - ------------------------------------------------------------------------------------------ - //
inline const bool operator != ( const ShapeRect2D& a, const Vector2D& b ) {
	return !(a == b);
}
// - ------------------------------------------------------------------------------------------ - //
inline const bool operator != ( const Vector2D& a, const ShapeRect2D& b ) {
	return !(b == a);
}
// - ------------------------------------------------------------------------------------------ - //
// RadiusRect vs. Vector //
const bool RadiusRect2D::operator == ( const Vector2D& Vs ) const {
	if ( Vs.x >= P1().x )
		if ( Vs.x < P2().x )
			if ( Vs.y >= P1().y )
				return ( Vs.y < P2().y );
	return false;
}
// - ------------------------------------------------------------------------------------------ - //
inline const bool operator == ( const Vector2D& a, const RadiusRect2D& b ) {
	return b == a;
}
// - ------------------------------------------------------------------------------------------ - //
inline const bool operator != ( const RadiusRect2D& a, const Vector2D& b ) {
	return !(a == b);
}
// - ------------------------------------------------------------------------------------------ - //
inline const bool operator != ( const Vector2D& a, const RadiusRect2D& b ) {
	return !(b == a);
}
// - ------------------------------------------------------------------------------------------ - //
// PairRect vs. Vector //
const bool PairRect2D::operator == ( const Vector2D& Vs ) const {
	if ( Vs.x >= P1().x )
		if ( Vs.x < P2().x )
			if ( Vs.y >= P1().y )
				return ( Vs.y < P2().y );
	return false;
}
// - ------------------------------------------------------------------------------------------ - //
inline const bool operator == ( const Vector2D& a, const PairRect2D& b ) {
	return b == a;
}
// - ------------------------------------------------------------------------------------------ - //
inline const bool operator != ( const PairRect2D& a, const Vector2D& b ) {
	return !(a == b);
}
// - ------------------------------------------------------------------------------------------ - //
inline const bool operator != ( const Vector2D& a, const PairRect2D& b ) {
	return !(b == a);
}
// - ------------------------------------------------------------------------------------------ - //



// - ------------------------------------------------------------------------------------------ - //
// Rect Conversions //
// - ------------------------------------------------------------------------------------------ - //
const RadiusRect2D ShapeRect2D::ToRadiusRect() const {
	return RadiusRect2D( P1(), Shape() );
}
// - ------------------------------------------------------------------------------------------ - //
const PairRect2D ShapeRect2D::ToPairRect() const {
	return PairRect2D( P1(), Shape() );
}
// - ------------------------------------------------------------------------------------------ - //
const Rect2D ShapeRect2D::ToRect() const {
	return Rect2D( P1(), Shape() );
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// RadiusRect Conversions //
// - ------------------------------------------------------------------------------------------ - //
const Rect2D RadiusRect2D::ToRect() const {
	return Rect2D::Radius( Center(), HalfShape() );
}
// - ------------------------------------------------------------------------------------------ - //
const PairRect2D RadiusRect2D::ToPairRect() const {
	return PairRect2D::Radius( Center(), HalfShape() );
}
// - ------------------------------------------------------------------------------------------ - //
const ShapeRect2D RadiusRect2D::ToShapeRect() const {
	return ShapeRect2D::Radius( Center(), HalfShape() );
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// PairRect Conversions //
// - ------------------------------------------------------------------------------------------ - //
const Rect2D PairRect2D::ToRect() const {
	return Rect2D::Pair( P1(), P2() );
}
// - ------------------------------------------------------------------------------------------ - //
const RadiusRect2D PairRect2D::ToRadiusRect() const {
	return RadiusRect2D::Pair( P1(), P2() );
}
// - ------------------------------------------------------------------------------------------ - //
const ShapeRect2D PairRect2D::ToShapeRect() const {
	return ShapeRect2D::Pair( P1(), P2() );
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// Rect vs. Rect //
const bool ShapeRect3D::operator == ( const ShapeRect3D& Vs ) const {
	PairRect3D r( P1(), Shape() + Vs.Shape() );
	Vector3D v( Vs.P2() );
	
	if ( v.x >= r.P1().x )
		if ( v.x < r.P2().x )
			if ( v.y >= r.P1().y )
				if ( v.y < r.P2().y )
					if ( v.z >= r.P1().z )
						return ( v.z < r.P2().z );
	return false;
}
// - ------------------------------------------------------------------------------------------ - //
// RadiusRect3D vs. RadiusRect3D //
const bool RadiusRect3D::operator == ( const RadiusRect3D& Vs ) const {
	PairRect3D r( P1(), Shape() + Vs.Shape() );
	Vector3D v( Vs.P2() );
	
	if ( v.x >= r.P1().x )
		if ( v.x < r.P2().x )
			if ( v.y >= r.P1().y )
				if ( v.y < r.P2().y )
					if ( v.z >= r.P1().z )
						return ( v.z < r.P2().z );
	return false;
}
// - ------------------------------------------------------------------------------------------ - //
// PairRect3D vs. PairRect3D //
const bool PairRect3D::operator == ( const PairRect3D& Vs ) const {
	PairRect3D r( P1(), Shape() + Vs.Shape() );
	Vector3D v( Vs.P2() );
	
	if ( v.x >= r.P1().x )
		if ( v.x < r.P2().x )
			if ( v.y >= r.P1().y )
				if ( v.y < r.P2().y )
					if ( v.z >= r.P1().z )
						return ( v.z < r.P2().z );
	return false;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// Rect vs. Vector //
const bool ShapeRect3D::operator == ( const Vector3D& Vs ) const {
	if ( Vs.x >= P1().x )
		if ( Vs.x < P2().x )
			if ( Vs.y >= P1().y )
				if ( Vs.y < P2().y )
					if ( Vs.z >= P1().z )
						return ( Vs.z < P2().z );
	return false;
}
// - ------------------------------------------------------------------------------------------ - //
inline const bool operator == ( const Vector3D& a, const ShapeRect3D& b ) {
	return b == a;
}
// - ------------------------------------------------------------------------------------------ - //
inline const bool operator != ( const ShapeRect3D& a, const Vector3D& b ) {
	return !(a == b);
}
// - ------------------------------------------------------------------------------------------ - //
inline const bool operator != ( const Vector3D& a, const ShapeRect3D& b ) {
	return !(b == a);
}
// - ------------------------------------------------------------------------------------------ - //
// RadiusRect vs. Vector //
const bool RadiusRect3D::operator == ( const Vector3D& Vs ) const {
	if ( Vs.x >= P1().x )
		if ( Vs.x < P2().x )
			if ( Vs.y >= P1().y )
				if ( Vs.y < P2().y )
					if ( Vs.z >= P1().z )
						return ( Vs.z < P2().z );
	return false;
}
// - ------------------------------------------------------------------------------------------ - //
inline const bool operator == ( const Vector3D& a, const RadiusRect3D& b ) {
	return b == a;
}
// - ------------------------------------------------------------------------------------------ - //
inline const bool operator != ( const RadiusRect3D& a, const Vector3D& b ) {
	return !(a == b);
}
// - ------------------------------------------------------------------------------------------ - //
inline const bool operator != ( const Vector3D& a, const RadiusRect3D& b ) {
	return !(b == a);
}
// - ------------------------------------------------------------------------------------------ - //
// PairRect vs. Vector //
const bool PairRect3D::operator == ( const Vector3D& Vs ) const {
	if ( Vs.x >= P1().x )
		if ( Vs.x < P2().x )
			if ( Vs.y >= P1().y )
				if ( Vs.y < P2().y )
					if ( Vs.z >= P1().z )
						return ( Vs.z < P2().z );
	return false;
}
// - ------------------------------------------------------------------------------------------ - //
inline const bool operator == ( const Vector3D& a, const PairRect3D& b ) {
	return b == a;
}
// - ------------------------------------------------------------------------------------------ - //
inline const bool operator != ( const PairRect3D& a, const Vector3D& b ) {
	return !(a == b);
}
// - ------------------------------------------------------------------------------------------ - //
inline const bool operator != ( const Vector3D& a, const PairRect3D& b ) {
	return !(b == a);
}
// - ------------------------------------------------------------------------------------------ - //



// - ------------------------------------------------------------------------------------------ - //
// Rect Conversions //
// - ------------------------------------------------------------------------------------------ - //
const RadiusRect3D ShapeRect3D::ToRadiusRect() const {
	return RadiusRect3D( P1(), Shape() );
}
// - ------------------------------------------------------------------------------------------ - //
const PairRect3D ShapeRect3D::ToPairRect() const {
	return PairRect3D( P1(), Shape() );
}
// - ------------------------------------------------------------------------------------------ - //
const Rect3D ShapeRect3D::ToRect() const {
	return Rect3D( P1(), Shape() );
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// RadiusRect Conversions //
// - ------------------------------------------------------------------------------------------ - //
const Rect3D RadiusRect3D::ToRect() const {
	return Rect3D::Radius( Center(), HalfShape() );
}
// - ------------------------------------------------------------------------------------------ - //
const PairRect3D RadiusRect3D::ToPairRect() const {
	return PairRect3D::Radius( Center(), HalfShape() );
}
// - ------------------------------------------------------------------------------------------ - //
const ShapeRect3D RadiusRect3D::ToShapeRect() const {
	return ShapeRect3D::Radius( Center(), HalfShape() );
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// PairRect Conversions //
// - ------------------------------------------------------------------------------------------ - //
const Rect3D PairRect3D::ToRect() const {
	return Rect3D::Pair( P1(), P2() );
}
// - ------------------------------------------------------------------------------------------ - //
const RadiusRect3D PairRect3D::ToRadiusRect() const {
	return RadiusRect3D::Pair( P1(), P2() );
}
// - ------------------------------------------------------------------------------------------ - //
const ShapeRect3D PairRect3D::ToShapeRect() const {
	return ShapeRect3D::Pair( P1(), P2() );
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
#endif // __Geometry_Rect_H__ //
// - ------------------------------------------------------------------------------------------ - //
