// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/GraphicsDraw.h>
#include "RenderObjectInstance.h"

#include <Graphics/Texture/TexturePool.h>
// - ------------------------------------------------------------------------------------------ - //
cRenderObjectInstance Instantiate( const cRenderObject& Object ) {
	cRenderObjectInstance Instance;
	
	Instance.Object = &Object;
	Instance.Matrix = Matrix4x4::Identity;
		
	// Allocate Rect //
	Instance.FaceGroup = new_GelArray<cROIFaceGroup>(Instance.Object->FaceGroup->Size);
	Instance.CalculateRect();
	Instance.CalculateFaceGroupRects();
	
	// Software Lighting //
	{
		Instance.Vertex.Color.resize( Object.Vertex->Size, GEL_RGB_DEFAULT );
	}
	
	Instance.CalculateLighting();
	
	return Instance;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cRenderObjectInstance::CalculateLighting() {
/*
	extern Vector3D LightPos;
	Vector3D Light = LightPos;
	
//	Matrix3x3 NormMatrix( 
//		Matrix.Row0().ToVector3D().Normal(), 
//		Matrix.Row1().ToVector3D().Normal(),
//		Matrix.Row2().ToVector3D().Normal()
//		);

	Matrix4x4 NormMatrix( 
		Matrix.Row0().Normal(), 
		Matrix.Row1().Normal(),
		Matrix.Row2().Normal()
		);
		
//	Light = Light.ApplyMatrix( NormMatrix.Transpose() );
//	Light -= Matrix.Column3().ToVector3D();
	
	for ( size_t idx = 0; idx < Vertex.Color.size(); idx++ ) {
		Vector3D& Point = Object->Vertex->Data[ idx ].Pos;
		Vector3D& Norm = Object->Vertex->Data[ idx ].Normal;
		
		Vector3D Ray = Light - Point.ApplyMatrix( Matrix );
		Real Length = Ray.NormalizeRet();

		int Intensity = Real((256*10)/Length) * (Ray * Norm.ApplyMatrix( NormMatrix ));
		if ( Intensity > 255 )
			Intensity = 255;
		if ( Intensity < 0 )
			Intensity = 0;
		
		int Lighter = ((float)Intensity * 0.8f);

		extern GelColor Ambient;

		Vertex.Color[idx] = GEL_RGB( 
			GEL_GET_R(Ambient) > Intensity ? GEL_GET_R(Ambient) : Intensity, 
			GEL_GET_G(Ambient) > Lighter ? GEL_GET_G(Ambient) : Lighter, 
			GEL_GET_B(Ambient) > Intensity ? GEL_GET_B(Ambient) : Intensity
			);
	}
*/
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
void cRenderObjectInstance::CalculateFaceGroupRect( const size_t Index ) {
}
// - ------------------------------------------------------------------------------------------ - //
void cRenderObjectInstance::CalculateFaceGroupRects() {
	if ( Object ) {
		for ( size_t FG = 0; FG < Object->FaceGroup->Size; FG++ ) {
			Vector3D Point = Object->Vertex->Data[ Object->FaceGroup->Data[FG].Face->Data[0] ].Pos;
			Point = Point.ApplyMatrix( Matrix );
			
			FaceGroup->Data[FG].Rect = PairRect3D( Point, Vector3D::Zero );
			for ( size_t idx = 1; idx < Object->FaceGroup->Data[FG].Face->Size; idx++ ) {
				Point = Object->Vertex->Data[ Object->FaceGroup->Data[FG].Face->Data[idx] ].Pos;
				Point = Point.ApplyMatrix( Matrix );
	
				FaceGroup->Data[FG].Rect.IncludePoint( Point );
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cRenderObjectInstance::CalculateRect() {
	if ( Object ) {
		Vector3D Point = Object->Vertex->Data[0].Pos;
		Point = Point.ApplyMatrix( Matrix );
		
		Rect = PairRect3D( Point, Vector3D::Zero );
		for ( size_t idx = 1; idx < Object->Vertex->Size; idx++ ) {
			Point = Object->Vertex->Data[idx].Pos;
			Point = Point.ApplyMatrix( Matrix );

			Rect.IncludePoint( Point );
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cRenderObjectInstance::_DrawFaceGroup( const size_t Index ) {
/*
	glEnable(GL_TEXTURE_2D);
	//gelEnableAlphaBlending();
	gelSetTexture( Object->Material->Data[ Object->FaceGroup->Data[Index].MaterialIndex ].Texture );
	gelSetSmoothTexturesMipMapped();
	
	
	cPrimitive Primitive;
	Primitive.Count = Object->FaceGroup->Data[Index].Face->Size;
	Primitive.Vertex = &Object->Vertex->Data[0].Pos;
	Primitive.Normal = &Object->Vertex->Data[0].Normal;
	Primitive.UV = &Object->Vertex->Data[0].UV;
	
	Primitive.Color = &Vertex.Color[0];
	Primitive.ColorStride = 0;
	
	Primitive.Index = &Object->FaceGroup->Data[Index].Face->Data[0];
	Primitive.Stride = sizeof( cROVertex );
	Primitive.Flags = PRIMITIVE_DEFAULT | PRIMITIVE_TRIANGLES;
	
	Primitive.Draw();


	glDisable(GL_TEXTURE_2D);
*/
}
// - ------------------------------------------------------------------------------------------ - //
void cRenderObjectInstance::DrawFaceGroup( const size_t Index ) {
/*
	glPushMatrix();
	glMultMatrixf( (const float*)&Matrix );

	_DrawFaceGroup( Index );

	glPopMatrix();
*/
}
// - ------------------------------------------------------------------------------------------ - //
void cRenderObjectInstance::Draw() {
/*
	gelEnableAlphaBlending();
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	gelDrawRect( Rect.P1(), Rect.P2(), GEL_RGBA(255,255,255,64) );
	
	gelDrawCircleFill( Rect.P1(), Real(0.2), GEL_RGB_RED );
	gelDrawCircleFill( Rect.P2(), Real(0.2), GEL_RGB_YELLOW );

	gelDisableBlending();
	
	glPushMatrix();
	glMultMatrixf( (const float*)&Matrix );
	
	for ( size_t idx = 0; idx < Object->FaceGroup->Size; idx++ ) {
		_DrawFaceGroup( idx );
	}
	
	glPopMatrix();
*/
}
// - ------------------------------------------------------------------------------------------ - //
