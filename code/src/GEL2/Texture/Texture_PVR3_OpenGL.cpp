// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL2) || defined(USES_OPENGLES2)
// - ------------------------------------------------------------------------------------------ - //
#include <API/API_OpenGL2.h>
#include <Debug/GelDebug.h>
// - ------------------------------------------------------------------------------------------ - //
#include "Texture_PVR3.h"
// - ------------------------------------------------------------------------------------------ - //
#include <System/System.h>
#include <Texture/NativeHandle.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Texture {
// - ------------------------------------------------------------------------------------------ - //
NativeHandle upload_PVR3Texture( PVR3Texture* Texture ) {
	// Texture ID we'll be returning //
	unsigned int TextureID;

	Log("+ Loading Texture (PVR3 Loader)..." );

	VLog("* Allocating GL Texture ID..." );

	// Generate a GL Texture //
	glGenTextures( 1, (GLuint*)&TextureID );
	glBindTexture( GL_TEXTURE_2D, TextureID );
//	VLog("* GL Texture ID: %i (IsTexture: %i)", TextureID, glIsTexture(TextureID) );
	
	if ( glGetError() != GL_NO_ERROR ) {
		ELog( "Texture Bind Failed!" );
	}
	
//	if ( !glIsTexture(TextureID) ) {
//		ELog( "IsTexture Failed!" );	
//	}
	
	// Default Load Format //
	int RGBFormat = 0;
	int ReadFormat = GL_RGBA;
	int InternalFormat = GL_RGBA;
	int BitsPerPixel = 32;
	int CompressedFormat = 0;

	switch ( Texture->PixelFormat ) {
		case PVR3_RGBA_4444:
			VLog("* GL_UNSIGNED_BYTE (RGBA_4444) - (OGL4444)");
			RGBFormat = GL_UNSIGNED_SHORT_4_4_4_4;
			break;
		case PVR3_RGBA_8888:
			VLog("* GL_UNSIGNED_BYTE (RGBA_8888) - (OGL8888)");
			RGBFormat = GL_UNSIGNED_BYTE;
			break;

		case PVR3_ARGB_8888:
			ELog( "Unsupported PVR Format PVR3_ARGB_8888" );
			break;
		case PVR3_ARGB_4444:
			ELog( "Unsupported PVR Format PVR3_ARGB_8888" );
			break;

		default:
			// 0xI64x - MSVC, 0x%llx - GCC //
			ELog( "Unknown PVR Format (0x%llx)!", Texture->PixelFormat );
			break;
	};			
	
/*
#ifdef USES_PVRTC
	int PVRTC = 0;
#endif // USES_POWERVR //
	
	// Switch the Load Format found inside the PVR File //
	switch ( Texture->Flags & PVR_TYPE_MASK ) {
		case PVR_RGBA_4444:
			VLog("* GL_UNSIGNED_SHORT_4_4_4_4 (RGBA_4444)");
			RGBFormat = GL_UNSIGNED_SHORT_4_4_4_4;
			break;
		case PVR_RGBA_5551:
			VLog("* GL_UNSIGNED_SHORT_5_5_5_1 (RGBA_5551)");
			RGBFormat = GL_UNSIGNED_SHORT_5_5_5_1;
			break;
		case PVR_RGBA_8888:
			VLog("* GL_UNSIGNED_BYTE (RGBA_8888)");
			RGBFormat = GL_UNSIGNED_BYTE;
			break;
		case PVR_RGB_565:
			VLog("* GL_UNSIGNED_SHORT_5_6_5 (RGB_565)");
			RGBFormat = GL_UNSIGNED_SHORT_5_6_5;
			ReadFormat = GL_RGB;
			InternalFormat = GL_RGB;
			break;
		case PVR_RGB_888:
			VLog("* GL_UNSIGNED_BYTE (RGB_888)");
			RGBFormat = GL_UNSIGNED_BYTE;
			ReadFormat = GL_RGB;
			InternalFormat = GL_RGB;
			break;
		case PVR_I_8:
			VLog("* GL_UNSIGNED_BYTE (I_8)");
			RGBFormat = GL_UNSIGNED_BYTE;
			ReadFormat = GL_LUMINANCE;
			InternalFormat = GL_LUMINANCE;
			break;
		case PVR_AI_88:
			VLog("* GL_UNSIGNED_SHORT (AI_88)");
			RGBFormat = GL_UNSIGNED_SHORT;
			ReadFormat = GL_LUMINANCE_ALPHA;
			InternalFormat = GL_LUMINANCE_ALPHA;
			break;
#ifdef USES_PVRTC
		case PVR_PVRTC2:
		case PVR_OGL_PVRTC2:
			PVRTC = 2;
			CompressedFormat = 10;
			if ( (Texture->Flags & PVR_ALPHA) == 0 ) {
				VLog("* GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG");
				ReadFormat = GL_RGB;
				InternalFormat = GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG;
			}
			else {
				VLog("* GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG");
				InternalFormat = GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG;
			}
			break;
		case PVR_PVRTC4:
		case PVR_OGL_PVRTC4:
			PVRTC = 4;
			CompressedFormat = 10;
			if ( (Texture->Flags & PVR_ALPHA) == 0 ) {
				VLog("* GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG");
				ReadFormat = GL_RGB;
				InternalFormat = GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG;
			}
			else {
				VLog("* GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG");
				InternalFormat = GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG;
			}
			break;
#endif // USES_PVRTC //
		case PVR_DXT1:
			VLog("* COMPRESSED_RGB_S3TC_DXT1_EXT");
			// NOTE: There is a DXT1 variant with a single bit of alpha -- that is code 0x83F1 //
			CompressedFormat = 1;
			InternalFormat = 0x83F0; // COMPRESSED_RGB_S3TC_DXT1_EXT //
			ReadFormat = GL_RGB;
			break;
		case PVR_DXT3:
			VLog("* COMPRESSED_RGBA_S3TC_DXT3_EXT");
			CompressedFormat = 3;
			InternalFormat = 0x83F2; // COMPRESSED_RGBA_S3TC_DXT3_EXT //
			//ReadFormat = GL_RGBA;
			break;
		case PVR_DXT5:
			VLog("* COMPRESSED_RGBA_S3TC_DXT5_EXT");
			CompressedFormat = 5;
			InternalFormat = 0x83F3; // COMPRESSED_RGBA_S3TC_DXT5_EXT //
			//ReadFormat = GL_RGBA;
			break;
		default:
			ELog( "Unknown PVR Format (0x%x)!", Texture->Flags & PVR_TYPE_MASK );
			break;
	};
*/	
	// Remember a few things about this texture //
//	if ( Detail ) {
//		Detail->Width = Texture->Width;
//		Detail->Height = Texture->Height;
//	}

	// Various Settings for executing glTexImage //
	int Width = Texture->Width;
	int Height = Texture->Height;
	int SizeOffset = Texture->MetaDataSize;
	int ChunkSize = 0;
	
	// New feature.  If MaxTextureSize is greater than the current mipmap size, throw it away. //
	int OmittedTexture = 0;
	
	Log("* Details: %ix%i, Textures (Mipmaps): %i", Width, Height, Texture->MipMapCount );

	// Load the MipMaps (Mipmap count don't include the original texture) //
	for ( size_t MipMap = 0; MipMap < Texture->MipMapCount; MipMap++ ) {
/*
//	int MipMap = 0; {
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
*/
		if ( CompressedFormat == 1 ) {
			// DXT1 //
			ChunkSize = 8 * ((Width+3) >> 2) * ((Height+3) >> 2);
		}
		else if ( CompressedFormat == 3 ) {
			// DXT3 //
			ChunkSize = 16 * ((Width+3) >> 2) * ((Height+3) >> 2);
		}
		else if ( CompressedFormat == 5 ) {
			// DXT5 //
			ChunkSize = 16 * ((Width+3) >> 2) * ((Height+3) >> 2);
		}
		else {
			// If an uncompressed scheme //
			ChunkSize = (Width * Height) * (BitsPerPixel >> 3);
		}

		int TextureSize = Width;
		if ( Height > TextureSize )
			TextureSize = Height;
		
		// A new check. If texture is larger than our max allowed size, keep omitting textures until they fit. //
		if ( TextureSize > System::MaxTextureSize ) {
			Log( "* NOTE: Mipmap %i omitted (TextureSize: %i | MaxTextureSize: %i)", MipMap, TextureSize, System::MaxTextureSize );
			OmittedTexture++;
		}
		else {
			// Bilinear Filtering + Mipmaps //
//			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
//			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			// Trilinear + Mipmaps//
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			float MaxAnisotropy;
			glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &MaxAnisotropy);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, MaxAnisotropy );
			
//			Log( "> MaxAnisotropy: %f", MaxAnisotropy );
			
			// Bilinear //
//			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			// Load the Mipmap Texture //
			if ( CompressedFormat ) {
				glCompressedTexImage2D(GL_TEXTURE_2D, MipMap-OmittedTexture, InternalFormat, Width, Height, 0, ChunkSize, &Texture->Data[SizeOffset]);
			}
			else {
				glTexImage2D(GL_TEXTURE_2D, MipMap-OmittedTexture, InternalFormat, Width, Height, 0, ReadFormat, RGBFormat, &Texture->Data[SizeOffset]);
			}
			
			GLenum Err = glGetError();
			if ( Err != GL_NO_ERROR ) {
				ELog("GL ERROR: ???" );
			}
		}
		
		// Offset and reduce the dimensions //
		SizeOffset += ChunkSize;
		Width >>= 1;
		Height >>= 1;
	}
	
	Log("- %i Texture levels loaded.", Texture->MipMapCount );

	// Return the Texture ID //
	return TextureID;
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Texture //
// - ------------------------------------------------------------------------------------------ - //
#endif // defined(USES_OPENGL2) || defined(USES_OPENGLES2) //
// - ------------------------------------------------------------------------------------------ - //
