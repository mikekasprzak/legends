// - ------------------------------------------------------------------------------------------ - //
#include "GelAsset.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Core/GelString_Core.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/Texture/PVRTexture.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
const char LZMA_FILE_HEADER[] = { 0x5D, 0x0, 0x0, 0x80 };

GelAsset_T is_Compression_GelAsset( const char* InData ) {
	// TODO: Verify there's enough data space to determine file format //
	// EDIT: No. Changed this from DataBlock to char* //
	
	if ( compare_String( LZMA_FILE_HEADER, &(InData[0]), 4 ) ) {
		return GEL_ASSET_LZMA;
	}
	else {
		return GEL_ASSET_NULL;
	}
}
// - ------------------------------------------------------------------------------------------ - //
const char PNG_FILE_HEADER[] = { 0x89, 'P', 'N', 'G' };

GelAsset_T is_Texture_GelAsset( const char* InData ) {
	if ( IsPVR( InData ) ) {
		return (GelAsset_T)(GEL_ASSET_PVR | GEL_ASSET_HAS_INFO);
	}
	else if ( compare_String( PNG_FILE_HEADER, &(InData[0]), 4 ) ) {
		return (GelAsset_T)(GEL_ASSET_PNG | GEL_ASSET_HAS_INFO);
	}
	else {
		return GEL_ASSET_NULL;
	}
}
// - ------------------------------------------------------------------------------------------ - //
GelAsset_T is_Model_GelAsset( const char* InData ) {
	return GEL_ASSET_NULL;
}
// - ------------------------------------------------------------------------------------------ - //
GelAsset_T is_Audio_GelAsset( const char* InData ) {
	return GEL_ASSET_NULL;
}
// - ------------------------------------------------------------------------------------------ - //
GelAsset_T is_Text_GelAsset( const char* InData ) {
	// NOTE: Text formats can only be detected from filenames. //
	return GEL_ASSET_NULL;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
GelAsset_T is_GelAsset( const char* InData ) {
	GelAsset_T Type = is_Compression_GelAsset( InData );
	if ( Type != GEL_ASSET_NULL )
		return Type;

	Type = is_Texture_GelAsset( InData );
	if ( Type != GEL_ASSET_NULL )
		return Type;

	Type = is_Model_GelAsset( InData );
	if ( Type != GEL_ASSET_NULL )
		return Type;

	Type = is_Audio_GelAsset( InData );
	if ( Type != GEL_ASSET_NULL )
		return Type;

	Type = is_Text_GelAsset( InData );
	if ( Type != GEL_ASSET_NULL )
		return Type;
	
	return GEL_ASSET_RAW;	
}
// - ------------------------------------------------------------------------------------------ - //
