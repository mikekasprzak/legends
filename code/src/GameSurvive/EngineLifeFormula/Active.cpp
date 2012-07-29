// - ------------------------------------------------------------------------------------------ - //
#include <sdl/sdl.h>

#include "Active.h"
#include "World.h"
// - ------------------------------------------------------------------------------------------ - //
namespace LifeFormula {
// - ------------------------------------------------------------------------------------------ - //
void cActive::Step( class cWorld* World ) {
	static int Tuff = 0;
	Tuff++;
	if ( (Tuff & 31) == 0 ) {
		Uint8 *keystate = SDL_GetKeyboardState(NULL);
		if ( keystate[SDL_SCANCODE_UP] ) {
			World->MoveActive( this, PosIndex, World->AddToIndex( PosIndex, IVector2D(+0,-1) ) );
		}
		if ( keystate[SDL_SCANCODE_DOWN] ) {
			World->MoveActive( this, PosIndex, World->AddToIndex( PosIndex, IVector2D(+0,+1) ) );
		}
		if ( keystate[SDL_SCANCODE_LEFT] ) {
			World->MoveActive( this, PosIndex, World->AddToIndex( PosIndex, IVector2D(-1,+0) ) );
		}
		if ( keystate[SDL_SCANCODE_RIGHT] ) {
			World->MoveActive( this, PosIndex, World->AddToIndex( PosIndex, IVector2D(+1,+0) ) );
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cActive::Draw() {
	
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace LifeFormula //
// - ------------------------------------------------------------------------------------------ - //
