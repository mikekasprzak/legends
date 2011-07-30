// - ------------------------------------------------------------------------------------------ - //
// String File - Extended String features, reading, writing, and initializing from a file/FILE*
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_GELCore_String_File_H__
#define __Library_GELCore_String_File_H__
// - ------------------------------------------------------------------------------------------ - //
#include "GelFile.h"
#include "GelVFile.h"
#include "GelContentHandle.h"
#include "GelStorageHandle.h"

#include "GelString_Core.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Unfortunately, since we use char* to represent a filename, we can't use new_String here. //
//   So instead, we're overloading read without a target string argument. //
// - ------------------------------------------------------------------------------------------ - //
inline char* read_String( const char* _FileName ) {
	// Open File //
	GelFile* fp = open_readonly_GelFile( _FileName );
	if ( fp == 0 ) {
		return 0;
	}
	
	// Read Size //
	size_t Size = read_GelFile<size_t>( fp );
	
	// Allocate space //
	char* p = new char[ Size + 1 ];
	
	// Read data //
	read_GelFile( fp, p, Size );
	
	p[ Size ] = 0;
	
	// Close file //
	close_GelFile( fp );
	
	// Return data //
	return p;
}
// - ------------------------------------------------------------------------------------------ - //
// Use this alternative "new" function when you don't know how big a file is //
// - ------------------------------------------------------------------------------------------ - //
inline char* new_String( GelFile* fp ) {
	// Read Size //
	size_t Size = read_GelFile<size_t>( fp );
	
	// Allocate space //
	char* p = new char[ Size + 1 ];
	
	// Read data //
	read_GelFile( fp, p, Size );
	
	p[ Size ] = 0;
	
	// Return data //
	return p;
}
// - ------------------------------------------------------------------------------------------ - //
inline char* new_String( GelVFile* fp ) {
	// Read Size //
	size_t Size = read_GelVFile<size_t>( fp );
	
	// Allocate space //
	char* p = new char[ Size + 1 ];
	
	// Read data //
	read_GelVFile( fp, p, Size );
	
	p[ Size ] = 0;
	
	// Return data //
	return p;
}
// - ------------------------------------------------------------------------------------------ - //
inline char* read_String( GelFile* fp ) {
	return new_String( fp );
}
// - ------------------------------------------------------------------------------------------ - //
inline char* read_String( GelVFile* fp ) {
	return new_String( fp );
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// These functions are for when you know how large a file is //
// TODO: Add file offsetting as optional 3rd argument (defalts to 0) //
// TODO: Or, add a "file" type that you can construct at the top of a function, and pass to these //
// NOTE: The above should be part of the streaming library? //
// - ------------------------------------------------------------------------------------------ - //
inline const size_t read_String( char* p, const char* _FileName ) {
	// Open File //
	GelFile* fp = open_readonly_GelFile( _FileName );
	if ( fp == 0 ) {
		return 0;
	}
	
	// Read Size //
	size_t Size = read_GelFile<size_t>( fp );
	
	// Read data //
	size_t BytesRead = read_GelFile( fp, p, Size );
	
	p[ Size ] = 0;
	
	// Close file //
	close_GelFile( fp );
	
	// Return the number of bytes read //
	return BytesRead + sizeof( size_t );
}
// - ------------------------------------------------------------------------------------------ - //
inline const size_t write_String( const char* p, const char* _FileName ) {
	// Open File //
	GelFile* fp = open_writeonly_GelFile( _FileName );
	if ( fp == 0 ) {
		return 0;
	}
	
	// Calculate Size //
	size_t Size = length_String( p );
	
	// Write Size //
	size_t BytesWritten = write_GelFile( fp, Size );
	
	// Write the data //
	BytesWritten += write_GelFile( fp, p, Size );

	// TODO: Assert on fire write error //
	
	// Close file //
	close_GelFile( fp );
		
	// Return the number of bytes write //
	return BytesWritten;
}
// - ------------------------------------------------------------------------------------------ - //
// For syntactical compatability, read_String which functions the same as new_String. //
// Note: This is bad, as it's unclear allocation is done.  new_String() is preferred. //
// - ------------------------------------------------------------------------------------------ - //
//inline String* read_String( const char* _FileName ) {
//	return new_String( _FileName );
//}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline const size_t read_String( char* p, GelFile* fp ) {
	// Read Size //
	size_t Size = read_GelFile<size_t>( fp );
	
	// Read data //
	size_t BytesRead = read_GelFile( fp, p, Size );
	
	p[ Size ] = 0;
			
	// TODO: If I happen to only read some of the file, less than Size, that would be bad. //
	
	// Return the number of bytes read //
	return BytesRead + sizeof( Size );
}
// - ------------------------------------------------------------------------------------------ - //
inline const size_t write_String( const char* p, GelFile* fp ) {
	// Calculate Size //
	size_t Size = length_String( p );
	
	// Write Size //
	size_t BytesWritten = write_GelFile( fp, Size );
	
	// Write the data //
	BytesWritten += write_GelFile( fp, p, Size );
	
	// TODO: Assert on fire write error //
		
	// Return the number of bytes write //
	return BytesWritten;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline const size_t read_String( char* p, GelVFile* fp ) {
	// Read Size //
	size_t Size = read_GelVFile<size_t>( fp );
	
	// Read data //
	size_t BytesRead = read_GelVFile( fp, p, Size );
	
	p[ Size ] = 0;
			
	// TODO: If I happen to only read some of the file, less than Size, that would be bad. //
	
	// Return the number of bytes read //
	return BytesRead + sizeof( Size );
}
// - ------------------------------------------------------------------------------------------ - //
inline const size_t write_String( const char* p, GelVFile* fp ) {
	// Calculate Size //
	size_t Size = length_String( p );
	
	// Write Size //
	size_t BytesWritten = write_GelVFile( fp, Size );
	
	// Write the data //
	BytesWritten += write_GelVFile( fp, p, Size );
	
	// TODO: Assert on fire write error //
		
	// Return the number of bytes write //
	return BytesWritten;
}
// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_String_Core_H__ //
// - ------------------------------------------------------------------------------------------ - //
