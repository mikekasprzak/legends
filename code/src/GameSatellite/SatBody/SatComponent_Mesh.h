// - ------------------------------------------------------------------------------------------ - //
#ifndef __SATBODY_COMPONENT_MESH_H__
#define __SATBODY_COMPONENT_MESH_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Core/GelTypes.h>
#include <Core/GelArray.h>
#include <Math/Vector.h>
// - ------------------------------------------------------------------------------------------ - //
class cSatComponent_Mesh {
public:
	int	Type;
public:
	class Mesh {
	public:
		class VertType {
		public:
			Vector3D Pos;
		};
		
		GelArray<VertType>* Vertex;
		GelArray<u16>* 		Index;
	};

public:
	GelArray<Mesh>* Data;
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __SATBODY_COMPONENT_MESH_H__ //
// - ------------------------------------------------------------------------------------------ - //
