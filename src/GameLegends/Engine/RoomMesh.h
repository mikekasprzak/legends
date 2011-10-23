// - ------------------------------------------------------------------------------------------ - //
#ifndef __RoomMesh_H__
#define __RoomMesh_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector.h>
#include <Graphics/GraphicsDraw.h>
#include <Graphics/Mesh/PMEFile.h>
#include <AssetPool/AssetPool.h>

#include "../Physics.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
class cRoomMesh {
public:
	Vector3D Pos;
	Real Scalar;
	Matrix3x3 Orientation;
	
//	cPMEFile* Mesh;
	GelAssetHandle MeshHandle;

	cPhysicsObject* PhysicsObject;

public:
	cRoomMesh() :
		PhysicsObject( 0 )
	{
	}

	cRoomMesh( const Vector3D& _Pos, const char* _File, Real _Scalar = Real(32) ) :
		Pos( _Pos),
//		Mesh( _Mesh ),
		MeshHandle( AssetPool::Load( _File ) ),
		Scalar( _Scalar ),
		PhysicsObject( 0 )
	{
	}
	
	void Step() {
		
	}
	
	void Draw() {
		gelMultMatrix( Matrix4x4::TranslationMatrix( Pos ) );
		gelMultMatrix( Matrix4x4::ScalarMatrix( Vector3D( Scalar, Scalar, Scalar ) ) );

//		gelMultMatrix( Orientation.ToMatrix4x4() );

		cPMEFile* Mesh = AssetPool::GetMesh( MeshHandle );

		for ( int idx = 0; idx < Mesh->Mesh.size(); idx++ ) {
			AssetPool::Set( Mesh->Mesh[idx].Material[0].Texture );
				
			gelDrawIndexedTrianglesTextured( &(Mesh->Mesh[idx].Vertex[0]), (const GelUV*)&(Mesh->Mesh[idx].Vertex[0].UV), (unsigned short*)&(Mesh->Mesh[idx].FaceGroup[0].Face[0]), Mesh->Mesh[idx].FaceGroup[0].Face.size()*3 );
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
#endif // __Room_H__ //
// - ------------------------------------------------------------------------------------------ - //