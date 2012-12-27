// - ------------------------------------------------------------------------------------------ - //
// TODO: Don't just add one version of a file to AssetLookup, but one per directory. It is just
//   an Index, so it wont be too too expensive, just an extra entry per file per subdirectory.
//   The total files in the content file system don't tend to be that many, so lets say about
//   ~100 bytes per file more (on average). PROTIP: Set the content folder to limit redundants.
//   Also, be sure to discard any attempts to add a symbol that already exists. FIFO.
//   Content/Art, Content/Scripts, etc. Do all these explicitly, so to disregard "Tools"
// - ------------------------------------------------------------------------------------------ - //
#include <map>
#include <vector>
#include <string>
// - ------------------------------------------------------------------------------------------ - //
#include "Search.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Style/Style.h>

#include <Core/GelFileInfo.h>
#include <Core/GelDirectory.h>
#include <Util/String/String.h>		// TODO: Promote from Util //
// - ------------------------------------------------------------------------------------------ - //
#include <System/System.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Search {
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
std::string FilePrefix;	
std::vector< cAssetInfo > AssetInfo;
std::map< std::string, SearchHandle > AssetLookup;
// - ------------------------------------------------------------------------------------------ - //
void Init( const char* BaseDirectory ) {
	atexit( Exit );
	
	// If an empty string (i.e. first character is terminator) //
	if ( BaseDirectory[0] == 0 )
		FilePrefix = System::BaseDir;
	else
		FilePrefix = std::string( System::BaseDir ) + BaseDirectory;

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

// - -------------------------------------------------------------------------------------- - //
const SearchHandle FindHandle( const char* FileName ) {
	// Search the map for the specific pattern //
	std::map<std::string, SearchHandle>::iterator SearchIterator = AssetLookup.find( FileName );
	VLog( "* Searching for %s...", FileName );
	
	// If it was found, return the Id //
	if ( SearchIterator != AssetLookup.end() ) {
		VLog( "* %s found in lookup cache!", FileName );
		return SearchIterator->second;
	}

	// Linear pattern matching search (if it contains the pattern, instead of exact match) //
	for ( size_t idx = 0; idx < AssetInfo.size(); idx++ ) {
		// Linear test strings if they contain the pattern passed //
		if ( AssetInfo[idx].FileName.find( FileName ) != std::string::npos ) {
			VLog( "* Found %s!", FileName );
			return idx;
		}
	}
	Log( "* %s NOT FOUND!!", FileName );
	
	// Otherwise, no file was found.  Return the dummy Id (0). //
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
const cAssetInfo& GetHandle( const SearchHandle Handle ) {
	// TODO: Asserts
	return AssetInfo[ Handle ];
}
// - ------------------------------------------------------------------------------------------ - //
const char* Search( const char* FileName ) {
	// TODO: If threadlocal unsupported, use a mutex, and add a direct verison (_Search) w/o. //
	static threadlocal char Text[4096];
	
	const cAssetInfo& Info = GetHandle( FindHandle( FileName ) );
	
	safe_sprintf( Text, sizeof(Text), "%s%s", FilePrefix.c_str(), Info.FileName.c_str() );
	
	return Text;
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Search //
// - ------------------------------------------------------------------------------------------ - //
