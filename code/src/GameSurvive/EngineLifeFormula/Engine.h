// - ------------------------------------------------------------------------------------------ - //
#ifndef __LIFEFORMULA_ENGINE_H__
#define __LIFEFORMULA_ENGINE_H__
// - ------------------------------------------------------------------------------------------ - //
// LifeFormula Engine -- A rigid grid based world simulation //
// - ------------------------------------------------------------------------------------------ - //
#include <Core/GelArray.h>

#include "Active.h"
#include "Passive.h"
#include "Tile.h"

#include "Room.h"    
#include "RoomViewer.h"
#include "TileMesh.h"

#include "../Camera/Camera.h"
// - ------------------------------------------------------------------------------------------ - //
namespace LifeFormula {
// - ------------------------------------------------------------------------------------------ - //
class cEngine {
public:
	static cEngine* Instance;

	static cGelArrayPtr<cActiveTemplate*>	ActiveTemplate;		// Pointers because every time these 2 Arrays
	static cGelArrayPtr<cPassiveTemplate*>	PassiveTemplate;	//   resize, the addresses would break.
	
	static cRoomViewer* View;

	static cRoom* Room;
	
	static cTileMeshRenderer* TileMeshRenderer;
public:
	cEngine() {
		Log( "+ Start of cEngine()..." );
		
		Instance = this; // *IMPORTANT* THIS MUST COME FIRST BEFORE ANY ROOMS ARE CREATED! //

		// - ----- - //

		View = new cRoomViewer();
		Room = new cRoom( 32, 32 );
		View->Set( Room );
		
		TileMeshRenderer = new cTileMeshRenderer();

		Log( "- cEngine() done." );
	}

	~cEngine() {
		Log( "+ Start of ~cEngine()..." );

		delete TileMeshRenderer;
		
		delete View;
		delete Room;
		
		ActiveTemplate._DeleteAll();
		PassiveTemplate._DeleteAll();
		Log( "- ~cEngine() done." );
	}		
public:
	// Static Functions (using the Instance) //
	inline static cActiveTemplate* LoadActiveTemplate( const char* FileName ) {
		cEngine::ActiveTemplate.PushBack( new cActiveTemplate() );
		cEngine::ActiveTemplate.Back()->Load( FileName );
		return cEngine::ActiveTemplate.Back();
	}
	
	inline static cPassiveTemplate* LoadPassiveTemplate( const char* FileName ) {
		cEngine::PassiveTemplate.PushBack( new cPassiveTemplate() );
		cEngine::PassiveTemplate.Back()->Load( FileName );
		return cEngine::PassiveTemplate.Back();
	}
public:
	void Step( const Vector3D& MouseRay );
	void Draw( const GelCamera& Camera );	
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace LifeFormula //
// - ------------------------------------------------------------------------------------------ - //
#endif // __LIFEFORMULA_ENGINE_H__ //
// - ------------------------------------------------------------------------------------------ - //
