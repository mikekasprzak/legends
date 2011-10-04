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
	Vector3D Pos;
	
	typedef unsigned char GType;
	Grid2D<GType>* Grid;
	
	GelArray<VertType>* Vert;
	GelArray<unsigned short>* Index;
	GelArray<unsigned short>* OutlineIndex;

	GelArray<GelColor>* Color;

	cPhysicsObject* PhysicsObject;

public:
	cRoom() :
		PhysicsObject( 0 )
	{
	}

	cRoom( const Vector3D& _Pos ) :
		Pos( _Pos ),
		PhysicsObject( 0 )
	{
	}
	
	void Step() {
		
	}
	
	void Draw() {
		gelMultMatrix( Matrix4x4::TranslationMatrix( Pos ) );

		gelDrawIndexedTrianglesColors( &Vert->Data[0], (unsigned int*)(&Color->Data[0]), Index->Data, Index->Size );
	
//		gelDrawIndexedTriangles( Vert->Data, Index->Data, Index->Size, GEL_RGBA(255,255,255,64) );
//		gelDrawIndexedLines( Vert->Data, OutlineIndex->Data, OutlineIndex->Size, GEL_RGBA(0,255,0,64) );
//		gelDrawPoints( Vert->Data, Vert->Size, GEL_RGB_YELLOW );		
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
