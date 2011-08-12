// - ------------------------------------------------------------------------------------------ - //
// GelVFile File - Extended GelVFile features, reading, writing, and initializing from a file/FILE*
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_GELCore_GelVFile_File_H__
#define __Library_GELCore_GelVFile_File_H__
// - ------------------------------------------------------------------------------------------ - //
#include "GelFile.h"
#include "GelContentHandle.h"
#include "GelStorageHandle.h"

#include "GelVFile_Core.h"

#include "GelArray_File.h"
// - ------------------------------------------------------------------------------------------ - //
// These functions are required by this code, but since VFile relies on GelArray, it's a circle.  //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline GelArray<Type>* new_read_GelArray( const char* _FileName );
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline GelArray<Type>* new_read_GelArray( GelFile* fp );
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const size_t read_GelArray( GelArray<Type>* p, const char* _FileName );
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const size_t write_GelArray( const GelArray<Type>* p, const char* _FileName );
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// Use this alternative "new" function when you don't know how big a file is //
// - ------------------------------------------------------------------------------------------ - //
inline GelVFile* new_read_GelVFile( const char* _FileName ) {
	// GelVFile is too complicated a type to rely on the file size alone, so we need to read //
	//   and write a stored heap in much the same way as we would to a FILE*. //
	GelVFile* p = new GelVFile;
	
	p->Position = 0;
	p->Data = new_read_GelArray<char>( _FileName );
	
	// Return data //
	return p;
}
// - ------------------------------------------------------------------------------------------ - //
inline GelVFile* new_read_GelVFile( GelFile* fp ) {
	GelVFile* p = new GelVFile;
	
	p->Position = 0;
	p->Data = new_read_GelArray<char>( fp );
	
	// Return data //
	return p;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void delete_GelVFile( GelVFile* fp ) {
	close_GelVFile( fp );
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// This function is only so useful, as it relys on the arrays being correctly allocated //
inline const size_t readfile_GelVFile( GelVFile* p, const char* _FileName ) {
	size_t BytesRead = read_GelArray( p->Data, _FileName ); 

	// Return the number of bytes read //
	return BytesRead;
}
// - ------------------------------------------------------------------------------------------ - //
inline const size_t writefile_GelVFile( const GelVFile* p, const char* _FileName ) {
	size_t BytesWritten = write_GelArray( p->Data, _FileName ); 

	// Return the number of bytes read //
	return BytesWritten;
}
// - ------------------------------------------------------------------------------------------ - //
inline GelVFile* readfile_GelVFile( const char* _FileName ) {
	return new_read_GelVFile( _FileName );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_GelVFile_Core_H__ //
// - ------------------------------------------------------------------------------------------ - //
