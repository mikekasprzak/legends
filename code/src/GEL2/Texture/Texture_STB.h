// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL2_TEXTURE_TEXTURE_STB_H__
#define __GEL2_TEXTURE_TEXTURE_STB_H__
// - ------------------------------------------------------------------------------------------ - //
#include <string.h>
#include <Texture/TextureHandle.h>
#include <Grid/Grid2D_Class.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Texture {
// - ------------------------------------------------------------------------------------------ - //
struct STBTexture {
	int Width;
	int Height;
	int Info;
	unsigned char* Data;
};
// - ------------------------------------------------------------------------------------------ - //
const bool is_STBTexture( const void* Data, const size_t Size );	// Is unprocessed Data an STBTexture?
// - ------------------------------------------------------------------------------------------ - //
// Read the STB data in to an STBTexture Structure //
STBTexture new_STBTexture( const void* Data, const size_t Size );
void delete_STBTexture( STBTexture& Image );

// Load an STBTexture in to VRAM //
TextureHandle upload_STBTexture( STBTexture& Texture, const bool Smooth = true, const bool PreMultiplyAlpha = true );
// NOTE: If you want Width, Height, or Info, you should retrieve it directly from //
//   the STBTexture type, before deleting the STBTexture (i.e. Texture.Width, etc) //
// - ------------------------------------------------------------------------------------------ - //
inline cGrid2D<unsigned> to_32bit_Grid2D_STBTexture( STBTexture& Texture ) {
	typedef unsigned tType;
	cGrid2D<tType> Grid;
	
	Grid.SetW( Texture.Width );
	Grid.SetH( Texture.Height );
	tType* Data = new tType[ Texture.Width * Texture.Height ];
	Grid.SetData( Data );

	unsigned* SrcData = (unsigned*)Texture.Data;
		
	for ( int h = 0; h < Texture.Height; h++ ) {
		for ( int w = 0; w < Texture.Width; w++ ) {
			size_t Index = w + (h * Texture.Width);
			Data[Index] = SrcData[Index];
		}
	}
	
	return Grid;
}
// - ------------------------------------------------------------------------------------------ - //
inline cGrid2D<unsigned short> to_16bit_Grid2D_STBTexture( STBTexture& Texture ) {
	typedef unsigned short tType;
	cGrid2D<tType> Grid;
	
	Grid.SetW( Texture.Width );
	Grid.SetH( Texture.Height );
	tType* Data = new tType[ Texture.Width * Texture.Height ];
	Grid.SetData( Data );

	unsigned char* SrcData = (unsigned char*)Texture.Data;
		
	for ( int h = 0; h < Texture.Height; h++ ) {
		for ( int w = 0; w < Texture.Width; w++ ) {
			size_t Index = w + (h * Texture.Width);
			Data[Index] = 
				((SrcData[(Index<<2)+0]>>4) << 0) | 
				((SrcData[(Index<<2)+1]>>4) << 4) | 
				((SrcData[(Index<<2)+2]>>4) << 8) | 
				((SrcData[(Index<<2)+3]>>4) << 12);
		}
	}
	
	return Grid;
}
// - ------------------------------------------------------------------------------------------ - //
inline cGrid2D<unsigned char> to_8bit_Grid2D_STBTexture( STBTexture& Texture ) {
	typedef unsigned char tType;
	cGrid2D<tType> Grid;
	
	Grid.SetW( Texture.Width );
	Grid.SetH( Texture.Height );
	tType* Data = new tType[ Texture.Width * Texture.Height ];
	Grid.SetData( Data );

	unsigned char* SrcData = (unsigned char*)Texture.Data;
		
	for ( int h = 0; h < Texture.Height; h++ ) {
		for ( int w = 0; w < Texture.Width; w++ ) {
			size_t Index = w + (h * Texture.Width);
			Data[Index] = 
				((SrcData[(Index<<2)+0]>>6) << 0) | 
				((SrcData[(Index<<2)+1]>>6) << 2) | 
				((SrcData[(Index<<2)+2]>>6) << 4) | 
				((SrcData[(Index<<2)+3]>>6) << 6);
		}
	}
	
	return Grid;
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Texture //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL2_TEXTURE_TEXTURE_STB_H__ //
// - ------------------------------------------------------------------------------------------ - //
