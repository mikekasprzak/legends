// - ------------------------------------------------------------------------------------------ - //
#include "Engine.h"
// - ------------------------------------------------------------------------------------------ - //
namespace LifeFormula {
// - ------------------------------------------------------------------------------------------ - //
cEngine* cEngine::Instance = 0;
	
cGelArrayPtr<cActiveTemplate*>	cEngine::ActiveTemplate;
cGelArrayPtr<cPassiveTemplate*>	cEngine::PassiveTemplate;
	
cRoomViewer* cEngine::View = 0;
	
cRoom* cEngine::Room = 0;
	
cTileMeshRenderer* cEngine::TileMeshRenderer = 0;
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cEngine::Step( const Vector3D& MouseRay ) {
	Room->Step();
	View->Step( MouseRay );
}
// - ------------------------------------------------------------------------------------------ - //
void cEngine::Draw() {
	// No Room->Draw() here, because the room is too large to draw //
	View->Draw();
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace LifeFormula //
// - ------------------------------------------------------------------------------------------ - //
