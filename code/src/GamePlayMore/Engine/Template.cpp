// - ------------------------------------------------------------------------------------------ - //
#include "Engine.h"
// - ------------------------------------------------------------------------------------------ - //
void cTemplate::CreateObject( cObject* Object, const Vector3D& Pos ) {
}
// - ------------------------------------------------------------------------------------------ - //
void cTemplate::DestroyObject( cObject* Object ) {
}
// - ------------------------------------------------------------------------------------------ - //
void cTemplate::Step( cObject* Object ) {
}
// - ------------------------------------------------------------------------------------------ - //
void cTemplate::Draw( cObject* Object, const Matrix4x4& Matrix ) {
	if ( Art ) {
		Matrix4x4 Result = Object->GetTransform() * Matrix;
		Art->Draw( Result );
	}
}
// - ------------------------------------------------------------------------------------------ - //
const bool cTemplate::Contact( cObject* Object, cObject* Vs ) {
	return true;
}
// - ------------------------------------------------------------------------------------------ - //
void cTemplate::Sense( cObject* Object, cObject* Vs, const st32 SensorIndex ) {
	Log("Ttt %i",SensorIndex);
}
// - ------------------------------------------------------------------------------------------ - //
void cTemplate::Notice( cObject* Object, cObject* Sender, const int Message ) {
}
// - ------------------------------------------------------------------------------------------ - //
