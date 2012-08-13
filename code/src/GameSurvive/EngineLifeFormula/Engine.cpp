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
void cEngine::Draw( const GelCamera& Camera ) {//Matrix4x4& ViewMatrix ) {
	// No Room->Draw() here, because the room is too large to draw //
	View->Draw( Camera );
/*	
	cTileMesh Mesh(5,4);

	Mesh.Vertex.Add( cTileMeshVertex( Vector3D(0,0,0), Vector3D(0,0,1), GEL_RGBA(255,255,255,128), GEL_RGBA(255,255,255,0) ) );

	Mesh.Vertex.Add( cTileMeshVertex( Vector3D(-1,-1,0), Vector3D(-1,-1,1).Normal(), GEL_RGBA(255,255,255,0), GEL_RGBA(255,255,255,0) ) );
	Mesh.Vertex.Add( cTileMeshVertex( Vector3D(+1,-1,0), Vector3D(+1,-1,1).Normal(), GEL_RGBA(255,255,255,0), GEL_RGBA(255,255,255,0) ) );
	Mesh.Vertex.Add( cTileMeshVertex( Vector3D(+1,+1,0), Vector3D(+0,+0,1).Normal(), GEL_RGBA(255,255,255,255), GEL_RGBA(255,255,255,0) ) );
	Mesh.Vertex.Add( cTileMeshVertex( Vector3D(-1,+1,0), Vector3D(-0,+0,1).Normal(), GEL_RGBA(255,255,255,255), GEL_RGBA(255,255,255,0) ) );
                                             
	// Standard Away Pointing (Acute/Creases) //
//	Mesh.Vertex.Add( cTileMeshVertex( Vector3D(-1,-1,0), Vector3D(-1,-1,1).Normal(), GEL_RGBA(255,255,255,0), GEL_RGBA(255,255,255,0) ) );
//	Mesh.Vertex.Add( cTileMeshVertex( Vector3D(+1,-1,0), Vector3D(+1,-1,1).Normal(), GEL_RGBA(255,255,255,0), GEL_RGBA(255,255,255,0) ) );
//	Mesh.Vertex.Add( cTileMeshVertex( Vector3D(+1,+1,0), Vector3D(+1,+1,1).Normal(), GEL_RGBA(255,255,255,0), GEL_RGBA(255,255,255,0) ) );
//	Mesh.Vertex.Add( cTileMeshVertex( Vector3D(-1,+1,0), Vector3D(-1,+1,1).Normal(), GEL_RGBA(255,255,255,0), GEL_RGBA(255,255,255,0) ) );

	// Inverse Pointing (Obtuse) //
//	Mesh.Vertex.Add( cTileMeshVertex( Vector3D(-1,-1,0), Vector3D(+1,+1,1).Normal(), GEL_RGBA(255,255,255,0), GEL_RGBA(255,255,255,0) ) );
//	Mesh.Vertex.Add( cTileMeshVertex( Vector3D(+1,-1,0), Vector3D(-1,+1,1).Normal(), GEL_RGBA(255,255,255,0), GEL_RGBA(255,255,255,0) ) );
//	Mesh.Vertex.Add( cTileMeshVertex( Vector3D(+1,+1,0), Vector3D(-1,-1,1).Normal(), GEL_RGBA(255,255,255,0), GEL_RGBA(255,255,255,0) ) );
//	Mesh.Vertex.Add( cTileMeshVertex( Vector3D(-1,+1,0), Vector3D(+1,-1,1).Normal(), GEL_RGBA(255,255,255,0), GEL_RGBA(255,255,255,0) ) );

	// Up Pointing //
//	Mesh.Vertex.Add( cTileMeshVertex( Vector3D(0,0,1), Vector3D(0,0,1).Normal(), GEL_RGBA(255,255,255,0), GEL_RGBA(255,255,255,0) ) );
//	Mesh.Vertex.Add( cTileMeshVertex( Vector3D(0,0,1), Vector3D(0,0,1).Normal(), GEL_RGBA(255,255,255,0), GEL_RGBA(255,255,255,0) ) );
//	Mesh.Vertex.Add( cTileMeshVertex( Vector3D(0,0,1), Vector3D(0,0,1).Normal(), GEL_RGBA(255,255,255,0), GEL_RGBA(255,255,255,0) ) );
//	Mesh.Vertex.Add( cTileMeshVertex( Vector3D(0,0,1), Vector3D(0,0,1).Normal(), GEL_RGBA(255,255,255,0), GEL_RGBA(255,255,255,0) ) );

	Mesh.Index.Add( ABCSet<unsigned short>(0,1,2) );
	Mesh.Index.Add( ABCSet<unsigned short>(0,2,3) );
	Mesh.Index.Add( ABCSet<unsigned short>(0,3,4) );
	Mesh.Index.Add( ABCSet<unsigned short>(0,4,1) );
	
//	Log( "BWEEEO: %i 0x%x (Vert: 0x%x Index: 0x%x)", Room->Map(0,1).Height, &Room->Map(0,1).Mesh, &Room->Map(0,1).Mesh.Vertex.Data, &Room->Map(0,1).Mesh.Index.Data );
	*/
	
//	TileMeshRenderer->Bind();
////	TileMeshRenderer->DrawMesh( Mesh, ViewMatrix );
//	TileMeshRenderer->DrawMesh( Room->Map(0,0).Mesh, ViewMatrix );
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace LifeFormula //
// - ------------------------------------------------------------------------------------------ - //
