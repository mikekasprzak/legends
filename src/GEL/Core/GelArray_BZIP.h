// - ------------------------------------------------------------------------------------------ - //
// ArrayCompression - Compression code for Array library //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_GelArray_BZIP_H__
#define __Library_Data_GelArray_BZIP_H__
// - ------------------------------------------------------------------------------------------ - //
#include "DataBlock_Core.h"
#include "DataBlock_BZIP.h"

#include "GelArray_Core.h"
// - ------------------------------------------------------------------------------------------ - //
// Decode packed BZIP data to a new GelArray //
template< class Type >
inline GelArray<Type>* unpack_BZIP_GelArray( DataBlock* _Src ) {
	DataBlock* Uncompressed = unpack_BZIP_DataBlock( _Src );
	GelArray<Type>* UncompressedGelArray = new_GelArray<Type>( Uncompressed );
	
	// Delet our intermediary //
	delete_DataBlock( Uncompressed );
	
	return UncompressedGelArray;
}
// - ------------------------------------------------------------------------------------------ - //
// Decode packed BZIP data to a new GelArray //
template< class Type >
inline GelArray<Type>* unpack_BZIP_GelArray( char* _Src, const st32 _SrcSize ) {
	DataBlock* Uncompressed = unpack_BZIP_DataBlock( _Src, _SrcSize );
	GelArray<Type>* UncompressedGelArray = new_GelArray<Type>( Uncompressed );
	
	// Delet our intermediary //
	delete_DataBlock( Uncompressed );
	
	return UncompressedGelArray;
}
// - ------------------------------------------------------------------------------------------ - //
// Encode GelArray data to a packed BZIP DataBlock //
template< class Type >
inline DataBlock* pack_BZIP_DataBlock( GelArray<Type>* _Src ) {
	DataBlock* Source = copy_DataBlock( (char*)_Src->Data, _Src->Size * sizeof( Type ) );
	DataBlock* Compressed = pack_BZIP_DataBlock( Source );
	
	// Delete our Intermediary //
	delete_DataBlock( Source );
	
	return Compressed;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void cGelArray<Type>::UnpackBZIP( cDataBlock& _Src ) {
	*this = cGelArray<Type>( unpack_BZIP_GelArray<Type>( _Src._Data ) );
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void cGelArray<Type>::UnpackBZIP( DataBlock* _Src ) {
	*this = cGelArray<Type>( unpack_BZIP_GelArray<Type>( _Src ) );
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline DataBlock* cGelArray<Type>::PackBZIP() {
	return pack_BZIP_DataBlock( _Data );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_GelArray_BZIP_H__ //
// - ------------------------------------------------------------------------------------------ - //
