// - ------------------------------------------------------------------------------------------ - //
// DataArray - A typed DataBlock.  A C implementation, and a lightweight STL vector. //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_DataArray_Core_H__
#define __Library_Data_DataArray_Core_H__
// - ------------------------------------------------------------------------------------------ - //
#ifdef _MSC_VER
#pragma warning (disable : 4200) // Zero sized array member //
#endif // _MSC_VER
// - ------------------------------------------------------------------------------------------ - //
//#include <cstring>
#include "DataBlock_Core.h"
// - ------------------------------------------------------------------------------------------ - //
// TODO: Insertion code, Alignment resizing (min, max), searching, sorting  //
// NOTE: Consider making reallocate specific to max size change.
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
struct DataArray {
	st32 Size;
	Type Data[0];
};
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// Set DataArray //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void set_DataArray( DataArray<Type>* _Dest, const Type& _InitValue ) {
	// Set value in all entries //
	for( st idx = _Dest->Size; idx--; ) {
		_Dest->Data[idx] = _InitValue;
	}
}
// - ------------------------------------------------------------------------------------------ - //
// Copy one DataArray to another, no larger than Destination DataArray Size //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void copy_DataArray( DataArray<Type>* _Src, DataArray<Type>* _Dest ) {
	// If source is smaller than the destination //
	if ( _Dest->Size > _Src->Size ) {
		// Copy only Source number of entries //
		for( st idx = _Src->Size; idx--; ) {
			_Dest->Data[idx] = _Src->Data[idx];
		}
	}
	else {
		// Copy Destination number of entries //
		for( st idx = _Dest->Size; idx--; ) {
			_Dest->Data[idx] = _Src->Data[idx];
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void copy_DataArray( DataBlock* _Src, DataArray<Type>* _Dest ) {
	Type* SrcPtr = (Type*)_Src->Data;
	st32 SrcSize = _Src->Size / sizeof( Type );
	
	// If source is smaller than the destination //
	if ( _Dest->Size > SrcSize ) {
		// Copy only Source number of entries //
		for( st idx = SrcSize; idx--; ) {
			_Dest->Data[idx] = SrcPtr[idx];
		}
	}
	else {
		// Copy Destination number of entries //
		for( st idx = _Dest->Size; idx--; ) {
			_Dest->Data[idx] = SrcPtr[idx];
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void copy_DataBlock( DataArray<Type>* _Src, DataBlock* _Dest  ) {
	char* SrcPtr = (char*)_Src->Data;
	st32 SrcSize = _Src->Size * sizeof( Type );
	
	copy_DataBlock( SrcPtr, SrcSize, _Dest );
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline DataArray<Type>* new_DataArray( const st32 _Size ) {
	DataArray<Type>* p = reinterpret_cast<DataArray<Type>*>(new char[ (_Size * sizeof(Type)) + sizeof(DataArray<Type>) ]);

	p->Size = _Size;

	return p;
}
// - ------------------------------------------------------------------------------------------ - //
// Use this alternative "new" function when you want to initialize the DataArray to a value //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline DataArray<Type>* new_DataArray( const st32 _Size, const Type& _InitValue ) {
	// Allocate it //
	DataArray<Type>* NewDataArray = new_DataArray<Type>( _Size );
	
	// Initialize it //
	set_DataArray<Type>( NewDataArray, _InitValue );
	
	// Return it //
	return NewDataArray;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void delete_DataArray( DataArray<Type>* p ) {
	delete p;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void copy_DataArray( DataArray<Type>* _Src, DataArray<Type>* _Dest, const Type& _InitValue ) {
	// If source is smaller than the destination //
	if ( _Dest->Size > _Src->Size ) {
		// Copy Source number of entries //
		for( st idx = _Src->Size; idx--; ) {
			_Dest->Data[idx] = _Src->Data[idx];
		}
		
		// Fill the rest of the data with initializer //
		Type* NewDest = &_Dest->Data[_Src->Size];
		for( st idx = (_Dest->Size - _Src->Size); idx--; ) {
			NewDest[idx] = _InitValue;
		}
	}
	else {
		// Copy Destination number of entries //
		for( st idx = _Dest->Size; idx--; ) {
			_Dest->Data[idx] = _Src->Data[idx];
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
// Return a duplicate of an DataArray //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline DataArray<Type>* copy_DataArray( DataArray<Type>* _Src ) {
	// Allocate our new block //
	DataArray<Type>* NewBlock = new_DataArray<Type>( _Src->Size );
	
	// Copy the data to our new block //
	copy_DataArray<Type>( _Src, NewBlock );
	
	// Return the block //
	return NewBlock;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline DataArray<Type>* new_DataArray( DataArray<Type>* _Src ) {
	return copy_DataArray<Type>( _Src );
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// Construct an DataArray from a DataBlock //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline DataArray<Type>* copy_DataArray( DataBlock* _Src ) {
	// Allocate our new block //
	DataArray<Type>* NewBlock = new_DataArray<Type>( _Src->Size / sizeof(Type) );
	
	// Copy the data to our new block //
	copy_DataArray<Type>( _Src, NewBlock );
	
	// Return the block //
	return NewBlock;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline DataArray<Type>* new_DataArray( DataBlock* _Src ) {
	return copy_DataArray<Type>( _Src );
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline DataBlock* copy_DataBlock( DataArray<Type>* _Src ) {
	// Allocate our new block //
	DataBlock* NewBlock = new_DataBlock( _Src->Size * sizeof( Type ) );
	
	// Copy the data to our new block //
	copy_DataBlock( _Src, NewBlock );
	
	// Return the block //
	return NewBlock;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline DataBlock* new_DataBlock( DataArray<Type>* _Src ) {
	return copy_DataBlock( _Src );
}
// - ------------------------------------------------------------------------------------------ - //



// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void reallocate_DataArray( DataArray<Type>** p, const st32 _NewSize ) {
	// Allocate our new block //
	DataArray<Type>* NewDataArray = new_DataArray<Type>( _NewSize );
	
	// Copy the data to our new block //
	copy_DataArray<Type>( *p, NewDataArray );
	
	// Delete the old block ponted to //
	delete_DataArray<Type>( *p );
	
	// Make the pointer point to the new block //
	(*p) = NewDataArray;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void reallocate_DataArray( DataArray<Type>** p, const st32 _NewSize, const Type& _InitValue ) {
	// Allocate our new block //
	DataArray<Type>* NewDataArray = new_DataArray<Type>( _NewSize );
	
	// Copy the data to our new block //
	copy_DataArray<Type>( *p, NewDataArray, _InitValue );
	
	// Delete the old block ponted to //
	delete_DataArray<Type>( *p );
	
	// Make the pointer point to the new block //
	(*p) = NewDataArray;
}
// - ------------------------------------------------------------------------------------------ - //
// Variation of reallocate that looks at the internal size //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void reallocate_DataArray( DataArray<Type>** p ) {
	reallocate_DataArray<Type>( p, (*p)->Size );
}
// - ------------------------------------------------------------------------------------------ - //



// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void resize_DataArray( DataArray<Type>** p, const st32 _NewSize ) {
	// A cheat.  We can resize the block without reallocating
	if ( _NewSize <= (*p)->Size ) {
		// Set the size to the new size, and we're done //
		(*p)->Size = _NewSize;
	}
	else {
		// Well, we tried.  We need to reallocate and copy the data. //
		reallocate_DataArray<Type>( p, _NewSize );
	}
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void resize_DataArray( DataArray<Type>** p, const st32 _NewSize, const Type& _InitValue ) {
	// A cheat.  We can resize the block without reallocating
	if ( _NewSize <= (*p)->Size ) {
		st32 OldSize = (*p)->Size;
		
		// Set the size to the new size, and we're done //
		(*p)->Size = _NewSize;
		
		// If this grows us //
		if ( OldSize < _NewSize ) {
			// Fill in new values with passed value //
			for( st idx = (_NewSize - OldSize); idx--; ) {
				(*p)->Data[OldSize + idx] = _InitValue;
			}
		}
	}
	else {
		// Well, we tried.  We need to reallocate and copy the data. //
		reallocate_DataArray<Type>( p, _NewSize, _InitValue );
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void resize2_DataArray( DataArray<Type>** p, const st32 _NewSize ) {
	// A cheat.  We can resize the block without reallocating
	if ( _NewSize <= (*p)->Size ) {
		// Set the size to the new size, and we're done //
		(*p)->Size = _NewSize;
	}
	else {
		// Well, we tried.  We need to reallocate and copy the data. //
		reallocate_DataArray<Type>( p, _NewSize );
	}
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void resize2_DataArray( DataArray<Type>** p, const st32 _NewSize, const Type& _InitValue ) {
	// A cheat.  We can resize the block without reallocating
	if ( _NewSize <= (*p)->Size ) {
		st32 OldSize = (*p)->Size;
		
		// Set the size to the new size, and we're done //
		(*p)->Size = _NewSize;
		
		// If this grows us //
		if ( OldSize < _NewSize ) {
			// Fill in new values with passed value //
			for( st idx = (_NewSize - OldSize); idx--; ) {
				(*p)->Data[OldSize + idx] = _InitValue;
			}
		}
	}
	else {
		// Well, we tried.  We need to reallocate and copy the data. //
		reallocate_DataArray<Type>( p, _NewSize, _InitValue );
	}
}
// - ------------------------------------------------------------------------------------------ - //



// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void pushback_DataArray( DataArray<Type>** p, const Type& _InitValue ) {
	resize2_DataArray( p, (*p)->Size + 1, _InitValue );
} 
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline Type popback_DataArray( DataArray<Type>** p ) {
	// TODO: Assert if Size == 0 //
	(*p)->Size--;
	
	return (*p)->Data[ (*p)->Size ];
} 
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Push and pop large groups of objects on to the DataArray //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void pushblockback_DataArray( DataArray<Type>** p, const st32 _Value ) {
	resize2_DataArray( p, (*p)->Size + _Value );
} 
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void pushblockback_DataArray( DataArray<Type>** p, const st32 _Value, const Type& _InitValue ) {
	resize2_DataArray( p, (*p)->Size + _Value, _InitValue );
} 
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline Type popblockback_DataArray( DataArray<Type>** p, const st32 _Value ) {
	// TODO: Assert if Size == 0 //
	(*p)->Size -= _Value;
	
	return (*p)->Data[ (*p)->Size ];
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_DataArray_Core_H__ //
// - ------------------------------------------------------------------------------------------ - //
