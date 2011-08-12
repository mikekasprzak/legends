// - ------------------------------------------------------------------------------------------ - //
// GelDirectory - File Name tree cataloging library //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_GelDirectory_Core_H__
#define __Library_Data_GelDirectory_Core_H__
// - ------------------------------------------------------------------------------------------ - //
#include "GelString_Core.h"
#include "GelString_File.h"
#include "GelHeap_Core.h"
#include "GelHeap_File.h"

#include "GelFileInfo.h"
// - ------------------------------------------------------------------------------------------ - //
// Directories are lists of file names.  They can be populated manually, or be polled from disk
//   and other sources.  The next step up from a Directory is an Archive, which contains data too.
//
// TODO: When indexing a string, consider attaching the name (BaseName/) to the front.
// TODO: Searching for a file (given a pattern to match)
// TODO: Saving and loading Directories to and from disk/streams. (Need FILE* library)
// - ------------------------------------------------------------------------------------------ - //
struct GelDirectory {
	// The given Base GelDirectory name (include the trailing backslash .. ?) //
	char* BaseName;
	// A GelHeap of filenames //
	GelHeap* FileName;
	
	GelArray<GelFileInfo>* FileInfo;
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline const size_t add_GelDirectory( GelDirectory* p, const char* _String, const GelFileInfo* _FileInfo ) {
	size_t StringLength = length_String( _String ) + 1;
	
	Log( "Mem: 0x%x  0x%x\n", _FileInfo, *_FileInfo );
	pushback_GelArray<GelFileInfo>( &p->FileInfo, *_FileInfo );
	
	return allocate_GelHeap( p->FileName, _String, StringLength );
}
// - ------------------------------------------------------------------------------------------ - //
//inline const size_t add_GelDirectory( GelDirectory* p, const char* _String ) {
//	size_t StringLength = length_String( _String ) + 1;
//		
//	return allocate_GelHeap( p->FileName, _String, StringLength );
//}
// - ------------------------------------------------------------------------------------------ - //
inline const size_t size_GelDirectory( const GelDirectory* p ) {
	return size_GelHeap( p->FileName );
}
// - ------------------------------------------------------------------------------------------ - //
inline const char* index_GelDirectory( const GelDirectory* p, const size_t Index ) { 
	return index_GelHeap( p->FileName, Index );
}
// - ------------------------------------------------------------------------------------------ - //
inline const GelFileInfo& info_GelDirectory( const GelDirectory* p, const size_t Index ) { 
	return index_GelArray<GelFileInfo>( p->FileInfo, Index );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Create a dummy empty File Name list //
inline GelDirectory* new_GelDirectory() {
	GelDirectory* NewDir = new GelDirectory;
	
	// Create and initalize an empty name string //
	NewDir->BaseName = new_String("");
	
	NewDir->FileName = new_GelHeap(0, 0);
	
	NewDir->FileInfo = new_GelArray<GelFileInfo>( 0 );
	
	return NewDir;
}
// - ------------------------------------------------------------------------------------------ - //
inline void delete_GelDirectory( GelDirectory* p ) {
	if ( p->BaseName )
		delete [] p->BaseName;
		
	if ( p->FileName )
		delete_GelHeap( p->FileName );
	
	if ( p->FileInfo )
		delete_GelArray( p->FileInfo );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Create a GelDirectory from an existing GelDirectory, by pattern matching //
inline GelDirectory* new_GelDirectory( GelDirectory* p, const char* Pattern ) {
	GelDirectory* NewDir = new_GelDirectory();
	delete_String( NewDir->BaseName );
	NewDir->BaseName = new_String( p->BaseName );
	
	for (size_t idx = 0; idx < size_GelDirectory( p ); idx++ ) {
		if ( find_String( Pattern, index_GelDirectory( p, idx ) ) )
			add_GelDirectory( NewDir, index_GelDirectory( p, idx ), &info_GelDirectory( p, idx ) );
	}
	
	return NewDir;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_GelDirectory_Core_H__ //
// - ------------------------------------------------------------------------------------------ - //
