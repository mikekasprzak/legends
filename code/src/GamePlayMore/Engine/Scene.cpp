// - ------------------------------------------------------------------------------------------ - //
#include "Engine.h"
// - ------------------------------------------------------------------------------------------ - //
void cScene::Step() {
	// Step All Objects //
	{
		// Step Statics First (because they never do tests, instead are tested) //
		for ( auto Itr = Static.begin(); Itr != Static.end(); Itr++ ) {
			Shared.Object = *Itr;
			Shared.Template = (*Itr)->Template;
			(*Itr)->Step();
		}
		// Step Actives Second //
		for ( auto Itr = Active.begin(); Itr != Active.end(); Itr++ ) {
			Shared.Object = *Itr;
			Shared.Template = (*Itr)->Template;
			(*Itr)->Step();
		}
	}
	
	// Do Collision Tests //
	{
		// Step Only Actives //
		for ( auto Itr = Active.begin(); Itr != Active.end(); Itr++ ) {
			Shared.Object = *Itr;
			Shared.Template = (*Itr)->Template;

			// Vs Statics //
			for ( auto Itr2 = Static.begin(); Itr2 != Static.end(); Itr2++ ) {
				// TODO: Set shared Object and Template correctly before the Contact Call //
//				if ( (*Itr)->Body.Check( (*Itr2)->Body ) ) {
//					if ( (*Itr)->Template->Contact(*Itr,*Itr2) && (*Itr2)->Template->Contact(*Itr2,*Itr) ) {
//						(*Itr)->Body.Solve( (*Itr2)->Body );
//						(*Itr)->UpdateRect();
//						(*Itr2)->UpdateRect();
//					}
//				}
			}

			// Vs Other Actives //
			{
				auto Itr2 = Itr;
				Itr2++;
				for ( ; Itr2 != Active.end(); Itr2++ ) {
					// TODO: Set shared Object and Template correctly before the Contact Call //
//					if ( (*Itr)->Body.Check( (*Itr2)->Body ) ) {
//						if ( (*Itr)->Template->Contact(*Itr,*Itr2) && (*Itr2)->Template->Contact(*Itr2,*Itr) ) {
//							(*Itr)->Body.Solve( (*Itr2)->Body );
//							(*Itr)->UpdateRect();
//							(*Itr2)->UpdateRect();
//						}
//					}
				}
			}
			
			// My Sensors //
			st Size = (*Itr)->Sensor.size();
			for ( st idx = 0; idx < Size; idx++ ) {
				// Vs Statics //
				for ( auto Itr2 = Static.begin(); Itr2 != Static.end(); Itr2++ ) {
//					if ( (*Itr)->Sensor[idx].Check( (*Itr2)->Body ) ) {
//						(*Itr)->Template->Sense(*Itr,*Itr2);
//					}
				}
	
				// Vs Other Actives //
				{
					auto Itr2 = Itr;
					Itr2++;
					for ( ; Itr2 != Active.end(); Itr2++ ) {
//						if ( (*Itr)->Sensor[idx].Check( (*Itr2)->Body ) ) {
//							(*Itr)->Template->Sense(*Itr,*Itr2);
//						}
					}
				}				
			}
		}
	}
	Shared.Template = 0;
	Shared.Object = 0;
	
	// Update All Object Rectangles //
	{
		// Step Statics First (because they never do tests, instead are tested) //
		for ( auto Itr = Static.begin(); Itr != Static.end(); Itr++ ) {
			(*Itr)->UpdateRect();
		}
		// Step Actives Second //
		for ( auto Itr = Active.begin(); Itr != Active.end(); Itr++ ) {
			(*Itr)->UpdateRect();
		}
	}
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
	Shared.Template = 0;
	Shared.Object = 0;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cScene::DrawRect( const Matrix4x4& Matrix ) {
	// Draw Statics First (because they'll typically occlude Actives) //
	for ( auto Itr = Static.begin(); Itr != Static.end(); Itr++ ) {
		(*Itr)->DrawRect( Matrix );
	}
	// Draw Actives Second //
	for ( auto Itr = Active.begin(); Itr != Active.end(); Itr++ ) {
		(*Itr)->DrawRect( Matrix );
	}
}// - ------------------------------------------------------------------------------------------ - //
void cScene::DrawBody( const Matrix4x4& Matrix ) {
	// Draw Statics First (because they'll typically occlude Actives) //
	for ( auto Itr = Static.begin(); Itr != Static.end(); Itr++ ) {
		(*Itr)->Body->Draw( Matrix );
	}
	// Draw Actives Second //
	for ( auto Itr = Active.begin(); Itr != Active.end(); Itr++ ) {
		(*Itr)->Body->Draw( Matrix );
	}
}
// - ------------------------------------------------------------------------------------------ - //
