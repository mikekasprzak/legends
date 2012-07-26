// - ------------------------------------------------------------------------------------------ - //
#ifndef __LIFESYSTEM_TILE_H__
#define __LIFESYSTEM_TILE_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Integer.h>
#include <Debug/Log.h>

#include "Passive.h"
#include "Active.h"
#include "Soil.h"

#include "CArrayPtr.h"
// - ------------------------------------------------------------------------------------------ - //
namespace LifeSystem {
// - ------------------------------------------------------------------------------------------ - //
class cTile {
public:
	// Constants //
	enum {
		DEFAULT_TILE_HEIGHT = 1024,
		MAX_ACTIVE = 4,
		MAX_PASSIVE = 8
	};

public:
	int Height;								// Elevation //

	CArrayPtr<cActive*,MAX_ACTIVE>	Active;
//	cActive*	Active[MAX_ACTIVE];
	cPassive*	Passive[MAX_PASSIVE];	
	cSoil		Soil;					// Soil Content //

public:
	cTile() :
		Height( DEFAULT_TILE_HEIGHT )
	{
		Log( "HEEP! %i %i -- %x %x", Active.SizeOf(), Active.Size(), Active.ErrorPtr, &Active.ErrorPtr );
		
//		Active.Get() = new cActive();
		Active.Get() = (cActive*)1;
		Active.Get() = (cActive*)2;
		Active.Get() = (cActive*)3;
		Active.Get() = (cActive*)4;

//		Active.Front() = Active.PopBack();
//		Active.PushFront((cActive*)15);
//		Active.MoveBackward(1,2);//PushFront((cActive*)15);
		Active.Back() = Active.PopFront();
		Active.PushBack((cActive*)15);
		
		Log( "MEEP! %i %i", Active.SizeOf(), Active.Size() );
		for ( size_t idx = 0; idx < Active.SizeOf(); idx++ ) {
			Log( "%i -- %x", idx, Active[idx] );
		}
	}
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace LifeSystem //
// - ------------------------------------------------------------------------------------------ - //
#endif // __LIFESYSTEM_TILE_H__ //
// - ------------------------------------------------------------------------------------------ - //
