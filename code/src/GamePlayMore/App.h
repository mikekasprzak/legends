// - ------------------------------------------------------------------------------------------ - //
#ifndef __PLAYMORE_APP_H__
#define __PLAYMORE_APP_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Style/Style.h>
#include <Screen/Screen.h>
// - ------------------------------------------------------------------------------------------ - //
#include "Engine.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
class cApp {
public: // Class Helpers //
	typedef cApp thistype;
	inline void* GetThis() { return this; }
public: // - Members -------------------------------------------------------------------------- - //
	cGame* Game;
public: // Main ------------------------------------------------------------------------------- - //
	cApp();
	~cApp();

	void Step();
	void Draw( Screen::cNative& Native );
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PLAYMORE_APP_H__ //
// - ------------------------------------------------------------------------------------------ - //
