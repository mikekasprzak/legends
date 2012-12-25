// - ------------------------------------------------------------------------------------------ - //
#include "Texture_STB.h"
#include <External/STB/stb_image.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Texture {
// - ------------------------------------------------------------------------------------------ - //
const bool is_STBTexture( const void* Data, const size_t Size ) {
	const unsigned char* Buffer = (const unsigned char*)Data;
	
	if ( stbi_jpeg_test_memory(Buffer,Size) )
		return true;
	if ( stbi_png_test_memory(Buffer,Size) )
		return true;
	if ( stbi_bmp_test_memory(Buffer,Size) )
		return true;
	if ( stbi_psd_test_memory(Buffer,Size) )
		return true;
#ifndef STBI_NO_HDR
	if ( stbi_hdr_test_memory(Buffer,Size) )
		return true;
#endif // STBI_NO_HDR //
	if ( stbi_tga_test_memory(Buffer,Size) )
		return true;
	return false;
}
// - ------------------------------------------------------------------------------------------ - //
STBTexture new_STBTexture( const void* Data, const size_t Size ) {
	STBTexture Image;
	
	Image.Data = stbi_load_from_memory( 
		(unsigned char*)Data, Size,
		&Image.Width, &Image.Height, &Image.Info, 0 );
	
	return Image;
}
// - ------------------------------------------------------------------------------------------ - //
void delete_STBTexture( STBTexture& Image ) {
	stbi_image_free( Image.Data );
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Texture //
// - ------------------------------------------------------------------------------------------ - //
