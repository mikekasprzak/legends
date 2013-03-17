// - ------------------------------------------------------------------------------------------ - //
#include "Engine.h"
#include <Render/Render.h>
#include <Generate/Vertex.h>
// - ------------------------------------------------------------------------------------------ - //
using namespace Render;
// - ------------------------------------------------------------------------------------------ - //
void cArt::Draw( const Matrix4x4& Matrix ) {
	if ( Type == AT_CIRCLE ) {
		cArt_Sphere* Art = GetCirclePtr();
	
		const st32 VertCount = size_Vertex3D_Circle();
		Vector3D Verts[ VertCount ];
		generate_Vertex3D_Circle( Verts, Art->Pos, Art->Radius );

		Render::Flat( GEL_TRIANGLE_FAN, Matrix, Art->Color, Verts, VertCount );
		//GEL_LINE_LOOP
	}
	else if ( Type == AT_HALFCIRCLE ) {
		cArt_HalfSphere* Art = GetHalfCirclePtr();
	
		const st32 VertCount = size_Vertex3D_HalfCircle();
		Vector3D Verts[ VertCount ];
		generate_Vertex3D_HalfCircle( Verts, Art->Pos, Art->Radius, Art->Normal );

		Render::Flat( GEL_TRIANGLE_FAN, Matrix, Art->Color, Verts, VertCount );
		//GEL_LINE_LOOP
	}
	else if ( Type == AT_RADIUSRECT ) {
		cArt_RadiusRect* Art = GetRadiusRectPtr();

		const st32 VertCount = size_Vertex3D_RadiusRect();
		Vector3D Verts[ VertCount ];
		generate_Vertex3D_RadiusRect( Verts, Art->Pos, Art->Radius._xy0() );

		Render::Flat( GEL_TRIANGLE_FAN, Matrix, Art->Color, Verts, VertCount );
		//GEL_LINE_LOOP
	}
	else if ( Type == AT_CAPSULE ) {
		cArt_Capsule* Art = GetCapsulePtr();

//		const st32 VertCount = size_Vertex3D_DiamondCapsule();
//		Vector3D Verts[ VertCount ];
//		generate_Vertex3D_DiamondCapsule( Verts, Art->PosA, Art->RadiusA, Art->PosB, Art->RadiusB );

//		const st32 VertCount = size_Vertex3D_FlatCapsule();
//		Vector3D Verts[ VertCount ];
//		generate_Vertex3D_FlatCapsule( Verts, Art->PosA, Art->RadiusA, Art->PosB, Art->RadiusB );

		const st32 VertCount = size_Vertex3D_Capsule();
		Vector3D Verts[ VertCount ];
		generate_Vertex3D_Capsule( Verts, Art->PosA, Art->RadiusA, Art->PosB, Art->RadiusB );
		
//		int Steps = 32;
//		float Verts[(Steps+2)*3];
//		float FloatSteps = Steps;
//	    
//		for ( int idx = 0; idx < Steps; idx++ ) {
//			st32 BaseIndex = idx*3;
//			Verts[BaseIndex+0] = Art->Pos.x + (Real::Cos(0.0f+(idx / FloatSteps)) * Art->Radius);
//			Verts[BaseIndex+1] = Art->Pos.y + (Real::Sin(0.0f+(idx / FloatSteps)) * Art->Radius);
//			Verts[BaseIndex+2] = Art->Pos.z;
//		}
		
		Render::Flat( GEL_TRIANGLE_FAN, Matrix, Art->Color, Verts, VertCount );
		//GEL_LINE_LOOP
	}
}
// - ------------------------------------------------------------------------------------------ - //
