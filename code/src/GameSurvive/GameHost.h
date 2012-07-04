// - ------------------------------------------------------------------------------------------ - //
#ifndef __GameHost_H__
#define __GameHost_H__
// - ------------------------------------------------------------------------------------------ - //
#include "Game.h"
#include "GameSupport.h"
// - ------------------------------------------------------------------------------------------ - //
class cGameHost {
public:
	cGameHost();
	~cGameHost();
	
	void CreateGame();
	
	void Step();
	void Draw();
	
	void GotFocus();
	void LostFocus();
	
	void ForcePaused();
	bool FirstRun();
	void Save();
public:
	cGame* Game;
	cGameSupport* GameSupport;
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GameHost_H__ //
// - ------------------------------------------------------------------------------------------ - //
