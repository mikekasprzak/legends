// - ------------------------------------------------------------------------------------------ - //
#ifndef __Object3D_H__
#define __Object3D_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector.h>
#include <Graphics/GraphicsDraw.h>
#include <Graphics/Mesh/PMEFile.h>
// - ------------------------------------------------------------------------------------------ - //
class cObject3D {
public:
	Vector3D Pos;
	
	cPMEFile* Mesh;
	
	cObject3D( Vector3D _Pos, cPMEFile* _Mesh ) :
		Pos( _Pos),
		Mesh( _Mesh )
	{	
	}
	
	void Step() {
		
	}
	
	void Draw() {
		gelMultMatrix( Matrix4x4::TranslationMatrix( Pos ) );
		gelMultMatrix( Matrix4x4::ScalarMatrix( Vector3D( 16, 16, 16 ) ) );

		gelDrawIndexedTriangles( &(Mesh->Mesh[0].Vertex[0]), (unsigned short*)&(Mesh->Mesh[0].FaceGroup[0].Face[0]), Mesh->Mesh[0].FaceGroup[0].Face.size()*3 );
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Object3D_H__ //
// - ------------------------------------------------------------------------------------------ - //
