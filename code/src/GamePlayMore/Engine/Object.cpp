// - ------------------------------------------------------------------------------------------ - //
#include "Engine.h"
#include <Render/Render.h>
#include <Generate/Vertex.h>
// - ------------------------------------------------------------------------------------------ - //
void cObject::Step() {
	Shared.Template = Template;
	Template->Step( this );
}
// - ------------------------------------------------------------------------------------------ - //
void cObject::Draw( const Matrix4x4& Matrix ) {
	Shared.Template = Template;
	Template->Draw( this, Matrix );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cObject::DrawRect( const Matrix4x4& Matrix ) {
	const GelColor RectColor = GEL_RGB_RED;
	
	const st32 VertCount = size_Vertex3D_Cube();
	Vector3D Verts[ VertCount ];
	generate_Vertex3D_Cube( Verts, Rect.P1(), Rect.Shape() );

	Render::Flat( GEL_LINES, Matrix, RectColor, Verts, VertCount );
}
// - ------------------------------------------------------------------------------------------ - //
