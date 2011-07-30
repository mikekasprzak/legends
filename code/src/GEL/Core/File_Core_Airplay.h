// - ------------------------------------------------------------------------------------------ - //
// File - Airplay File wrapping and utility library //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_File_Core_Airplay_H__
#define __Library_Data_File_Core_Airplay_H__
// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_AIRPLAY_FILEIO
// - ------------------------------------------------------------------------------------------ - //
// TODO: Add a function for reading a DataBlock from an open file //
// TODO: Also add functions for reading data of an expected size, zero terminated strings, etc. //
// TODO: Add functions for reading/adapting floating point numbers from IEEE to other needed types
// TODO: Add functions for converting/writing floats to fixed point numbers (a cheat)
// - ------------------------------------------------------------------------------------------ - //
#include <string.h>
//#include <stdio.h>
#include <s3eFile.h>

#include "Endian.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Get the size of a file in bytes //
// - ------------------------------------------------------------------------------------------ - //
inline const size_t size_File( const char* _FileName ) {
	// Open File //
	s3eFile* fp = s3eFileOpen( _FileName, "rb" );
	if ( fp == 0 ) {
		return 0;
	}
	
	// Determine how large file is //
	s3eFileSeek( fp, 0, S3E_FILESEEK_END );
	size_t Size = s3eFileTell( fp );
	
	// Close file //
	s3eFileClose( fp );
	
	// Return data //
	return Size;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Get the size of an open file, in bytes //
// - ------------------------------------------------------------------------------------------ - //
inline const size_t size_File( s3eFile* fp ) {
	size_t Position = s3eFileTell( fp );
	
//	fpos_t Position;
//	fgetpos( fp, &Position );
	
	s3eFileSeek( fp, 0, S3E_FILESEEK_END );
	size_t Size = s3eFileTell( fp );
	s3eFileSeek( fp, Position, S3E_FILESEEK_SET );
	
//	fsetpos( fp, &Position );
	
	return Size;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline const bool exists_File( const char* _FileName ) {
	// Open File //
	s3eFile* fp = s3eFileOpen( _FileName, "rb" );
	if ( fp == 0 ) {
		return false;
	}
	
	// Close file //
	s3eFileClose( fp );
	
	// Return data //
	return true;
}
// - ------------------------------------------------------------------------------------------ - //
inline const int delete_File( const char* _FileName ) {
	return s3eFileDelete( _FileName );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Opening files //
// - ------------------------------------------------------------------------------------------ - //
inline s3eFile* open_File( const char* _FileName, const char* _OpenMask = "rb" ) {
	return s3eFileOpen( _FileName, _OpenMask );
}
// - ------------------------------------------------------------------------------------------ - //
inline s3eFile* open_readonly_File( const char* _FileName ) {
	return s3eFileOpen( _FileName, "rb" );
}
// - ------------------------------------------------------------------------------------------ - //
inline s3eFile* open_writeonly_File( const char* _FileName ) {
	return s3eFileOpen( _FileName, "wb" );
}
// - ------------------------------------------------------------------------------------------ - //

// NOTE: C library has 2 interesting functions.  tmpfile() and tmpname( .. ).  tmpfile creates //
//   a temorary file instance, that erases itself when closed.  tmpname returns a legit temporary //
//   filename, that does not conflict (with what, I don't know).  If you choose to open the file, //
//   don't forget to delete it with "remove( "File.blah" );". //


// - ------------------------------------------------------------------------------------------ - //
// Closing Files //
// - ------------------------------------------------------------------------------------------ - //
inline void close_File( s3eFile* fp ) {
	s3eFileClose( fp );
}
// - ------------------------------------------------------------------------------------------ - //


// NOTE: s3eFileRead( TargetPointer, DataSize, Count, FilePointer ); //

// - ------------------------------------------------------------------------------------------ - //
// Read Function //
// - ------------------------------------------------------------------------------------------ - //
inline const size_t read_File( s3eFile* fp, char* Data, const size_t Size ) {
	return s3eFileRead( Data, Size, 1, fp );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Templated read functions (read_File<int>( fp );) //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const Type read_File( s3eFile* fp ) {
	Type Target;
	read_File( fp, (char*)&Target, sizeof(Target) );
	//s3eFileRead( &Target, sizeof(Target), 1, fp );
	return Target;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const Type readswap_File( s3eFile* fp ) {
	Type Target = read_File<Type>(fp);
	//s3eFileRead( &Target, sizeof(Target), 1, fp );
	return byteswap(Target);
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const Type readbe_File( s3eFile* fp ) {
	Type Target = read_File<Type>(fp);
	//s3eFileRead( &Target, sizeof(Target), 1, fp );
	return beswap(Target);
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const Type readle_File( s3eFile* fp ) {
	Type Target = read_File<Type>(fp);
	//s3eFileRead( &Target, sizeof(Target), 1, fp );
	return leswap(Target);
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// Write Function //
// - ------------------------------------------------------------------------------------------ - //
inline const size_t write_File( s3eFile* fp, const char* Data, const size_t Size ) {
	return s3eFileWrite( Data, Size, 1, fp );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Templated write functions (write_File<int>( fp );) //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const size_t write_File( s3eFile* fp, const Type Data ) {
	return write_File( fp, (const char*)&Data, sizeof(Data) );
	//return s3eFileWrite( &Data, sizeof(Data), 1, fp );
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const size_t writeswap_File( s3eFile* fp, const Type Data ) {
	Type Copy = byteswap(Data);
	return write_File<Type>( fp, Copy );
	//return s3eFileWrite( &Copy, sizeof(Data), 1, fp );
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const size_t writebe_File( s3eFile* fp, const Type Data ) {
	Type Copy = beswap(Data);
	return write_File<Type>( fp, Copy );
	//return s3eFileWrite( &Copy, sizeof(Data), 1, fp );
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const size_t writele_File( s3eFile* fp, const Type Data ) {
	Type Copy = leswap(Data);
	return write_File<Type>( fp, Copy );
	//return s3eFileWrite( &Copy, sizeof(Data), 1, fp );
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void fill_File( s3eFile* fp, const Type Data, int Count ) {
	for ( ; Count--; ) {
		write_File<Type>(fp, Data );
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // USES_AIRPLAY_FILEIO //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_File_Core_Airplay_H__ //
// - ------------------------------------------------------------------------------------------ - //
