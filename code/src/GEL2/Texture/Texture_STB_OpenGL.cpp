// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL2) || defined(USES_OPENGLES2)
// - ------------------------------------------------------------------------------------------ - //
// TODO: Make the Alpha Premultiply optional... or better yet, figure out if it should be. //
// - ------------------------------------------------------------------------------------------ - //
#include <API/API_OpenGL2.h>
#include <Style/Style.h>
// - ------------------------------------------------------------------------------------------ - //
#include "Texture_STB.h"
// - ------------------------------------------------------------------------------------------ - //
#include <System/System.h>
#include <Texture/TextureHandle.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Texture {
// - ------------------------------------------------------------------------------------------ - //
TextureHandle upload_STBTexture( STBTexture& Texture, const bool Smooth, const bool Flip, const bool PreMultiplyAlpha ) {
	// Texture ID we'll be returning //
//	TextureHandle TextureID;

	Log("+ Loading Texture (STB Loader)..." );

	VLog("* Allocating GL Texture ID..." );
	// Generate a GL Texture //
	//glGenTextures( 1, (GLuint*)&TextureID );
	TextureHandle TextureID = new_TextureHandle();
	bind_TextureHandle( TextureID );
//	VVLog("* GL Texture ID: %i (IsTexture: %i)", TextureID, glIsTexture(TextureID) );	
//	glBindTexture( GL_TEXTURE_2D, TextureID );
//	VLog("* GL Texture ID: %i (IsTexture: %i)", TextureID, glIsTexture(TextureID) );
	
//	if ( glGetError() != GL_NO_ERROR ) {
//		ELog( "Texture Bind Failed!" );
//	}
	
//	if ( !glIsTexture(TextureID) ) {
//		ELog( "IsTexture Failed!" );	
//	}
	
	// Default Load Format //
	int RGBFormat = 0;
	int ReadFormat = GL_RGBA;
	int InternalFormat = GL_RGBA;
	
		
	// Switch the Load Format found inside the PVR File //
	switch ( Texture.Info ) {
		case 4:
			VLog("* GL_UNSIGNED_BYTE (RGBA_8888)");
			RGBFormat = GL_UNSIGNED_BYTE;
			break;
		case 3:
			VLog("* GL_UNSIGNED_BYTE (RGB_888)");
			RGBFormat = GL_UNSIGNED_BYTE;
			ReadFormat = GL_RGB;
			InternalFormat = GL_RGB;
			break;
		case 1:
			VLog("* GL_UNSIGNED_BYTE (I_8)");
			RGBFormat = GL_UNSIGNED_BYTE;
			ReadFormat = GL_LUMINANCE;
			InternalFormat = GL_LUMINANCE;
			break;
		case 2:
			VLog("* GL_UNSIGNED_SHORT (AI_88)");
			RGBFormat = GL_UNSIGNED_SHORT;
			ReadFormat = GL_LUMINANCE_ALPHA;
			InternalFormat = GL_LUMINANCE_ALPHA;
			break;	
		default:
			ELog( "Unknown STB Format (0x%x)!", Texture.Info );
			break;
	};
	
	// Remember a few things about this texture //
//	if ( Detail ) {
//		Detail->Width = Texture.Width;
//		Detail->Height = Texture.Height;
//	}

	// Various Settings for executing glTexImage //
	int Width = Texture.Width;
	int Height = Texture.Height;
	int SizeOffset = 0;
	int ChunkSize = 0;
	int MipMapCount = 0;
	
	// New feature.  If MaxTextureSize is greater than the current mipmap size, throw it away. //
	int OmittedTexture = 0;
	
	VLog("* Details: %ix%i, Textures (Mipmaps): %i+1", Width, Height, MipMapCount );

	unsigned char* Pixels = 0;
	unsigned char* Orig = (unsigned char*)(&Texture.Data[0]);

	if ( Flip ) {
		VLog("* Flipping Image...");
		Pixels = new unsigned char[ Texture.Width * Texture.Height * Texture.Info ];
		
		// Flip the Image Data (Since OpenGL Textures are upside down) //
		unsigned LineWidth = Texture.Width * Texture.Info;
		unsigned CurrentPos = 0;
		
		for ( unsigned idx = Texture.Height; idx--; ) {
			copy_Data( Orig + (idx*LineWidth), Pixels + CurrentPos, LineWidth );
			CurrentPos += LineWidth;
		}
	}
	else {
		// Don't flip the Image Data (for some reason) //
		//copy_Data( Orig, Pixels, Texture.Width*Texture.Height*Texture.Info );
		Pixels = Orig;
	}
	
	// Premultiply the Alpha, but only if it has alpha //
	if ( PreMultiplyAlpha && (Texture.Info == 4) ) {
		VLog("* Premultiplying Alpha...");
		unsigned int* Data = (unsigned int*)Pixels;//(&Texture.Data[0]);
		for ( int texHeight = 0; texHeight < Texture.Height; texHeight++ ) {
			for ( int texWidth = 0; texWidth < Texture.Width; texWidth++ ) {
				register int Index = (texHeight * (int)Texture.Width) + texWidth;
				int R = (Data[ Index ] >> 0) & 0xff;
				int G = (Data[ Index ] >> 8) & 0xff;
				int B = (Data[ Index ] >> 16) & 0xff;
				int A = (Data[ Index ] >> 24);// & 0xff;
				
				R = (R * A) / 255;
				G = (G * A) / 255;
				B = (B * A) / 255;
				
				Data[ Index ] = (R << 0) | (G << 8) | (B << 16) | (A << 24);
			}
		}
	}
	
	// Load the MipMaps (Mipmap count don't include the original texture) //
	for ( int MipMap = 0; MipMap < MipMapCount+1; MipMap++ ) {
		{
			// If an uncompressed scheme //
			ChunkSize = (Width * Height) * (Texture.Info >> 3);
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
			// Bilinear Filtering + Mipmaps (Never Used) //
//			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
//			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			// Trilinear + Mipmaps//
//			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			if ( Smooth ) {
				VLog("* Bilinear Filtering...");
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			}
			else {
				VLog("* No Filtering (Nearest Neighbor)...");
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			}

			// Load the Mipmap Texture //
			glTexImage2D(GL_TEXTURE_2D, MipMap-OmittedTexture, InternalFormat, Width, Height, 0, ReadFormat, RGBFormat, Pixels );// &Texture.Data[SizeOffset]);
			
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
	
	if ( Pixels != Orig ) {
		delete [] Pixels;
	}
	
	Log("- %i Texture levels loaded.", MipMapCount+1 );

	// Return the Texture ID //
	return TextureID;
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Texture //
// - ------------------------------------------------------------------------------------------ - //
#endif // defined(USES_OPENGL2) || defined(USES_OPENGLES2) //
// - ------------------------------------------------------------------------------------------ - //
