// - ------------------------------------------------------------------------------------------ - //
#include "Engine.h"
#include <Render/Render.h>
// - ------------------------------------------------------------------------------------------ - //
using namespace Render;
// - ------------------------------------------------------------------------------------------ - //
void cArt::Draw( const Matrix4x4& Matrix ) {
	if ( Type == AT_CIRCLE ) {
		cArt_Sphere* Art = GetCirclePtr();
		
		int Steps = 32;//16;
		float Verts[Steps*3];
		float FloatSteps = Steps;
	    
		for ( int idx = 0; idx < Steps; idx++ ) {
			st32 BaseIndex = idx*3;
			Verts[BaseIndex+0] = Art->Pos.x + (Real::Cos(idx / FloatSteps) * Art->Radius);
			Verts[BaseIndex+1] = Art->Pos.y + (Real::Sin(idx / FloatSteps) * Art->Radius);
			Verts[BaseIndex+2] = Art->Pos.z;
		}
		
		Default->Bind( FlatShader );
		Default->UniformMatrix4x4( 0, Matrix );
		Default->UniformColor( 1, Art->Color ); // GlobalColor //
		Default->BindUniforms();
		Default->Attrib( 0, Verts );
		Default->DrawArrays( GEL_TRIANGLE_FAN, Steps );
//		Default->DrawArrays( GEL_LINE_LOOP, Steps );
	}
	else if ( Type == AT_LEFTHALFCIRCLE ) {
		cArt_Sphere* Art = GetCirclePtr();
		
		int Steps = 16+1;
		float Verts[Steps*3];
		float FloatSteps = (Steps-1)*2; // Half //
	    
		for ( int idx = 0; idx < Steps; idx++ ) {
			st32 BaseIndex = idx*3;
			Verts[BaseIndex+0] = Art->Pos.x - (Real::Sin(idx / FloatSteps) * Art->Radius);
			Verts[BaseIndex+1] = Art->Pos.y + (Real::Cos(idx / FloatSteps) * Art->Radius);
			Verts[BaseIndex+2] = Art->Pos.z;
		}
		
		Default->Bind( FlatShader );
		Default->UniformMatrix4x4( 0, Matrix );
		Default->UniformColor( 1, Art->Color ); // GlobalColor //
		Default->BindUniforms();
		Default->Attrib( 0, Verts );
		Default->DrawArrays( GEL_TRIANGLE_FAN, Steps );
//		Default->DrawArrays( GEL_LINE_LOOP, Steps );
	}
	else if ( Type == AT_RIGHTHALFCIRCLE ) {
		cArt_Sphere* Art = GetCirclePtr();
		
		int Steps = 16+1;
		float Verts[Steps*3];
		float FloatSteps = (Steps-1)*2; // Half //
	    
		for ( int idx = 0; idx < Steps; idx++ ) {
			st32 BaseIndex = idx*3;
			Verts[BaseIndex+0] = Art->Pos.x + (Real::Sin(idx / FloatSteps) * Art->Radius);
			Verts[BaseIndex+1] = Art->Pos.y + (Real::Cos(idx / FloatSteps) * Art->Radius);
			Verts[BaseIndex+2] = Art->Pos.z;
		}
		
		Default->Bind( FlatShader );
		Default->UniformMatrix4x4( 0, Matrix );
		Default->UniformColor( 1, Art->Color ); // GlobalColor //
		Default->BindUniforms();
		Default->Attrib( 0, Verts );
		Default->DrawArrays( GEL_TRIANGLE_FAN, Steps );
//		Default->DrawArrays( GEL_LINE_LOOP, Steps );
	}
	else if ( Type == AT_RADIUSRECT ) {
		cArt_RadiusRect* Art = GetRadiusRectPtr();
		
		float Verts[4*3] = {
			Art->Pos.x - Art->Radius.x, Art->Pos.y - Art->Radius.y, Art->Pos.z,
			Art->Pos.x + Art->Radius.x, Art->Pos.y - Art->Radius.y, Art->Pos.z,
			Art->Pos.x + Art->Radius.x, Art->Pos.y + Art->Radius.y, Art->Pos.z,
			Art->Pos.x - Art->Radius.x, Art->Pos.y + Art->Radius.y, Art->Pos.z
		};
		
		Default->Bind( FlatShader );
		Default->UniformMatrix4x4( 0, Matrix );
		Default->UniformColor( 1, Art->Color ); // GlobalColor //
		Default->BindUniforms();
		Default->Attrib( 0, Verts );
		Default->DrawArrays( GEL_TRIANGLE_FAN, 4 );
//		Default->DrawArrays( GEL_LINE_LOOP, 4 );
	}
	else if ( Type == AT_CAPSULE ) {
		cArt_Capsule* Art = GetCapsulePtr();
		
//		int Steps = 32;
//		float Verts[(Steps+2)*3];
//		float FloatSteps = Steps;
//	    
//		for ( int idx = 0; idx < Steps/2; idx++ ) {
//			st32 BaseIndex = idx*3;
//			Verts[BaseIndex+0] = Art->Pos.x + (Real::Cos(idx / FloatSteps) * Art->Radius);
//			Verts[BaseIndex+1] = Art->Pos.y + (Real::Sin(idx / FloatSteps) * Art->Radius);
//			Verts[BaseIndex+2] = Art->Pos.z;
//		}

		Vector3D Line = Art->PosB - Art->PosA;
		Vector3D Tangent = cross(Line,Vector3D(0,0,1)).Normal();
		Vector3D LineNormal = Line.Normal();

		// HACK! Not a rounded capsule //
		float Verts[(4+2)*3] = {
			// Side //
			Art->PosA.x + (Art->RadiusA * Tangent.x), Art->PosA.y + (Art->RadiusA * Tangent.y), Art->PosA.z,
			Art->PosB.x + (Art->RadiusB * Tangent.x), Art->PosB.y + (Art->RadiusB * Tangent.y), Art->PosB.z,
			// End Cap //
			Art->PosB.x + (Art->RadiusB * LineNormal.x), Art->PosB.y + (Art->RadiusB * LineNormal.y), Art->PosA.z,
			// Side //
			Art->PosB.x - (Art->RadiusB * Tangent.x), Art->PosB.y - (Art->RadiusB * Tangent.y), Art->PosB.z,
			Art->PosA.x - (Art->RadiusB * Tangent.x), Art->PosA.y - (Art->RadiusA * Tangent.y), Art->PosA.z,
			// End Cap //
			Art->PosA.x - (Art->RadiusA * LineNormal.x), Art->PosA.y - (Art->RadiusA * LineNormal.y), Art->PosA.z,
		};

		
		Default->Bind( FlatShader );
		Default->UniformMatrix4x4( 0, Matrix );
		Default->UniformColor( 1, Art->Color ); // GlobalColor //
		Default->BindUniforms();
		Default->Attrib( 0, Verts );
		Default->DrawArrays( GEL_TRIANGLE_FAN, sizeof(Verts)/sizeof(float)/3 );
//		Default->DrawArrays( GEL_LINE_LOOP, sizeof(Verts)/sizeof(float)/3 );
	}
}
// - ------------------------------------------------------------------------------------------ - //
