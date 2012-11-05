// - ------------------------------------------------------------------------------------------ - //
// GelDirectory BadaDir - Bada Style implementation of polling a directory tree //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_GelDirectory_BadaDir_H__
#define __Library_Data_GelDirectory_BadaDir_H__
// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_BADA
// - ------------------------------------------------------------------------------------------ - //
#include <Debug/GelDebug.h>
#include <FIo.h>
#include <FBase.h>

#include "GelDirectory_Core.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Init and Exit code, called once in case a platform needs to properly init directory support //
// - ------------------------------------------------------------------------------------------ - //
inline void init_GelDirectory() {
}
// - ------------------------------------------------------------------------------------------ - //
inline void exit_GelDirectory() {
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// This is called recursively. //
inline void populate_GelDirectory( GelDirectory* p, const char* SearchDirectory, const char* Prefix ) {
	// Extract the GelDirectory part, and open the GelDirectory //
	Osp::Io::Directory ThisDir;
	ThisDir.Construct( Osp::Base::String(SearchDirectory) );

	VVLog("o %s - %s\n", SearchDirectory, Prefix );
	VVLog("o\n");
	// Read the first entry in the directory //
	Osp::Io::DirEnumerator* DirEnum = ThisDir.ReadN();
	VVLog("o\n");
	
	// While we still have entries left in this directory //
	while( DirEnum->MoveNext() == E_SUCCESS ) {
		Osp::Io::DirEntry Data = DirEnum->GetCurrentDirEntry();

		Osp::Base::ByteBuffer DataName;
		DataName.Construct( *Osp::Base::Utility::StringUtil::StringToUtf8N(Data.GetName()) );
		char* DataPtr = (char*)DataName.GetPointer();
		size_t DataSize = Data.GetName().GetLength();

		// Build the full path name of the file //
		char* CurrentFile = new char[ length_String(SearchDirectory) + 1 + DataSize + 1 ];
		copy_String( SearchDirectory, CurrentFile );
		cat_String( "/", CurrentFile );
		cat_String( DataPtr, CurrentFile );

		VVLog("* %s\n", CurrentFile );

		// If it's a directory //
		if ( Data.IsDirectory() ) {
			// Recursively do this again, if not a dot file or folder //
			if( DataPtr[0] != '.' )
				if( DataPtr[0] != '_' ) {
					// Build our prefix string //
					char* PrefixString = new char[ length_String(Prefix) + DataSize + 2 ];
					copy_String( Prefix, PrefixString );
					cat_String( DataPtr, PrefixString );
					cat_String( "/", PrefixString );
					
					// Recursive call //
					populate_GelDirectory( p, CurrentFile, PrefixString );
						
					// Delete our prefix string //
					delete_String( PrefixString );
				}
		}
		// If it's a regular file //
		else {
			if( DataPtr[0] != '.' ) {
				if( DataPtr[0] != '_' ) {
					// Build our filename string //
					char* NewFile = new char[ length_String(Prefix) + DataSize + 1 ];
					copy_String( Prefix, NewFile );
					cat_String( DataPtr, NewFile );
		
					// Add the file //
					add_GelDirectory( p, NewFile );
					
					// Delete our filename string //
					delete_String( NewFile );
				}
			}
		}
		
		// Remove our string //
		delete_String( CurrentFile );
	
		// Read the next entry //
		//Data = readdir( ThisDir );
	};
	
	// Close the directory //
	//closedir( ThisDir );
}
// - ------------------------------------------------------------------------------------------ - //
inline void populate_GelDirectory( GelDirectory* p ) {
	populate_GelDirectory( p, p->BaseName, "" );
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
inline GelDirectory* new_GelDirectory( const char* _BaseName ) {

	GelDirectory* NewDir = new GelDirectory;
	
	NewDir->BaseName = new_String( _BaseName );
	NewDir->FileName = new_GelHeap();
	
	// Work //
	populate_GelDirectory( NewDir );
	
	return NewDir;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline bool is_Directory( const char* _Name ) {
/*
	struct stat Status;
	stat( _Name, &Status );
	
	// If it's a directory //
	return S_ISDIR( Status.st_mode );
*/
	return false;
}
// - ------------------------------------------------------------------------------------------ - //
inline bool is_File( const char* _Name ) {
/*
	struct stat Status;
	stat( _Name, &Status );
	
	// If it's a directory //
	return S_ISREG( Status.st_mode );
*/
	return false;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // USES_BADA //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_GelDirectory_BadaDir_H__ //
// - ------------------------------------------------------------------------------------------ - //
