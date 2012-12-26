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
void Init( const char* BaseDirectory = "" );
void Exit();										// No need to call //
void AddDirectory( const char* Directory );
const char* Search( const char* FileName );
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Search //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL2_SEARCH_SEARCH_H__ //
// - ------------------------------------------------------------------------------------------ - //
