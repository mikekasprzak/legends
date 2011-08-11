// - ------------------------------------------------------------------------------------------ - //
#include "GelAsset.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Core/GelString_Core.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/Texture/PVRTexture.h>
#include <Graphics/Texture/STBTexture.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
const char LZMA_FILE_HEADER[] = { 0x5D, 0x0, 0x0, 0x80 };

GelAsset_T is_Compression_Data_GelAsset( const char* InData ) {
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

GelAsset_T is_Texture_Data_GelAsset( const char* InData ) {
	if ( IsPVR( InData ) ) {
		return (GelAsset_T)(GEL_ASSET_PVR | GEL_ASSET_HAS_INFO);
	}
	else if ( IsSTB( InData ) ) {
		return (GelAsset_T)(GEL_ASSET_STB_IMAGE | GEL_ASSET_HAS_INFO);
	}
	else if ( compare_String( PNG_FILE_HEADER, &(InData[0]), 4 ) ) {
		return (GelAsset_T)(GEL_ASSET_PNG | GEL_ASSET_HAS_INFO);
	}
	else {
		return GEL_ASSET_NULL;
	}
}
// - ------------------------------------------------------------------------------------------ - //
GelAsset_T is_Model_Data_GelAsset( const char* InData ) {
	return GEL_ASSET_NULL;
}
// - ------------------------------------------------------------------------------------------ - //
GelAsset_T is_Audio_Data_GelAsset( const char* InData ) {
	return GEL_ASSET_NULL;
}
// - ------------------------------------------------------------------------------------------ - //
GelAsset_T is_Text_Data_GelAsset( const char* InData ) {
	// NOTE: Text formats can only be detected from filenames. //
	return GEL_ASSET_NULL;
}
// - ------------------------------------------------------------------------------------------ - //
GelAsset_T is_Script_Data_GelAsset( const char* InData ) {
	GelAsset_T Out = is_Text_Data_GelAsset( InData );
	if ( ((Out & GEL_ASSET_TYPE_MASK) >= GEL_ASSET_SCRIPT_BASE) && ((Out & GEL_ASSET_TYPE_MASK) <= GEL_ASSET_SCRIPT_MAX) ) {
		return Out;
	}
	else {
		return GEL_ASSET_NULL;
	}
}
// - ------------------------------------------------------------------------------------------ - //
GelAsset_T is_Shader_Data_GelAsset( const char* InData ) {
	GelAsset_T Out = is_Text_Data_GelAsset( InData );
	if ( ((Out & GEL_ASSET_TYPE_MASK) >= GEL_ASSET_SHADER_BASE) && ((Out & GEL_ASSET_TYPE_MASK) <= GEL_ASSET_SHADER_MAX) ) {
		return Out;
	}
	else {
		return GEL_ASSET_NULL;
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
GelAsset_T is_Data_GelAsset( const char* InData ) {
	GelAsset_T Type = is_Compression_Data_GelAsset( InData );
	if ( Type != GEL_ASSET_NULL )
		return Type;

	Type = is_Texture_Data_GelAsset( InData );
	if ( Type != GEL_ASSET_NULL )
		return Type;

	Type = is_Model_Data_GelAsset( InData );
	if ( Type != GEL_ASSET_NULL )
		return Type;

	Type = is_Audio_Data_GelAsset( InData );
	if ( Type != GEL_ASSET_NULL )
		return Type;

	Type = is_Text_Data_GelAsset( InData );
	if ( Type != GEL_ASSET_NULL )
		return Type;
	
	return GEL_ASSET_UNKNOWN;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
GelAsset_T is_Compression_Name_GelAsset( const char* FileName ) {
	if ( find_String( ".lzma", FileName ) ) {
		return GEL_ASSET_LZMA;
	}
	else if ( find_String( ".gz", FileName ) ) {
		return GEL_ASSET_ZLIB;
	}
	else if ( find_String( ".bz2", FileName ) ) {
		return GEL_ASSET_BZIP2;
	}
	else {
		return GEL_ASSET_NULL;
	}
}
// - ------------------------------------------------------------------------------------------ - //
GelAsset_T is_Texture_Name_GelAsset( const char* FileName ) {
	if ( find_String( ".png", FileName ) ) {
		return GEL_ASSET_PNG;
	}
	else if ( find_String( ".dxt", FileName ) ) {
		return GEL_ASSET_DXT;
	}
	else if ( find_String( ".pvr", FileName ) ) {
		return GEL_ASSET_PVR;
	}
	else if ( find_String( ".tga", FileName ) ) {
		return GEL_ASSET_TGA;
	}
	else if ( find_String( ".psd", FileName ) ) {
		return GEL_ASSET_PSD;
	}
	else {
		return GEL_ASSET_NULL;
	}
}
// - ------------------------------------------------------------------------------------------ - //
GelAsset_T is_Model_Name_GelAsset( const char* FileName ) {
	if ( find_String( ".pme", FileName ) ) {
		return GEL_ASSET_PME;
	}
	else if ( find_String( ".blend", FileName ) ) {
		return GEL_ASSET_BLENDER;
	}
	else if ( find_String( ".wings", FileName ) ) {
		return GEL_ASSET_WINGS;
	}
	else if ( find_String( ".3ds", FileName ) ) {
		return GEL_ASSET_3DS;
	}
	else if ( find_String( ".obj", FileName ) ) {
		return GEL_ASSET_OBJ;
	}
	else if ( find_String( ".mtl", FileName ) ) {
		return GEL_ASSET_MTL;
	}
	else {
		return GEL_ASSET_NULL;
	}
}
// - ------------------------------------------------------------------------------------------ - //
GelAsset_T is_Audio_Name_GelAsset( const char* FileName ) {
	if ( find_String( ".wav", FileName ) ) {
		return GEL_ASSET_WAV;
	}
	else if ( find_String( ".ogg", FileName ) ) {
		return GEL_ASSET_OGG;
	}
	else if ( find_String( ".mp3", FileName ) ) {
		return GEL_ASSET_MP3;
	}
	else if ( find_String( ".aac", FileName ) ) {
		return GEL_ASSET_AAC;
	}
	else {
		return GEL_ASSET_NULL;
	}
}
// - ------------------------------------------------------------------------------------------ - //
GelAsset_T is_Text_Name_GelAsset( const char* FileName ) {
	// NOTE: Text formats can only be detected from filenames. //
	if ( find_String( ".txt", FileName ) ) {
		return GEL_ASSET_TXT;
	}
	else if ( find_String( ".xml", FileName ) ) {
		return GEL_ASSET_XML;
	}
	else if ( find_String( ".json", FileName ) ) {
		return GEL_ASSET_JSON;
	}
	else if ( find_String( ".csv", FileName ) ) {
		return GEL_ASSET_CSV;
	}
	else if ( find_String( ".nut", FileName ) ) {
		return GEL_ASSET_SQUIRREL;
	}
	else if ( find_String( ".cnut", FileName ) ) {
		return GEL_ASSET_SQUIRREL_COMPILED;
	}
	else if ( find_String( ".lua", FileName ) ) {
		return GEL_ASSET_LUA;
	}
	else if ( find_String( ".py", FileName ) ) {
		return GEL_ASSET_PYTHON;
	}
	else if ( find_String( ".c", FileName ) ) {
		return GEL_ASSET_C;
	}
	else if ( find_String( ".cpp", FileName ) ) {
		return GEL_ASSET_C_PLUS_PLUS;
	}
	else if ( find_String( ".h", FileName ) ) {
		return GEL_ASSET_C_HEADER;
	}
	else if ( find_String( ".hpp", FileName ) ) {
		return GEL_ASSET_C_PLUS_PLUS_HEADER;
	}
	else if ( find_String( ".glvs", FileName ) ) {
		return GEL_ASSET_GLSL_VERTEX_PROGRAM;
	}
	else if ( find_String( ".glfs", FileName ) ) {
		return GEL_ASSET_GLSL_FRAGMENT_PROGRAM;
	}
	else if ( find_String( ".glgs", FileName ) ) {
		return GEL_ASSET_GLSL_GEOMETRY_PROGRAM;
	}
	else if ( find_String( ".glsl", FileName ) ) {
		return GEL_ASSET_GLSL_PROGRAM;
	}
	else if ( find_String( ".fx", FileName ) ) {
		return GEL_ASSET_HLSL_PROGRAM;
	}
	else if ( find_String( ".cgfx", FileName ) ) {
		return GEL_ASSET_CG_PROGRAM;
	}
	else if ( find_String( ".cg", FileName ) ) {
		return GEL_ASSET_CG_PROGRAM;
	}
	else {
		return GEL_ASSET_NULL;
	}
}
// - ------------------------------------------------------------------------------------------ - //
GelAsset_T is_Script_Name_GelAsset( const char* FileName ) {
	GelAsset_T Out = is_Text_Name_GelAsset( FileName );
	if ( ((Out & GEL_ASSET_TYPE_MASK) >= GEL_ASSET_SCRIPT_BASE) && ((Out & GEL_ASSET_TYPE_MASK) <= GEL_ASSET_SCRIPT_MAX) ) {
		return Out;
	}
	else {
		return GEL_ASSET_NULL;
	}
}
// - ------------------------------------------------------------------------------------------ - //
GelAsset_T is_Shader_Name_GelAsset( const char* FileName ) {
	GelAsset_T Out = is_Text_Name_GelAsset( FileName );
	if ( ((Out & GEL_ASSET_TYPE_MASK) >= GEL_ASSET_SHADER_BASE) && ((Out & GEL_ASSET_TYPE_MASK) <= GEL_ASSET_SHADER_MAX) ) {
		return Out;
	}
	else {
		return GEL_ASSET_NULL;
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
GelAsset_T is_Name_GelAsset( const char* FileName ) {
	GelAsset_T Type = GEL_ASSET_NULL;
	
	Type = is_Texture_Name_GelAsset( FileName );
	if ( Type != GEL_ASSET_NULL )
		return Type;

	Type = is_Model_Name_GelAsset( FileName );
	if ( Type != GEL_ASSET_NULL )
		return Type;

	Type = is_Audio_Name_GelAsset( FileName );
	if ( Type != GEL_ASSET_NULL )
		return Type;

	Type = is_Text_Name_GelAsset( FileName );
	if ( Type != GEL_ASSET_NULL )
		return Type;

	// Check if a compression last, as I will often combine formats //
	Type = is_Compression_Name_GelAsset( FileName );
	if ( Type != GEL_ASSET_NULL )
		return Type;
	
	return GEL_ASSET_UNKNOWN;
}
// - ------------------------------------------------------------------------------------------ - //
