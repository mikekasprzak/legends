// - ------------------------------------------------------------------------------------------ - //
#ifndef __LIFEFORMULA_TILEMESH_H__
#define __LIFEFORMULA_TILEMESH_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector.h>
#include <Graphics/GelColor.h>
#include <Graphics/GelUV.h>

#include <Graphics/Allocator/Allocator.h>
#include <Types/Set.h>

#include "../UberShader/UberShader.h"
// - ------------------------------------------------------------------------------------------ - //
namespace LifeFormula {
// - ------------------------------------------------------------------------------------------ - //
// The UVs are generated automatically from the vertex positions in the vertex shader.
// The Vertex Colors modulate and tint the two surface textures. 
class cTileMeshVertex {
public:					// WORDS //
	Vector3D Pos;		// 3 - Position //
	Vector3D Normal;	// 3 - Normal //
	GelColor Color1;	// 1 - Soil Color //
	GelColor Color2;	// 1 - Vegetation Color //
						// TOTAL: 8 Words //

public:
	inline cTileMeshVertex()
	{
	}
	
	inline cTileMeshVertex( const Vector3D& _Pos, const Vector3D& _Normal, const GelColor& _Color1, const GelColor& _Color2 ) :
		Pos( _Pos ),
		Normal( _Normal ),
		Color1( _Color1 ),
		Color2( _Color2 )
	{
	}
};
// - ------------------------------------------------------------------------------------------ - //
class cTileMesh {
public:
	Allocator<cTileMeshVertex> Vertex;
	Allocator< ABCSet<unsigned short> > Index;

public:
	cTileMesh( const size_t Vertexes, const size_t Indexes ) :
		Vertex( Vertexes ),
		Index( Indexes )
	{
	}
};
// - ------------------------------------------------------------------------------------------ - //
class cTileMeshRenderer {
public:
	cUberShader UberShader;
	GelShaderHandle Handle;
	
	cTileMeshRenderer() :
		UberShader( "Content/Scripts/glsl/TileMesh.json" )
	{	
		Handle = UberShader.Find( "Normal" );
	}

public:
	inline void Bind() {
		UberShader.Bind( Handle );
	}
	
	inline void DrawMesh( const cTileMesh& Mesh, const Matrix4x4& ViewMatrix ) {
		UberShader.BindUniformMatrix4x4( "ViewMatrix", ViewMatrix );
//		InShader->BindUniformColor( "MinColor", GEL_SRGB(0,-92,-64) );
//		InShader->BindUniformColor( "MaxColor", Color ); //GEL_SRGB(148,250,84) );

		UberShader.Vector3DAttribPointer<cTileMeshVertex>( 0, (cTileMeshVertex*)&Mesh.Vertex[0].Pos );
		UberShader.Vector3DAttribPointer<cTileMeshVertex>( 1, (cTileMeshVertex*)&Mesh.Vertex[0].Normal );
		UberShader.ColorAttribPointer<cTileMeshVertex>( 2, (cTileMeshVertex*)&Mesh.Vertex[0].Color1 );
		UberShader.ColorAttribPointer<cTileMeshVertex>( 3, (cTileMeshVertex*)&Mesh.Vertex[0].Color2 );
		
//		UberShader.DrawArrays( GL_TRIANGLES, 3 );
//		UberShader.DrawArrays( GL_TRIANGLE_STRIP, 4 );
//		UberShader.DrawArrays( GL_LINE_LOOP, 4 );
		UberShader.DrawElements( GL_TRIANGLES, (const unsigned short*)Mesh.Index.Get(), Mesh.Index.Size() * 3 );		
	}
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace LifeFormula //
// - ------------------------------------------------------------------------------------------ - //
#endif // __LIFEFORMULA_TILEMESH_H__ //
// - ------------------------------------------------------------------------------------------ - //
