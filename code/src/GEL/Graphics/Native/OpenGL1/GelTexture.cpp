// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL) || defined(USES_OPENGLES)
// - ------------------------------------------------------------------------------------------ - //
#include <Debug/Log.h>

#include <Graphics/Graphics.h>
#include <Graphics/GelTexture.h>
// - ------------------------------------------------------------------------------------------ - //
bool GelTexture::FreePolicy_Processed = false;
bool GelTexture::FreePolicy_UnProcessed = false;
// - ------------------------------------------------------------------------------------------ - //
void GelTexture::SetFreePolicy( const bool _Processed = false, const bool _UnProcessed = false ) {
	Log("* Free Policy set: %i %i\n", _Processed, _UnProcessed );
	FreePolicy_Processed = _Processed;
	FreePolicy_UnProcessed = _UnProcessed;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void GelTexture::Bind( const int /*Channel*/ ) {
	// TODO: Use Channel //
	
	glBindTexture( GL_TEXTURE_2D, Handle );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
bool GelTexture::Process() {
	// Bail successfully if the data is already processed. //
	if ( Processed.Data != 0 )
		return true;
	
	// Fail if there is no UnProcessed Data //
	if ( UnProcessed.Data == 0 )
		return false;
	
/*	
	// File Headers //
	const char LZMA_HEADER[] = { 0x5D, 0x0, 0x0, 0x80, 0x0 };
	
	// Figure out what type of file it is //
	if ( compare_String( LZMA_HEADER, UnProcessed.Data->Data, 4 ) ) {
		// Note the Asset Type //
		UnProcessed.AssetType = GEL_ASSET_LZMA;
		
		Log("* Data is LZMA Compressed. Decompressing...\n" );
		
		Processed.Data = unpack_LZMA_DataBlock( Compressed );
		Processed.AssetType = GEL_
	}
	else {
		Log("* ERROR! Unknown Texture Format!\n" );
		return false;
	}
*/	
	return Processed.Data != 0;
}
// - ------------------------------------------------------------------------------------------ - //
bool GelTexture::Cache( DataBlock* InData ) {
	// If we get an explicity DataBlock, we should dispose of our data //
	Free();
	
	// Set the DataBlock. **I AM NOW MANAGING THIS DATA** //
	UnProcessed.Data = InData;

	// If the data

	
	// Process the texture, setting up the Processed pointer //
	bool Error = Process();
	
	// Run the Free Policy //
	FreePolicy();
	
	return Error;
}
// - ------------------------------------------------------------------------------------------ - //
bool GelTexture::Cache( const char* FileName ) {
	DataBlock* InData = new_read_DataBlock( FileName );

	if ( InData == 0 ) {
		Log( "* ERROR! Unable to load \"%s\"\n", FileName );
		return false;
	}
		
	return Cache( InData );
}
// - ------------------------------------------------------------------------------------------ - //
// Load Data in to VRAM. 
bool GelTexture::Load() {
	Process();
	
	
}
// - ------------------------------------------------------------------------------------------ - //
// The DataBlock version is the primary, as eventually an Async reader may replace the game's //
// regular use of the load function may
bool GelTexture::Load( DataBlock* InData ) {
	Cache( InData );
	
	Load();
	
	return true;
}
// - ------------------------------------------------------------------------------------------ - //
bool GelTexture::Load( const char* FileName ) {
	DataBlock* InData = new_read_DataBlock( FileName );

	if ( InData == 0 ) {
		Log( "* ERROR! Unable to load \"%s\"\n", FileName );
		return false;
	}	
	return Load( InData );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void GelTexture::FreeUnProcessed() {
	if ( UnProcessed.Data ) {
		delete_DataBlock( UnProcessed.Data );
		
		UnProcessed.AssetType = GEL_ASSET_NULL;
		UnProcessed.Data = 0;
	}
}
// - ------------------------------------------------------------------------------------------ - //
void GelTexture::FreeProcessed() {
	if ( Processed.Data ) {
		delete_DataBlock( Processed.Data );

		Processed.AssetType = GEL_ASSET_NULL;
		Processed.Data = 0;
	}
}
// - ------------------------------------------------------------------------------------------ - //
void GelTexture::FreeHandle() {
	// If we have have a Handle to VRAM //
	if ( Handle ) {
//		TexturePool::AllocCount--;
//		TexturePool::AllocSum -= Handle;

		Log( "* GL Texture %i Free'd\n", Handle );
		glDeleteTextures( 1, (const GLuint*)&Handle );
		
		Handle = 0;
	}	
}
// - ------------------------------------------------------------------------------------------ - //
void GelTexture::Free() {
	FreeUnProcessed();
	FreeProcessed();	
	FreeHandle();
}
// - ------------------------------------------------------------------------------------------ - //
// Execute the "Free Policy", post Load or Cache //
void GelTexture::FreePolicy() {
	if ( FreePolicy_UnProcessed ) {
		if ( UnProcessed.SharesData ) {
			// Data sharing means the implementation is usable as-is, so the data is linked to //
			// instead of seperately allocated and copied. //
			if ( FreePolicy_Processed ) {
				// No Error, because both are freed //
				FreeUnProcessed();
			}
			else {
				Log( "* ERROR! This File Format shares data with Processed!\n" );
			}
		}
		else {
			// Free the data, only if a share is not made //
			FreeUnProcessed();
		}
	}
	
	if ( FreePolicy_Processed )
		FreeProcessed();
}
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_OPENGL //
// - ------------------------------------------------------------------------------------------ - //
