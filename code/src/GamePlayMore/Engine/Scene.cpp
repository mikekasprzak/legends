// - ------------------------------------------------------------------------------------------ - //
#include "Engine.h"
// - ------------------------------------------------------------------------------------------ - //
void cScene::Step() {
	// Step Statics First (because they never do tests, instead are tested) //
	for ( auto Itr = Static.begin(); Itr != Static.end(); Itr++ ) {
		Shared.Object = *Itr;
		(*Itr)->Step();
	}
	// Step Actives Second //
	for ( auto Itr = Active.begin(); Itr != Active.end(); Itr++ ) {
		Shared.Object = *Itr;
		(*Itr)->Step();
	}
	Shared.Object = 0;
}
// - ------------------------------------------------------------------------------------------ - //
void cScene::Draw( const Matrix4x4& Matrix ) {
	// Draw Statics First (because they'll typically occlude Actives) //
	for ( auto Itr = Static.begin(); Itr != Static.end(); Itr++ ) {
		Shared.Object = *Itr;
		(*Itr)->Draw( Matrix );
	}
	// Draw Actives Second //
	for ( auto Itr = Active.begin(); Itr != Active.end(); Itr++ ) {
		Shared.Object = *Itr;
		(*Itr)->Draw( Matrix );
	}
	Shared.Object = 0;
}
// - ------------------------------------------------------------------------------------------ - //
