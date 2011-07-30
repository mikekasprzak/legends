// - ------------------------------------------------------------------------------------------ - //
#ifndef __Object_H__
#define __Object_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector.h>
#include <Graphics/GraphicsDraw.h>
// - ------------------------------------------------------------------------------------------ - //
class cObject {
public:
	Vector3D Pos;
	
	TextureID Texture;
	
	cObject( Vector3D _Pos, TextureID _Texture ) :
		Pos( _Pos),
		Texture( _Texture )
	{	
	}
	
	void Step() {
		
	}
	
	void Draw() {
		gelMultMatrix( Matrix4x4::TranslationMatrix( Pos ) );

		gelSetTexture( Texture );
		gelDrawRectFillTextured( Vector3D(-12,-12,0), Vector3D(12,12,0) );
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Object_H__ //
// - ------------------------------------------------------------------------------------------ - //
