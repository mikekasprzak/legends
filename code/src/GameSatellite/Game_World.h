// - ------------------------------------------------------------------------------------------ - //
#ifndef __BOAT_GAME_WORLD_H__
#define __BOAT_GAME_WORLD_H__
// - ------------------------------------------------------------------------------------------ - //
#include <System/System.h>
#include <Node/GelList.h>
#include <Grid/Grid2D.h>
#include <Grid/SubGrid2D.h>
#include <Search/Search.h>
// - ------------------------------------------------------------------------------------------ - //
#ifdef PRODUCT_CLIENT
#include <Texture/Texture.h>
#endif // PRODUCT_CLIENT //
// - ------------------------------------------------------------------------------------------ - //
#include "Game_Player.h"
// - ------------------------------------------------------------------------------------------ - //
// A known limitation of this game: Replicate the entire world map on both client and server. //
//   Thus Max Level Size Should be 4096x4096 == 16,777,216 * 5 == 83,886,080 (80 MB) //
//   Well, at least for now anyway. One could eventually add a subsection feature. X,Y,W,H of the //
//   real map that gets pushed around along with all the map data as you travel the world. //
//   A full XYWH is stored with the map (0,0,W,H) to compare against. //
// - ------------------------------------------------------------------------------------------ - //

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
	tModTime ModTime;			// Also has a ModTime //
	
	GelList<cThing> Thing;
	GelList<cPlayer> Player;

public:
	inline bool IsActive() {
		return HasPlayer() || HasThing();
	}
	
	bool HasPlayer() {
		return Player.Size() > 0;	
	}
	
	bool HasThing() {
		return Thing.Size() > 0;
	}

public:
	void Step() {
		
	}
};
// - ------------------------------------------------------------------------------------------ - //
class cMap {
public:
	typedef unsigned char tTile;

	Grid2D<tTile>		Tile;		// Must be separate from other data, because it's bytes //
	Grid2D<cTileInfo> 	TileInfo;
	Grid2D<cRegion>		Region;		// 8x8 Areas (so Width/8 and Height/8 in size) //

public:
	cMap()
	{	
	}
	
	// Must be multiples of 8 //
	cMap( const size_t _Width, const size_t _Height ) :
		Tile( _Width, _Height ),
		TileInfo( _Width, _Height ),
		Region( _Width >> 3, _Height >> 3 )	// div 8 //
	{
		Warning( (_Width & 7) != 0, "Bad Width %i (%i)", _Width, _Width & 7 );		// mod 8 //
		Warning( (_Height & 7) != 0, "Bad Height %i (%i)", _Height, _Height & 7 );	// mod 8 //	
	}

public:
	inline const size_t Width() {
		return Tile.Width();
	}
	inline const size_t Height() {
		return Tile.Height();
	}
	inline const size_t Size() {
		return Tile.Size();
	}
	inline const size_t SizeOf() {
		return Tile.SizeOf();
	}
};
// - ------------------------------------------------------------------------------------------ - //
class cWorld {
public:
	tModTime BaseModTime;	// Base time added to the current time. Save this, so you have the age of the world. //
	cMap Map;
//	Grid2D<u16> Island;
		
	// Current Player //
	IVector2D Pos;
	// Camera relative current player //
	// Or instead, make a cGameClient? cGameViewer? cGameObserver? //
	// Ya, the observer should be separate. A server doesn't need an observer. //
	
	enum {
		TL_DIRT = 0,
		TL_WATER = 128,
		
		TL_GRASS = 5,
		TL_SHRUB = 32,
		TL_TREE = 33,
		
		TL_SAND = 1,
		TL_STONE = 2,
		TL_ROCK = 17,
		
		TL_MUSHROOM = 64,
		TL_MINERAL = 65,
		
		TL_CAVE = 80,
	};

public: // Client ----------------------------------------------------------------------------- - //
#ifdef PRODUCT_CLIENT
	Texture::TextureHandle TilesetArt;
	Grid2D<u8> TilesetInfo;
	
	void Client_Init();
	void Client_Exit();
	
	void Client_Step();
	void Client_Draw( const Matrix4x4& ViewMatrix );
#endif // PRODUCT_CLIENT //

public:
	cWorld() : 
		BaseModTime( 0 ),
		Map( 32, 32 )
	{
		#ifdef PRODUCT_CLIENT
		Client_Init();
		#endif // PRODUCT_CLIENT //
		
		float WaterLevel = 0.4f;
		
		float PlantFertility3 = 0.6f;	// Trees //
		float PlantFertility2 = 0.3f;	// Shrubs //
		float PlantFertility1 = 0.1f;	// Grass //
		float RockFertility1 = -0.2f;	// Sand //
		float RockFertility2 = -0.4f;	// Stones //
		float RockFertility3 = -0.5f;	// Rocks //
		
		srand( 1 );

		Grid2D<float> Land = generate_PlasmaFractal_HeightMapFloat( Map.Width(), Map.Height() );
		Land.RoundData( WaterLevel );
		Land.SoftenRigidData(2);
		Land.SoftenRigidData(4);
		Land.SoftenRigidData(2);
		Grid2D<float> Fertility = generate_PlasmaFractal_HeightMapFloat( Map.Width(), Map.Height() );
		Fertility._EqualizeData();

//		{
//			Grid2D<u16> Swirl = GenerateSwirlGrid2D<u16>(9,3,4,1);
//			for ( size_t y = 0; y < Swirl.Height(); y++ ) {
//				for ( size_t x = 0; x < Swirl.Width(); x++ ) {
//					_Log( "%02x,", (int)Swirl(x,y)&0xff );
//				}
//				Log("");
//			}
//		}

//		Island = BlobExtractWrapped(Land, WaterLevel);
		
		for ( size_t y = 0; y < Land.Height(); y++ ) {
			for ( size_t x = 0; x < Land.Width(); x++ ) {
				//_Log( "%02x,", (int)Island(x,y)&0xff );
				int Val = TL_DIRT;
				if ( Land(x,y) >= WaterLevel ) {
					float Fert = (Fertility(x,y) * 2.0f) - 1.0f;
					if ( Fert >= 0.0f ) {
						// Plant (Note >=) //
						if ( Fert >= PlantFertility3 ) {
							Val = TL_TREE;
						}
						else if ( Fert >= PlantFertility2 ) {
							Val = TL_SHRUB;
						}
						else if ( Fert >= PlantFertility1 ) {
							Val = TL_GRASS;
						}
					}
					else {
						// Rock (Note <=) //
						if ( Fert <= RockFertility3 ) {
							Val = TL_ROCK;
						}
						else if ( Fert <= RockFertility2 ) {
							Val = TL_STONE;
						}
						else if ( Fert <= RockFertility1 ) {
							Val = TL_SAND;
						}
					}
				}
				else {
					Val = TL_WATER;
				}
					
				Map.Tile(x,y) = Val;
			}
			//Log( "" );
		}
		
//		Map.Tile.Resize(8,8);
//		Map.TileInfo.Resize(8,8);
//		Island.Resize(8,8);

		Pos.x = 21/2;
		Pos.y = 21/2;
	}
	
	~cWorld() {
		#ifdef PRODUCT_CLIENT
		Client_Exit();
		#endif // PRODUCT_CLIENT //
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
#endif // __BOAT_GAMEWORLD_H__ //
// - ------------------------------------------------------------------------------------------ - //
