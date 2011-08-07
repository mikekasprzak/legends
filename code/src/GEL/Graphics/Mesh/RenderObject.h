// - ------------------------------------------------------------------------------------------ - //
#ifndef __GLGraphics_RenderObject_H__
#define __GLGraphics_RenderObject_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Core/GelArray.h>

#include <Types/UVSet.h>
#include <Types/ABCSet.h>
#include <Math/Vector.h>

#include <Graphics/GelUV.h>
#include <Graphics/GelColor.h>
#include <Graphics/GelTextureID.h>
// - ------------------------------------------------------------------------------------------ - //
class cROMaterial {
public:
	GelTextureID Texture;
};
// - ------------------------------------------------------------------------------------------ - //
class cROVertex {
public:
	typedef UVSet<GelUV> tUVType;
	
	Vector3D Pos;
	Vector3D Normal;
	tUVType UV;
	GelColor Color;
};
// - ------------------------------------------------------------------------------------------ - //
class cROFaceGroup {
public:
	typedef int IndexType;
	
	unsigned short MaterialIndex;
	unsigned short Flags;
	GelArray<IndexType>* Face;

public:
	inline cROFaceGroup() :
		Face(0)
	{
	}
	
//	inline ~cROFaceGroup() 
	inline void Free() {
		if ( Face )
			delete_GelArray(Face);
	}
};
// - ------------------------------------------------------------------------------------------ - //
class cRenderObject {
public:
	GelArray<cROMaterial>* Material;
	GelArray<cROVertex>* Vertex;
	GelArray<cROFaceGroup>* FaceGroup;

public:
	inline cRenderObject() :
		Material(0),
		Vertex(0),
		FaceGroup(0)
	{
	}

//	inline ~cRenderObject()
	inline void Free() {
		if ( Material )
			delete_GelArray(Material);
		if ( Vertex )
			delete_GelArray(Vertex);
		if ( FaceGroup )
			delete_GelArray(FaceGroup);
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GLGraphics_RenderObject_H__ //
// - ------------------------------------------------------------------------------------------ - //
