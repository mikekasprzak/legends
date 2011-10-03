// - ------------------------------------------------------------------------------------------ - //
#ifndef __Room_H__
#define __Room_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/GraphicsDraw.h>
#include "../Physics.h"
// - ------------------------------------------------------------------------------------------ - //
struct VertType {
	Vector3D Pos;
};
// - ------------------------------------------------------------------------------------------ - //
class cRoom {
public:
	typedef unsigned char GType;
	Grid2D<GType>* Grid;
	
	GelArray<VertType>* Vert;
	GelArray<unsigned short>* Index;
	GelArray<unsigned short>* OutlineIndex;

	cPhysicsObject* PhysicsObject;

public:
	cRoom() :
		PhysicsObject( 0 )
	{
	}
	
	void Step() {
		
	}
	
	void DrawDebug() {
		if ( PhysicsObject ) {
			btVector3 Min, Max;
			PhysicsObject->shape->getAabb( PhysicsObject->trans, Min, Max );
			
			gelDrawCube( *((Vector3D*)&Min), *((Vector3D*)&Max), GEL_RGB_RED );
		}
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Room_H__ //
// - ------------------------------------------------------------------------------------------ - //
