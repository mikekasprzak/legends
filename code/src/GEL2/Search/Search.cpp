// - ------------------------------------------------------------------------------------------ - //
#include <map>
#include <vector>
#include <string>
// - ------------------------------------------------------------------------------------------ - //
#include "Search.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Core/GelFileInfo.h>
#include <Core/GelDirectory.h>
#include <Util/String/String.h>
// - ------------------------------------------------------------------------------------------ - //
// Up here, so this isn't considered part of the namespace //
extern char AppBaseDir[];
// - ------------------------------------------------------------------------------------------ - //
namespace Search {
// - ------------------------------------------------------------------------------------------ - //
std::string FilePrefix;	
std::vector< cAssetInfo > AssetInfo;
std::map< std::string, SearchHandle > AssetLookup;
// - ------------------------------------------------------------------------------------------ - //
void Init( const char* BaseDirectory ) {		
	// If an empty string (i.e. first character is terminator) //
	if ( BaseDirectory[0] == 0 )
		FilePrefix = AppBaseDir;
	else
		FilePrefix = std::string( AppBaseDir ) + BaseDirectory;

	// Store the prefix (without trailing slash.  Slash will be part of search strings) //

	Log( "Search::FilePrefix: %s", FilePrefix.c_str() );
	
	// Initalize the AssetInstance //
	AssetInfo.clear();
	AssetInfo.push_back( cAssetInfo() );	// Dummy (0) //
	
	// Initalize the AssetLookup //
	AssetLookup.clear();
}
// - ------------------------------------------------------------------------------------------ - //
void Exit() {
}
// - ------------------------------------------------------------------------------------------ - //
// TODO: Be sure to include a beginning "/" in the populated filenames //
// TODO: Be sure to remove file extensions in the search query //
void AddDirectory( const char* Directory ) {
	std::string ReadDir = FilePrefix;
	if ( Directory[0] != 0 ) {
		ReadDir += Directory;
	}
	//ReadDir += String::Slash;
	
	{
		// TODO: Make this a less dumb structure (i.e. calling Test) //
		GelFileInfo FileInfo( ReadDir.c_str() );
		
//		struct stat st;
//		if( stat( ReadDir.c_str(), &st ) != 0 ) {
		if ( FileInfo.Exists() ) {
			Log( "* Asset Directory \"%s\" not found!", ReadDir.c_str() );
			return;
		}
	}
	
	GelDirectory* Dir = new_GelDirectory( ReadDir.c_str() );
	Log( "+ Adding Asset Directory \"%s\" (%i Files)", ReadDir.c_str(), size_GelDirectory( Dir ) );
	
	for( size_t idx = 0; idx < size_GelDirectory( Dir ); idx++ ) {
		std::string SlashString = String::Slash;
		SlashString += index_GelDirectory( Dir, idx );
		AssetInfo.push_back( cAssetInfo( (std::string(Directory) + SlashString).c_str() ) );
		
		std::string NoExt = String::NoExtensions( SlashString );
		AssetLookup[ NoExt.c_str() ] = AssetInfo.size() - 1;
		
		VVLog( "* %s [%s] (%i)", SlashString.c_str(), NoExt.c_str(), idx );
	}
	
	delete_GelDirectory( Dir );
	
	Log( "- Asset Directory added." );
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Search //
// - ------------------------------------------------------------------------------------------ - //
