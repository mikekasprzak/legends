// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_GRAPHICS_GELTEXTURE_H__
#define __GEL_GRAPHICS_GELTEXTURE_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/GelTexture_NativeHandle.h>
// - ------------------------------------------------------------------------------------------ - //
class GelTexture {
public:
	// The different levels of texture usability status //
	GelTexture_NativeHandle Handle;		// Texture is in VRAM //
	DataBlock* Uncompressed;			// Uncompressed Data Ready to be Transfered //
	DataBlock* Compressed;				// Compressed Data is Loaded, ready to be decompressed //
	std::string FileName;				// All we have is a filename //

	// TODO: Load policy above for whether to throw away current texture or not //

	struct GelTexture_Detail {
		int Width, Height;
	};			
	GelTexture_Detail Detail;

public:
	GelTexture() :
		Handle( 0 ),
		Uncompressed( 0 ),
		Compressed( 0 )
	{
	}
	GelTexture( const char* _FileName ) :
		Handle( 0 ),
		Uncompressed( 0 ),
		Compressed( 0 ),
		FileName( _FileName )
	{
	}
	GelTexture( std::string _FileName ) :
		Handle( 0 ),
		Uncompressed( 0 ),
		Compressed( 0 ),
		FileName( _FileName )
	{
	}
	
	// Defined in Native/PLATFORM/GelTexture.cpp
	void Free();
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_GRAPHICS_GELTEXTURE_H__ //
// - ------------------------------------------------------------------------------------------ - //
