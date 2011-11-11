// - ------------------------------------------------------------------------------------------ - //
#ifndef __Object3D_H__
#define __Object3D_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector.h>
#include <Graphics/GraphicsDraw.h>
#include <Graphics/Mesh/PMEFile.h>
#include <AssetPool/AssetPool.h>

#include "../UberShader/UberShader.h"

#ifdef USES_SIXENSE
#include <sixense.h>
#endif // USES_SIXENSE //

// - ------------------------------------------------------------------------------------------ - //
class cObject3D {
public:
	Vector3D Pos;
	Real Scalar;
	Matrix3x3 Orientation;
	
	//cPMEFile* Mesh;
	GelAssetHandle MeshHandle;
	
	GelColor Color;
	GelColor GlowColor;

	cPhysicsObject* PhysicsObject;
	
	bool IsGlowing;
	
	cObject3D( const Vector3D& _Pos, const char* _File, Real _Scalar = Real(32), GelColor _Color = GEL_RGB_WHITE, GelColor _GlowColor = GEL_RGBA(255,255,255,32) ) :
		Pos( _Pos),
		MeshHandle( AssetPool::Load( _File ) ),
		Color( _Color ),
		GlowColor( _GlowColor ),
		Scalar( _Scalar ),
		PhysicsObject( 0 ),
		IsGlowing( false )
	{
	}
	
	void Step() {
		if ( PhysicsObject ) {
			PhysicsObject->Step();
			Pos = PhysicsObject->GetPos();
			
			Orientation = PhysicsObject->GetBasis();
		}		
	}
	
	void Draw() {
		gelMultMatrix( Matrix4x4::TranslationMatrix( Pos ) );
		gelMultMatrix( Matrix4x4::ScalarMatrix( Vector3D( Scalar, Scalar, Scalar ) ) );
		
//#ifdef USES_SIXENSE
//		sixenseSetActiveBase(0);
//		sixenseAllControllerData acd;
//		sixenseGetAllNewestData( &acd );
//
//		gelMultMatrix( Matrix3x3( (const float*)&(acd.controllers[0].rot_mat) ).Transpose().ToMatrix4x4() );
//#endif // USES_SIXENSE //

		gelMultMatrix( Orientation.ToMatrix4x4() );

		cPMEFile* Mesh = AssetPool::GetMesh( MeshHandle );

		gelSetColor( Color );
		for ( size_t idx = 0; idx < Mesh->Mesh.size(); idx++ ) {
			if ( Mesh->Mesh[idx].Material.size() == 1 ) {
				AssetPool::Set( Mesh->Mesh[idx].Material[0].Texture );
			}
			else {
				Log( "Honk" );
			}
			
			//gelDrawIndexedTriangles( &(Mesh->Mesh[idx].Vertex[0]), (unsigned short*)&(Mesh->Mesh[idx].FaceGroup[0].Face[0]), Mesh->Mesh[idx].FaceGroup[0].Face.size()*3 );
//			gelDrawIndexedTrianglesColors( &(Mesh->Mesh[idx].Vertex[0]), (unsigned int*)&(Mesh->Mesh[idx].Vertex[0].Color), (unsigned short*)&(Mesh->Mesh[idx].FaceGroup[0].Face[0]), Mesh->Mesh[idx].FaceGroup[0].Face.size()*3 );
			gelDrawIndexedTrianglesTextured( &(Mesh->Mesh[idx].Vertex[0]), (const GelUV*)&(Mesh->Mesh[idx].Vertex[0].UV), (unsigned short*)&(Mesh->Mesh[idx].FaceGroup[0].Face[0]), Mesh->Mesh[idx].FaceGroup[0].Face.size()*3 );
		}
	}

	void Draw( cUberShader* InShader, const Matrix4x4& ViewMatrix ) {
		Matrix4x4 Me = ViewMatrix;
		Me = Matrix4x4::TranslationMatrix( Pos ) * Me;
		Me = Matrix4x4::ScalarMatrix( Vector3D( Scalar, Scalar, Scalar ) ) * Me;
		Me = Orientation.ToMatrix4x4() * Me;

		cPMEFile* Mesh = AssetPool::GetMesh( MeshHandle );
		
		InShader->BindUniformMatrix4x4( "ViewMatrix", Me );
		InShader->BindUniformColor( "MaxColor", GEL_RGB(148,250,84) );
		InShader->BindUniformColor( "MinColor", GEL_RGB(84,84,84) );
		
		for ( size_t idx = 0; idx < Mesh->Mesh.size(); idx++ ) {
			if ( Mesh->Mesh[idx].Material.size() == 1 ) {
				AssetPool::Set( Mesh->Mesh[idx].Material[0].Texture );
			}
			else {
				Log( "Honk" );
			}
			
			gelDrawIndexedTrianglesTextured( &(Mesh->Mesh[idx].Vertex[0]), (const GelUV*)&(Mesh->Mesh[idx].Vertex[0].UV), (unsigned short*)&(Mesh->Mesh[idx].FaceGroup[0].Face[0]), Mesh->Mesh[idx].FaceGroup[0].Face.size()*3 );
		}
	}

	void DrawGlow() {
		gelMultMatrix( Matrix4x4::TranslationMatrix( Pos ) );
		gelMultMatrix( Matrix4x4::ScalarMatrix( Vector3D( Scalar, Scalar, Scalar ) ) );
		gelMultMatrix( Orientation.ToMatrix4x4() );

		cPMEFile* Mesh = AssetPool::GetMesh( MeshHandle );

		gelSetColor( GlowColor );
		for ( size_t idx = 0; idx < Mesh->Mesh.size(); idx++ ) {
			gelDrawIndexedTriangles( &(Mesh->Mesh[idx].Vertex[0]), (unsigned short*)&(Mesh->Mesh[idx].FaceGroup[0].Face[0]), Mesh->Mesh[idx].FaceGroup[0].Face.size()*3 );
		}
	}

	void DrawDebug() {
		if ( PhysicsObject ) {
			btVector3 Min, Max;
			PhysicsObject->shape->getAabb( PhysicsObject->trans, Min, Max );
			
			gelDrawCube( *((Vector3D*)&Min), *((Vector3D*)&Max), GEL_RGB_RED );
		}
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Object3D_H__ //
// - ------------------------------------------------------------------------------------------ - //
