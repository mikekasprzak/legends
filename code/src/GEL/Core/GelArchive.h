// - ------------------------------------------------------------------------------------------ - //
// GelArchive - File Name tree cataloging library //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_GelArchive_H__
#define __Library_Data_GelArchive_H__
// - ------------------------------------------------------------------------------------------ - //
#include <string.h>
#include <stdio.h>

#include <Core/GelArray.h>
#include "GelHeap.h"
// - ------------------------------------------------------------------------------------------ - //
// Archives are lists of file names with Data.  They can be populated manually, or be polled from
//   disk and other sources.
//
// Unfortunately, for archives to work, we need either array of DataBlock pointers, or GelHeap 
//   insert/deletes.
// - ------------------------------------------------------------------------------------------ - //
//namespace Data {
// - ------------------------------------------------------------------------------------------ - //
struct GelArchive {
	// The given Base Archive name (include the trailing backslash .. ?) //
	char* Name;
	// A GelHeap of filenames //
	GelHeap* FileName;
	// A GelHeap of Data (DataBlocks?) //
	//GelHeap* Data;
	GelArray<DataBlock*> Data;
};
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// Create a dummy empty GelArchive //
inline GelArchive* new_GelArchive() {
	GelArchive* NewDir = new GelArchive;
	
	// Create and initalize an empty name string //
	NewDir->Name = new char[ 1 ];
	NewDir->Name[0] = 0;
	
	NewDir->FileName = new_GelHeap();
	
	return NewDir;
}
// - ------------------------------------------------------------------------------------------ - //
inline GelArchive* new_GelArchive( const char* _BaseName ) {
	GelArchive* NewGelArchive = new GelArchive;
	
	size_t NameLength = strlen(_BaseName);
	
	NewGelArchive->Name = new char[NameLength];
	copy_Data( _BaseName, NewGelArchive->Name, NameLength );
	
	// Allocate an empty FileName table //
	NewGelArchive->FileName = new_GelHeap();
	
	// Allocate an empty Data table //
	NewGelArchive->Data = new_GelHeap();
	
	// Work //
	
	return NewGelArchive;
}
// - ------------------------------------------------------------------------------------------ - //
inline void delete_GelArchive( GelArchive* p ) {
	if ( p->Name )
		delete [] p->Name;
	if ( p->FileName )
		delete_GelHeap( p->FileName );
	if ( p->Data )
		delete_GelHeap( p->Data );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
//inline void add_GelArchive( GelArchive* p, char* _String ) {
//	size_t StringLength = strlen( _String );
//	
//	size_t Index = allocate_GelHeap( p->FileName, StringLength );
//	memcpy( index_GelHeap( p->FileName, Index ), _String, StringLength );
//}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
//}; // namespace Data //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_GelArchive_H__ //
// - ------------------------------------------------------------------------------------------ - //
