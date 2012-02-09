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
		
	bool IsGlowing;

public:	
	cObject( Vector3D _Pos, const char* InFile, const Real _Scalar = Real(8) ) :
		Pos( _Pos ),
		Scalar( _Scalar ),
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
		gelSetColor( Disc->GlowColor );
		gelDrawRectFillTextured( Vector3D(-Scalar,-Scalar,0), Vector3D(Scalar,Scalar,0) );
	}
	
	void DrawDebug() {
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Object_H__ //
// - ------------------------------------------------------------------------------------------ - //
