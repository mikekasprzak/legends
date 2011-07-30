// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_GELCore_File_ReadWriteUtil_H__
#define __Library_GELCore_File_ReadWriteUtil_H__
// - ------------------------------------------------------------------------------------------ - //
#include "Endian.h"
// - ------------------------------------------------------------------------------------------ - //
#define MAKE_GEL_FILE_READWRITE_UTIL_FUNCTIONS( _TYPE ) \
\
template< class Type > \
inline const Type read_##_TYPE( _TYPE* fp ) { \
	Type Target; \
	read_##_TYPE( fp, (char*)&Target, sizeof(Target) ); \
	return Target; \
} \
\
template< class Type > \
inline const Type readswap_##_TYPE( _TYPE* fp ) { \
	Type Target = read_##_TYPE<Type>(fp); \
	return byteswap(Target); \
} \
\
template< class Type > \
inline const Type readbe_##_TYPE( _TYPE* fp ) { \
	Type Target = read_##_TYPE<Type>(fp); \
	return beswap(Target); \
} \
\
template< class Type > \
inline const Type readle_##_TYPE( _TYPE* fp ) { \
	Type Target = read_##_TYPE<Type>(fp); \
	return leswap(Target); \
} \
\
\
template< class Type > \
inline const size_t write_##_TYPE( _TYPE* fp, const Type Data ) { \
	return write_##_TYPE( fp, (const char*)&Data, sizeof(Data) ); \
} \
\
template< class Type > \
inline const size_t writeswap_##_TYPE( _TYPE* fp, const Type Data ) { \
	Type Copy = byteswap(Data); \
	return write_##_TYPE<Type>( fp, Copy ); \
} \
\
template< class Type > \
inline const size_t writebe_##_TYPE( _TYPE* fp, const Type Data ) { \
	Type Copy = beswap(Data); \
	return write_##_TYPE<Type>( fp, Copy ); \
} \
\
template< class Type > \
inline const size_t writele_##_TYPE( _TYPE* fp, const Type Data ) { \
	Type Copy = leswap(Data); \
	return write_##_TYPE<Type>( fp, Copy ); \
} \
\
\
template< class Type > \
inline void fill_##_TYPE( _TYPE* fp, const Type Data, int Count ) { \
	for ( ; Count--; ) { \
		write_##_TYPE<Type>(fp, Data ); \
	} \
} \
\
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_GEL_Core_File_ReadWriteUtil_H__ //
// - ------------------------------------------------------------------------------------------ - //
