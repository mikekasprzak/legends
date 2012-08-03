// - ------------------------------------------------------------------------------------------ - //
#ifndef __LIFEFORMULA_TILEMESH_H__
#define __LIFEFORMULA_TILEMESH_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector.h>
#include <Graphics/GelColor.h>
// - ------------------------------------------------------------------------------------------ - //
namespace LifeFormula {
// - ------------------------------------------------------------------------------------------ - //
// The UVs are generated automatically from the vertex positions in the vertex shader.
// The Vertex Colors modulate and tint the two surface textures. 
class cTileMeshVertex {
public:					// WORDS //
	Vector3D Pos;		// 3 - Position //
	Vector3D Normal;	// 3 - Normal //
	GelColor Color;		// 1 - Soil Color //
	GelColor Color2;	// 1 - Vegetation Color //
						// TOTAL: 8 Words //
};
// - ------------------------------------------------------------------------------------------ - //
class cTileMesh {
public:
	
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace LifeFormula //
// - ------------------------------------------------------------------------------------------ - //
#endif // __LIFEFORMULA_TILEMESH_H__ //
// - ------------------------------------------------------------------------------------------ - //
