// - ------------------------------------------------------------------------------------------ - //
#ifndef __LIFEFORMULA_TILE_H__
#define __LIFEFORMULA_TILE_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Integer.h>
#include <Debug/Log.h>

#include "Passive.h"
#include "Active.h"
#include "Soil.h"

#include "CArrayPtr.h"
#include "CArray.h"
//#include "Array.h"	// NO! Update GelArray_Class.h instead.
// - ------------------------------------------------------------------------------------------ - //
namespace LifeFormula {
// - ------------------------------------------------------------------------------------------ - //
class cTile {
public:
	enum { 
		// Constants //
		DEFAULT_TILE_HEIGHT = 1024,
		MAX_ACTIVE = 4,
		MAX_PASSIVE = 8,
	};

public:												// --Words (32bit)-- //
	cSoil								Soil;		// 4 - Soil Content //
	CArrayPtr<cActive*,MAX_ACTIVE>		Active;		// 4 //
	CArrayPtr<cPassive*,MAX_PASSIVE>	Passive;	// 8 //
	int Height;										// 1 - Elevation //

public:
	cTile() :
		Height( DEFAULT_TILE_HEIGHT )
	{
		
/*
		Log( "HEEP! %i %i -- %x %x", Active.SizeOf(), Active.Size(), Active.ErrorPtr, &Active.ErrorPtr );
		
//		Active.Get() = new cActive();
		Active.Get() = (cActive*)1;
		Active.Get() = (cActive*)2;
		Active.Get() = (cActive*)3;
		Active.Get() = (cActive*)4;

//		Active.Front() = Active.PopBack();
//		Active.PushFront((cActive*)15);
		Active.MoveBackward(1,2);//PushFront((cActive*)15);
//		Active.Back() = Active.PopFront();
//		Active.PushBack((cActive*)15);
		
		int Index = Active.FrontIterator;
		while( !Active.IsError( Index = Active.NextIterator(Index) ) ) {
			Log( "%i -- %x", Index, Active[Index] );			
		}
		
		Log( "MEEP! %i %i", Active.SizeOf(), Active.Size() );
		for ( size_t idx = 0; idx < Active.SizeOf(); idx++ ) {
			Log( "%i -- %x", idx, Active[idx] );
		}
*/
	}
	
	~cTile() {
		Active.DeleteAll();
		Passive.DeleteAll();
	}
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace LifeFormula //
// - ------------------------------------------------------------------------------------------ - //
#endif // __LIFEFORMULA_TILE_H__ //
// - ------------------------------------------------------------------------------------------ - //
