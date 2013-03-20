// - ------------------------------------------------------------------------------------------ - //
#include "Engine.h"
// - ------------------------------------------------------------------------------------------ - //
void cProject::Step() {
	for ( auto Itr = Active.begin(); Itr != Active.end(); Itr++ ) {
		Shared.Scene = *Itr;
		(*Itr)->Step();
	}
	Shared.Scene = 0;
}
// - ------------------------------------------------------------------------------------------ - //
void cProject::Draw( const Matrix4x4& Matrix ) {
	for ( auto Itr = Active.begin(); Itr != Active.end(); Itr++ ) {
		Shared.Scene = *Itr;
		(*Itr)->Draw( Matrix );
	}
	Shared.Scene = 0;
}
// - ------------------------------------------------------------------------------------------ - //
void cProject::DrawRect( const Matrix4x4& Matrix ) {
	for ( auto Itr = Active.begin(); Itr != Active.end(); Itr++ ) {
		(*Itr)->DrawRect( Matrix );
	}	
}
// - ------------------------------------------------------------------------------------------ - //
void cProject::DrawBody( const Matrix4x4& Matrix ) {
	for ( auto Itr = Active.begin(); Itr != Active.end(); Itr++ ) {
		(*Itr)->DrawBody( Matrix );
	}	
}
// - ------------------------------------------------------------------------------------------ - //