// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL2_TEXTURE_TEXTURE_STB_H__
#define __GEL2_TEXTURE_TEXTURE_STB_H__
// - ------------------------------------------------------------------------------------------ - //
#include <string.h>
#include <Texture/TextureHandle.h>
#include <Grid/Grid2D.h>
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
TextureHandle upload_STBTexture( STBTexture& Texture, const bool Smooth = true, const bool Flip = true, const bool PreMultiplyAlpha = true );
// NOTE: If you want Width, Height, or Info, you should retrieve it directly from //
//   the STBTexture type, before deleting the STBTexture (i.e. Texture.Width, etc) //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// StepX and StepY as 1 is an ordinary copy from an image to Grid2D. //
inline Grid2D<unsigned> to_32bit_Grid2D_STBTexture( STBTexture& Texture, const int StepX = 1, const int StepY = 1 ) {
	typedef unsigned tType;
	Grid2D<tType> Grid;
	
	szt Width = Texture.Width / StepX;
	szt Height = Texture.Height / StepY;
	szt Size = Width * Height;
	
	Grid.SetW( Width );
	Grid.SetH( Height );
	tType* Data = new tType[ Size ];
	Grid.SetData( Data );
	
	if ( Texture.Info == 4 ) {
		unsigned* SrcData = (unsigned*)Texture.Data;

		for ( szt h = 0; h < Height; h++ ) {
			for ( szt w = 0; w < Width; w++ ) {
				szt SrcIndex = (w*StepX) + ((h*StepY) * Texture.Width);
				szt DestIndex = w + (h * Width);
				Data[DestIndex] = SrcData[SrcIndex];
			}
		}
	}
	else if ( Texture.Info == 3 ) {
		unsigned char* SrcData = (unsigned char*)Texture.Data;
			
		for ( szt h = 0; h < Height; h++ ) {
			for ( szt w = 0; w < Width; w++ ) {
				szt SrcIndex = (w*StepX) + ((h*StepY) * Texture.Width);
				szt DestIndex = w + (h * Width);
				Data[DestIndex] = 
					(SrcData[(SrcIndex*3)+0] << 0) | 
					(SrcData[(SrcIndex*3)+1] << 8) | 
					(SrcData[(SrcIndex*3)+2] << 16) | 
					(0xFF << 24);
			}
		}
	}
	else if ( Texture.Info == 1 ) {
		unsigned char* SrcData = (unsigned char*)Texture.Data;
			
		for ( szt h = 0; h < Height; h++ ) {
			for ( szt w = 0; w < Width; w++ ) {
				szt SrcIndex = (w*StepX) + ((h*StepY) * Texture.Width);
				szt DestIndex = w + (h * Width);
				Data[DestIndex] = 
					(SrcData[SrcIndex] << 0) | 
					(SrcData[SrcIndex] << 8) | 
					(SrcData[SrcIndex] << 16) | 
					(0xFF << 24);
			}
		}
	}
	else {
		Log( "! Unsupported Bit Depth (%i)", Texture.Info );
	}
	
	return Grid;
}
// - ------------------------------------------------------------------------------------------ - //
inline Grid2D<unsigned short> to_16bit_Grid2D_STBTexture( STBTexture& Texture, const int StepX = 1, const int StepY = 1 ) {
	typedef unsigned short tType;
	Grid2D<tType> Grid;
	
	szt Width = Texture.Width / StepX;
	szt Height = Texture.Height / StepY;
	szt Size = Width * Height;
	
	Grid.SetW( Width );
	Grid.SetH( Height );
	tType* Data = new tType[ Size ];
	Grid.SetData( Data );

	unsigned char* SrcData = (unsigned char*)Texture.Data;
		
	if ( Texture.Info == 4 ) {
		for ( szt h = 0; h < Height; h++ ) {
			for ( szt w = 0; w < Width; w++ ) {
				szt SrcIndex = (w*StepX) + ((h*StepY) * Texture.Width);
				szt DestIndex = w + (h * Width);
				Data[DestIndex] = 
					((SrcData[(SrcIndex<<2)+0]>>4) << 0) | 
					((SrcData[(SrcIndex<<2)+1]>>4) << 4) | 
					((SrcData[(SrcIndex<<2)+2]>>4) << 8) | 
					((SrcData[(SrcIndex<<2)+3]>>4) << 12);
			}
		}
	}
	else if ( Texture.Info == 3 ) {
		for ( szt h = 0; h < Height; h++ ) {
			for ( szt w = 0; w < Width; w++ ) {
				szt SrcIndex = (w*StepX) + ((h*StepY) * Texture.Width);
				szt DestIndex = w + (h * Width);
				Data[DestIndex] = 
					((SrcData[(SrcIndex*3)+0]>>4) << 0) | 
					((SrcData[(SrcIndex*3)+1]>>4) << 4) | 
					((SrcData[(SrcIndex*3)+2]>>4) << 8) | 
					(0xF << 12);
			}
		}
	}
	else if ( Texture.Info == 1 ) {
		for ( szt h = 0; h < Height; h++ ) {
			for ( szt w = 0; w < Width; w++ ) {
				szt SrcIndex = (w*StepX) + ((h*StepY) * Texture.Width);
				szt DestIndex = w + (h * Width);
				Data[DestIndex] = 
					((SrcData[SrcIndex]>>4) << 0) | 
					((SrcData[SrcIndex]>>4) << 4) | 
					((SrcData[SrcIndex]>>4) << 8) | 
					(0xF << 12);
			}
		}
	}
	else {
		Log( "! Unsupported Bit Depth (%i)", Texture.Info );
	}
	
	return Grid;
}
// - ------------------------------------------------------------------------------------------ - //
inline Grid2D<unsigned char> to_8bit_Grid2D_STBTexture( STBTexture& Texture, const int StepX = 1, const int StepY = 1 ) {
	typedef unsigned char tType;
	Grid2D<tType> Grid;
	
	szt Width = Texture.Width / StepX;
	szt Height = Texture.Height / StepY;
	szt Size = Width * Height;
	
	Grid.SetW( Width );
	Grid.SetH( Height );
	tType* Data = new tType[ Size ];
	Grid.SetData( Data );

	unsigned char* SrcData = (unsigned char*)Texture.Data;
		
	if ( Texture.Info == 4 ) {
		for ( szt h = 0; h < Height; h++ ) {
			for ( szt w = 0; w < Width; w++ ) {
				szt SrcIndex = (w*StepX) + ((h*StepY) * Texture.Width);
				szt DestIndex = w + (h * Width);
				Data[DestIndex] = 
					((SrcData[(SrcIndex<<2)+0]>>6) << 0) | 
					((SrcData[(SrcIndex<<2)+1]>>6) << 2) | 
					((SrcData[(SrcIndex<<2)+2]>>6) << 4) | 
					((SrcData[(SrcIndex<<2)+3]>>6) << 6);
			}
		}
	}
	else if ( Texture.Info == 3 ) {
		for ( szt h = 0; h < Height; h++ ) {
			for ( szt w = 0; w < Width; w++ ) {
				szt SrcIndex = (w*StepX) + ((h*StepY) * Texture.Width);
				szt DestIndex = w + (h * Width);
				Data[DestIndex] = 
					((SrcData[(SrcIndex*3)+0]>>6) << 0) | 
					((SrcData[(SrcIndex*3)+1]>>6) << 2) | 
					((SrcData[(SrcIndex*3)+2]>>6) << 4) | 
					(0x3 << 6);
			}
		}
	}
	else if ( Texture.Info == 1 ) {
		for ( szt h = 0; h < Height; h++ ) {
			for ( szt w = 0; w < Width; w++ ) {
				szt SrcIndex = (w*StepX) + ((h*StepY) * Texture.Width);
				szt DestIndex = w + (h * Width);
				Data[DestIndex] = 
					((SrcData[SrcIndex]>>6) << 0) | 
					((SrcData[SrcIndex]>>6) << 2) | 
					((SrcData[SrcIndex]>>6) << 4) | 
					(0x3 << 6);
			}
		}
	}
	else {
		Log( "! Unsupported Bit Depth (%i)", Texture.Info );
	}
	
	return Grid;
}
// - ------------------------------------------------------------------------------------------ - //
inline Grid2D<unsigned char> to_8bit_1_Channel_Grid2D_STBTexture( STBTexture& Texture, const int StepX = 1, const int StepY = 1 ) {
	typedef unsigned char tType;
	Grid2D<tType> Grid;
	
	szt Width = Texture.Width / StepX;
	szt Height = Texture.Height / StepY;
	szt Size = Width * Height;
	
	Grid.SetW( Width );
	Grid.SetH( Height );
	tType* Data = new tType[ Size ];
	Grid.SetData( Data );

	unsigned char* SrcData = (unsigned char*)Texture.Data;
		
	if ( Texture.Info == 4 ) {
		for ( szt h = 0; h < Height; h++ ) {
			for ( szt w = 0; w < Width; w++ ) {
				szt SrcIndex = (w*StepX) + ((h*StepY) * Texture.Width);
				szt DestIndex = w + (h * Width);
				Data[DestIndex] = SrcData[(SrcIndex<<2)+0];
			}
		}
	}
	else if ( Texture.Info == 3 ) {
		for ( szt h = 0; h < Height; h++ ) {
			for ( szt w = 0; w < Width; w++ ) {
				szt SrcIndex = (w*StepX) + ((h*StepY) * Texture.Width);
				szt DestIndex = w + (h * Width);
				Data[DestIndex] = SrcData[(SrcIndex*3)+0];
			}
		}
	}
	else if ( Texture.Info == 1 ) {
		for ( szt h = 0; h < Height; h++ ) {
			for ( szt w = 0; w < Width; w++ ) {
				szt SrcIndex = (w*StepX) + ((h*StepY) * Texture.Width);
				szt DestIndex = w + (h * Width);
				Data[DestIndex] = SrcData[SrcIndex];
			}
		}
	}
	else {
		Log( "! Unsupported Bit Depth (%i)", Texture.Info );
	}
	
	return Grid;
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Texture //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL2_TEXTURE_TEXTURE_STB_H__ //
// - ------------------------------------------------------------------------------------------ - //
