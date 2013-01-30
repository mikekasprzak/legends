// - ------------------------------------------------------------------------------------------ - //
#ifdef PRODUCT_CLIENT
// - ------------------------------------------------------------------------------------------ - //
#include "Game.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Render/Render.h>
#include <Graphics/Allocator/Allocator.h>
#include <Graphics/Allocator/Vector3DAllocator.h>
// - ------------------------------------------------------------------------------------------ - //
// Hack //
extern bool __UpKey;
extern bool __DownKey;
extern bool __LeftKey;
extern bool __RightKey;
// - ------------------------------------------------------------------------------------------ - //
namespace BOAT {
// - ------------------------------------------------------------------------------------------ - //
void cWorld::Client_Init() {
	// Tileset Loading //
	{
		const char* File = Search::Search( "Tiles0" );
		
		DataBlock* Data = new_read_DataBlock( File );
		Texture::STBTexture Tex = Texture::new_STBTexture( Data->Data, Data->Size );
		delete_DataBlock( Data );
		
		Log( "%s -- %i, %i (%i)", File, Tex.Width, Tex.Height, Tex.Info );
		
		TilesetArt = Texture::upload_STBTexture( Tex, false );
		
		delete_STBTexture( Tex );
	}
	
	// Tileset Info Loading //
	{
		const char* File = Search::Search( "Tiles_Info" );
		
		DataBlock* Data = new_read_DataBlock( File );
		Texture::STBTexture Tex = Texture::new_STBTexture( Data->Data, Data->Size );
		delete_DataBlock( Data );
		
		Log( "%s -- %i, %i (%i)", File, Tex.Width, Tex.Height, Tex.Info );
		
		// Tileset, despite actual size, will be 16x16 unique pieces of data //
		TilesetInfo = Texture::to_8bit_Grid2D_STBTexture( Tex, Tex.Width/16, Tex.Height/16 );
		
		delete_STBTexture( Tex );
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cWorld::Client_Exit() {
	Texture::delete_TextureHandle( TilesetArt );	
}
// - ------------------------------------------------------------------------------------------ - //
void cWorld::Client_Step() {
	static int Delay = 0;
	Delay++;
	if ( Delay == 16 ) {
		Delay = 0;
		if ( __UpKey )
			Pos.y--;
		if ( __DownKey )
			Pos.y++;
		if ( __LeftKey )
			Pos.x--;
		if ( __RightKey )
			Pos.x++;
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cWorld::Client_Draw( const Matrix4x4& ViewMatrix ) {
	SubGrid2D<cMap::tTile> SubMap( 0,0, 31,31, Map.Tile );
	//SubGrid2D<cMap::tTile> SubMap( Map.Tile );
	
	Grid2D<u8> Occlusion( SubMap.Width(), SubMap.Height() );
	//GenerateMagnitudeDistanceGrid2D( Occlusion, SubMap.HalfWidth(), SubMap.HalfHeight() );
	//GenerateRaycastGrid( SubMap, Occlusion, SubMap.HalfWidth(), SubMap.HalfHeight(), *TilesetInfo, 0x8 );
	//GenerateRaycastGrid( SubMap, Occlusion, Pos.x.ToInt(), Pos.y.ToInt(), *TilesetInfo, 0x8, 6 );
	GenerateShadowGrid( SubMap, Occlusion, Pos.x.ToInt(), Pos.y.ToInt(), *TilesetInfo, 0x8 );
	
	Vector3DAllocator Vert( SubMap.Size()*6 );
	UVAllocator UV( SubMap.Size()*6 );
	Allocator<GelColor> Color( SubMap.Size()*6 );

	Vert.Clear();
	UV.Clear();
	Color.Clear();

	Vector3D PlusX(1.0f,0,0);
	Vector3D PlusY(0,1.0f,0);
	Vector3D PlusXY(1.0f,1.0f,0);
	
	GelUV UVStep = GEL_UV_ONE / 16;
	
	Real TileSize = 2*12*2;
	
	int HalfWidth = SubMap.HalfWidth();
	int HalfHeight = SubMap.HalfHeight();
	
	for ( size_t y = 0; y < SubMap.Height(); y++ ) {
		for ( size_t x = 0; x < SubMap.Width(); x++ ) {
			int TX = x;
			int TY = SubMap.Height()-1-y;
			int Index = SubMap.Wrap(TX,TY);
			// UV Texture is 16x16 (in tiles) //
			int UVX = (Index & 15);
			int UVY = 15-((Index >> 4) & 15);
			
			GelColor Col = GEL_RGB_WHITE;
			if ( (Pos.x.ToInt() == (int)x) && (SubMap.Height()-1-Pos.y.ToInt() == y) ) {
				Col = GEL_RGB_GREEN;
			}
			else {
				u8 Val = Occlusion(TX,TY);
				if ( Val > 3 ) {
					// Omit geometry //
					continue;
				}
				else if ( Val > 0 ) {
					Col = GEL_RGBA(255,255,255,160-(Val*48));
				}
			}
//				if ( Island(TX,TY) != 0xFFFF ) {
//					float Val = Island(TX,TY);
//					Val /= 16.0f;
//					Val *= 360.0f;
//					Col = GEL_HSV( Val, 1, 1 );
//				}
			
			Vector3D VecXY((int)x - HalfWidth,(int)y - HalfHeight,0);

			Vert.Add( (VecXY+PlusY)*TileSize );
			Vert.Add( (VecXY+PlusXY)*TileSize );
			Vert.Add( (VecXY+PlusX)*TileSize );
			
			Vert.Add( (VecXY+PlusX)*TileSize );
			Vert.Add( (VecXY)*TileSize );
			Vert.Add( (VecXY+PlusY)*TileSize );
			
			UV.Add( UVSet<GelUV>((UVX)*UVStep, (UVY+1)*UVStep) );
			UV.Add( UVSet<GelUV>((UVX+1)*UVStep, (UVY+1)*UVStep) );
			UV.Add( UVSet<GelUV>((UVX+1)*UVStep, (UVY)*UVStep) );
			
			UV.Add( UVSet<GelUV>((UVX+1)*UVStep, (UVY)*UVStep) );
			UV.Add( UVSet<GelUV>((UVX)*UVStep, (UVY)*UVStep) );
			UV.Add( UVSet<GelUV>((UVX)*UVStep, (UVY+1)*UVStep) );
							
			Color.Add( Col );
			Color.Add( Col );
			Color.Add( Col );
			
			Color.Add( Col );
			Color.Add( Col );
			Color.Add( Col );
		}
	}

	Render::Default->Bind( Render::ColorTextureShader );
	Render::Default->UniformMatrix4x4( 0, ViewMatrix );
	Render::Default->UniformColor( 1, GEL_RGB_WHITE ); // GlobalColor //
	Render::Default->Uniform1i( 2, 0 ); // TexImage0 //
	Render::Default->BindUniforms();
	Texture::Bind( TilesetArt, 0 );
	Render::Default->Attrib( 0, Vert.Get() );
	Render::Default->Attrib( 1, UV.Get() );
	Render::Default->Attrib( 2, Color.Get() );
	Render::Default->DrawArrays( GEL_TRIANGLES, Vert.Size() );
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace BOAT //
// - ------------------------------------------------------------------------------------------ - //
#endif // PRODUCT_CLIENT //
// - ------------------------------------------------------------------------------------------ - //
