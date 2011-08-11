// - ------------------------------------------------------------------------------------------ - //
// GelDirectory UnixDir - Unix Style implementation of polling a directory tree //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_GelDirectory_UnixDir_H__
#define __Library_Data_GelDirectory_UnixDir_H__
// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_UNIX_DIR
// - ------------------------------------------------------------------------------------------ - //
#include <Debug/Log.h>
#include <dirent.h>
#include <sys/stat.h>

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
	// Extract the directory part, and open the directory //
	DIR* ThisDir = opendir( SearchDirectory );

	VVLog("o %s - %s\n", SearchDirectory, Prefix );
	VVLog("o\n");
	// Read the first entry in the directory //
	dirent* Data = readdir( ThisDir );
	VVLog("o\n");
	
	// While we still have entries left in this directory //
	while( Data != 0 ) {
		// Build the full path name of the file //
		char* CurrentFile = new char[ length_String(SearchDirectory) + 1 + length_String(Data->d_name) + 1 ];
		copy_String( SearchDirectory, CurrentFile );
		cat_String( "/", CurrentFile );
		cat_String( Data->d_name, CurrentFile );

		// Get the status of the file //
		struct stat DIRStatus;
		stat( CurrentFile, &DIRStatus );

		VVLog("> Populated: %s\n", CurrentFile );

		// If it's a directory //
		if ( S_ISDIR( DIRStatus.st_mode ) ) {
			// Recursively do this again, if not a dot file or folder //
			if( Data->d_name[0] != '.' ) 
				if( Data->d_name[0] != '_' ) {
					// Build our prefix string //
					char* PrefixString = new char[ length_String(Prefix) + length_String(Data->d_name) + 2 ];
					copy_String( Prefix, PrefixString );
					cat_String( Data->d_name, PrefixString );
					cat_String( "/", PrefixString );
					
					// Recursive call //
					populate_GelDirectory( p, CurrentFile, PrefixString );
						
					// Delete our prefix string //
					delete_String( PrefixString );
				}
		}
		// If it's a regular file //
		else if ( S_ISREG( DIRStatus.st_mode ) ) {
			if( Data->d_name[0] != '.' ) {
				if( Data->d_name[0] != '_' ) {
					// Build our filename string //
					char* NewFile = new char[ length_String(Prefix) + length_String(Data->d_name) + 1 ];
					copy_String( Prefix, NewFile );
					cat_String( Data->d_name, NewFile );
		
					// Add the file //
					add_GelDirectory( p, NewFile );
					
					// Delet our filename string //
					delete_String( NewFile );
				}
			}
		}
		
		// Remove our string //
		delete_String( CurrentFile );
	
		// Read the next entry //
		Data = readdir( ThisDir );
	};
	
	// Close the directory //
	closedir( ThisDir );		
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
	NewDir->FileName = new_GelHeap(0, 0);
	
	// Work //
	populate_GelDirectory( NewDir );
	
	return NewDir;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline bool is_Directory( const char* _Name ) {
	struct stat DIRStatus;
	stat( _Name, &DIRStatus );
	
	// If it's a directory //
	return S_ISDIR( DIRStatus.st_mode );
}
// - ------------------------------------------------------------------------------------------ - //
inline bool is_File( const char* _Name ) {
	struct stat DIRStatus;
	stat( _Name, &DIRStatus );
	
	// If it's a directory //
	return S_ISREG( DIRStatus.st_mode );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // USES_UNIX_DIR //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_GelDirectory_UnixDir_H__ //
// - ------------------------------------------------------------------------------------------ - //
