// - ------------------------------------------------------------------------------------------ - //
#include "Engine.h"
#include <Render/Render.h>
#include <Generate/Vertex.h>
// - ------------------------------------------------------------------------------------------ - //
using namespace Render;
// - ------------------------------------------------------------------------------------------ - //
const Matrix4x4 cBody::GetTransform() {
	if ( IsPoint() ) {
		return Matrix4x4::TranslationMatrix( GetPoint() );
	}
	else if ( IsCircle() || IsSphere() ) {
		return Matrix4x4::TranslationMatrix( GetCircle().Pos );
	}
	else if ( IsCircleV() || IsSphereV() ) {
		return Matrix4x4::TranslationMatrix( GetCircleV().Pos );
	}
	else {
		return Matrix4x4::Identity;
	}
}
// - ------------------------------------------------------------------------------------------ - //
const Rect3D cBody::GetRect() {
	// TODO: Make HalfCircles return a smaller bounding box //
	if ( IsPoint() ) {
		return Rect3D( GetPoint(), Vector3D::Zero );
	}
	else if ( IsCircle() || IsHalfCircle() ) {
		return Rect3D( 
			GetCircle().Pos - GetCircle().Radius._xx0(),	// NOTICE: _xx0, not _xxx //
			GetCircle().Radius._xx0() * Real::Two 
			);
	}
	else if ( IsCircleV() || IsHalfCircleV() ) {
		return Rect3D( 
			GetCircleV().Pos - GetCircleV().Radius._xx0(),	// NOTICE: _xx0, not _xxx //
			GetCircleV().Radius._xx0() * Real::Two 
			);
	}
	else if ( IsSphere() || IsHalfSphere() ) {
		return Rect3D( 
			GetSphere().Pos - GetSphere().Radius._xxx(),
			GetSphere().Radius._xxx() * Real::Two 
			);
	}
	else if ( IsSphereV() || IsHalfSphereV() ) {
		return Rect3D( 
			GetSphereV().Pos - GetSphereV().Radius._xxx(),
			GetSphereV().Radius._xxx() * Real::Two 
			);
	}
	else {
		return Rect3D( Vector3D::Zero, Vector3D::Zero );
	}		
}
// - ------------------------------------------------------------------------------------------ - //
void cBody::Draw( const Matrix4x4& Matrix ) {
	const GelColor PointColor = GEL_RGB_WHITE;
	const GelColor GeometryColor = GEL_RGB_YELLOW;

	if ( IsPoint() ) {
		const st32 VertCount = size_Vertex3D_RadiusRect();
		Vector3D Verts[ VertCount ];
		generate_Vertex3D_RadiusRect( Verts, GetPoint(), Real(1) );

		Render::Flat( GEL_LINE_LOOP, Matrix, PointColor, Verts, VertCount );
	}
	else if ( IsCircle() || IsCircleV() ) {
		const st32 VertCount = size_Vertex3D_Circle();
		Vector3D Verts[ VertCount ];
		generate_Vertex3D_Circle( Verts, GetCircle().Pos, GetCircle().Radius );

		Render::Flat( GEL_LINE_LOOP, Matrix, GeometryColor, Verts, VertCount );
	}
//	else if ( IsSphere() || IsSphereV() ) {
//		const st32 VertCount = size_Vertex3D_Sphere();
//		Vector3D Verts[ VertCount ];
//		generate_Vertex3D_Sphere( Verts, GetSphere().Pos, GetSphere().Radius );
//
//		Render::Flat( GEL_LINE_LOOP, Matrix, GeometryColor, Verts, VertCount );
//	}
//	else if ( IsHalfCircle() || IsHalfCircleV() ) {
//		const st32 VertCount = size_Vertex3D_Circle();
//		Vector3D Verts[ VertCount ];
//		generate_Vertex3D_Circle( Verts, GetCircle().Pos, GetCircle().Radius );
//
//		Render::Flat( GEL_LINE_LOOP, Matrix, GeometryColor, Verts, VertCount );
//	}
	else if ( IsCapsule() || IsCapsuleV() ) {
		const st32 VertCount = size_Vertex3D_Capsule();
		Vector3D Verts[ VertCount ];
		generate_Vertex3D_Capsule( Verts, GetCapsule().PosA, GetCapsule().RadiusA, GetCapsule().PosB, GetCapsule().RadiusB );

		Render::Flat( GEL_LINE_LOOP, Matrix, GeometryColor, Verts, VertCount );
	}
}
// - ------------------------------------------------------------------------------------------ - //
