// - ------------------------------------------------------------------------------------------ - //
// My own barebones version of Signal, inspired by Boost and Loki signals, but not shit * //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_UTIL_SIGNAL_H__
#define __GEL_UTIL_SIGNAL_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Core/GelArray.h>
// - ------------------------------------------------------------------------------------------ - //
class Signal {
public:
	typedef void (*FVoidPtr)(void*);
	
	GelArray<FVoidPtr>* Func;

public:
	inline Signal() :
		Func( 0 ) 
	{
	}
	
	inline void operator () ( void* UserDataPtr = 0 ) const {
		if ( Func ) {
			for ( size_t idx = 0; idx < Func->Size; idx++ ) {
				Func[idx](UserDataPtr);
			}
		}
	}
	
	inline void Connect( FVoidPtr _Func ) {
		pushback_GelArray<FVoidPtr>( Func, _Func );
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_UTIL_SIGNAL_H__ //
// - ------------------------------------------------------------------------------------------ - //
