// - ------------------------------------------------------------------------------------------ - //
// GelArray - A dynamically allocated array.  A C implementation, and a lightweight STL vector. //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_GelArray_Core_H__
#define __Library_Data_GelArray_Core_H__
// - ------------------------------------------------------------------------------------------ - //
#ifdef _MSC_VER
#pragma warning (disable : 4200) // Zero sized array member //
#endif // _MSC_VER
// - ------------------------------------------------------------------------------------------ - //
#include <new>

#include <Style/GelStyle.h>
#include "DataBlock_Core.h"
// - ------------------------------------------------------------------------------------------ - //
// TODO: Insertion code, Alignment resizing (min, max), searching, sorting  //
// NOTE: Consider making reallocate specific to max size change.
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
struct GelArray {
//	st32 MaxSize;
	st32 Size;
	Type Data[0];
	
	inline Type& Back() {
		// TODO: Assert Size //
		return Data[Size-1];
	}
	
	inline const Type& Back() const {
		// TODO: Assert Size //
		return Data[Size-1];
	}
	
	inline Type& Front() {
		// TODO: Assert Size //
		return Data[0];
	}

	inline const Type& Front() const {
		// TODO: Assert Size //
		return Data[0];
	}
	
	// No Operator [] because GelArray's are always pointers //
};
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// Set GelArray //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void set_GelArray( GelArray<Type>* _Dest, const Type& _InitValue ) {
	// Set value in all entries //
	for( st idx = _Dest->Size; idx--; ) {
		_Dest->Data[idx] = _InitValue;
	}
}
// - ------------------------------------------------------------------------------------------ - //
// Copy one GelArray to another, no larger than Destination GelArray Size //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void copy_GelArray( GelArray<Type>* _Src, GelArray<Type>* _Dest ) {
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
inline void copy_GelArray( DataBlock* _Src, GelArray<Type>* _Dest ) {
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
inline void copy_DataBlock( GelArray<Type>* _Src, DataBlock* _Dest  ) {
	char* SrcPtr = (char*)_Src->Data;
	st32 SrcSize = _Src->Size * sizeof( Type );
	
	copy_DataBlock( SrcPtr, SrcSize, _Dest );
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline GelArray<Type>* _new_GelArray( const st32 _Size ) {
	GelArray<Type>* p = reinterpret_cast<GelArray<Type>*>(new char[ (_Size * sizeof(Type)) + sizeof(GelArray<Type>) ]);

	p->Size = _Size;
//	p->MaxSize = _Size;

	return p;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline GelArray<Type>* new_GelArray( const st32 _Size ) {
	GelArray<Type>* p = _new_GelArray<Type>( _Size );
	
	// Placement New //
	for ( st32 idx = 0; idx < _Size; idx++ ) {
		new(&(p->Data[idx])) Type;
	}

	return p;
}
// - ------------------------------------------------------------------------------------------ - //
// Use this alternative "new" function when you want to initialize the GelArray to a value //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline GelArray<Type>* new_GelArray( const st32 _Size, const Type& _InitValue ) {
	// Allocate it //
	GelArray<Type>* NewGelArray = _new_GelArray<Type>( _Size );
	
	// Initialize it //
	set_GelArray<Type>( NewGelArray, _InitValue );
	
	// Return it //
	return NewGelArray;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void _delete_GelArray( GelArray<Type>* p ) {
	delete [] p;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void delete_GelArray( GelArray<Type>* p ) {
	// Placement Delete //
	for ( st32 idx = 0; idx < p->Size; idx++ ) {
		p->Data[idx].~Type();
	}
	
	_delete_GelArray<Type>( p );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Now returns a pointer. All functions will return pointers. Never References. //
template< class Type >
inline Type* index_GelArray( GelArray<Type>* p, const size_t _Index ) {
	return &(p->Data[ _Index ]);
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const st32 size_GelArray( GelArray<Type>* p ) {
	return p->Size;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// New that set the maximum size //
// - ------------------------------------------------------------------------------------------ - //
//template< class Type >
//inline GelArray<Type>* newmax_GelArray( const st32 _MaxSize ) {
//	GelArray<Type>* p = reinterpret_cast<GelArray<Type>*>(new char[ (_MaxSize * sizeof(Type)) + sizeof(GelArray<Type>) ]);
//
//	p->Size = 0;
//	p->MaxSize = _MaxSize;
//
//	return p;
//}
// - ------------------------------------------------------------------------------------------ - //
//template< class Type >
//inline GelArray<Type>* newmax_GelArray( const st32 _MaxSize, const st32 _Size ) {
//	GelArray<Type>* p = reinterpret_cast<GelArray<Type>*>(new char[ (_MaxSize * sizeof(Type)) + sizeof(GelArray<Type>) ]);
//
//	p->Size = _Size;
//	p->MaxSize = _MaxSize;
//
//	return p;
//}
// - ------------------------------------------------------------------------------------------ - //
//template< class Type >
//inline GelArray<Type>* newmax_GelArray( const st32 _MaxSize, const st32 _Size, const Type& _InitValue ) {
//	// Allocate it //
//	GelArray<Type>* NewGelArray = newmax_GelArray<Type>( _MaxSize, _Size );
//	
//	// Initialize it //
//	set_GelArray<Type>( NewGelArray, _InitValue );
//	
//	// Return it //
//	return NewGelArray;
//}
// - ------------------------------------------------------------------------------------------ - //



// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void copy_GelArray( GelArray<Type>* _Src, GelArray<Type>* _Dest, const Type& _InitValue ) {
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
// Return a duplicate of an GelArray //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline GelArray<Type>* copy_GelArray( GelArray<Type>* _Src ) {
	// Allocate our new block //
	GelArray<Type>* NewBlock = new_GelArray<Type>( _Src->Size );
	
	// Copy the data to our new block //
	copy_GelArray<Type>( _Src, NewBlock );
	
	// Return the block //
	return NewBlock;
}
// - ------------------------------------------------------------------------------------------ - //
//template< class Type >
//inline GelArray<Type>* new_GelArray( GelArray<Type>* _Src ) {
//	return copy_GelArray<Type>( _Src );
//}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// Construct an GelArray from a DataBlock //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline GelArray<Type>* copy_GelArray( DataBlock* _Src ) {
	// Allocate our new block //
	GelArray<Type>* NewBlock = new_GelArray<Type>( _Src->Size / sizeof(Type) );
	
	// Copy the data to our new block //
	copy_GelArray<Type>( _Src, NewBlock );
	
	// Return the block //
	return NewBlock;
}
// - ------------------------------------------------------------------------------------------ - //
//template< class Type >
//inline GelArray<Type>* new_GelArray( DataBlock* _Src ) {
//	return copy_GelArray<Type>( _Src );
//}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline DataBlock* copy_DataBlock( GelArray<Type>* _Src ) {
	// Allocate our new block //
	DataBlock* NewBlock = new_DataBlock( _Src->Size * sizeof( Type ) );
	
	// Copy the data to our new block //
	copy_DataBlock( _Src, NewBlock );
	
	// Return the block //
	return NewBlock;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline DataBlock* new_DataBlock( GelArray<Type>* _Src ) {
	return copy_DataBlock( _Src );
}
// - ------------------------------------------------------------------------------------------ - //



// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void reallocate_GelArray( GelArray<Type>** p, const st32 _NewSize ) {
	// Allocate our new block //
	GelArray<Type>* NewGelArray = new_GelArray<Type>( _NewSize );
	
	if ( *p ) {
		// Copy the data to our new block //
		copy_GelArray<Type>( *p, NewGelArray );
		
		// Delete the old block ponted to //
		delete_GelArray<Type>( *p );
	}
	
	// Make the pointer point to the new block //
	(*p) = NewGelArray;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void reallocate_GelArray( GelArray<Type>** p, const st32 _NewSize, const Type& _InitValue ) {
	// Allocate our new block //
	GelArray<Type>* NewGelArray = new_GelArray<Type>( _NewSize );
	
	if ( *p ) {
		// Copy the data to our new block //
		copy_GelArray<Type>( *p, NewGelArray, _InitValue );
		
		// Delete the old block ponted to //
		delete_GelArray<Type>( *p );
	}
	else {
		// No copy made, so fill in with the data //
		set_GelArray<Type>( NewGelArray, _InitValue );
	}
	
	// Make the pointer point to the new block //
	(*p) = NewGelArray;
}
// - ------------------------------------------------------------------------------------------ - //
// Variation of reallocate that looks at the internal size //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void reallocate_GelArray( GelArray<Type>** p ) {
	reallocate_GelArray<Type>( p, (*p)->Size );
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
//template< class Type >
//inline void reallocatemax_GelArray( GelArray<Type>** p, const st32 _NewMaxSize ) {
//	// Allocate our new block //
//	GelArray<Type>* NewGelArray = newmax_GelArray<Type>( _NewMaxSize, (*p)->Size );
//	
//	if ( *p ) {
//		// Copy the data to our new block //
//		copy_GelArray<Type>( *p, NewGelArray );
//		
//		// Delete the old block ponted to //
//		delete_GelArray<Type>( *p );
//	}
//		
//	// Make the pointer point to the new block //
//	(*p) = NewGelArray;
//}
// - ------------------------------------------------------------------------------------------ - //
//template< class Type >
//inline void reallocatemax_GelArray( GelArray<Type>** p, const st32 _NewMaxSize, const st32 _NewSize ) {
//	// Allocate our new block //
//	GelArray<Type>* NewGelArray = newmax_GelArray<Type>( _NewMaxSize, _NewSize );
//	
//	if ( *p ) {
//		// Copy the data to our new block //
//		copy_GelArray<Type>( *p, NewGelArray );
//		
//		// Delete the old block ponted to //
//		delete_GelArray<Type>( *p );
//	}
//	
//	// Make the pointer point to the new block //
//	(*p) = NewGelArray;
//}
// - ------------------------------------------------------------------------------------------ - //
//template< class Type >
//inline void reallocatemax_GelArray( GelArray<Type>** p, const st32 _NewMaxSize, const st32 _NewSize, const Type& _InitValue ) {
//	// Allocate our new block //
//	GelArray<Type>* NewGelArray = newmax_GelArray<Type>( _NewMaxSize, _NewSize );
//	
//	if ( *p ) {
//		// Copy the data to our new block //
//		copy_GelArray<Type>( *p, NewGelArray, _InitValue );
//		
//		// Delete the old block ponted to //
//		delete_GelArray<Type>( *p );
//	}
//	else {
//		// No copy made, so fill in with the data //
//		set_GelArray<Type>( NewGelArray, _InitValue );		
//	}
//	
//	// Make the pointer point to the new block //
//	(*p) = NewGelArray;
//}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void resize_GelArray( GelArray<Type>** p, const st32 _NewSize ) {
	if ( *p == 0 ) {
		*p = new_GelArray<Type>( _NewSize );
	}
	// A cheat.  We can resize the block without reallocating
	else if ( _NewSize <= (*p)->Size ) {
		// Set the size to the new size, and we're done //
		(*p)->Size = _NewSize;
	}
	else {
		// Well, we tried.  We need to reallocate and copy the data. //
		reallocate_GelArray<Type>( p, _NewSize );
	}
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void resize_GelArray( GelArray<Type>** p, const st32 _NewSize, const Type& _InitValue ) {
	if ( *p == 0 ) {
		*p = new_GelArray<Type>( _NewSize, _InitValue );
	}
	// A cheat.  We can resize the block without reallocating
	else if ( _NewSize <= (*p)->Size ) {
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
		reallocate_GelArray<Type>( p, _NewSize, _InitValue );
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
//template< class Type >
//inline void resize2_GelArray( GelArray<Type>** p, const st32 _NewSize ) {
//	if ( *p == 0 ) {
//		*p = new_GelArray<Type>( _NewSize );		
//	}
//	// A cheat.  We can resize the block without reallocating
//	else if ( _NewSize <= (*p)->MaxSize ) {
//		// Set the size to the new size, and we're done //
//		(*p)->Size = _NewSize;
//	}
//	else {
//		// Well, we tried.  We need to reallocate and copy the data. //
//		st32 DoubleSize = (*p)->MaxSize + (*p)->MaxSize;
//		st32 NewMaxSize = DoubleSize > _NewSize ? DoubleSize : _NewSize;
//		
//		reallocatemax_GelArray<Type>( p, NewMaxSize, _NewSize );
//	}
//}
// - ------------------------------------------------------------------------------------------ - //
//template< class Type >
//inline void resize2_GelArray( GelArray<Type>** p, const st32 _NewSize, const Type& _InitValue ) {
//	if ( *p == 0 ) {
//		*p = new_GelArray<Type>( _NewSize, _InitValue );
//	}
//	// A cheat.  We can resize the block without reallocating
//	else if ( _NewSize <= (*p)->MaxSize ) {
//		st32 OldSize = (*p)->Size;
//		
//		// Set the size to the new size, and we're done //
//		(*p)->Size = _NewSize;
//		
//		// If this grows us //
//		if ( OldSize < _NewSize ) {
//			// Fill in new values with passed value //
//			for( st32 idx = (_NewSize - OldSize); idx--; ) {
//				(*p)->Data[OldSize + idx] = _InitValue;
//			}
//		}
//	}
//	else {
//		// Well, we tried.  We need to reallocate and copy the data. //
//		st32 DoubleSize = (*p)->MaxSize + (*p)->MaxSize;
//		st32 NewMaxSize = DoubleSize > _NewSize ? DoubleSize : _NewSize;
//		
//		reallocatemax_GelArray<Type>( p, NewMaxSize, _NewSize, _InitValue );
//	}
//}
// - ------------------------------------------------------------------------------------------ - //



// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void pushback_GelArray( GelArray<Type>** p ) {
	Warning( p == 0, "Zero Pointer Pointer" );

	if ( (*p) == 0 ) {
//		resize2_GelArray<Type>( p, 1 );
		resize_GelArray<Type>( p, 1 );
	}
	else {
//		resize2_GelArray<Type>( p, (*p)->Size + 1 );
		resize_GelArray<Type>( p, (*p)->Size + 1 );
	}
} 
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void pushback_GelArray( GelArray<Type>** p, const Type& _Value ) {
	Warning( p == 0, "Zero Pointer Pointer" );

	if ( (*p) == 0 )
//		resize2_GelArray<Type>( p, 1, _Value );
		resize_GelArray<Type>( p, 1, _Value );
	else
//		resize2_GelArray<Type>( p, (*p)->Size + 1, _Value );
		resize_GelArray<Type>( p, (*p)->Size + 1, _Value );
} 
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline Type popback_GelArray( GelArray<Type>** p ) {
	Warning( p == 0, "Zero Pointer Pointer" );
	
	return_value_Warning ( Type(), (*p)->Size == 0, "Zero Size" );

	// TODO: Assert if Size == 0 //
	(*p)->Size--;
	
	return (*p)->Data[ (*p)->Size ];
} 
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void insert_GelArray( GelArray<Type>** p, const size_t Index, const Type& _Value ) {
	Warning( p == 0, "Zero Pointer Pointer" );

	pushback_GelArray( p );

	Warning( Index >= (*p)->Size, "Invalid Index %i (Size: %i)", (int)Index, (int)(*p)->Size );

	if ( (*p)->Size > 1 ) {
		for( st idx = (*p)->Size-1; idx-- != Index; ) {
			(*p)->Data[idx+1] = (*p)->Data[idx];
		}
	}

	(*p)->Data[ Index ] = _Value;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void erase_GelArray( GelArray<Type>** p, const size_t Index ) {
	Warning( p == 0, "Zero Pointer Pointer" );
	//Warning( (*p) == 0, "Zero Pointer" );
	Warning( Index >= (*p)->Size, "Invalid Index %i (Size: %i)", Index, (*p)->Size );

	// This is okay //
	if ( (*p) == 0 )
		return;
	
	// TODO: Assert this? 
	if ( (*p)->Size == 0 )
		return;
	
	st Size = (*p)->Size-1;
	for( st idx = Index; idx < Size; idx++ ) {
		(*p)->Data[idx] = (*p)->Data[idx+1];
	}

	(*p)->Size--;
	
	// NOTE: popback doesn't work here, since popback gets the last element //
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline int findfirst_GelArray( GelArray<Type>** p, const Type& _Value ) {
	Warning( p == 0, "Zero Pointer Pointer" );

	// This is okay //
	if ( (*p) == 0 )
		return -1;
		
	for( st idx = 0; idx < (*p)->Size; idx++ ) {
		if ( (*p)->Data[idx] == _Value ) {
			return idx;
		}
	}

	return -1;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline int findlast_GelArray( GelArray<Type>** p, const Type& _Value ) {
	Warning( p == 0, "Zero Pointer Pointer" );

	// This is okay //
	if ( (*p) == 0 )
		return -1;
		
	for( st idx = (*p)->Size; idx--; ) {
		if ( (*p)->Data[idx] == _Value ) {
			return idx;
		}
	}

	return -1;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline Type* back_GelArray( GelArray<Type>* p ) {
	if ( p == 0 )
		return 0;
	else
		return &(p->Data[ p->Size - 1 ]);
} 
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline Type* front_GelArray( GelArray<Type>* p ) {
	if ( p == 0 )
		return 0;
	else
		return &(p->Data[ 0 ]);
} 
// - ------------------------------------------------------------------------------------------ - //



// - ------------------------------------------------------------------------------------------ - //
// Push and pop large groups of objects on to the GelArray //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void pushblockback_GelArray( GelArray<Type>** p, const st32 _Count ) {
	if ( (*p) == 0 )
		resize_GelArray( p, _Count );
	else
		resize_GelArray( p, (*p)->Size + _Count );
} 
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void pushblockback_GelArray( GelArray<Type>** p, const void* Src, const st32 _Count ) {
	st32 OldSize = (*p)->Size;
	
	if ( (*p) == 0 )
		resize_GelArray( p, _Count );
	else
		resize_GelArray( p, (*p)->Size + _Count );
	
	copy_Data( Src, &((*p)->Data[ OldSize ]), sizeof( Type ) * _Count );
} 
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline Type* popblockback_GelArray( GelArray<Type>** p, const st32 _Count ) {
	// TODO: Assert if Size == 0 //
	(*p)->Size -= _Count;
	
	return &((*p)->Data[ (*p)->Size ]);
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_GelArray_Core_H__ //
// - ------------------------------------------------------------------------------------------ - //
