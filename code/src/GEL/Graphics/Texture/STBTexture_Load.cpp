// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL) || defined(USES_OPENGLES)
// - ------------------------------------------------------------------------------------------ - //
#include <Debug/Log.h>
#include <Core/DataBlock.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/API.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/Graphics_System.h>
#include "STBTexture.h"
#include "STBTexture_Load.h"
#include <External/STB/stb_image.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/GelTexture_NativeHandle.h>
// - ------------------------------------------------------------------------------------------ - //
bool IsSTB( const void* Data ) {
	// Hack! Assume all images are > 256 bytes in size //
	int len=256;
	const unsigned char* buffer = (const unsigned char*)Data;
	
	if (stbi_jpeg_test_memory(buffer,len))
		return true;
	if (stbi_png_test_memory(buffer,len))
		return true;
	if (stbi_bmp_test_memory(buffer,len))
		return true;
	if (stbi_psd_test_memory(buffer,len))
		return true;
#ifndef STBI_NO_HDR
	if (stbi_hdr_test_memory(buffer, len))
		return true;
#endif
	if (stbi_tga_test_memory(buffer,len))
		return true;
	return false;
}
// - ------------------------------------------------------------------------------------------ - //
GelTexture_NativeHandle load_STBTexture( STBTexture* Texture, GelTexture::GelTexture_Detail* Detail ) {
	// Texture ID we'll be returning //
	unsigned int TextureID;

	VLog("* Allocating GL Texture ID...\n" );
	// Generate a GL Texture //
	glGenTextures( 1, (GLuint*)&TextureID );
	VVLog("* GL Texture ID: %i (IsTexture: %i)\n", TextureID, glIsTexture(TextureID) );	
	glBindTexture( GL_TEXTURE_2D, TextureID );
	VLog("* GL Texture ID: %i (IsTexture: %i)\n", TextureID, glIsTexture(TextureID) );
	
	if ( glGetError() != GL_NO_ERROR ) {
		ELog( "Texture Bind Failed!\n" );
	}
	
	if ( !glIsTexture(TextureID) ) {
		ELog( "IsTexture Failed!\n" );	
	}
	
	// Default Load Format //
	int RGBFormat = 0;
	int ReadFormat = GL_RGBA;
	int InternalFormat = GL_RGBA;
	
	
		
	// Switch the Load Format found inside the PVR File //
	switch ( Texture->Info ) {
		case 4:
			VLog("* GL_UNSIGNED_BYTE (RGBA_8888)\n");
			RGBFormat = GL_UNSIGNED_BYTE;
			break;
		case 3:
			VLog("* GL_UNSIGNED_BYTE (RGB_888)\n");
			RGBFormat = GL_UNSIGNED_BYTE;
			ReadFormat = GL_RGB;
			InternalFormat = GL_RGB;
			break;
		case 1:
			VLog("* GL_UNSIGNED_BYTE (I_8)\n");
			RGBFormat = GL_UNSIGNED_BYTE;
			ReadFormat = GL_LUMINANCE;
			InternalFormat = GL_LUMINANCE;
			break;
		case 2:
			VLog("* GL_UNSIGNED_SHORT (AI_88)\n");
			RGBFormat = GL_UNSIGNED_SHORT;
			ReadFormat = GL_LUMINANCE_ALPHA;
			InternalFormat = GL_LUMINANCE_ALPHA;
			break;	
		default:
			ELog( "Unknown STB Format (0x%x)!\n", Texture->Info );
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
	int MipMapCount = 0;
	
	// New feature.  If MaxTextureSize is greater than the current mipmap size, throw it away. //
	int OmittedTexture = 0;
	
	VLog("* Details: %ix%i, Textures (Mipmaps): %i+1\n", Width, Height, MipMapCount );

	// Load the MipMaps (Mipmap count don't include the original texture) //
	for ( int MipMap = 0; MipMap < MipMapCount+1; MipMap++ ) {
		{
			// If an uncompressed scheme //
			ChunkSize = (Width * Height) * (Texture->Info >> 3);
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
//			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			// Bilinear //
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			// Load the Mipmap Texture //
			glTexImage2D(GL_TEXTURE_2D, MipMap-OmittedTexture, InternalFormat, Width, Height, 0, ReadFormat, RGBFormat, &Texture->Data[SizeOffset]);
			
			GLenum Err = glGetError();
			if ( Err != GL_NO_ERROR ) {
				ELog("GL ERROR: ???\n" );
			}
		}
		
		// Offset and reduce the dimensions //
		SizeOffset += ChunkSize;
		Width >>= 1;
		Height >>= 1;
	}
	
	Log("- %i Texture levels loaded.\n", MipMapCount+1 );

	// Return the Texture ID //
	return TextureID;
}
// - ------------------------------------------------------------------------------------------ - //
GelTexture_NativeHandle load_STBTexture( GelTexture* Texture ) {
	STBTexture Image;
	
	Image.Data = stbi_load_from_memory( 
		(unsigned char*)Texture->Processed.Data->Data, Texture->Processed.Data->Size,
		&Image.Width, &Image.Height, &Image.Info, 0 );
	
	Texture->Handle = load_STBTexture( &Image, &(Texture->Detail) );
	
	stbi_image_free( Image.Data );
	
	return Texture->Handle;
}
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_OPENGL //
// - ------------------------------------------------------------------------------------------ - //
