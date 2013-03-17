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
	
	const st32 VertCount = size_Vertex3D_Rect();
	Vector3D Verts[ VertCount ];
	generate_Vertex3D_Rect( Verts, Rect.P1(), Rect.Shape() );

	Render::Flat( GEL_LINE_LOOP, Matrix, RectColor, Verts, VertCount );
}
// - ------------------------------------------------------------------------------------------ - //
