// - ------------------------------------------------------------------------------------------ - //
//#include <Graphics/API.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include "DDSTexture.h"
#include "DDSTexture_Load.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Core/DataBlock.h>
#include <Core/DataBlock_LZMA.h>
//#include <Core/DataBlock_ZLIB.h>
//#include <Core/DataBlock_BZIP.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
unsigned int LoadDDSTexture( const char* MyFile ) {
	// Texture ID we'll be returning //
	unsigned int TextureID = 0;
	
//	// Loaded Texture Data and a useful pointer for accessing it's members //
//	DataBlock* TextureData;
//	DDSTexture* Texture;
//
//	// Load the compressed data //
//	{
//		DataBlock* Compressed = new_DataBlock( MyFile );
//		TextureData = unpack_LZMA_DataBlock( Compressed );
//		Texture = (DDSTexture*)TextureData->Data;
//		delete_DataBlock( Compressed );
//	}
//
//	// Generate a GL Texture //
//	glGenTextures( 1, &TextureID );
//	glBindTexture( GL_TEXTURE_2D, TextureID );
//	
//	// Default Load Format //
//	int LoadFormat = 0;
//	int RGBMode = GL_RGBA;
//
//#ifdef IPHONE_BUILD
//	int DDSTC = 0;
//#endif // IPHONE_BUILD //
//	
//	// Switch the Load Format found inside the DDS File //
//	switch ( Texture->Flags & DDS_TYPE_MASK ) {
//		case DDS_RGBA_4444:
//			LoadFormat = GL_UNSIGNED_SHORT_4_4_4_4;
//			break;
//		case DDS_RGBA_5551:
//			LoadFormat = GL_UNSIGNED_SHORT_5_5_5_1;
//			break;
//		case DDS_RGBA_8888:
//			LoadFormat = GL_UNSIGNED_BYTE;
//			break;
//		case DDS_RGB_565:
//			LoadFormat = GL_UNSIGNED_SHORT_5_6_5;
//			RGBMode = GL_RGB;
//			break;
//		case DDS_RGB_888:
//			LoadFormat = GL_UNSIGNED_BYTE;
//			RGBMode = GL_RGB;
//			break;
//		case DDS_I_8:
//			LoadFormat = GL_UNSIGNED_BYTE;
//			RGBMode = GL_LUMINANCE;
//			break;
//		case DDS_AI_88:
//			LoadFormat = GL_UNSIGNED_SHORT;
//			RGBMode = GL_LUMINANCE_ALPHA;
//			break;
//#ifdef IPHONE_BUILD
//		case DDS_DDSTC2:
//			DDSTC = 2;
//			if ( (Texture->Flags & DDS_ALPHA) == 0 ) {
//				LoadFormat = GL_COMPRESSED_RGB_DDSTC_2BPPV1_IMG;
//				RGBMode = GL_RGB;
//			}
//			else {
//				LoadFormat = GL_COMPRESSED_RGBA_DDSTC_2BPPV1_IMG;
//			}
//			break;
//		case DDS_DDSTC4:
//			DDSTC = 4;
//			if ( (Texture->Flags & DDS_ALPHA) == 0 ) {
//				LoadFormat = GL_COMPRESSED_RGB_DDSTC_4BPPV1_IMG;
//				RGBMode = GL_RGB;
//			}
//			else {
//				LoadFormat = GL_COMPRESSED_RGBA_DDSTC_4BPPV1_IMG;
//			}
//			break;
//#endif // IPHONE_BUILD //
//		default:
//			printf("Error!  Unknown DDS Format!");
//			break;
//	};
//
//	// Various Settings for executing glTexImage //
//	int Width = Texture->Width;
//	int Height = Texture->Height;
//	int SizeOffset = 0;
//	int ChunkSize = 0;
//
//	// Load the First (Main) Texture //
//	glTexImage2D(GL_TEXTURE_2D, 0, RGBMode, Width, Height, 0, RGBMode, LoadFormat, &Texture->Data[SizeOffset]);
//
//	// Load the MipMaps (Mipmap count don't include the original texture) //
//	for ( int MipMap = 0; MipMap < Texture->MipMapCount; MipMap++ ) {		
//#ifdef IPHONE_BUILD
//		// If a DDSTC compression scheme //
//		if ( DDSTC == 2 ) {
//			ChunkSize = ( (Width >? 16) * (Height >? 8) * 2 + 7) / 8;
//		}
//		else if ( DDSTC == 4 ) {
//			ChunkSize = ( (Width >? 8) * (Height >? 8) * 4 + 7) / 8;
//		}
//		else
//#endif // IPHONE_BUILD //
//		// If an uncompressed scheme //
//		{
//			ChunkSize = (Width * Height) * (Texture->BitsPerPixel >> 3);
//		}
//		
//		// Offset and reduce the dimensions //
//		SizeOffset += ChunkSize;
//		Width >>= 1;
//		Height >>= 1;
//		
//		// Load the Mipmap Texture //
//		glTexImage2D(GL_TEXTURE_2D, MipMap+1, RGBMode, Width, Height, 0, RGBMode, LoadFormat, &Texture->Data[SizeOffset]);
//	}
//	
//	// Delete our DataBlock of the uncompressed texture data //
//	delete_DataBlock( TextureData );

	// Return the Texture ID //
	return TextureID;
}
// - ------------------------------------------------------------------------------------------ - //
