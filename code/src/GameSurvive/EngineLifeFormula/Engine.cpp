// - ------------------------------------------------------------------------------------------ - //
#include "Engine.h"
// - ------------------------------------------------------------------------------------------ - //
namespace LifeFormula {
// - ------------------------------------------------------------------------------------------ - //
cEngine* cEngine::Instance = 0;
	
cGelArrayPtr<cActiveTemplate*>	cEngine::ActiveTemplate;
cGelArrayPtr<cPassiveTemplate*>	cEngine::PassiveTemplate;
	
cRoomViewer* cEngine::View = 0;
	
cRoom* cEngine::Room = 0;
	
cTileMeshRenderer* cEngine::TileMeshRenderer = 0;
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cEngine::Step( const Vector3D& MouseRay ) {
	Room->Step();
	View->Step( MouseRay );
}
// - ------------------------------------------------------------------------------------------ - //
void cEngine::Draw( const Matrix4x4& ViewMatrix ) {
	// No Room->Draw() here, because the room is too large to draw //
	View->Draw( ViewMatrix );
	
//	Log( "! PREADD" );
	
	cTileMesh Mesh(4,2);

	Mesh.Vertex.Add( cTileMeshVertex( Vector3D(-1,-1,0), Vector3D(0,0,1), GEL_RGB_BLUE, GEL_RGB_RED ) );
	Mesh.Vertex.Add( cTileMeshVertex( Vector3D(+1,-1,0), Vector3D(0,0,1), GEL_RGB_BLUE, GEL_RGB_RED ) );
	Mesh.Vertex.Add( cTileMeshVertex( Vector3D(+1,+1,0), Vector3D(0,0,1), GEL_RGB_BLUE, GEL_RGB_RED ) );
	Mesh.Vertex.Add( cTileMeshVertex( Vector3D(-1,+1,0), Vector3D(0,0,1), GEL_RGB_BLUE, GEL_RGB_RED ) );

	Mesh.Index.Add( ABCSet<unsigned short>(0,1,2) );
	Mesh.Index.Add( ABCSet<unsigned short>(2,3,0) );

//	Log( "! POSTADD" );

//	cTileMesh& TM = Room->Map(0,0).Mesh;
//	cTileMesh& TM = Mesh;
//	
//	for ( int idx = 0; idx < TM.Vertex.Size(); idx++ ) {
//		Log( "! VVV %i (%f %f %f)", idx, TM.Vertex[idx].Pos.x.ToFloat(), TM.Vertex[idx].Pos.y.ToFloat(), TM.Vertex[idx].Pos.z.ToFloat() );
//	}
	
	TileMeshRenderer->Bind();
	TileMeshRenderer->DrawMesh( Mesh, ViewMatrix );
//	TileMeshRenderer->DrawMesh( Room->Map(0,0).Mesh, ViewMatrix );
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace LifeFormula //
// - ------------------------------------------------------------------------------------------ - //
