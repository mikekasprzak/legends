// - ------------------------------------------------------------------------------------------ - //
#ifndef __Object3D_H__
#define __Object3D_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector.h>
#include <Graphics/GraphicsDraw.h>
#include <Graphics/Mesh/PMEFile.h>

#ifdef USES_SIXENSE
#include <sixense.h>
#endif // USES_SIXENSE //

// - ------------------------------------------------------------------------------------------ - //
class cObject3D {
public:
	Vector3D Pos;
	Real Scalar;
	
	cPMEFile* Mesh;
	
	cObject3D( Vector3D _Pos, cPMEFile* _Mesh, Real _Scalar = Real(32) ) :
		Pos( _Pos),
		Mesh( _Mesh ),
		Scalar( _Scalar )
	{	
	}
	
	void Step() {
		
	}
	
	void Draw() {
		gelMultMatrix( Matrix4x4::TranslationMatrix( Pos ) );
		gelMultMatrix( Matrix4x4::ScalarMatrix( Vector3D( Scalar, -Scalar, Scalar ) ) );
		
#ifdef USES_SIXENSE
		sixenseSetActiveBase(0);
		sixenseAllControllerData acd;
		sixenseGetAllNewestData( &acd );

		gelMultMatrix( Matrix3x3( (const float*)&(acd.controllers[0].rot_mat) ).Transpose().ToMatrix4x4() );
#endif // USES_SIXENSE //

		for ( int idx = 0; idx < Mesh->Mesh.size(); idx++ ) {
			gelDrawIndexedTriangles( &(Mesh->Mesh[idx].Vertex[0]), (unsigned short*)&(Mesh->Mesh[idx].FaceGroup[0].Face[0]), Mesh->Mesh[idx].FaceGroup[0].Face.size()*3 );
		}
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Object3D_H__ //
// - ------------------------------------------------------------------------------------------ - //
