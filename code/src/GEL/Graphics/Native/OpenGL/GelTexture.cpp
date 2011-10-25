// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL) || defined(USES_OPENGLES)
// - ------------------------------------------------------------------------------------------ - //
#include <Debug/GelDebug.h>

#include <Graphics/Graphics.h>
#include <Graphics/GelTexture.h>

#include <Core/DataBlock.h>
#include <Core/DataBlock_LZMA.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/Texture/PVRTexture_Load.h>
#include <Graphics/Texture/STBTexture_Load.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
bool GelTexture::FreePolicy_Processed = false;
bool GelTexture::FreePolicy_UnProcessed = false;
int GelTexture::AllocCount = 0;
int GelTexture::AllocSum = 0;
// - ------------------------------------------------------------------------------------------ - //
void GelTexture::Init( const bool _Processed, const bool _UnProcessed ) {
	AllocCount = 0;
	AllocSum = 0;
	SetFreePolicy( _Processed, _UnProcessed );
}
// - ------------------------------------------------------------------------------------------ - //
void GelTexture::LogAllocations() {
	VVLog( "> GelTextures GL Allocations: %i  Sum: %i", AllocCount, AllocSum );	
}
// - ------------------------------------------------------------------------------------------ - //
void GelTexture::Exit( ) {
	LogAllocations();
	
	if ( AllocCount != 0 ) {
		ELog( "GL ALLOCATION MISSMATCHED!!" );
	}
	
	if ( AllocSum != 0 ) {
		ELog( "GL ALLOCATION SUM MISSMATCHED!!" );
	}
}
// - ------------------------------------------------------------------------------------------ - //
void GelTexture::SetFreePolicy( const bool _Processed, const bool _UnProcessed ) {
	Log("* Free Policy set: %i %i", _Processed, _UnProcessed );
	FreePolicy_Processed = _Processed;
	FreePolicy_UnProcessed = _UnProcessed;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void GelTexture::Bind( const int /*Channel*/ ) {
	// TODO: Assert //
	if ( this == 0 )
		return;
	
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

	UnProcessed.Asset.BitMask = is_Data_GelAsset( UnProcessed.Data->Data );
	
	bool ProcessNextSection = true;
	
	switch ( UnProcessed.Asset.Type ) {
		case GEL_ASSET_LZMA: {
			Processed.Data = new_unpack_LZMA_DataBlock( UnProcessed.Data );
			break;
		}
		case GEL_ASSET_STB_IMAGE:
		case GEL_ASSET_PVR:
		{
			// Cheat! Move data over to processed, 'cause I am lazy! //
			Processed.Data = UnProcessed.Data;
			Processed.Asset.BitMask = UnProcessed.Asset.BitMask;
			
			UnProcessed.Data = 0;
			UnProcessed.Asset.BitMask = GEL_ASSET_NULL;
			
			ProcessNextSection = false;
			break;
		}
		default: {
			ELog("Unknown Asset Format!" );
			return false;
			break;
		}
	};
	
	if ( ProcessNextSection ) {
		Processed.Asset.BitMask = is_Data_GelAsset( Processed.Data->Data );
	}
	
	return Processed.Data != 0;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Load Data in to VRAM. 
bool GelTexture::Load() {
	bool ValidData = Process();
	if ( !ValidData )
		return false;
	
	// Load in to VRAM //
	switch ( Processed.Asset.Type ) {
		case GEL_ASSET_PVR: {
			load_PVRTexture( this );
			break;
		}
		case GEL_ASSET_STB_IMAGE: {
			load_STBTexture( this );
			break;
		}
		default: {
			ELog( "Unknown Asset Format (%i)!", Processed.Asset.Type );
			return false;
			break;
		}
	};
		
	// Increment the internal counting //
	AllocCount++;
	AllocSum += Handle;

	// Run the Free Policy //
	FreePolicy();
	
	return ValidData;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
bool GelTexture::Cache( DataBlock* InData ) {
	// TODO: Assert //
	if ( this == 0 ) {
		ELog( "Null pointer GelTexture" );
		return false;
	}
		
	if ( InData == 0 ) {
		ELog( "Null pointer DataBlock" );
		return false;
	}
	
	// If we get an explicity DataBlock, we should dispose of our data //
	Free();
	
	// Set the DataBlock. **I AM NOW MANAGING THIS DATA** //
	UnProcessed.Data = InData;
	
	// Process the texture, setting up the Processed pointer //
	bool ValidData = Process();
	
	// Run the Free Policy //
	FreePolicy();
	
	return ValidData;
}
// - ------------------------------------------------------------------------------------------ - //
bool GelTexture::Cache( const char* FileName ) {
	DataBlock* InData = new_read_DataBlock( FileName );

	if ( InData == 0 ) {
		ELog( "Unable to load \"%s\"", FileName );
		return false;
	}
		
	return Cache( InData );
}
// - ------------------------------------------------------------------------------------------ - //
// The DataBlock version is the primary, as eventually an Async reader may replace the game's //
// regular use of the load function may
bool GelTexture::Load( DataBlock* InData ) {
	bool ValidData = Cache( InData );
	
	if ( !ValidData )
		return ValidData;
		
	return Load();
}
// - ------------------------------------------------------------------------------------------ - //
bool GelTexture::Load( const char* FileName ) {
	Log( "* Reading file \"%s\"...", FileName );
	DataBlock* InData = new_read_DataBlock( FileName );

	if ( InData == 0 ) {
		ELog( "Unable to Read \"%s\"!!", FileName );
		return false;
	}
		
	return Load( InData );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void GelTexture::FreeUnProcessed() {
	if ( UnProcessed.Data ) {
		delete_DataBlock( UnProcessed.Data );
		
		UnProcessed.Asset.BitMask = GEL_ASSET_NULL;
		UnProcessed.Data = 0;
	}
}
// - ------------------------------------------------------------------------------------------ - //
void GelTexture::FreeProcessed() {
	if ( Processed.Data ) {
		if ( !Processed.Asset.IsProxy )	
			delete_DataBlock( Processed.Data );

		Processed.Asset.BitMask = GEL_ASSET_NULL;
		Processed.Data = 0;
	}
}
// - ------------------------------------------------------------------------------------------ - //
void GelTexture::FreeHandle() {
	// If we have have a Handle to VRAM //
	if ( Handle ) {
		// Debug Information, Reference Counting //
		AllocCount--;
		AllocSum -= Handle;

		_VVLog( "* GL Tex (%i) ", Handle );
		glDeleteTextures( 1, (const GLuint*)&Handle );
		
		Handle = 0;
	}	
}
// - ------------------------------------------------------------------------------------------ - //
void GelTexture::Free() {
	if ( this ) {
		FreeUnProcessed();
		FreeProcessed();	
		FreeHandle();
	}
}
// - ------------------------------------------------------------------------------------------ - //
// Execute the "Free Policy", post Load or Cache //
void GelTexture::FreePolicy() {
	if ( this == 0 )
		return;
		
	if ( FreePolicy_UnProcessed ) {
		if ( UnProcessed.Asset.IsShare ) {
			// Data sharing means the implementation is usable as-is, so the data is linked to //
			// instead of seperately allocated and copied. //
			if ( FreePolicy_Processed ) {
				// No Error, because both are freed //
				FreeUnProcessed();
			}
			else {
				ELog( "This File Format shares data with Processed!" );
			}
		}
		else {
			// Free the data, only if a share is not made //
			FreeUnProcessed();
		}
	}
	
	if ( FreePolicy_Processed ) {
		if ( !Processed.Asset.IsProxy ) {
			FreeProcessed();
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_OPENGL //
// - ------------------------------------------------------------------------------------------ - //
