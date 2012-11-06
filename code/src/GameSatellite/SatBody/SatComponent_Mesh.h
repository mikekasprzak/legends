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
	Mesh* Data;

public:
	inline void New( const size_t = 0, const size_t = 0 ) { }
	inline void Delete() { }
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __SATBODY_COMPONENT_MESH_H__ //
// - ------------------------------------------------------------------------------------------ - //
