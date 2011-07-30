// - ------------------------------------------------------------------------------------------ - //
// GelHeap File - Extended GelHeap features, reading, writing, and initializing from a file/FILE*
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_GELCore_GelHeap_File_H__
#define __Library_GELCore_GelHeap_File_H__
// - ------------------------------------------------------------------------------------------ - //
#include "GelFile.h"
#include "GelVFile.h"
#include "GelContentHandle.h"
#include "GelStorageHandle.h"

#include "GelArray_File.h"

#include "GelHeap_Core.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Use this alternative "new" function when you don't know how big a file is //
// - ------------------------------------------------------------------------------------------ - //
inline GelHeap* new_GelHeap( const char* _FileName ) {
	// Open File //
	GelFile* fp = open_readonly_GelFile( _FileName );
	if ( fp == 0 ) {
		return 0;
	}
	
	// GelHeap is too complicated a type to rely on the file size alone, so we need to read //
	//   and write a stored GelHeap in much the same way as we would to a FILE*. //
	GelHeap* p = new GelHeap;
	
	p->Index = new_GelArray<size_t>( fp );
	p->Data = new_GelArray<char>( fp );

	
	// Close file //
	close_GelFile( fp );
	
	// Return data //
	return p;
}
// - ------------------------------------------------------------------------------------------ - //
inline GelHeap* new_GelHeap( GelFile* fp ) {
	GelHeap* p = new GelHeap;
	
	p->Index = new_GelArray<size_t>( fp );
	p->Data = new_GelArray<char>( fp );
	
	// Return data //
	return p;
}
// - ------------------------------------------------------------------------------------------ - //
inline GelHeap* new_GelHeap( GelVFile* fp ) {
	GelHeap* p = new GelHeap;
	
	p->Index = new_GelArray<size_t>( fp );
	p->Data = new_GelArray<char>( fp );
	
	// Return data //
	return p;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// This function is only so useful, as it relys on the arrays being correctly allocated //
inline const size_t read_GelHeap( GelHeap* p, const char* _FileName ) {
	// Open File //
	GelFile* fp = open_readonly_GelFile( _FileName );
	if ( fp == 0 ) {
		return 0;
	}
	
	size_t BytesRead = read_GelArray( p->Index, fp );
	BytesRead += read_GelArray( p->Data, fp ); 

	// Close file //
	close_GelFile( fp );
	
	// Return the number of bytes read //
	return BytesRead;
}
// - ------------------------------------------------------------------------------------------ - //
inline const size_t write_GelHeap( const GelHeap* p, const char* _FileName ) {
	// Open File //
	GelFile* fp = open_writeonly_GelFile( _FileName );
	if ( fp == 0 ) {
		return 0;
	}

	size_t BytesWritten = write_GelArray( p->Index, fp );
	BytesWritten += write_GelArray( p->Data, fp ); 

	// TODO: Assert on fire write error //
	
	// Close file //
	close_GelFile( fp );
		
	// Return the number of bytes read //
	return BytesWritten;
}
// - ------------------------------------------------------------------------------------------ - //
// For syntactical compatability, read_GelHeap which functions the same as new_GelHeap. //
// Note: This is bad, as it's unclear allocation is done.  new_GelHeap() is preferred. //
// - ------------------------------------------------------------------------------------------ - //
//inline GelHeap* read_GelHeap( const char* _FileName ) {
//	return new_GelHeap( _FileName );
//}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// This function is only so useful, as it rely's on the arrays being correctly allocated //
inline const size_t read_GelHeap( GelHeap* p, GelFile* fp ) {
	size_t BytesRead = read_GelArray( p->Index, fp );
	BytesRead += read_GelArray( p->Data, fp ); 
		
	// TODO: If I happen to only read some of the file, less than Size, that would be bad. //
	
	// Return the number of bytes read //
	return BytesRead;
}
// - ------------------------------------------------------------------------------------------ - //
inline const size_t write_GelHeap( const GelHeap* p, GelFile* fp ) {
	size_t BytesWritten = write_GelArray( p->Index, fp );
	BytesWritten += write_GelArray( p->Data, fp ); 
	
	// TODO: Assert on fire write error //
		
	// Return the number of bytes read //
	return BytesWritten;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// This function is only so useful, as it rely's on the arrays being correctly allocated //
inline const size_t read_GelHeap( GelHeap* p, GelVFile* fp ) {
	size_t BytesRead = read_GelArray( p->Index, fp );
	BytesRead += read_GelArray( p->Data, fp ); 
		
	// TODO: If I happen to only read some of the file, less than Size, that would be bad. //
	
	// Return the number of bytes read //
	return BytesRead;
}
// - ------------------------------------------------------------------------------------------ - //
inline const size_t write_GelHeap( const GelHeap* p, GelVFile* fp ) {
	size_t BytesWritten = write_GelArray( p->Index, fp );
	BytesWritten += write_GelArray( p->Data, fp ); 
	
	// TODO: Assert on fire write error //
		
	// Return the number of bytes read //
	return BytesWritten;
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_GelHeap_Core_H__ //
// - ------------------------------------------------------------------------------------------ - //
