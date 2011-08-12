// - ------------------------------------------------------------------------------------------ - //
// GelArray File - Extended Array features, reading, writing, and initializing from a file/FILE* //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_GELCore_GelArray_File_H__
#define __Library_GELCore_GelArray_File_H__
// - ------------------------------------------------------------------------------------------ - //
#include "GelFile.h"
#include "GelVFile.h"
#include "GelContentHandle.h"
#include "GelStorageHandle.h"

#include "GelArray_Core.h"
#include "DataBlock_File.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Use this alternative "new" function when you don't know how big it is //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline GelArray<Type>* new_read_GelArray( const char* _FileName ) {
	// Open File //
	GelFile* fp = open_readonly_GelFile( _FileName );
	if ( fp == 0 ) {
		// Return a dummy instance.  This might be bad, since an empty file will look the same. //
		//return new_GelArray<Type>( (size_t)0 );
		
		// Or return a zero pointer.  Better, because it's clearer that allocation failed. //
		return 0;
	}
	
	// Determine how large file is //
	size_t Size = size_GelFile( fp );
	
	// Allocate space (Size is automatically set inside new_DataBlock) //
	GelArray<Type>* p = new_GelArray<Type>( Size / sizeof(Type) );
	
	// Read data //
	read_GelFile( fp, (char*)&p->Data[0], Size );
	
	// Close file //
	close_GelFile( fp );
	
	// Return data //
	return p;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline GelArray<Type>* new_read_GelArray( GelFile* fp ) {
	// Read Size (in bytes) //
	size_t Size = read_GelFile<size_t>( fp );
	
	// Allocate space (size in bytes divided by the size of a type) //
	GelArray<Type>* p = new_GelArray<Type>( Size / sizeof(Type) );
	
	// Read data (in bytes) //
	read_GelFile( fp, (char*)&p->Data[0], Size );
	
	// Return data //
	return p;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline GelArray<Type>* new_read_GelArray( GelVFile* fp ) {
	// Read Size (in bytes) //
	size_t Size = read_GelVFile<size_t>( fp );
	
	// Allocate space (size in bytes divided by the size of a type) //
	GelArray<Type>* p = new_GelArray<Type>( Size / sizeof(Type) );
	
	// Read data (in bytes) //
	read_GelVFile( fp, (char*)&p->Data[0], Size );
	
	// Return data //
	return p;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline GelArray<Type>* read_GelArray( GelFile* fp ) {
	return new_read_GelArray<Type>( fp );
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline GelArray<Type>* read_GelArray( GelVFile* fp ) {
	return new_read_GelArray<Type>( fp );
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// These functions are for when you know how large a file is //
// TODO: Add file offsetting as optional 3rd argument (defalts to 0) //
// TODO: Or, add a "file" type that you can construct at the top of a function, and pass to these //
// NOTE: The above should be part of the streaming library? //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const size_t read_GelArray( GelArray<Type>* p, const char* _FileName ) {
	// Open File //
	GelFile* fp = open_readonly_GelFile( _FileName );
	if ( fp == 0 ) {
		// TODO: Log file open error //
		return 0;
	}
	
	// Determine how large file is //
	size_t Size = size_GelFile( fp );
	
	// Verify if we have enough room //
	size_t DataSize = p->Size * sizeof(Type);
	
	// Read data (only as much as the smallest size) //
	size_t BytesRead = read_GelFile( fp, p->Data, Size > DataSize ? DataSize : Size );
	
	// Close file //
	close_GelFile( fp );
	
	// Return the number of bytes read //
	return BytesRead;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const size_t write_GelArray( const GelArray<Type>* p, const char* _FileName ) {
	// Open File //
	GelFile* fp = open_writeonly_GelFile( _FileName );
	if ( fp == 0 ) {
		return 0;
	}
	
	// Write the data //
	size_t BytesWritten = write_GelFile( fp, p->Data, p->Size * sizeof(Type) );

	// TODO: Assert on fire write error //
	
	// Close file //
	close_GelFile( fp );
		
	// Return the number of bytes written //
	return BytesWritten;
}
// - ------------------------------------------------------------------------------------------ - //
// For syntactical compatability, read_DataBlock which functions the same as new_DataBlock. //
// Note: This is bad, as it's unclear allocation is done.  new_DataBlock() is preferred. //
// - ------------------------------------------------------------------------------------------ - //
//template< class Type >
//inline GelArray<Type>* read_GelArray( const char* _FileName ) {
//	return new_GelArray<Type>( _FileName );
//}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// GelFile* Versions read and write sizes //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const size_t read_GelArray( GelArray<Type>* p, GelFile* fp ) {
	// Read Size (in bytes) //
	size_t Size = read_GelFile<size_t>( fp );
	
	// Verify if we have enough room //
	size_t DataSize = p->Size * sizeof(Type);
	
	// Read data (only as much as the smallest size) //
	size_t BytesRead = read_GelFile( fp, (char*)&p->Data[0], Size > DataSize ? DataSize : Size );
	
	// Return the number of bytes read //
	return BytesRead + sizeof( size_t );
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const size_t write_GelArray( const GelArray<Type>* p, GelFile* fp ) {
	// Write Size (Size multiplied by size of a type) //
	size_t BytesWritten = write_GelFile( fp, p->Size * sizeof(Type) );

	// Write the data (Size multiplied by size of a type) //
	BytesWritten += write_GelFile( fp, (char*)&p->Data[0], p->Size * sizeof(Type) );

	// TODO: Assert on fire write error //
			
	// Return the number of bytes written //
	return BytesWritten;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// GelVFile* Versions read and write sizes //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const size_t read_GelArray( GelArray<Type>* p, GelVFile* fp ) {
	// Read Size (in bytes) //
	size_t Size = read_GelVFile<size_t>( fp );
	
	// Verify if we have enough room //
	size_t DataSize = p->Size * sizeof(Type);
	
	// Read data (only as much as the smallest size) //
	size_t BytesRead = read_GelVFile( fp, (char*)&p->Data[0], Size > DataSize ? DataSize : Size );
	
	// Return the number of bytes read //
	return BytesRead + sizeof( size_t );
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const size_t write_GelArray( const GelArray<Type>* p, GelVFile* fp ) {
	// Write Size (Size multiplied by size of a type) //
	size_t BytesWritten = write_GelVFile( fp, p->Size * sizeof(Type) );

	// Write the data (Size multiplied by size of a type) //
	BytesWritten += write_GelVFile( fp, (char*)&p->Data[0], p->Size * sizeof(Type) );

	// TODO: Assert on fire write error //
			
	// Return the number of bytes written //
	return BytesWritten;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_GelArray_File_H__ //
// - ------------------------------------------------------------------------------------------ - //
