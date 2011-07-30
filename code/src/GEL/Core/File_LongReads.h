// - ------------------------------------------------------------------------------------------ - //
// File - C "FILE*" wrapping and utility library //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_GELCore_File_LongReads_H__
#define __Library_GELCore_File_LongReads_H__
// - ------------------------------------------------------------------------------------------ - //
#include "File_Core.h"
// - ------------------------------------------------------------------------------------------ - //
//namespace Data {
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Standard reads, no endianness correction //
// - ------------------------------------------------------------------------------------------ - //
inline const long long int read_int64_File( FILE* fp ) {
	long long int Target;
	fread( &Target, sizeof(Target), 1, fp );
	return Target;
}
// - ------------------------------------------------------------------------------------------ - //
inline const unsigned long long int read_uint64_File( FILE* fp ) {
	unsigned long long int Target;
	fread( &Target, sizeof(Target), 1, fp );
	return Target;
}
// - ------------------------------------------------------------------------------------------ - //
inline const int read_int_File( FILE* fp ) {
	int Target;
	fread( &Target, sizeof(Target), 1, fp );
	return Target;
}
// - ------------------------------------------------------------------------------------------ - //
inline const unsigned int read_uint_File( FILE* fp ) {
	unsigned int Target;
	fread( &Target, sizeof(Target), 1, fp );
	return Target;
}
// - ------------------------------------------------------------------------------------------ - //
inline const short read_short_File( FILE* fp ) {
	short Target;
	fread( &Target, sizeof(Target), 1, fp );
	return Target;
}
// - ------------------------------------------------------------------------------------------ - //
inline const unsigned short read_ushort_File( FILE* fp ) {
	unsigned short Target;
	fread( &Target, sizeof(Target), 1, fp );
	return Target;
}
// - ------------------------------------------------------------------------------------------ - //
inline const char read_char_File( FILE* fp ) {
	char Target;
	fread( &Target, sizeof(Target), 1, fp );
	return Target;
}
// - ------------------------------------------------------------------------------------------ - //
inline const unsigned char read_uchar_File( FILE* fp ) {
	unsigned char Target;
	fread( &Target, sizeof(Target), 1, fp );
	return Target;
}
// - ------------------------------------------------------------------------------------------ - //
inline const float read_float_File( FILE* fp ) {
	float Target;
	fread( &Target, sizeof(Target), 1, fp );
	return Target;
}
// - ------------------------------------------------------------------------------------------ - //
inline const double read_double_File( FILE* fp ) {
	double Target;
	fread( &Target, sizeof(Target), 1, fp );
	return Target;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Platform endianness inversion read //
// - ------------------------------------------------------------------------------------------ - //
inline const long long int readswap_int64_File( FILE* fp ) {
	long long int Target;
	fread( &Target, sizeof(Target), 1, fp );
	return byteswap8(Target);
}
// - ------------------------------------------------------------------------------------------ - //
inline const unsigned long long int readswap_uint64_File( FILE* fp ) {
	unsigned long long int Target;
	fread( &Target, sizeof(Target), 1, fp );
	return byteswap8(Target);
}
// - ------------------------------------------------------------------------------------------ - //
inline const int readswap_int_File( FILE* fp ) {
	int Target;
	fread( &Target, sizeof(Target), 1, fp );
	return byteswap4(Target);
}
// - ------------------------------------------------------------------------------------------ - //
inline const unsigned int readswap_uint_File( FILE* fp ) {
	unsigned int Target;
	fread( &Target, sizeof(Target), 1, fp );
	return byteswap4(Target);
}
// - ------------------------------------------------------------------------------------------ - //
inline const short readswap_short_File( FILE* fp ) {
	short Target;
	fread( &Target, sizeof(Target), 1, fp );
	return byteswap2(Target);
}
// - ------------------------------------------------------------------------------------------ - //
inline const unsigned short readswap_ushort_File( FILE* fp ) {
	unsigned short Target;
	fread( &Target, sizeof(Target), 1, fp );
	return byteswap2(Target);
}
// - ------------------------------------------------------------------------------------------ - //
inline const char readswap_char_File( FILE* fp ) {
	char Target;
	fread( &Target, sizeof(Target), 1, fp );
	return Target;
}
// - ------------------------------------------------------------------------------------------ - //
inline const unsigned char readswap_uchar_File( FILE* fp ) {
	unsigned char Target;
	fread( &Target, sizeof(Target), 1, fp );
	return Target;
}
// - ------------------------------------------------------------------------------------------ - //
inline const float readswap_float_File( FILE* fp ) {
	float Target;
	fread( &Target, sizeof(Target), 1, fp );
	return byteswap4(Target);
}
// - ------------------------------------------------------------------------------------------ - //
inline const double readswap_double_File( FILE* fp ) {
	double Target;
	fread( &Target, sizeof(Target), 1, fp );
	return byteswap8(Target);
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Endianness specific inversion read //
// - ------------------------------------------------------------------------------------------ - //
inline const long long int readbe_int64_File( FILE* fp ) {
	long long int Target;
	fread( &Target, sizeof(Target), 1, fp );
	return beswap8(Target);
}
// - ------------------------------------------------------------------------------------------ - //
inline const unsigned long long int readbe_uint64_File( FILE* fp ) {
	unsigned long long int Target;
	fread( &Target, sizeof(Target), 1, fp );
	return beswap8(Target);
}
// - ------------------------------------------------------------------------------------------ - //
inline const int readbe_int_File( FILE* fp ) {
	int Target;
	fread( &Target, sizeof(Target), 1, fp );
	return beswap4(Target);
}
// - ------------------------------------------------------------------------------------------ - //
inline const unsigned int readbe_uint_File( FILE* fp ) {
	unsigned int Target;
	fread( &Target, sizeof(Target), 1, fp );
	return beswap4(Target);
}
// - ------------------------------------------------------------------------------------------ - //
inline const short readbe_short_File( FILE* fp ) {
	short Target;
	fread( &Target, sizeof(Target), 1, fp );
	return beswap2(Target);
}
// - ------------------------------------------------------------------------------------------ - //
inline const unsigned short readbe_ushort_File( FILE* fp ) {
	unsigned short Target;
	fread( &Target, sizeof(Target), 1, fp );
	return beswap2(Target);
}
// - ------------------------------------------------------------------------------------------ - //
inline const char readbe_char_File( FILE* fp ) {
	char Target;
	fread( &Target, sizeof(Target), 1, fp );
	return Target;
}
// - ------------------------------------------------------------------------------------------ - //
inline const unsigned char readbe_uchar_File( FILE* fp ) {
	unsigned char Target;
	fread( &Target, sizeof(Target), 1, fp );
	return Target;
}
// - ------------------------------------------------------------------------------------------ - //
inline const float readbe_float_File( FILE* fp ) {
	float Target;
	fread( &Target, sizeof(Target), 1, fp );
	return beswap4(Target);
}
// - ------------------------------------------------------------------------------------------ - //
inline const double readbe_double_File( FILE* fp ) {
	double Target;
	fread( &Target, sizeof(Target), 1, fp );
	return beswap8(Target);
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Endianness Specific inversion read //
// - ------------------------------------------------------------------------------------------ - //
inline const long long int readle_int64_File( FILE* fp ) {
	long long int Target;
	fread( &Target, sizeof(Target), 1, fp );
	return leswap8(Target);
}
// - ------------------------------------------------------------------------------------------ - //
inline const unsigned long long int readle_uint64_File( FILE* fp ) {
	unsigned long long int Target;
	fread( &Target, sizeof(Target), 1, fp );
	return leswap8(Target);
}
// - ------------------------------------------------------------------------------------------ - //
inline const int readle_int_File( FILE* fp ) {
	int Target;
	fread( &Target, sizeof(Target), 1, fp );
	return leswap4(Target);
}
// - ------------------------------------------------------------------------------------------ - //
inline const unsigned int readle_uint_File( FILE* fp ) {
	unsigned int Target;
	fread( &Target, sizeof(Target), 1, fp );
	return leswap4(Target);
}
// - ------------------------------------------------------------------------------------------ - //
inline const short readle_short_File( FILE* fp ) {
	short Target;
	fread( &Target, sizeof(Target), 1, fp );
	return leswap2(Target);
}
// - ------------------------------------------------------------------------------------------ - //
inline const unsigned short readle_ushort_File( FILE* fp ) {
	unsigned short Target;
	fread( &Target, sizeof(Target), 1, fp );
	return leswap2(Target);
}
// - ------------------------------------------------------------------------------------------ - //
inline const char readle_char_File( FILE* fp ) {
	char Target;
	fread( &Target, sizeof(Target), 1, fp );
	return Target;
}
// - ------------------------------------------------------------------------------------------ - //
inline const unsigned char readle_uchar_File( FILE* fp ) {
	unsigned char Target;
	fread( &Target, sizeof(Target), 1, fp );
	return Target;
}
// - ------------------------------------------------------------------------------------------ - //
inline const float readle_float_File( FILE* fp ) {
	float Target;
	fread( &Target, sizeof(Target), 1, fp );
	return leswap4(Target);
}
// - ------------------------------------------------------------------------------------------ - //
inline const double readle_double_File( FILE* fp ) {
	double Target;
	fread( &Target, sizeof(Target), 1, fp );
	return leswap8(Target);
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
//}; // namespace Data //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_File_LongReads_H__ //
// - ------------------------------------------------------------------------------------------ - //
