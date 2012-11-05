// - ------------------------------------------------------------------------------------------ - //
// GelMaxArray - A dynamically allocated array.  A C implementation, and a lightweight STL vector. //
//
// NOTE: resize2 is the double size function. Should really be "resize2x" //
// Formerly GelArray
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_GelMaxArray_Core_H__
#define __Library_Data_GelMaxArray_Core_H__
// - ------------------------------------------------------------------------------------------ - //
#ifdef _MSC_VER
#pragma warning (disable : 4200) // Zero sized array member //
#endif // _MSC_VER
// - ------------------------------------------------------------------------------------------ - //
#include <new>

#include "GelTypes.h"
#include "DataBlock_Core.h"
// - ------------------------------------------------------------------------------------------ - //
// TODO: Insertion code, Alignment resizing (min, max), searching, sorting  //
// NOTE: Consider making reallocate specific to max size change.
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
struct GelMaxArray {
	st32 MaxSize;
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
	
	// No Operator [] because GelMaxArray's are always pointers //
};
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// Set GelMaxArray //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void set_GelMaxArray( GelMaxArray<Type>* _Dest, const Type& _InitValue ) {
	// Set value in all entries //
	for( st idx = _Dest->Size; idx--; ) {
		_Dest->Data[idx] = _InitValue;
	}
}
// - ------------------------------------------------------------------------------------------ - //
// Copy one GelMaxArray to another, no larger than Destination GelMaxArray Size //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void copy_GelMaxArray( GelMaxArray<Type>* _Src, GelMaxArray<Type>* _Dest ) {
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
inline void copy_GelMaxArray( DataBlock* _Src, GelMaxArray<Type>* _Dest ) {
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
inline void copy_DataBlock( GelMaxArray<Type>* _Src, DataBlock* _Dest  ) {
	char* SrcPtr = (char*)_Src->Data;
	st32 SrcSize = _Src->Size * sizeof( Type );
	
	copy_DataBlock( SrcPtr, SrcSize, _Dest );
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline GelMaxArray<Type>* _new_GelMaxArray( const st32 _Size ) {
	GelMaxArray<Type>* p = reinterpret_cast<GelMaxArray<Type>*>(new char[ (_Size * sizeof(Type)) + sizeof(GelMaxArray<Type>) ]);

	p->Size = _Size;
	p->MaxSize = _Size;

	return p;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline GelMaxArray<Type>* new_GelMaxArray( const st32 _Size ) {
	GelMaxArray<Type>* p = _new_GelMaxArray<Type>( _Size );
	
	// Placement New //
	for ( st32 idx = 0; idx < _Size; idx++ ) {
		new(&(p->Data[idx])) Type;
	}

	return p;
}
// - ------------------------------------------------------------------------------------------ - //
// Use this alternative "new" function when you want to initialize the GelMaxArray to a value //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline GelMaxArray<Type>* new_GelMaxArray( const st32 _Size, const Type& _InitValue ) {
	// Allocate it //
	GelMaxArray<Type>* NewGelMaxArray = _new_GelMaxArray<Type>( _Size );
	
	// Initialize it //
	set_GelMaxArray<Type>( NewGelMaxArray, _InitValue );
	
	// Return it //
	return NewGelMaxArray;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void _delete_GelMaxArray( GelMaxArray<Type>* p ) {
	delete [] p;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void delete_GelMaxArray( GelMaxArray<Type>* p ) {
	// Placement Delete //
	for ( st32 idx = 0; idx < p->Size; idx++ ) {
		p->Data[idx].~Type();
	}
	
	_delete_GelMaxArray<Type>( p );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline Type& index_GelMaxArray( GelMaxArray<Type>* p, const size_t _Index ) {
	return (p->Data[ _Index ]);
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const st32 size_GelMaxArray( GelMaxArray<Type>* p ) {
	return p->Size;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// New that set the maximum size //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline GelMaxArray<Type>* newmax_GelMaxArray( const st32 _MaxSize ) {
	GelMaxArray<Type>* p = reinterpret_cast<GelMaxArray<Type>*>(new char[ (_MaxSize * sizeof(Type)) + sizeof(GelMaxArray<Type>) ]);

	p->Size = 0;
	p->MaxSize = _MaxSize;

	return p;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline GelMaxArray<Type>* newmax_GelMaxArray( const st32 _MaxSize, const st32 _Size ) {
	GelMaxArray<Type>* p = reinterpret_cast<GelMaxArray<Type>*>(new char[ (_MaxSize * sizeof(Type)) + sizeof(GelMaxArray<Type>) ]);

	p->Size = _Size;
	p->MaxSize = _MaxSize;

	return p;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline GelMaxArray<Type>* newmax_GelMaxArray( const st32 _MaxSize, const st32 _Size, const Type& _InitValue ) {
	// Allocate it //
	GelMaxArray<Type>* NewGelMaxArray = newmax_GelMaxArray<Type>( _MaxSize, _Size );
	
	// Initialize it //
	set_GelMaxArray<Type>( NewGelMaxArray, _InitValue );
	
	// Return it //
	return NewGelMaxArray;
}
// - ------------------------------------------------------------------------------------------ - //



// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void copy_GelMaxArray( GelMaxArray<Type>* _Src, GelMaxArray<Type>* _Dest, const Type& _InitValue ) {
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
// Return a duplicate of an GelMaxArray //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline GelMaxArray<Type>* copy_GelMaxArray( GelMaxArray<Type>* _Src ) {
	// Allocate our new block //
	GelMaxArray<Type>* NewBlock = new_GelMaxArray<Type>( _Src->Size );
	
	// Copy the data to our new block //
	copy_GelMaxArray<Type>( _Src, NewBlock );
	
	// Return the block //
	return NewBlock;
}
// - ------------------------------------------------------------------------------------------ - //
//template< class Type >
//inline GelMaxArray<Type>* new_GelMaxArray( GelMaxArray<Type>* _Src ) {
//	return copy_GelMaxArray<Type>( _Src );
//}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// Construct an GelMaxArray from a DataBlock //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline GelMaxArray<Type>* copy_GelMaxArray( DataBlock* _Src ) {
	// Allocate our new block //
	GelMaxArray<Type>* NewBlock = new_GelMaxArray<Type>( _Src->Size / sizeof(Type) );
	
	// Copy the data to our new block //
	copy_GelMaxArray<Type>( _Src, NewBlock );
	
	// Return the block //
	return NewBlock;
}
// - ------------------------------------------------------------------------------------------ - //
//template< class Type >
//inline GelMaxArray<Type>* new_GelMaxArray( DataBlock* _Src ) {
//	return copy_GelMaxArray<Type>( _Src );
//}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline DataBlock* copy_DataBlock( GelMaxArray<Type>* _Src ) {
	// Allocate our new block //
	DataBlock* NewBlock = new_DataBlock( _Src->Size * sizeof( Type ) );
	
	// Copy the data to our new block //
	copy_DataBlock( _Src, NewBlock );
	
	// Return the block //
	return NewBlock;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline DataBlock* new_DataBlock( GelMaxArray<Type>* _Src ) {
	return copy_DataBlock( _Src );
}
// - ------------------------------------------------------------------------------------------ - //



// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void reallocate_GelMaxArray( GelMaxArray<Type>** p, const st32 _NewSize ) {
	// Allocate our new block //
	GelMaxArray<Type>* NewGelMaxArray = new_GelMaxArray<Type>( _NewSize );
	
	if ( *p ) {
		// Copy the data to our new block //
		copy_GelMaxArray<Type>( *p, NewGelMaxArray );
		
		// Delete the old block ponted to //
		delete_GelMaxArray<Type>( *p );
	}
	
	// Make the pointer point to the new block //
	(*p) = NewGelMaxArray;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void reallocate_GelMaxArray( GelMaxArray<Type>** p, const st32 _NewSize, const Type& _InitValue ) {
	// Allocate our new block //
	GelMaxArray<Type>* NewGelMaxArray = new_GelMaxArray<Type>( _NewSize );
	
	if ( *p ) {
		// Copy the data to our new block //
		copy_GelMaxArray<Type>( *p, NewGelMaxArray, _InitValue );
		
		// Delete the old block ponted to //
		delete_GelMaxArray<Type>( *p );
	}
	else {
		// No copy made, so fill in with the data //
		set_GelMaxArray<Type>( NewGelMaxArray, _InitValue );
	}
	
	// Make the pointer point to the new block //
	(*p) = NewGelMaxArray;
}
// - ------------------------------------------------------------------------------------------ - //
// Variation of reallocate that looks at the internal size //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void reallocate_GelMaxArray( GelMaxArray<Type>** p ) {
	reallocate_GelMaxArray<Type>( p, (*p)->Size );
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void reallocatemax_GelMaxArray( GelMaxArray<Type>** p, const st32 _NewMaxSize ) {
	// Allocate our new block //
	GelMaxArray<Type>* NewGelMaxArray = newmax_GelMaxArray<Type>( _NewMaxSize, (*p)->Size );
	
	if ( *p ) {
		// Copy the data to our new block //
		copy_GelMaxArray<Type>( *p, NewGelMaxArray );
		
		// Delete the old block ponted to //
		delete_GelMaxArray<Type>( *p );
	}
		
	// Make the pointer point to the new block //
	(*p) = NewGelMaxArray;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void reallocatemax_GelMaxArray( GelMaxArray<Type>** p, const st32 _NewMaxSize, const st32 _NewSize ) {
	// Allocate our new block //
	GelMaxArray<Type>* NewGelMaxArray = newmax_GelMaxArray<Type>( _NewMaxSize, _NewSize );
	
	if ( *p ) {
		// Copy the data to our new block //
		copy_GelMaxArray<Type>( *p, NewGelMaxArray );
		
		// Delete the old block ponted to //
		delete_GelMaxArray<Type>( *p );
	}
	
	// Make the pointer point to the new block //
	(*p) = NewGelMaxArray;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void reallocatemax_GelMaxArray( GelMaxArray<Type>** p, const st32 _NewMaxSize, const st32 _NewSize, const Type& _InitValue ) {
	// Allocate our new block //
	GelMaxArray<Type>* NewGelMaxArray = newmax_GelMaxArray<Type>( _NewMaxSize, _NewSize );
	
	if ( *p ) {
		// Copy the data to our new block //
		copy_GelMaxArray<Type>( *p, NewGelMaxArray, _InitValue );
		
		// Delete the old block ponted to //
		delete_GelMaxArray<Type>( *p );
	}
	else {
		// No copy made, so fill in with the data //
		set_GelMaxArray<Type>( NewGelMaxArray, _InitValue );		
	}
	
	// Make the pointer point to the new block //
	(*p) = NewGelMaxArray;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void resize_GelMaxArray( GelMaxArray<Type>** p, const st32 _NewSize ) {
	if ( *p == 0 ) {
		*p = new_GelMaxArray<Type>( _NewSize );
	}
	// A cheat.  We can resize the block without reallocating
	else if ( _NewSize <= (*p)->MaxSize ) {
		// Set the size to the new size, and we're done //
		(*p)->Size = _NewSize;
	}
	else {
		// Well, we tried.  We need to reallocate and copy the data. //
		reallocate_GelMaxArray<Type>( p, _NewSize );
	}
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void resize_GelMaxArray( GelMaxArray<Type>** p, const st32 _NewSize, const Type& _InitValue ) {
	if ( *p == 0 ) {
		*p = new_GelMaxArray<Type>( _NewSize, _InitValue );
	}
	// A cheat.  We can resize the block without reallocating
	else if ( _NewSize <= (*p)->MaxSize ) {
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
		reallocate_GelMaxArray<Type>( p, _NewSize, _InitValue );
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void resize2_GelMaxArray( GelMaxArray<Type>** p, const st32 _NewSize ) {
	if ( *p == 0 ) {
		*p = new_GelMaxArray<Type>( _NewSize );		
	}
	// A cheat.  We can resize the block without reallocating
	else if ( _NewSize <= (*p)->MaxSize ) {
		// Set the size to the new size, and we're done //
		(*p)->Size = _NewSize;
	}
	else {
		// Well, we tried.  We need to reallocate and copy the data. //
		st32 DoubleSize = (*p)->MaxSize + (*p)->MaxSize;
		st32 NewMaxSize = DoubleSize > _NewSize ? DoubleSize : _NewSize;
		
		reallocatemax_GelMaxArray<Type>( p, NewMaxSize, _NewSize );
	}
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void resize2_GelMaxArray( GelMaxArray<Type>** p, const st32 _NewSize, const Type& _InitValue ) {
	if ( *p == 0 ) {
		*p = new_GelMaxArray<Type>( _NewSize, _InitValue );
	}
	// A cheat.  We can resize the block without reallocating
	else if ( _NewSize <= (*p)->MaxSize ) {
		st32 OldSize = (*p)->Size;
		
		// Set the size to the new size, and we're done //
		(*p)->Size = _NewSize;
		
		// If this grows us //
		if ( OldSize < _NewSize ) {
			// Fill in new values with passed value //
			for( st32 idx = (_NewSize - OldSize); idx--; ) {
				(*p)->Data[OldSize + idx] = _InitValue;
			}
		}
	}
	else {
		// Well, we tried.  We need to reallocate and copy the data. //
		st32 DoubleSize = (*p)->MaxSize + (*p)->MaxSize;
		st32 NewMaxSize = DoubleSize > _NewSize ? DoubleSize : _NewSize;
		
		reallocatemax_GelMaxArray<Type>( p, NewMaxSize, _NewSize, _InitValue );
	}
}
// - ------------------------------------------------------------------------------------------ - //



// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void pushback_GelMaxArray( GelMaxArray<Type>** p ) {
	if ( *p == 0 )
		resize2_GelMaxArray<Type>( p, 1 );
	else
		resize2_GelMaxArray<Type>( p, (*p)->Size + 1 );
} 
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void pushback_GelMaxArray( GelMaxArray<Type>** p, const Type& _Value ) {
	if ( *p == 0 )
		resize2_GelMaxArray<Type>( p, 1, _Value );
	else
		resize2_GelMaxArray<Type>( p, (*p)->Size + 1, _Value );
} 
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline Type popback_GelMaxArray( GelMaxArray<Type>** p ) {
	// TODO: Assert if Size == 0 //
	(*p)->Size--;
	
	return (*p)->Data[ (*p)->Size ];
} 
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline Type* back_GelMaxArray( GelMaxArray<Type>* p ) {
	if ( p == 0 )
		return 0;
	else
		return &(p->Data[ p->Size - 1 ]);
} 
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline Type* front_GelMaxArray( GelMaxArray<Type>* p ) {
	if ( p == 0 )
		return 0;
	else
		return &(p->Data[ 0 ]);
} 
// - ------------------------------------------------------------------------------------------ - //



// - ------------------------------------------------------------------------------------------ - //
// Push and pop large groups of objects on to the GelMaxArray //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void pushblockback_GelMaxArray( GelMaxArray<Type>** p, const st32 _Value ) {
	resize2_GelMaxArray( p, (*p)->Size + _Value );
} 
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void pushblockback_GelMaxArray( GelMaxArray<Type>** p, const st32 _Value, const Type& _InitValue ) {
	resize2_GelMaxArray( p, (*p)->Size + _Value, _InitValue );
} 
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline Type popblockback_GelMaxArray( GelMaxArray<Type>** p, const st32 _Value ) {
	// TODO: Assert if Size == 0 //
	(*p)->Size -= _Value;
	
	return (*p)->Data[ (*p)->Size ];
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_GelMaxArray_Core_H__ //
// - ------------------------------------------------------------------------------------------ - //
