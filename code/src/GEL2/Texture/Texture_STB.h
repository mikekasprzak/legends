// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL2_TEXTURE_TEXTURE_STB_H__
#define __GEL2_TEXTURE_TEXTURE_STB_H__
// - ------------------------------------------------------------------------------------------ - //
#include <string.h>
#include <Texture/TextureHandle.h>
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

TextureHandle upload_STBTexture( STBTexture& Texture );				// Load an STBTexture in to VRAM //
// NOTE: If you want Width, Height, or Info, you should retrieve it directly from //
//   the STBTexture type, before deleting the STBTexture (i.e. Texture.Width, etc) //
// - ------------------------------------------------------------------------------------------ - //
// template<class T=int>
// toGrid2D_STBTexture
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Texture //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL2_TEXTURE_TEXTURE_STB_H__ //
// - ------------------------------------------------------------------------------------------ - //
