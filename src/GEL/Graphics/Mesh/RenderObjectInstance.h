// - ------------------------------------------------------------------------------------------ - //
#ifndef __GLGraphics_RenderObjectInstance_H__
#define __GLGraphics_RenderObjectInstance_H__
// - ------------------------------------------------------------------------------------------ - //
#include <vector>

// - ------------------------------------------------------------------------------------------ - //
#include <Core/GelArray.h>

#include <Math/Vector.h>
#include <Math/Matrix.h>
#include <Geometry/Rect.h>

#include <Graphics/GelColor.h>
// - ------------------------------------------------------------------------------------------ - //
#include "RenderObject.h"
// - ------------------------------------------------------------------------------------------ - //
//class cROIMaterial {
//public:
//	cROMaterial* Material;
//};
// - ------------------------------------------------------------------------------------------ - //
class cROIVertex {
public:
	// VBO
	
//	cROVertex* Vertex;
	
	// Computed Colors - Software Vertex Lighting Only //
	std::vector<GelColor> Color;
};
// - ------------------------------------------------------------------------------------------ - //
class cROIFaceGroup {
public:
	PairRect3D Rect;
	
//	cROFaceGroup* FaceGroup;
};
// - ------------------------------------------------------------------------------------------ - //
class cRenderObjectInstance {
public:
	const cRenderObject* Object;
	
	Matrix4x4 Matrix;
	
	PairRect3D Rect;
	
//	cROIMaterial Material;
	cROIVertex Vertex;
	GelArray<cROIFaceGroup>* FaceGroup;

public:
	cRenderObjectInstance() :
		Object(0),
		FaceGroup(0)
	{
	}

//	inline ~cRenderObjectInstance() 
	inline void Free() {
		if ( FaceGroup )
			delete_GelArray(FaceGroup);
	}
	
private:
	void _DrawFaceGroup( const size_t Index );

public:	
	void CalculateFaceGroupRect( const size_t Index );
	void CalculateFaceGroupRects();
	void CalculateRect();

	void CalculateLighting();
	
	void DrawFaceGroup( const size_t Index );
	void Draw();
};
// - ------------------------------------------------------------------------------------------ - //
cRenderObjectInstance Instantiate( const cRenderObject& Object );
// - ------------------------------------------------------------------------------------------ - //
#endif // __GLGraphics_RenderObjectInstance_H__ //
// - ------------------------------------------------------------------------------------------ - //
