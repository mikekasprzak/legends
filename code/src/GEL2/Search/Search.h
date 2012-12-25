// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL2_SEARCH_SEARCH_H__
#define __GEL2_SEARCH_SEARCH_H__
// - ------------------------------------------------------------------------------------------ - //
// Finding files in Content and UserContent folders is now handled by a general Search Library
// - ------------------------------------------------------------------------------------------ - //
#include <Core/GelFileInfo.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Search {
// - ------------------------------------------------------------------------------------------ - //
typedef unsigned int SearchHandle;
// - ------------------------------------------------------------------------------------------ - //
enum eAssetClass {
	ASSETCLASS_NULL = 0,
	ASSETCLASS_TEXTURE = 1,
	ASSETCLASS_MESH,
	ASSETCLASS_AUDIO,
	ASSETCLASS_SCRIPT,
	ASSETCLASS_SHADER,
	ASSETCLASS_TEXT,
};
// - ------------------------------------------------------------------------------------------ - //
class cAssetInfo {
public:
	std::string FileName;
	GelFileInfo FileInfo;
	eAssetClass Type;					// Based on FileName only //

//	DataBlock* UnProcessed;
//
//	union {
//		GelTexture* Texture;
//		cPMEFile* Mesh;
//		DataBlock* Data;
//	};
public:
	inline cAssetInfo() {	
	}
	
	inline cAssetInfo( const char* _FileName ) :
		FileName( _FileName ),
		FileInfo( _FileName )
	{
		// TODO: Lookup the Type 
	}
};
// - ------------------------------------------------------------------------------------------ - //
void Init( const char* BaseDirectory );
void Exit();
void AddDirectory( const char* Directory );
const SearchHandle FindHandle( const char* FileName );
const cAssetInfo& GetHandle( const SearchHandle Handle );
const char* Find( const char* FileName );
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Search //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL2_SEARCH_SEARCH_H__ //
// - ------------------------------------------------------------------------------------------ - //
