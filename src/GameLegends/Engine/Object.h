// - ------------------------------------------------------------------------------------------ - //
#ifndef __Object_H__
#define __Object_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector.h>
#include <Graphics/GraphicsDraw.h>
#include <AssetPool/AssetPool.h>
// - ------------------------------------------------------------------------------------------ - //
class cObject {
public:
	Vector3D Pos;
	
	GelAssetHandle Texture;
	
	cObject( Vector3D _Pos, GelAssetHandle _Texture ) :
		Pos( _Pos),
		Texture( _Texture )
	{	
	}
	
	void Step() {
		
	}
	
	void Draw() {
		gelMultMatrix( Matrix4x4::TranslationMatrix( Pos ) );

		AssetPool::Set( Texture );
		gelDrawRectFillTextured( Vector3D(-64,-64,0), Vector3D(64,64,0) );
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Object_H__ //
// - ------------------------------------------------------------------------------------------ - //
