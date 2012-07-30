// - ------------------------------------------------------------------------------------------ - //
#include <sdl/sdl.h>

#include "Active.h"
#include "Engine.h"
// - ------------------------------------------------------------------------------------------ - //
namespace LifeFormula {
// - ------------------------------------------------------------------------------------------ - //
const int cActive::Age() const {
	return -Born + cEngine::Room->Iteration;
}
// - ------------------------------------------------------------------------------------------ - //
void cActive::Step( class cRoom* Room ) {
	static int Tuff = 0;
	Tuff++;
	if ( (Tuff & 31) == 0 ) {
		Uint8 *keystate = SDL_GetKeyboardState(NULL);
		if ( keystate[SDL_SCANCODE_UP] ) {
			Room->MoveActive( this, PosIndex, Room->AddToIndex( PosIndex, IVector2D(+0,-1) ) );
		}
		if ( keystate[SDL_SCANCODE_DOWN] ) {
			Room->MoveActive( this, PosIndex, Room->AddToIndex( PosIndex, IVector2D(+0,+1) ) );
		}
		if ( keystate[SDL_SCANCODE_LEFT] ) {
			Room->MoveActive( this, PosIndex, Room->AddToIndex( PosIndex, IVector2D(-1,+0) ) );
		}
		if ( keystate[SDL_SCANCODE_RIGHT] ) {
			Room->MoveActive( this, PosIndex, Room->AddToIndex( PosIndex, IVector2D(+1,+0) ) );
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cActive::Draw() {
	
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace LifeFormula //
// - ------------------------------------------------------------------------------------------ - //
