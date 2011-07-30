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
//#include <string.h>
#include "DataBlock_Core.h"
// - ------------------------------------------------------------------------------------------ - //
// TODO: Insertion code, Alignment resizing (min, max), searching, sorting  //
// NOTE: Consider making reallocate specific to max size change.
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
struct GelArray {
	st32 MaxSize;
	st32 Size;
	Type Data[0];
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
inline GelArray<Type>* new_GelArray( const st32 _Size ) {
	GelArray<Type>* p = reinterpret_cast<GelArray<Type>*>(new char[ (_Size * sizeof(Type)) + sizeof(GelArray<Type>) ]);

	p->Size = _Size;
	p->MaxSize = _Size;

	return p;
}
// - ------------------------------------------------------------------------------------------ - //
// Use this alternative "new" function when you want to initialize the GelArray to a value //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline GelArray<Type>* new_GelArray( const st32 _Size, const Type& _InitValue ) {
	// Allocate it //
	GelArray<Type>* NewGelArray = new_GelArray<Type>( _Size );
	
	// Initialize it //
	set_GelArray<Type>( NewGelArray, _InitValue );
	
	// Return it //
	return NewGelArray;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void delete_GelArray( GelArray<Type>* p ) {
	delete p;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// New that set the maximum size //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline GelArray<Type>* newmax_GelArray( const st32 _MaxSize ) {
	GelArray<Type>* p = reinterpret_cast<GelArray<Type>*>(new char[ (_MaxSize * sizeof(Type)) + sizeof(GelArray<Type>) ]);

	p->Size = 0;
	p->MaxSize = _MaxSize;

	return p;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline GelArray<Type>* newmax_GelArray( const st32 _MaxSize, const st32 _Size ) {
	GelArray<Type>* p = reinterpret_cast<GelArray<Type>*>(new char[ (_MaxSize * sizeof(Type)) + sizeof(GelArray<Type>) ]);

	p->Size = _Size;
	p->MaxSize = _MaxSize;

	return p;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline GelArray<Type>* newmax_GelArray( const st32 _MaxSize, const st32 _Size, const Type& _InitValue ) {
	// Allocate it //
	GelArray<Type>* NewGelArray = newmax_GelArray<Type>( _MaxSize, _Size );
	
	// Initialize it //
	set_GelArray<Type>( NewGelArray, _InitValue );
	
	// Return it //
	return NewGelArray;
}
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
template< class Type >
inline GelArray<Type>* new_GelArray( GelArray<Type>* _Src ) {
	return copy_GelArray<Type>( _Src );
}
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
template< class Type >
inline GelArray<Type>* new_GelArray( DataBlock* _Src ) {
	return copy_GelArray<Type>( _Src );
}
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
	
	// Copy the data to our new block //
	copy_GelArray<Type>( *p, NewGelArray );
	
	// Delete the old block ponted to //
	delete_GelArray<Type>( *p );
	
	// Make the pointer point to the new block //
	(*p) = NewGelArray;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void reallocate_GelArray( GelArray<Type>** p, const st32 _NewSize, const Type& _InitValue ) {
	// Allocate our new block //
	GelArray<Type>* NewGelArray = new_GelArray<Type>( _NewSize );
	
	// Copy the data to our new block //
	copy_GelArray<Type>( *p, NewGelArray, _InitValue );
	
	// Delete the old block ponted to //
	delete_GelArray<Type>( *p );
	
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
template< class Type >
inline void reallocatemax_GelArray( GelArray<Type>** p, const st32 _NewMaxSize ) {
	// Allocate our new block //
	GelArray<Type>* NewGelArray = newmax_GelArray<Type>( _NewMaxSize, (*p)->Size );
	
	// Copy the data to our new block //
	copy_GelArray<Type>( *p, NewGelArray );
	
	// Delete the old block ponted to //
	delete_GelArray<Type>( *p );
	
	// Make the pointer point to the new block //
	(*p) = NewGelArray;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void reallocatemax_GelArray( GelArray<Type>** p, const st32 _NewMaxSize, const st32 _NewSize ) {
	// Allocate our new block //
	GelArray<Type>* NewGelArray = newmax_GelArray<Type>( _NewMaxSize, _NewSize );
	
	// Copy the data to our new block //
	copy_GelArray<Type>( *p, NewGelArray );
	
	// Delete the old block ponted to //
	delete_GelArray<Type>( *p );
	
	// Make the pointer point to the new block //
	(*p) = NewGelArray;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void reallocatemax_GelArray( GelArray<Type>** p, const st32 _NewMaxSize, const st32 _NewSize, const Type& _InitValue ) {
	// Allocate our new block //
	GelArray<Type>* NewGelArray = newmax_GelArray<Type>( _NewMaxSize, _NewSize );
	
	// Copy the data to our new block //
	copy_GelArray<Type>( *p, NewGelArray, _InitValue );
	
	// Delete the old block ponted to //
	delete_GelArray<Type>( *p );
	
	// Make the pointer point to the new block //
	(*p) = NewGelArray;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void resize_GelArray( GelArray<Type>** p, const st32 _NewSize ) {
	// A cheat.  We can resize the block without reallocating
	if ( _NewSize <= (*p)->MaxSize ) {
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
	// A cheat.  We can resize the block without reallocating
	if ( _NewSize <= (*p)->MaxSize ) {
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
template< class Type >
inline void resize2_GelArray( GelArray<Type>** p, const st32 _NewSize ) {
	// A cheat.  We can resize the block without reallocating
	if ( _NewSize <= (*p)->MaxSize ) {
		// Set the size to the new size, and we're done //
		(*p)->Size = _NewSize;
	}
	else {
		// Well, we tried.  We need to reallocate and copy the data. //
		st32 DoubleSize = (*p)->MaxSize + (*p)->MaxSize;
		st32 NewMaxSize = DoubleSize > _NewSize ? DoubleSize : _NewSize;
		
		reallocatemax_GelArray<Type>( p, NewMaxSize, _NewSize );
	}
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void resize2_GelArray( GelArray<Type>** p, const st32 _NewSize, const Type& _InitValue ) {
	// A cheat.  We can resize the block without reallocating
	if ( _NewSize <= (*p)->MaxSize ) {
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
		
		reallocatemax_GelArray<Type>( p, NewMaxSize, _NewSize, _InitValue );
	}
}
// - ------------------------------------------------------------------------------------------ - //



// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void pushback_GelArray( GelArray<Type>** p, const Type& _InitValue ) {
	resize2_GelArray( p, (*p)->Size + 1, _InitValue );
} 
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline Type popback_GelArray( GelArray<Type>** p ) {
	// TODO: Assert if Size == 0 //
	(*p)->Size--;
	
	return (*p)->Data[ (*p)->Size ];
} 
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Push and pop large groups of objects on to the GelArray //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void pushblockback_GelArray( GelArray<Type>** p, const st32 _Value ) {
	resize2_GelArray( p, (*p)->Size + _Value );
} 
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void pushblockback_GelArray( GelArray<Type>** p, const st32 _Value, const Type& _InitValue ) {
	resize2_GelArray( p, (*p)->Size + _Value, _InitValue );
} 
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline Type popblockback_GelArray( GelArray<Type>** p, const st32 _Value ) {
	// TODO: Assert if Size == 0 //
	(*p)->Size -= _Value;
	
	return (*p)->Data[ (*p)->Size ];
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_GelArray_Core_H__ //
// - ------------------------------------------------------------------------------------------ - //
