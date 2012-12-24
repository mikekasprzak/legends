// - ------------------------------------------------------------------------------------------ - //
#ifndef __BOAT_GAME_PLAYER_H__
#define __BOAT_GAME_PLAYER_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/SVector.h>
// - ------------------------------------------------------------------------------------------ - //
namespace BOAT {
// - ------------------------------------------------------------------------------------------ - //
class cPlayer {
public:
	SVector2D Pos;

public:
	cPlayer()
	{
	}

	cPlayer( const int x, const int y ) :
		Pos( x, y )
	{
	}
	
public:
	// Which Region //
	inline const size_t GetRegionX() const {
		return Pos.x >> 3; // div 8 //
	}
	inline const size_t GetRegionY() const {
		return Pos.y >> 3; // div 8 //
	}

	// The Position inside the Region //
	inline const size_t GetRegionPosX() const {
		return Pos.x & 7; // mod 8 //
	}
	inline const size_t GetRegionPosY() const {
		return Pos.y & 7; // mod 8 //
	}
	
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace BOAT //
// - ------------------------------------------------------------------------------------------ - //
#endif // __BOAT_GAME_PLAYER_H__ //
// - ------------------------------------------------------------------------------------------ - //
