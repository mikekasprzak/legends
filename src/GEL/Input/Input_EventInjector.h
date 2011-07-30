// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_Input_EventInjector_H__
#define __GEL_Input_EventInjector_H__
// - ------------------------------------------------------------------------------------------ - //
class cEventInjector {
public:
	bool Active;
	int Event;
public:
	cEventInjector() {
		Active = false;
		Event = 0;
	}
	
	inline void Update() {
	}

	inline void Clear() {
		Active = false;
		Event = 0;
	}

	inline void Set( const int Value ) {
		if ( !Active ) {
			Active = true;
			Event = Value;
		}
	}
};
// - ------------------------------------------------------------------------------------------ - //
extern cEventInjector EventInjector;
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_Input_EventInjector_H__ //
// - ------------------------------------------------------------------------------------------ - //
