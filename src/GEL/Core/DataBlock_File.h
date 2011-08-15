// - ------------------------------------------------------------------------------------------ - //
// DataBlock File - Extended DataBlock features, reading, writing, and initializing from a file/FILE*
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_GELCore_DataBlock_File_H__
#define __Library_GELCore_DataBlock_File_H__
// - ------------------------------------------------------------------------------------------ - //
#include "GelFile.h"
#include "GelVFile.h"
#include "GelContentHandle.h"
#include "GelStorageHandle.h"

#include "DataBlock_Core.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Construct and read a file from Disk //
// - ------------------------------------------------------------------------------------------ - //
inline DataBlock* new_read_DataBlock( const char* _FileName ) {
	// Open File //
	GelFile* fp = open_readonly_GelFile( _FileName );
	if ( fp == 0 ) {
		return 0;
	}
	
	// Determine how large file is //
	size_t Size = size_GelFile( fp );
	
	// Allocate space (Size is automatically set inside new_DataBlock) //
	DataBlock* p = new_DataBlock( Size );
	
	// Read data //
	read_GelFile( fp, p->Data, Size );
	
	// Close file //
	close_GelFile( fp );
	
	// Return data //
	return p;
}
// - ------------------------------------------------------------------------------------------ - //
inline DataBlock* new_read_nullterminate_DataBlock( const char* _FileName ) {
	// Open File //
	GelFile* fp = open_readonly_GelFile( _FileName );
	if ( fp == 0 ) {
		return 0;
	}
	
	// Determine how large file is //
	size_t Size = size_GelFile( fp ) + 1;
	
	// Allocate space (Size is automatically set inside new_DataBlock) //
	DataBlock* p = new_DataBlock( Size );
	
	// Read data //
	read_GelFile( fp, p->Data, Size - 1 );
	
	// Write Zero to final byte //
	p->Data[Size-1] = 0;
	
	// Close file //
	close_GelFile( fp );
	
	// Return data //
	return p;
}
// - ------------------------------------------------------------------------------------------ - //
//DEPRECATED( DataBlock* new_DataBlock( const char* _FileName ) );
//inline DataBlock* new_DataBlock( const char* _FileName ) {
//	return new_read_DataBlock( _FileName );
//}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline DataBlock* new_read_DataBlock( GelFile* fp ) {
	// Read Size //
	size_t Size = read_GelFile<size_t>( fp );
	
	// Allocate space (Size is automatically set inside new_DataBlock) //
	DataBlock* p = new_DataBlock( Size );
	
	// Read data //
	read_GelFile( fp, p->Data, Size );
	
	// Return data //
	return p;
}
// - ------------------------------------------------------------------------------------------ - //
inline DataBlock* new_read_nullterminate_DataBlock( GelFile* fp ) {
	// Read Size //
	size_t Size = read_GelFile<size_t>( fp ) + 1;
	
	// Allocate space (Size is automatically set inside new_DataBlock) //
	DataBlock* p = new_DataBlock( Size );
	
	// Read data //
	read_GelFile( fp, p->Data, Size - 1 );

	// Write Zero to final byte //
	p->Data[Size-1] = 0;
	
	// Return data //
	return p;
}
// - ------------------------------------------------------------------------------------------ - //
inline DataBlock* new_read_DataBlock( GelVFile* fp ) {
	// Read Size //
	size_t Size = read_GelVFile<size_t>( fp );
	
	// Allocate space (Size is automatically set inside new_DataBlock) //
	DataBlock* p = new_DataBlock( Size );
	
	// Read data //
	read_GelVFile( fp, p->Data, Size );
	
	// Return data //
	return p;
}
// - ------------------------------------------------------------------------------------------ - //
inline DataBlock* new_read_nullterminate_DataBlock( GelVFile* fp ) {
	// Read Size //
	size_t Size = read_GelVFile<size_t>( fp ) + 1;
	
	// Allocate space (Size is automatically set inside new_DataBlock) //
	DataBlock* p = new_DataBlock( Size );
	
	// Read data //
	read_GelVFile( fp, p->Data, Size - 1 );

	// Write Zero to final byte //
	p->Data[Size-1] = 0;
	
	// Return data //
	return p;
}
// - ------------------------------------------------------------------------------------------ - //
//inline DataBlock* read_DataBlock( GelFile* fp ) {
//	return new_DataBlock( fp );
//}
// - ------------------------------------------------------------------------------------------ - //
//inline DataBlock* read_DataBlock( GelVFile* fp ) {
//	return new_DataBlock( fp );
//}
// - ------------------------------------------------------------------------------------------ - //
//DEPRECATED( DataBlock* new_DataBlock( GelFile* fp ) );
//inline DataBlock* new_DataBlock( GelFile* fp ) {
//	return new_read_DataBlock( fp );
//}
// - ------------------------------------------------------------------------------------------ - //
//DEPRECATED( DataBlock* new_DataBlock( GelVFile* fp ) );
//inline DataBlock* new_DataBlock( GelVFile* fp ) {
//	return new_read_DataBlock( fp );
//}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// These functions are for when you know how large a file is //
// TODO: Add file offsetting as optional 3rd argument (defalts to 0) //
// TODO: Or, add a "file" type that you can construct at the top of a function, and pass to these //
// NOTE: The above should be part of the streaming library? //
// - ------------------------------------------------------------------------------------------ - //
inline const size_t read_DataBlock( DataBlock* p, const char* _FileName ) {
	// Open File //
	GelFile* fp = open_readonly_GelFile( _FileName );
	if ( fp == 0 ) {
		return 0;
	}
	
	// Determine how large file is //
	size_t Size = size_GelFile( fp );
	
	// Read data (only as much as the smallest size) //
	size_t BytesRead = read_GelFile( fp, p->Data, Size > p->Size ? p->Size : Size );

	// Close file //
	close_GelFile( fp );
	
	// Return the number of bytes read //
	return BytesRead;
}
// - ------------------------------------------------------------------------------------------ - //
inline const size_t write_DataBlock( const DataBlock* p, const char* _FileName ) {
	// Open File //
	GelFile* fp = open_writeonly_GelFile( _FileName );
	if ( fp == 0 ) {
		return 0;
	}
	
	// Write the data //
	size_t BytesWritten = write_GelFile( fp, p->Data, p->Size );

	// TODO: Assert on fire write error //
	
	// Close file //
	close_GelFile( fp );
		
	// Return the number of bytes write //
	return BytesWritten;
}
// - ------------------------------------------------------------------------------------------ - //
// For syntactical compatability, read_DataBlock which functions the same as new_DataBlock. //
// Note: This is bad, as it's unclear allocation is done.  new_DataBlock() is preferred. //
// - ------------------------------------------------------------------------------------------ - //
//inline DataBlock* read_DataBlock( const char* _FileName ) {
//	return new_DataBlock( _FileName );
//}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline const size_t read_DataBlock( DataBlock* p, GelFile* fp ) {
	// Read Size //
	size_t Size = read_GelFile<size_t>( fp );
	
	// Read data (only as much as the smallest size) //
	size_t BytesRead = read_GelFile( fp, p->Data, Size > p->Size ? p->Size : Size );
		
	// TODO: If I happen to only read some of the file, less than Size, that would be bad. //
	
	// Return the number of bytes read //
	return BytesRead + sizeof( Size );
}
// - ------------------------------------------------------------------------------------------ - //
inline const size_t write_DataBlock( const DataBlock* p, GelFile* fp ) {
	// Write Size //
	size_t BytesWritten = write_GelFile( fp, p->Size );
	
	// Write the data //
	BytesWritten += write_GelFile( fp, p->Data, p->Size );
	
	// TODO: Assert on fire write error //
		
	// Return the number of bytes write //
	return BytesWritten;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline const size_t read_DataBlock( DataBlock* p, GelVFile* fp ) {
	// Read Size //
	size_t Size = read_GelVFile<size_t>( fp );
	
	// Read data (only as much as the smallest size) //
	size_t BytesRead = read_GelVFile( fp, p->Data, Size > p->Size ? p->Size : Size );
		
	// TODO: If I happen to only read some of the file, less than Size, that would be bad. //
	
	// Return the number of bytes read //
	return BytesRead + sizeof( Size );
}
// - ------------------------------------------------------------------------------------------ - //
inline const size_t write_DataBlock( const DataBlock* p, GelVFile* fp ) {
	// Write Size //
	size_t BytesWritten = write_GelVFile( fp, p->Size );
	
	// Write the data //
	BytesWritten += write_GelVFile( fp, p->Data, p->Size );
	
	// TODO: Assert on file write error //
		
	// Return the number of bytes write //
	return BytesWritten;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_DataBlock_Core_H__ //
// - ------------------------------------------------------------------------------------------ - //
