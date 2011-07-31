// - ------------------------------------------------------------------------------------------ - //
// StaticArray SHA1 Hash - SHA1 Hashing code for StaticArray library //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_StaticArray_SHA1_H__
#define __Library_Data_StaticArray_SHA1_H__
// - ------------------------------------------------------------------------------------------ - //
#include "StaticArray_Core.h"
#include "Data_SHA1.h"
// - ------------------------------------------------------------------------------------------ - //
//namespace Data {
// - ------------------------------------------------------------------------------------------ - //
// Hash a block of data with an SHA1 sum //
// - ------------------------------------------------------------------------------------------ - //
template< class Type, size_t MaxSize >
inline const SHA1Hash hash_SHA1_StaticArray( const StaticArray<Type,MaxSize>* _Src ) {
	return hash_SHA1_Data( _Src->Data, _Src->Size * sizeof(Type) );
}
// - ------------------------------------------------------------------------------------------ - //
//}; // namespace Data //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_StaticArray_SHA1_H__ //
// - ------------------------------------------------------------------------------------------ - //