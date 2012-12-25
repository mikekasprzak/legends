// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL2_TEXTURE_TEXTURE_STB_H__
#define __GEL2_TEXTURE_TEXTURE_STB_H__
// - ------------------------------------------------------------------------------------------ - //
#include <string.h>
#include <Texture/NativeHandle.h>
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

STBTexture new_STBTexture( const void* Data, const size_t Size );	// Process an STBTexture
void delete_STBTexture( STBTexture& Image );						// Delete an STBTexture

NativeHandle upload_STBTexture( STBTexture& Texture );				// Load an STBTexture in to VRAM
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Texture //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL2_TEXTURE_TEXTURE_STB_H__ //
// - ------------------------------------------------------------------------------------------ - //
