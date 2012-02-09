// - ------------------------------------------------------------------------------------------ - //
#ifndef __Room_H__
#define __Room_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/GraphicsDraw.h>
// - ------------------------------------------------------------------------------------------ - //
class cRoom {
public:
	struct VertType {
		Vector3D Pos;
	};
	
	Vector3D Pos;
	
	typedef unsigned char GType;
	Grid2D<GType>* Grid;
	
	GelArray<VertType>* Vert;
	GelArray<unsigned short>* Index;
	GelArray<unsigned short>* OutlineIndex;

	GelArray<GelColor>* Color;

public:
	cRoom()
	{
	}

	cRoom( const Vector3D& _Pos ) :
		Pos( _Pos )
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
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Room_H__ //
// - ------------------------------------------------------------------------------------------ - //
