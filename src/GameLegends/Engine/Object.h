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
	Real Scalar;
	
	GelAssetHandle Texture;
	GelColor Color;
	
	cPhysicsObject* PhysicsObject;

	bool IsGlowing;
	
	cObject( Vector3D _Pos, GelAssetHandle _Texture, const Real _Scalar = Real(12), GelColor _Color = GEL_RGB_WHITE ) :
		Pos( _Pos),
		Scalar( _Scalar ),
		Texture( _Texture ),
		Color( _Color ),
		PhysicsObject( 0 )
	{	
		IsGlowing = false;
	}
	
	void Step() {
		if ( PhysicsObject ) {
			PhysicsObject->Step();
			Pos = PhysicsObject->GetPos();
		}
	}
	
	void Draw() {
		gelMultMatrix( Matrix4x4::TranslationMatrix( Pos ) );

		AssetPool::Set( Texture );
		gelSetColor( Color );
		gelDrawRectFillTextured( Vector3D(-Scalar,-Scalar,0), Vector3D(Scalar,Scalar,0) );
	}
	
	void DrawGlow() {
		// If Player //
		Draw();
		
		// If enemy //
		// Draw Eyes //
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
