// - ------------------------------------------------------------------------------------------ - //
#include "Engine.h"
#include <Render/Render.h>
// - ------------------------------------------------------------------------------------------ - //
using namespace Render;
// - ------------------------------------------------------------------------------------------ - //
void cArt::Draw( const Matrix4x4& Matrix ) {
	if ( Type == AT_CIRCLE ) {
		cArt_Sphere* Art = GetCirclePtr();
		
		int Steps = 16;
		float Verts[Steps*3];
		float FloatSteps = Steps;
	    
		for ( int idx = 0; idx < Steps; idx++ ) {
			Verts[(idx*3)+0] = Art->Pos.x + (Real::Cos(idx / FloatSteps) * Art->Radius);
			Verts[(idx*3)+1] = Art->Pos.y + (Real::Sin(idx / FloatSteps) * Art->Radius);
			Verts[(idx*3)+2] = Art->Pos.z;
		}

		Default->Bind( FlatShader );
		Default->UniformMatrix4x4( 0, Matrix );
		Default->UniformColor( 1, Art->Color ); // GlobalColor //
		Default->BindUniforms();
		Default->Attrib( 0, Verts );
		Default->DrawArrays( GEL_TRIANGLE_FAN, Steps*3 );
	   
		//gelDrawLineLoop( (Vector2D*)Verts, Steps, Color );
	}
}
// - ------------------------------------------------------------------------------------------ - //
