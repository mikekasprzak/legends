// - ------------------------------------------------------------------------------------------ - //
// File - C "FILE*" wrapping and utility library //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_File_Core_H__
#define __Library_Data_File_Core_H__
// - ------------------------------------------------------------------------------------------ - //
#ifndef USES_AIRPLAY_FILEIO
// - ------------------------------------------------------------------------------------------ - //
// TODO: Rename to File_Core_STDIO
// - ------------------------------------------------------------------------------------------ - //
// TODO: Add a function for reading a DataBlock from an open file //
// TODO: Also add functions for reading data of an expected size, zero terminated strings, etc. //
// TODO: Add functions for reading/adapting floating point numbers from IEEE to other needed types
// TODO: Add functions for converting/writing floats to fixed point numbers (a cheat)
// - ------------------------------------------------------------------------------------------ - //
#include <string.h>
#include <stdio.h>

#include "Endian.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Get the size of a file in bytes //
// - ------------------------------------------------------------------------------------------ - //
inline const size_t size_File( const char* _FileName ) {
	// Open File //
	FILE* fp = fopen( _FileName, "rb" );
	if ( fp == 0 ) {
		return 0;
	}
	
	// Determine how large file is //
	fseek( fp, 0, SEEK_END );
	size_t Size = ftell( fp );
	
	// Close file //
	fclose( fp );
	
	// Return data //
	return Size;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Get the size of an open file, in bytes //
// - ------------------------------------------------------------------------------------------ - //
inline const size_t size_File( FILE* fp ) {
	size_t Position = ftell( fp );
	
//	fpos_t Position;
//	fgetpos( fp, &Position );
	
	fseek( fp, 0, SEEK_END );
	size_t Size = ftell( fp );
	fseek( fp, Position, SEEK_SET );
	
//	fsetpos( fp, &Position );
	
	return Size;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline const bool exists_File( const char* _FileName ) {
	// Open File //
	FILE* fp = fopen( _FileName, "rb" );
	if ( fp == 0 ) {
		return false;
	}
	
	// Close file //
	fclose( fp );
	
	// Return data //
	return true;
}
// - ------------------------------------------------------------------------------------------ - //
inline const int delete_File( const char* _FileName ) {
	return remove( _FileName );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Opening files //
// - ------------------------------------------------------------------------------------------ - //
inline FILE* open_File( const char* _FileName, const char* _OpenMask = "rb" ) {
	return fopen( _FileName, _OpenMask );
}
// - ------------------------------------------------------------------------------------------ - //
inline FILE* open_readonly_File( const char* _FileName ) {
	return fopen( _FileName, "rb" );
}
// - ------------------------------------------------------------------------------------------ - //
inline FILE* open_writeonly_File( const char* _FileName ) {
	return fopen( _FileName, "wb" );
}
// - ------------------------------------------------------------------------------------------ - //

// NOTE: C library has 2 interesting functions.  tmpfile() and tmpname( .. ).  tmpfile creates //
//   a temorary file instance, that erases itself when closed.  tmpname returns a legit temporary //
//   filename, that does not conflict (with what, I don't know).  If you choose to open the file, //
//   don't forget to delete it with "remove( "File.blah" );". //


// - ------------------------------------------------------------------------------------------ - //
// Closing Files //
// - ------------------------------------------------------------------------------------------ - //
inline void close_File( FILE* fp ) {
	fclose( fp );
}
// - ------------------------------------------------------------------------------------------ - //


// NOTE: fread( TargetPointer, DataSize, Count, FilePointer ); //

// - ------------------------------------------------------------------------------------------ - //
// Read Function //
// - ------------------------------------------------------------------------------------------ - //
inline const size_t read_File( FILE* fp, char* Data, const size_t Size ) {
	return fread( Data, Size, 1, fp );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Templated read functions (read_File<int>( fp );) //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const Type read_File( FILE* fp ) {
	Type Target;
	read_File( fp, (char*)&Target, sizeof(Target) );
	//fread( &Target, sizeof(Target), 1, fp );
	return Target;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const Type readswap_File( FILE* fp ) {
	Type Target = read_File<Type>(fp);
	//fread( &Target, sizeof(Target), 1, fp );
	return byteswap(Target);
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const Type readbe_File( FILE* fp ) {
	Type Target = read_File<Type>(fp);
	//fread( &Target, sizeof(Target), 1, fp );
	return beswap(Target);
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const Type readle_File( FILE* fp ) {
	Type Target = read_File<Type>(fp);
	//fread( &Target, sizeof(Target), 1, fp );
	return leswap(Target);
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// Write Function //
// - ------------------------------------------------------------------------------------------ - //
inline const size_t write_File( FILE* fp, const char* Data, const size_t Size ) {
	return fwrite( Data, Size, 1, fp );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Templated write functions (write_File<int>( fp );) //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const size_t write_File( FILE* fp, const Type Data ) {
	return write_File( fp, (const char*)&Data, sizeof(Data) );
	//return fwrite( &Data, sizeof(Data), 1, fp );
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const size_t writeswap_File( FILE* fp, const Type Data ) {
	Type Copy = byteswap(Data);
	return write_File<Type>( fp, Copy );
	//return fwrite( &Copy, sizeof(Data), 1, fp );
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const size_t writebe_File( FILE* fp, const Type Data ) {
	Type Copy = beswap(Data);
	return write_File<Type>( fp, Copy );
	//return fwrite( &Copy, sizeof(Data), 1, fp );
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const size_t writele_File( FILE* fp, const Type Data ) {
	Type Copy = leswap(Data);
	return write_File<Type>( fp, Copy );
	//return fwrite( &Copy, sizeof(Data), 1, fp );
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void fill_File( FILE* fp, const Type Data, int Count ) {
	for ( ; Count--; ) {
		write_File<Type>(fp, Data );
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // USES_AIRPLAY_FILEIO //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_File_Core_H__ //
// - ------------------------------------------------------------------------------------------ - //
