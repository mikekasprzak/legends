// - ------------------------------------------------------------------------------------------ - //
// GelFile - C "FILE*" wrapping and utility library //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_GELCore_GelFile_Airplay_H__
#define __Library_GELCore_GelFile_Airplay_H__
// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_AIRPLAY_FILEIO
// - ------------------------------------------------------------------------------------------ - //
// TODO: Add a function for reading a DataBlock from an open file //
// TODO: Also add functions for reading data of an expected size, zero terminated strings, etc. //
// TODO: Add functions for reading/adapting floating point numbers from IEEE to other needed types
// TODO: Add functions for converting/writing floats to fixed point numbers (a cheat)
// - ------------------------------------------------------------------------------------------ - //
#include <string.h>
#include <s3eFile.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// This is a define, since we can't always be sure the platform implementation is a type
// - ------------------------------------------------------------------------------------------ - //
typedef s3eFile GelFile;
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Init FileIO //
// - ------------------------------------------------------------------------------------------ - //
inline void init_GelFile( ) {
	// C Style File IO Requires no special init //
}
// - ------------------------------------------------------------------------------------------ - //
inline void exit_GelFile( ) {
	// C Style File IO Requires no special shutdown //
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Get the size of a file in bytes //
// - ------------------------------------------------------------------------------------------ - //
inline const size_t size_GelFile( const char* _FileName ) {
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
inline const size_t size_GelFile( GelFile* fp ) {
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
inline const bool exists_GelFile( const char* _FileName ) {
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
inline const int delete_GelFile( const char* _FileName ) {
	return s3eFileDelete( _FileName );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Opening files //
// - ------------------------------------------------------------------------------------------ - //
inline GelFile* open_GelFile( const char* _FileName, const char* _OpenMask = "rb" ) {
	return s3eFileOpen( _FileName, _OpenMask );
}
// - ------------------------------------------------------------------------------------------ - //
inline GelFile* open_readonly_GelFile( const char* _FileName ) {
	return s3eFileOpen( _FileName, "rb" );
}
// - ------------------------------------------------------------------------------------------ - //
inline GelFile* open_writeonly_GelFile( const char* _FileName ) {
	return s3eFileOpen( _FileName, "wb" );
}
// - ------------------------------------------------------------------------------------------ - //
inline GelFile* open_appendonly_GelFile( const char* _FileName ) {
	return s3eFileOpen( _FileName, "ab" );
}
// - ------------------------------------------------------------------------------------------ - //

// NOTE: C library has 2 interesting functions.  tmpfile() and tmpname( .. ).  tmpfile creates //
//   a temorary file instance, that erases itself when closed.  tmpname returns a legit temporary //
//   filename, that does not conflict (with what, I don't know).  If you choose to open the file, //
//   don't forget to delete it with "remove( "File.blah" );". //


// - ------------------------------------------------------------------------------------------ - //
// Closing Files //
// - ------------------------------------------------------------------------------------------ - //
inline void close_GelFile( GelFile* fp ) {
	s3eFileClose( fp );
}
// - ------------------------------------------------------------------------------------------ - //


// NOTE: fread( TargetPointer, DataSize, Count, FilePointer ); //

// - ------------------------------------------------------------------------------------------ - //
// Read Function //
// - ------------------------------------------------------------------------------------------ - //
inline const size_t read_GelFile( GelFile* fp, char* Data, const size_t Size ) {
	return s3eFileRead( Data, Size, 1, fp );
}
// - ------------------------------------------------------------------------------------------ - //
// Write Function //
// - ------------------------------------------------------------------------------------------ - //
inline const size_t write_GelFile( GelFile* fp, const char* Data, const size_t Size ) {
	return s3eFileWrite( Data, Size, 1, fp );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // USES_NON_STANDARD_FILE_IO //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_File_Airplay_H__ //
// - ------------------------------------------------------------------------------------------ - //
