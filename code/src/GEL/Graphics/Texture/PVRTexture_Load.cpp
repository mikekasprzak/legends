// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/API.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Debug/Log.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/Graphics_System.h>
#include "PVRTexture.h"
#include "PVRTexture_Load.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Core/DataBlock.h>
#include <Core/DataBlock_LZMA.h>
//#include <Core/DataBlock_ZLIB.h>
//#include <Core/DataBlock_BZIP.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
unsigned int LoadGL_PVRTexture( PVRTexture* Texture, GelTexture::GelTexture_Detail* Detail ) {
#ifndef PRODUCT_PSP
	// Texture ID we'll be returning //
	unsigned int TextureID;

	Log("* Allocating GL Texture ID...\n" );
	// Generate a GL Texture //
	glGenTextures( 1, (GLuint*)&TextureID );
	Log("* GL Texture ID: %i (IsTexture: %i)\n", TextureID, glIsTexture(TextureID) );	
	glBindTexture( GL_TEXTURE_2D, TextureID );
	Log("* GL Texture ID: %i (IsTexture: %i)\n", TextureID, glIsTexture(TextureID) );
	
	if ( glGetError() != GL_NO_ERROR ) {
		Log( "** ERROR ** : Texture Bind Failed!\n" );
	}
	
	if ( !glIsTexture(TextureID) ) {
		Log( "** ERROR ** : IsTexture Failed!\n" );	
	}
	
	// Default Load Format //
	int RGBFormat = 0;
	int ReadFormat = GL_RGBA;
	int InternalFormat = GL_RGBA;
	
#ifdef USES_TEXTURECOMPRESSION
	int CompressFormat = 0;

#ifdef USES_PVRTC
	int PVRTC = 0;
#endif // USES_POWERVR //
#endif // USES_TEXTURECOMPRESSION //
	
	// Switch the Load Format found inside the PVR File //
	switch ( Texture->Flags & PVR_TYPE_MASK ) {
		case PVR_RGBA_4444:
			Log("* GL_UNSIGNED_SHORT_4_4_4_4 (RGBA_4444)\n");
			RGBFormat = GL_UNSIGNED_SHORT_4_4_4_4;
			break;
		case PVR_RGBA_5551:
			Log("* GL_UNSIGNED_SHORT_5_5_5_1 (RGBA_5551)\n");
			RGBFormat = GL_UNSIGNED_SHORT_5_5_5_1;
			break;
		case PVR_RGBA_8888:
			Log("* GL_UNSIGNED_BYTE (RGBA_8888)\n");
			RGBFormat = GL_UNSIGNED_BYTE;
			break;
		case PVR_RGB_565:
			Log("* GL_UNSIGNED_SHORT_5_6_5 (RGB_565)\n");
			RGBFormat = GL_UNSIGNED_SHORT_5_6_5;
			ReadFormat = GL_RGB;
			InternalFormat = GL_RGB;
			break;
		case PVR_RGB_888:
			Log("* GL_UNSIGNED_BYTE (RGB_888)\n");
			RGBFormat = GL_UNSIGNED_BYTE;
			ReadFormat = GL_RGB;
			InternalFormat = GL_RGB;
			break;
		case PVR_I_8:
			Log("* GL_UNSIGNED_BYTE (I_8)\n");
			RGBFormat = GL_UNSIGNED_BYTE;
			ReadFormat = GL_LUMINANCE;
			InternalFormat = GL_LUMINANCE;
			break;
		case PVR_AI_88:
			Log("* GL_UNSIGNED_SHORT (AI_88)\n");
			RGBFormat = GL_UNSIGNED_SHORT;
			ReadFormat = GL_LUMINANCE_ALPHA;
			InternalFormat = GL_LUMINANCE_ALPHA;
			break;
#ifdef USES_TEXTURECOMPRESSION
#ifdef USES_PVRTC
		case PVR_PVRTC2:
		case PVR_OGL_PVRTC2:
			PVRTC = 2;
			CompressFormat = 10;
			if ( (Texture->Flags & PVR_ALPHA) == 0 ) {
				Log("* GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG\n");
				ReadFormat = GL_RGB;
				InternalFormat = GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG;
			}
			else {
				Log("* GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG\n");
				InternalFormat = GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG;
			}
			break;
		case PVR_PVRTC4:
		case PVR_OGL_PVRTC4:
			PVRTC = 4;
			CompressFormat = 10;
			if ( (Texture->Flags & PVR_ALPHA) == 0 ) {
				Log("* GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG\n");
				ReadFormat = GL_RGB;
				InternalFormat = GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG;
			}
			else {
				Log("* GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG\n");
				InternalFormat = GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG;
			}
			break;
#endif // USES_PVRTC //
		case PVR_DXT1:
			Log("* COMPRESSED_RGB_S3TC_DXT1_EXT\n");
			// NOTE: There is a DXT1 variant with a single bit of alpha -- that is code 0x83F1 //
			CompressFormat = 1;
			InternalFormat = 0x83F0; // COMPRESSED_RGB_S3TC_DXT1_EXT //
			ReadFormat = GL_RGB;
			break;
		case PVR_DXT3:
			Log("* COMPRESSED_RGBA_S3TC_DXT3_EXT\n");
			CompressFormat = 3;
			InternalFormat = 0x83F2; // COMPRESSED_RGBA_S3TC_DXT3_EXT //
			//ReadFormat = GL_RGBA;
			break;
		case PVR_DXT5:
			Log("* COMPRESSED_RGBA_S3TC_DXT5_EXT\n");
			CompressFormat = 5;
			InternalFormat = 0x83F3; // COMPRESSED_RGBA_S3TC_DXT5_EXT //
			//ReadFormat = GL_RGBA;
			break;
#endif // USES_TEXTURECOMPRESSION //		
		default:
			Log("* Error!  Unknown PVR Format!\n");
			break;
	};
	
	// Remember a few things about this texture //
	if ( Detail ) {
		Detail->Width = Texture->Width;
		Detail->Height = Texture->Height;
	}

	// Various Settings for executing glTexImage //
	int Width = Texture->Width;
	int Height = Texture->Height;
	int SizeOffset = 0;
	int ChunkSize = 0;
	
	// New feature.  If MaxTextureSize is greater than the current mipmap size, throw it away. //
	int OmittedTexture = 0;
	
	Log("* Details: %ix%i, Textures (Mipmaps): %i+1\n", Width, Height, Texture->MipMapCount );

	// Load the MipMaps (Mipmap count don't include the original texture) //
	for ( int MipMap = 0; MipMap < Texture->MipMapCount+1; MipMap++ ) {
//	int MipMap = 0; {
#ifdef USES_TEXTURECOMPRESSION		
#ifdef USES_PVRTC
		#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))
		#define MAX(X,Y) ((X) > (Y) ? (X) : (Y))

		// If a PVRTC compression scheme //
		if ( PVRTC == 2 ) {
			ChunkSize = ( MAX(Width,16) * MAX(Height,8) * 2 + 7) / 8;
		}
		else if ( PVRTC == 4 ) {
			ChunkSize = ( MAX(Width,8) * MAX(Height,8) * 4 + 7) / 8;
		}
		else
			
		#undef MIN
		#undef MAX
#endif // USES_PVRTC //
		if ( CompressFormat == 1 ) {
			ChunkSize = 8 * ((Width+3) >> 2) * ((Height+3) >> 2);
		}
		else if ( CompressFormat == 3 ) {
			ChunkSize = 16 * ((Width+3) >> 2) * ((Height+3) >> 2);
		}
		else if ( CompressFormat == 5 ) {
			ChunkSize = 16 * ((Width+3) >> 2) * ((Height+3) >> 2);
		}
		else
#endif // USES_TEXTURECOMPRESSION //
		{
			// If an uncompressed scheme //
			ChunkSize = (Width * Height) * (Texture->BitsPerPixel >> 3);
		}

		int TextureSize = Width;
		if ( Height > TextureSize )
			TextureSize = Height;
		
		// A new check. If texture is larger than our max allowed size, keep omitting textures until they fit. //
		if ( TextureSize > System::MaxTextureSize ) {
			Log( "* NOTE: Mipmap %i omitted (TextureSize: %i | MaxTextureSize: %i)\n", MipMap, TextureSize, System::MaxTextureSize );
			OmittedTexture++;
		}
		else {
			// Bilinear Filtering + Mipmaps //
//			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
//			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			// Trilinear + Mipmaps//
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			// Bilinear //
//			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			// Load the Mipmap Texture //
#ifdef USES_TEXTURECOMPRESSION
			if ( CompressFormat ) {
				glCompressedTexImage2D(GL_TEXTURE_2D, MipMap-OmittedTexture, InternalFormat, Width, Height, 0, ChunkSize, &Texture->Data[SizeOffset]);
			}
			else
#endif // USES_TEXTURECOMPRESSION //
			{
				glTexImage2D(GL_TEXTURE_2D, MipMap-OmittedTexture, InternalFormat, Width, Height, 0, ReadFormat, RGBFormat, &Texture->Data[SizeOffset]);
			}
			
			GLenum Err = glGetError();
			if ( Err != GL_NO_ERROR ) {
				Log("* GL ERROR: ???\n" );
			}
		}
		
		// Offset and reduce the dimensions //
		SizeOffset += ChunkSize;
		Width >>= 1;
		Height >>= 1;
	}
	
	Log("* %i Texture levels loaded.\n", Texture->MipMapCount+1 );

	// Return the Texture ID //
	return TextureID;
#endif // PRODUCT_PSP //
}
// - ------------------------------------------------------------------------------------------ - //
unsigned int LoadGL_PVRTexture( const char* MyFile, cTextureDetail* Detail ) {
#ifndef PRODUCT_PSP
	// Loaded Texture Data and a useful pointer for accessing it's members //
	DataBlock* TextureData;
	PVRTexture* Texture;

	// Load the compressed data //
	{
		DataBlock* Compressed = new_DataBlock( MyFile );
		TextureData = unpack_LZMA_DataBlock( Compressed );
		Texture = (PVRTexture*)TextureData->Data;
		delete_DataBlock( Compressed );
	}

	unsigned int TextureID = LoadGL_PVRTexture( Texture, Detail );

	delete_DataBlock( TextureData );

	return TextureID;
#endif // PRODUCT_PSP //
}
// - ------------------------------------------------------------------------------------------ - //
