// - ------------------------------------------------------------------------------------------ - //
#ifndef __Object_H__
#define __Object_H__
// - ------------------------------------------------------------------------------------------ - //
#include "DiscObject.h"

#include <Math/Vector.h>
#include <Graphics/GraphicsDraw.h>
#include <AssetPool/AssetPool.h>
// - ------------------------------------------------------------------------------------------ - //
class cObject {
public:
	Vector3D Pos;
	Real Scalar;
	
	cDiscObject* Disc;
		
	cPhysicsObject* PhysicsObject;

	bool IsGlowing;

public:	
	cObject( Vector3D _Pos, const char* InFile, const Real _Scalar = Real(8) ) :
		Pos( _Pos ),
		Scalar( _Scalar ),
		PhysicsObject( 0 ),
		IsGlowing( false )
	{
		Disc = new cDiscObject( InFile );
	}
	
	~cObject() {
		if ( Disc )
			delete Disc;
	}

public:
	void Step() {
		if ( PhysicsObject ) {
			PhysicsObject->Step();
			Pos = PhysicsObject->GetPos();
		}
	}
	
	void Draw() {
		gelMultMatrix( Matrix4x4::TranslationMatrix( Pos ) );

		AssetPool::Set( Disc->Texture );
		gelSetColor( Disc->Color );
		gelDrawRectFillTextured( Vector3D(-Scalar,-Scalar,0), Vector3D(Scalar,Scalar,0) );

		if ( Disc->OverlayTexture ) {
			AssetPool::Set( Disc->OverlayTexture );
			gelSetColor( Disc->OverlayColor );
			gelDrawRectFillTextured( Vector3D(-Scalar,-Scalar,0), Vector3D(Scalar,Scalar,0) );
		}
	}
	
	void DrawGlow() {
		gelMultMatrix( Matrix4x4::TranslationMatrix( Pos ) );

		AssetPool::Set( Disc->GlowTexture );
		gelSetColor( Disc->GlowColor & 0x7fffffff );
		gelDrawRectFillTextured( Vector3D(-Scalar,-Scalar,0), Vector3D(Scalar,Scalar,0) );
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
#endif // __Object_H__ //
// - ------------------------------------------------------------------------------------------ - //
