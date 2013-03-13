// - ------------------------------------------------------------------------------------------ - //
#ifndef __PUCK_SCENEGAME_H__
#define __PUCK_SCENEGAME_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Engine/Engine.h>
// - ------------------------------------------------------------------------------------------ - //
#include "Templates/Screwy.h"
// - ------------------------------------------------------------------------------------------ - //
class cSceneGame: public cScene {
public: // - Class Helpers -------------------------------------------------------------------- - //
	typedef cSceneGame thistype;
	inline void* GetThis() { return this; }
public: // - Members -------------------------------------------------------------------------- - //
public: // - Constructors and Destructors ----------------------------------------------------- - //
	//virtual void Create() { // Can't do this in C++. See Project.h. Using Constructor instead. //
	cSceneGame();
	//virtual void Destroy() { // See Above //
	virtual ~cSceneGame();

public: // - Methods -------------------------------------------------------------------------- - //
	virtual void Step();
	virtual void Draw( const Matrix4x4& Matrix );
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PUCK_SCENEGAME_H__ //
// - ------------------------------------------------------------------------------------------ - //
