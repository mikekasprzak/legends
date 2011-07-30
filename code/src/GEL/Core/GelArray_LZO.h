// - ------------------------------------------------------------------------------------------ - //
// ArrayCompression - Compression code for GelArray library //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_GelArray_LZO_H__
#define __Library_Data_GelArray_LZO_H__
// - ------------------------------------------------------------------------------------------ - //
#include "DataBlock_Core.h"
#include "DataBlock_LZO.h"

#include "GelArray_Core.h"
// - ------------------------------------------------------------------------------------------ - //
// Decode packed LZO data to a new GelArray //
template< class Type >
inline GelArray<Type>* unpack_LZO_GelArray( DataBlock* _Src ) {
	DataBlock* Uncompressed = unpack_LZO_DataBlock( _Src );
	GelArray<Type>* UncompressedArray = new_GelArray<Type>( Uncompressed );
	
	// Delet our intermediary //
	delete_DataBlock( Uncompressed );
	
	return UncompressedArray;
}
// - ------------------------------------------------------------------------------------------ - //
// Decode packed LZO data to a new GelArray //
template< class Type >
inline GelArray<Type>* unpack_LZO_GelArray( char* _Src, const st32 _SrcSize ) {
	DataBlock* Uncompressed = unpack_LZO_DataBlock( _Src, _SrcSize );
	GelArray<Type>* UncompressedArray = new_GelArray<Type>( Uncompressed );
	
	// Delet our intermediary //
	delete_DataBlock( Uncompressed );
	
	return UncompressedArray;
}
// - ------------------------------------------------------------------------------------------ - //
// Encode array data to a packed LZO DataBlock //
template< class Type >
inline DataBlock* pack_LZO_DataBlock( GelArray<Type>* _Src ) {
	DataBlock* Source = copy_DataBlock( (char*)_Src->Data, _Src->Size * sizeof( Type ) );
	DataBlock* Compressed = pack_LZO_DataBlock( Source );
	
	// Delete our Intermediary //
	delete_DataBlock( Source );
	
	return Compressed;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void cGelArray<Type>::UnpackLZO( cDataBlock& _Src ) {
	*this = cGelArray<Type>( unpack_LZO_GelArray<Type>( _Src._Data ) );
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void cGelArray<Type>::UnpackLZO( DataBlock* _Src ) {
	*this = cGelArray<Type>( unpack_LZO_GelArray<Type>( _Src ) );
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline DataBlock* cGelArray<Type>::PackLZO() {
	return pack_LZO_DataBlock( _Data );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_GelArray_LZO_H__ //
// - ------------------------------------------------------------------------------------------ - //
