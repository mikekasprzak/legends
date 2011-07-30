// - ------------------------------------------------------------------------------------------ - //
// StaticArray Compression - Compression of Static Data //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_StaticArray_BZIP_H__
#define __Library_Data_StaticArray_BZIP_H__
// - ------------------------------------------------------------------------------------------ - //
#include "DataBlock_Core.h"
#include "DataBlock_BZIP.h"

#include "StaticArray_Core.h"
// - ------------------------------------------------------------------------------------------ - //
//namespace Data {
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Encode array data to a packed BZIP DataBlock //
template< class Type, size_t MaxSize >
inline DataBlock* pack_BZIP_StaticArray( StaticArray<Type,MaxSize>* _Src ) {
	DataBlock* Source = copy_DataBlock( (char*)_Src->Data, _Src->Size * sizeof( Type ) );
	DataBlock* Compressed = pack_BZIP_DataBlock( Source );
	
	// Delete our Intermediary //
	delete_DataBlock( Source );
	
	return Compressed;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
//}; // namepsace Data //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_StaticArray_BZIP_H__ //
// - ------------------------------------------------------------------------------------------ - //
