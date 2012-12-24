// - ------------------------------------------------------------------------------------------ - //
#ifndef __BOAT_GAME_H__
#define __BOAT_GAME_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Grid/Grid2D.h>
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
};
// - ------------------------------------------------------------------------------------------ - //
class cMap {
public:
	typedef unsigned char tTile;

	cGrid<tTile>		Tile;		// Must be separate from other data, because it's bytes //
	cGrid<cTileInfo> 	TileInfo;
	cGrid<cRegion>		Region;		// 8x8 Areas (so Width/8 and Height/8 in size) //
	
public:
	const size_t GetWidth() {
		return Tile.Width();
	}
	const size_t GetHeight() {
		return Tile.Height();
	}
};
// - ------------------------------------------------------------------------------------------ - //
class cGame {
public:
	tModTime BaseModTime;	// Base time added to the current time to get the 
	cMap Map;

public:
	cGame : 
		BaseModTime( 0 )
	{
	}
	
public:
	// If called regularly, prevent the game 
//	inline void FixModTime() {
//		static LastTime;
//	}
	
	inline tModTime GetModTime() const {
		return BaseModTime + (tModTime)(System::GetTick() / (tick_t)(1000/4));
	}
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace BOAT //
// - ------------------------------------------------------------------------------------------ - //
#endif // __BOAT_GAME_H__ //
// - ------------------------------------------------------------------------------------------ - //
