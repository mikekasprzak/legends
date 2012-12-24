// - ------------------------------------------------------------------------------------------ - //
#ifndef __BOAT_GAME_SPHERE_H__
#define __BOAT_GAME_SPHERE_H__
// - ------------------------------------------------------------------------------------------ - //
#include <System/System.h>
#include <Grid/Grid2D_Class.h>
// - ------------------------------------------------------------------------------------------ - //
#include "Game_Player.h"
// - ------------------------------------------------------------------------------------------ - //
namespace BOAT {
// - ------------------------------------------------------------------------------------------ - //
typedef unsigned int tModTime;
// - ------------------------------------------------------------------------------------------ - //
class cTileInfo {
public:
	// At 1 tick per second, a uint32 is enough to last 136 years //
	// At 2 ticks per second, a uint32 is enough to last 68 years //
	// At 4 ticks per second, a uint32 is enough to last 34 years //
	// To solve the 34 years of uptime wrapping bug, simply reset all UserModified times, //
	//    make the BaseUserModified equal to the difference between the highest //
	//    UserModified time and the Current UserModified Time (Base+Now), and finally //
	//    kill and restart the server to reset the clock() and thus reset the epoch. //
	tModTime ModTime;		// When a tile was last user modified by a user //
};
// - ------------------------------------------------------------------------------------------ - //
// An 8x8 Region of the map. Everything else above and beyond the map itself. //
class cRegion {
public:
	tModTime ModTime;		// Also has a ModTime //
	
	// Things //
	
	// Players //

public:
	inline bool HasActive() {
		return HasActivePlayer() || HasActiveThing();
	}
	
	bool HasActivePlayer() {
		return false;	
	}
	
	bool HasActiveThing() {
		return false;
	}

public:
	void Step() {
		
	}
};
// - ------------------------------------------------------------------------------------------ - //
class cMap {
public:
	typedef unsigned char tTile;

	cGrid2D<tTile>		Tile;		// Must be separate from other data, because it's bytes //
	cGrid2D<cTileInfo> 	TileInfo;
	cGrid2D<cRegion>	Region;		// 8x8 Areas (so Width/8 and Height/8 in size) //

public:
	cMap()
	{	
	}
	
	cMap( const size_t Width, const size_t Height ) :
		Tile( Width, Height ),
		TileInfo( Width, Height ),
		Region( Width/8, Height/8 )
	{
		ELog( (Width & 7) != 0, "Bad Width %i (%i)", Width, Width & 7 );
		ELog( (Height & 7) != 0, "Bad Height %i (%i)", Height, Height & 7 );
		
	}

public:
	const size_t GetWidth() {
		return Tile.Width();
	}
	const size_t GetHeight() {
		return Tile.Height();
	}
};
// - ------------------------------------------------------------------------------------------ - //
class cSphere {
public:
	tModTime BaseModTime;	// Base time added to the current time. Save this, so you have the age of the world. //
	cMap Map;
	
	// Current Player //
	// Camera relative current player //
	// Or instead, make a cGameClient? cGameViewer? cGameObserver? //
	// Ya, the observer should be separate. A server doesn't need an observer. //

public:
	cSphere() : 
		BaseModTime( 0 )
	{
	}
	
	// Server Only //
	void Step() {
		//tModTime ModTime = GetModTime();
		
		// Do Stuff //
		
		// For all Players //
	}
	
public:
	
	// This function is good for 34 years of uptime (4 changes per second). Ideally, call once per frame. //
	inline tModTime GetModTime() const {
		return BaseModTime + (tModTime)(System::GetTick() / (System::tick_t)(1000/4));
	}
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace BOAT //
// - ------------------------------------------------------------------------------------------ - //
#endif // __BOAT_GAMESPHERE_H__ //
// - ------------------------------------------------------------------------------------------ - //
