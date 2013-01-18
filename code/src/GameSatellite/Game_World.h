// - ------------------------------------------------------------------------------------------ - //
#ifndef __BOAT_GAME_WORLD_H__
#define __BOAT_GAME_WORLD_H__
// - ------------------------------------------------------------------------------------------ - //
#include <System/System.h>
#include <Node/GelList.h>
#include <Grid/Grid2D_Class.h>
#include <Grid/Grid2D_HeightMap.h>
#include <Search/Search.h>
#include <Texture/Texture.h>

#include <Render/Render.h>
#include <Graphics/Allocator/Allocator.h>
#include <Graphics/Allocator/Vector3DAllocator.h>
// - ------------------------------------------------------------------------------------------ - //
#include "Game_Player.h"
// - ------------------------------------------------------------------------------------------ - //
// A known limitation of this game: Replicate the entire world map on both client and server. //
//   Thus Max Level Size Should be 4096x4096 == 16,777,216 * 5 == 83,886,080 (80 MB) //
//   Well, at least for now anyway. One could eventually add a subsection feature. X,Y,W,H of the //
//   real map that gets pushed around along with all the map data as you travel the world. //
//   A full XYWH is stored with the map (0,0,W,H) to compare against. //
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

	cGrid2D<tTile>		Tile;		// Must be separate from other data, because it's bytes //
	cGrid2D<cTileInfo> 	TileInfo;
	cGrid2D<cRegion>	Region;		// 8x8 Areas (so Width/8 and Height/8 in size) //

public:
	cMap()
	{	
	}
	
	// Must be multiples of 8 //
	cMap( const size_t Width, const size_t Height ) :
		Tile( Width, Height ),
		TileInfo( Width, Height ),
		Region( Width >> 3, Height >> 3 )	// div 8 //
	{
		Warning( (Width & 7) != 0, "Bad Width %i (%i)", Width, Width & 7 );		// mod 8 //
		Warning( (Height & 7) != 0, "Bad Height %i (%i)", Height, Height & 7 );	// mod 8 //
		
	}

public:
	const size_t GetWidth() {
		return Tile.Width();
	}
	const size_t GetHeight() {
		return Tile.Height();
	}
	const size_t GetSize() {
		return Tile.Size();
	}
};
// - ------------------------------------------------------------------------------------------ - //
class cWorld {
public:
	tModTime BaseModTime;	// Base time added to the current time. Save this, so you have the age of the world. //
	cMap Map;
	
	Texture::TextureHandle TileArt;
	
	// Current Player //
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

public:
	cWorld() : 
		BaseModTime( 0 ),
		Map( 32, 32 )
	{
		#ifdef PRODUCT_CLIENT
		{
			const char* File = Search::Search( "Tiles" );
			
			DataBlock* Data = new_read_DataBlock( File );
			Texture::STBTexture Tex = Texture::new_STBTexture( Data->Data, Data->Size );
			delete_DataBlock( Data );
			
			Log( "%s -- %i, %i (%i)", File, Tex.Width, Tex.Height, Tex.Info );
			
			TileArt = Texture::upload_STBTexture( Tex, true );
			
			delete_STBTexture( Tex );
		}
		#endif // PRODUCT_CLIENT //
		
		float WaterLevel = 0.4f;
		
		float PlantFertility3 = 0.6f;	// Trees //
		float PlantFertility2 = 0.3f;	// Shrubs //
		float PlantFertility1 = 0.1f;	// Grass //
		float RockFertility1 = -0.2f;	// Sand //
		float RockFertility2 = -0.4f;	// Stones //
		float RockFertility3 = -0.5f;	// Rocks //
		
		srand( 1 );

		cGrid2D<float> Land = generate_PlasmaFractal_HeightMapFloat( Map.GetWidth(), Map.GetHeight() );
		Land.RoundData( WaterLevel );
		Land.SoftenRigidData(2);
		Land.SoftenRigidData(4);
		Land.SoftenRigidData(2);
		cGrid2D<float> Fertility = generate_PlasmaFractal_HeightMapFloat( Map.GetWidth(), Map.GetHeight() );
		Fertility._EqualizeData();
//		Fertility.ClipData();
		
		for ( size_t y = 0; y < Land.Height(); y++ ) {
			for ( size_t x = 0; x < Land.Width(); x++ ) {
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
		}
	}
	
	~cWorld() {
		#ifdef PRODUCT_CLIENT
		Texture::delete_TextureHandle( TileArt );
		#endif // PRODUCT_CLIENT //
	}
	
	// Server Only //
	void Step() {
		//tModTime ModTime = GetModTime();
		
		// Do Stuff //
		
		// For all Players //
	}
	
	void Draw( const Matrix4x4& ViewMatrix ) {
		Vector3DAllocator Vert( Map.GetSize()*6 );
		UVAllocator UV( Map.GetSize()*6 );
		Allocator<GelColor> Color( Map.GetSize()*6 );

		Vert.Clear();
		UV.Clear();
		Color.Clear();

		Vector3D PlusX(1.0f,0,0);
		Vector3D PlusY(0,1.0f,0);
		Vector3D PlusXY(1.0f,1.0f,0);
		
		GelUV UVStep = GEL_UV_ONE / 16;
		
		Real TileSize = 2*12;
		
		int HalfWidth = Map.GetWidth() >> 1;
		int HalfHeight = Map.GetHeight() >> 1;

		for ( size_t y = 0; y < Map.GetHeight(); y++ ) {
			for ( size_t x = 0; x < Map.GetWidth(); x++ ) {
				Vector3D VecXY((int)x - HalfWidth,(int)y - HalfHeight,0);

				Vert.Add( (VecXY+PlusY)*TileSize );
				Vert.Add( (VecXY+PlusXY)*TileSize );
				Vert.Add( (VecXY+PlusX)*TileSize );
				
				Vert.Add( (VecXY+PlusX)*TileSize );
				Vert.Add( (VecXY)*TileSize );
				Vert.Add( (VecXY+PlusY)*TileSize );

				int Index = Map.Tile.Wrap(x,y);
				int UVX = (Index & 15);
				int UVY = 15-((Index >> 4) & 15);
				
				UV.Add( UVSet<GelUV>((UVX)*UVStep, (UVY+1)*UVStep) );
				UV.Add( UVSet<GelUV>((UVX+1)*UVStep, (UVY+1)*UVStep) );
				UV.Add( UVSet<GelUV>((UVX+1)*UVStep, (UVY)*UVStep) );
				
				UV.Add( UVSet<GelUV>((UVX+1)*UVStep, (UVY)*UVStep) );
				UV.Add( UVSet<GelUV>((UVX)*UVStep, (UVY)*UVStep) );
				UV.Add( UVSet<GelUV>((UVX)*UVStep, (UVY+1)*UVStep) );
				
				Color.Add( GEL_RGB_WHITE );
				Color.Add( GEL_RGB_WHITE );
				Color.Add( GEL_RGB_WHITE );
				
				Color.Add( GEL_RGB_WHITE );
				Color.Add( GEL_RGB_WHITE );
				Color.Add( GEL_RGB_WHITE );
				
				//int Val = Map.Tile.Wrap(x,y);
				//Color.Add( GEL_RGB(Val,Val,Val) );
			}
		}

		Render::Default->Bind( Render::ColorTextureShader );
		Render::Default->UniformMatrix4x4( 0, ViewMatrix );
		Render::Default->UniformColor( 1, GEL_RGB_WHITE ); // GlobalColor //
		Render::Default->Uniform1i( 2, 0 ); // TexImage0 //
		Render::Default->BindUniforms();
		Texture::Bind( TileArt, 0 );
		Render::Default->Attrib( 0, Vert.Get() );
		Render::Default->Attrib( 1, UV.Get() );
		Render::Default->Attrib( 2, Color.Get() );
		Render::Default->DrawArrays( GEL_TRIANGLES, Vert.Size() );

		
//		Vector3DAllocator Vert( Map.GetSize()*3*3 );
//		Allocator<GelColor> Color( Map.GetSize()*3*3 );
//
//		Vert.Clear();
//		Color.Clear();
//		
//		for ( size_t y = 0; y < Map.GetHeight()*3; y++ ) {
//			for ( size_t x = 0; x < Map.GetWidth()*3; x++ ) {
//				Vert.Add( Vector3D(x*2*2,y*2*2,0) );
//				int Val = Map.Tile.Wrap(x,y);
//				Color.Add( GEL_RGB(Val,Val,Val) );
//			}
//		}
//
//		Render::Default->Bind( Render::ColorShader );
//		Render::Default->UniformMatrix4x4( 0, ViewMatrix );
//		Render::Default->UniformColor( 1, GEL_RGB_WHITE ); // GlobalColor //
//		Render::Default->BindUniforms();
//		Render::Default->Attrib( 0, Vert.Get() );
//		Render::Default->Attrib( 2, Color.Get() );
//		Render::Default->DrawArrays( GEL_POINTS, Vert.Size() );
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
