// - ------------------------------------------------------------------------------------------ - //
// ArrayCompression - Compression code for Array library //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_GelArray_ZLIB_H__
#define __Library_Data_GelArray_ZLIB_H__
// - ------------------------------------------------------------------------------------------ - //
#include "DataBlock_Core.h"
#include "DataBlock_ZLIB.h"

#include "GelArray_Core.h"
// - ------------------------------------------------------------------------------------------ - //
// Decode packed ZLIB data to a new GelArray //
template< class Type >
inline GelArray<Type>* unpack_ZLIB_GelArray( DataBlock* _Src ) {
	DataBlock* Uncompressed = unpack_ZLIB_DataBlock( _Src );
	GelArray<Type>* UncompressedGelArray = new_GelArray<Type>( Uncompressed );
	
	// Delet our intermediary //
	delete_DataBlock( Uncompressed );
	
	return UncompressedGelArray;
}
// - ------------------------------------------------------------------------------------------ - //
// Decode packed ZLIB data to a new GelArray //
template< class Type >
inline GelArray<Type>* unpack_ZLIB_GelArray( char* _Src, const st32 _SrcSize ) {
	DataBlock* Uncompressed = unpack_ZLIB_DataBlock( _Src, _SrcSize );
	GelArray<Type>* UncompressedGelArray = new_GelArray<Type>( Uncompressed );
	
	// Delet our intermediary //
	delete_DataBlock( Uncompressed );
	
	return UncompressedGelArray;
}
// - ------------------------------------------------------------------------------------------ - //
// Encode GelArray data to a packed ZLIB DataBlock //
template< class Type >
inline DataBlock* pack_ZLIB_DataBlock( GelArray<Type>* _Src ) {
	DataBlock* Source = copy_DataBlock( (char*)_Src->Data, _Src->Size * sizeof( Type ) );
	DataBlock* Compressed = pack_ZLIB_DataBlock( Source );
	
	// Delete our Intermediary //
	delete_DataBlock( Source );
	
	return Compressed;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void cGelArray<Type>::UnpackZLIB( cDataBlock& _Src ) {
	*this = cGelArray<Type>( unpack_ZLIB_GelArray<Type>( _Src._Data ) );
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void cGelArray<Type>::UnpackZLIB( DataBlock* _Src ) {
	*this = cGelArray<Type>( unpack_ZLIB_GelArray<Type>( _Src ) );
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline DataBlock* cGelArray<Type>::PackZLIB() {
	return pack_ZLIB_DataBlock( _Data );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_GelArray_ZLIB_H__ //
// - ------------------------------------------------------------------------------------------ - //
