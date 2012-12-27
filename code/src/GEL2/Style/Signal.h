// - ------------------------------------------------------------------------------------------ - //
// My own barebones version of Signal, inspired by Boost and Loki signals, but not shit //
//
// Does not do: Slot Ordering, Arguments, Chaining Arguments/Returns, Blocking, Scoped Connections
// Reference: http://www.boost.org/doc/libs/1_52_0/doc/html/signals/tutorial.html
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_UTIL_SIGNAL_H__
#define __GEL_UTIL_SIGNAL_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Core/GelArray.h>
// - ------------------------------------------------------------------------------------------ - //
class Signal {
public:
	typedef void (*FVoidPtr)(void*);
	
	GelArray<FVoidPtr>* Funcs;

public:
	inline Signal() :
		Funcs( 0 ) 
	{
	}
	
	inline ~Signal() {
		if ( Funcs ) {
			delete_GelArray<FVoidPtr>( Funcs );
		}
	}
	
	inline void operator () ( void* UserDataPtr = 0 ) const {
		if ( Funcs ) {
			for ( size_t idx = 0; idx < Funcs->Size; idx++ ) {
				Funcs->Data[idx]( UserDataPtr );
			}
		}
	}
	
	inline void Connect( FVoidPtr _Func ) {
		pushback_GelArray<FVoidPtr>( &Funcs, _Func );
	}

	inline void Disconnect( FVoidPtr _Func ) {
		// findlast, to allow us to correctly nest a scoped connection //
		int Index = findlast_GelArray<FVoidPtr>( &Funcs, _Func );
		if ( Index > 0 ) {
			erase_GelArray<FVoidPtr>( &Funcs, Index );
		}
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_UTIL_SIGNAL_H__ //
// - ------------------------------------------------------------------------------------------ - //
