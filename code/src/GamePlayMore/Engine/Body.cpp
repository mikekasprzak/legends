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
	else if ( IsCircle() ) {
		return Matrix4x4::TranslationMatrix( GetCircle().Pos );
	}
	else {
		return Matrix4x4::Identity;
	}
}
// - ------------------------------------------------------------------------------------------ - //
const Rect3D cBody::GetRect() {
	if ( IsPoint() ) {
		return Rect3D( GetPoint(), Vector3D::Zero );
	}
	else if ( IsCircle() ) {
		return Rect3D( 
			GetCircle().Pos - GetCircle().Radius.xxx(),
			GetCircle().Radius.xxx() * Real::Two 
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
	else if ( IsCircle() ) {
		const st32 VertCount = size_Vertex3D_Circle();
		Vector3D Verts[ VertCount ];
		generate_Vertex3D_Circle( Verts, GetCirclePtr()->Pos, GetCirclePtr()->Radius );

		Render::Flat( GEL_LINE_LOOP, Matrix, GeometryColor, Verts, VertCount );
	}
}
// - ------------------------------------------------------------------------------------------ - //
