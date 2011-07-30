// - ------------------------------------------------------------------------------------------ - //
// StaticArray - A statically allocated array.  A C implementation, and a lightweight STL vector. //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_StaticArray_Core_H__
#define __Library_Data_StaticArray_Core_H__
// - ------------------------------------------------------------------------------------------ - //
#include "DataBlock_Core.h"
// - ------------------------------------------------------------------------------------------ - //
// TODO: Insertion code, Alignment resizing (min, max), searching, sorting  //
// - ------------------------------------------------------------------------------------------ - //
template< class Type, size_t MaxSize >
struct StaticArray {
//	size_t MaxSize;
	size_t Size;
	Type Data[MaxSize];
};
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// Set StaticArray //
// - ------------------------------------------------------------------------------------------ - //
template< class Type, size_t MaxSize >
inline void set_StaticArray( StaticArray<Type,MaxSize>* _Dest, const Type& _InitValue ) {
	// Set value in all entries //
	for( size_t idx = _Dest->Size; idx--; ) {
		_Dest->Data[idx] = _InitValue;
	}
}
// - ------------------------------------------------------------------------------------------ - //
// Copy one StaticArray to another, no larger than Destination StaticArray Size //
// - ------------------------------------------------------------------------------------------ - //
template< class Type, size_t MaxSize >
inline void copy_StaticArray( StaticArray<Type,MaxSize>* _Src, StaticArray<Type,MaxSize>* _Dest ) {
	// If source is smaller than the destination //
	if ( _Dest->Size > _Src->Size ) {
		// Copy only Source number of entries //
		for( size_t idx = _Src->Size; idx--; ) {
			_Dest->Data[idx] = _Src->Data[idx];
		}
	}
	else {
		// Copy Destination number of entries //
		for( size_t idx = _Dest->Size; idx--; ) {
			_Dest->Data[idx] = _Src->Data[idx];
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type, size_t MaxSize >
inline void copy_Array( DataBlock* _Src, StaticArray<Type,MaxSize>* _Dest ) {
	Type* SrcPtr = (Type*)_Src->Data;
	size_t SrcSize = _Src->Size / sizeof( Type );
	
	// If source is smaller than the destination //
	if ( _Dest->Size > SrcSize ) {
		// Copy only Source number of entries //
		for( size_t idx = SrcSize; idx--; ) {
			_Dest->Data[idx] = SrcPtr[idx];
		}
	}
	else {
		// Copy Destination number of entries //
		for( size_t idx = _Dest->Size; idx--; ) {
			_Dest->Data[idx] = SrcPtr[idx];
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type, size_t MaxSize >
inline void copy_DataBlock( StaticArray<Type,MaxSize>* _Src, DataBlock* _Dest  ) {
	char* SrcPtr = (char*)_Src->Data;
	size_t SrcSize = _Src->Size * sizeof( Type );
	
	copy_DataBlock( SrcPtr, SrcSize, _Dest );
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
//template< class Type, size_t MaxSize >
//inline StaticArray<Type,MaxSize>* new_StaticArray( const size_t _Size ) {
//	StaticArray<Type,MaxSize>* p = reinterpret_cast<StaticArray<Type,MaxSize>*>(new char[ (_Size * sizeof(Type)) + sizeof(StaticArray<Type,MaxSize>) ]);
//
//	p->Size = _Size;
//
//	return p;
//}
// - ------------------------------------------------------------------------------------------ - //
// Use this alternative "new" function when you want to initialize the Arary to a value //
// - ------------------------------------------------------------------------------------------ - //
//template< class Type, size_t MaxSize >
//inline StaticArray<Type,MaxSize>* new_StaticArray( const size_t _Size, const Type& _InitValue ) {
//	// Allocate it //
//	StaticArray<Type,MaxSize>* NewStaticArray = new_StaticArray<Type,MaxSize>( _Size );
//	
//	// Initialize it //
//	set_StaticArray<Type,MaxSize>( NewStaticArray, _InitValue );
//	
//	// Return it //
//	return NewStaticArray;
//}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
//template< class Type, size_t MaxSize >
//inline void delete_StaticArray( StaticArray<Type,MaxSize>* p ) {
//	delete p;
//}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
template< class Type, size_t MaxSize >
inline void copy_StaticArray( StaticArray<Type,MaxSize>* _Src, StaticArray<Type,MaxSize>* _Dest, const Type& _InitValue ) {
	// If source is smaller than the destination //
	if ( _Dest->Size > _Src->Size ) {
		// Copy Source number of entries //
		for( size_t idx = _Src->Size; idx--; ) {
			_Dest->Data[idx] = _Src->Data[idx];
		}
		
		// Fill the rest of the data with initializer //
		Type* NewDest = &_Dest->Data[_Src->Size];
		for( size_t idx = (_Dest->Size - _Src->Size); idx--; ) {
			NewDest[idx] = _InitValue;
		}
	}
	else {
		// Copy Destination number of entries //
		for( size_t idx = _Dest->Size; idx--; ) {
			_Dest->Data[idx] = _Src->Data[idx];
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
// Return a duplicate of an StaticArray //
// - ------------------------------------------------------------------------------------------ - //
//template< class Type, size_t MaxSize >
//inline StaticArray<Type,MaxSize>* copy_StaticArray( StaticArray<Type,MaxSize>* _Src ) {
//	// Allocate our new block //
//	StaticArray<Type,MaxSize>* NewBlock = new_StaticArray<Type,MaxSize>( _Src->Size );
//	
//	// Copy the data to our new block //
//	copy_StaticArray<Type,MaxSize>( _Src, NewBlock );
//	
//	// Return the block //
//	return NewBlock;
//}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
template< class Type, size_t MaxSize >
inline void resize_StaticArray( StaticArray<Type,MaxSize>** p, const size_t _NewSize ) {
	// A cheat.  We can resize the block without reallocating
	if ( _NewSize <= MaxSize ) {
		// Set the size to the new size, and we're done //
		(*p)->Size = _NewSize;
	}
	else {
		// Well, we're static.  If we could reallocate, we would.  Oh well. //
		// TODO: Assert, static allocation failed. //
	}
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type, size_t MaxSize >
inline void resize_StaticArray( StaticArray<Type,MaxSize>** p, const size_t _NewSize, const Type& _InitValue ) {
	// A cheat.  We can resize the block without reallocating
	if ( _NewSize <= MaxSize ) {
		size_t OldSize = (*p)->Size;
		
		// Set the size to the new size, and we're done //
		(*p)->Size = _NewSize;
		
		// If this grows us //
		if ( OldSize < _NewSize ) {
			// Fill in new values with passed value //
			for( size_t idx = (_NewSize - OldSize); idx--; ) {
				(*p)->Data[OldSize + idx] = _InitValue;
			}
		}
		
	}
	else {
		// Well, we're static.  If we could reallocate, we would.  Oh well. //
		// TODO: Assert, static allocation failed. //
	}
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
template< class Type, size_t MaxSize >
inline void pushback_StaticArray( StaticArray<Type,MaxSize>** p, const Type& _InitValue ) {
	resize_StaticArray( p, (*p)->Size + 1, _InitValue );
} 
// - ------------------------------------------------------------------------------------------ - //
template< class Type, size_t MaxSize >
inline Type popback_StaticArray( StaticArray<Type,MaxSize>** p ) {
	// TODO: Assert if Size == 0 //
	(*p)->Size--;
	
	return (*p)->Data[ (*p)->Size ];
} 
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_StaticArray_Core_H__ //
// - ------------------------------------------------------------------------------------------ - //
