// - ------------------------------------------------------------------------------------------ - //
// GelDirectory UnixDir - Unix Style implementation of polling a directory tree //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_GelDirectory_UnixDir_H__
#define __Library_Data_GelDirectory_UnixDir_H__
// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_UNIX_DIR
// - ------------------------------------------------------------------------------------------ - //
#include <Debug/GelDebug.h>
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

	VLog("o %s - %s\n", SearchDirectory, Prefix );
	VVVLog("o\n");
	// Read the first entry in the directory //
	dirent* Data = readdir( ThisDir );
	VVVLog("o\n");
	
	// While we still have entries left in this directory //
	while( Data != 0 ) {
		// Build the full path name of the file //
		char* CurrentFile = new char[ length_String(SearchDirectory) + 1 + length_String(Data->d_name) + 1 ];
		copy_String( SearchDirectory, CurrentFile );
		cat_String( "/", CurrentFile );
		cat_String( Data->d_name, CurrentFile );

		// Get the status of the file //
		GelFileInfo DIRStatus( CurrentFile );

		VVLog("> Populated: %s\n", CurrentFile );

		// If it's a directory //
		if ( DIRStatus.IsDirectory() ) {
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
		else if ( DIRStatus.IsFile() ) {
			if( Data->d_name[0] != '.' ) {
				if( Data->d_name[0] != '_' ) {
					// Build our filename string //
					char* NewFile = new char[ length_String(Prefix) + length_String(Data->d_name) + 1 ];
					copy_String( Prefix, NewFile );
					cat_String( Data->d_name, NewFile );
				
					// Add the file //
					add_GelDirectory( p, NewFile, DIRStatus );
					
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
inline const bool haschanged_GelDirectory( const GelDirectory* p, const size_t Index ) { 
	// Build the full path name of the file //
	char* CurrentFile = new char[ length_String(p->BaseName) + 1 + length_String( index_GelDirectory(p,Index) ) + 1 ];
	copy_String( p->BaseName, CurrentFile );
	cat_String( "/", CurrentFile );
	cat_String( index_GelDirectory(p,Index), CurrentFile );

	// Get the status of the file //
	GelFileInfo FileStatus( CurrentFile );
	
	// Compare the modified time //
	return FileStatus.Status.st_mtime != info_GelDirectory(p,Index).Status.st_mtime;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
inline GelDirectory* new_GelDirectory( const char* _BaseName ) {
	GelDirectory* NewDir = new GelDirectory;
	
	NewDir->BaseName = new_String( _BaseName );
	NewDir->FileName = new_GelHeap();
	NewDir->FileInfo = new_GelArray<GelFileInfo>( 0 );
	
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
