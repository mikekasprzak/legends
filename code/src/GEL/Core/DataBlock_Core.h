// - ------------------------------------------------------------------------------------------ - //
// DataBlock - Arbitrary data reading/writing wrapping library //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_DataBlock_Core_H__
#define __Library_Data_DataBlock_Core_H__
// - ------------------------------------------------------------------------------------------ - //
#ifdef _MSC_VER
#pragma warning (disable : 4200) // Zero sized array member //
#endif // _MSC_VER
// - ------------------------------------------------------------------------------------------ - //
#include <Style/GelTypes.h>
// - ------------------------------------------------------------------------------------------ - //
#include "Data_Core.h"
// - ------------------------------------------------------------------------------------------ - //
//namespace Data {
// - ------------------------------------------------------------------------------------------ - //
struct DataBlock {
	st32 Size; // NOT size_t due to 64bit compatibility //
	char Data[0];
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline DataBlock* new_DataBlock( const st32 _Size ) {
	DataBlock* p = reinterpret_cast<DataBlock*>(new_Data( _Size + sizeof(DataBlock) ));

	if ( p ) {
		p->Size = _Size;
		return p;
	}
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
inline void delete_DataBlock( DataBlock* p ) {
	delete_Data( reinterpret_cast<char*>(p) );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Use this alternative "new" function when you want to initialize the block to a value //
// - ------------------------------------------------------------------------------------------ - //
inline DataBlock* new_DataBlock( const st32 _Size, const int _InitValue ) {
	// Allocate it //
	DataBlock* NewBlock = new_DataBlock( _Size );
	
	// Initialize it //
	set_Data( _InitValue, NewBlock->Data, NewBlock->Size );
	
	// Return it //
	return NewBlock;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// Copy one DataBlock to another, no larger than Destination Size Bytes //
// - ------------------------------------------------------------------------------------------ - //
inline void copy_DataBlock( const DataBlock* _Src, DataBlock* _Dest ) {
	// If source is smaller than the destination //
	if ( _Dest->Size > _Src->Size ) {
		// Copy source number of bytes //
		copy_Data( _Src->Data, _Dest->Data, _Src->Size );
	}
	else {
		// Otherwise, copy destination number of bytes //
		copy_Data( _Src->Data, _Dest->Data, _Dest->Size );
	}
}
// - ------------------------------------------------------------------------------------------ - //
inline void copy_DataBlock( const char* _Src, const st32 _SrcSize, DataBlock* _Dest ) {
	// If source is smaller than the destination //
	if ( _Dest->Size > _SrcSize ) {
		// Copy source number of bytes //
		copy_Data( _Src, _Dest->Data, _SrcSize );
	}
	else {
		// Otherwise, copy destination number of bytes //
		copy_Data( _Src, _Dest->Data, _Dest->Size );
	}
}
// - ------------------------------------------------------------------------------------------ - //
// Return a duplicate of a DataBlock //
// - ------------------------------------------------------------------------------------------ - //
inline DataBlock* copy_DataBlock( const DataBlock* _Src ) {
	// Allocate our new block //
	DataBlock* NewBlock = new_DataBlock( _Src->Size );
	
	// Copy the data to our new block //
	copy_DataBlock( _Src, NewBlock );
	
	// Return the block //
	return NewBlock;
}
// - ------------------------------------------------------------------------------------------ - //
inline DataBlock* new_DataBlock( const DataBlock* _Src ) {
	return copy_DataBlock( _Src );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline DataBlock* copy_DataBlock( const char* _Src, const st32 _SrcSize ) {
	// Allocate our new block //
	DataBlock* NewBlock = new_DataBlock( _SrcSize );
	
	// Copy the data to our new block //
	copy_DataBlock( _Src, _SrcSize, NewBlock );
	
	// Return the block //
	return NewBlock;
}
// - ------------------------------------------------------------------------------------------ - //
inline DataBlock* new_DataBlock( const char* _Src, const st32 _SrcSize ) {
	return copy_DataBlock( _Src, _SrcSize );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Set DataBlock //
// - ------------------------------------------------------------------------------------------ - //
inline void set_DataBlock( DataBlock* _Data, const int _InitValue ) {
	set_Data( _InitValue, _Data->Data, _Data->Size );
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// A useful accessory, resizing. //
// Reducing size can work safely, but expanding would require new allocation //
//   this is because new/delete ignore my internal size variable //
// - ------------------------------------------------------------------------------------------ - //
inline void reallocate_DataBlock( DataBlock** p, const st32 _NewSize ) {
	// Allocate our new block //
	DataBlock* NewBlock = new_DataBlock( _NewSize );
	
	// Copy the data to our new block //
	copy_DataBlock( *p, NewBlock );
	
	// Delete the old block ponted to //
	delete_DataBlock( *p );
	
	// Make the pointer point to the new block //
	(*p) = NewBlock;
}
// - ------------------------------------------------------------------------------------------ - //
inline void resize_DataBlock( DataBlock** p, const st32 _NewSize ) {
	// A cheat.  We can resize the block without reallocating
	if ( _NewSize <= (*p)->Size ) {
		// Set the size to the new size, and we're done //
		(*p)->Size = _NewSize;
	}
	else {
		// Well, we tried.  We need to reallocate and copy the data. //
		reallocate_DataBlock( p, _NewSize );
	}
}
// - ------------------------------------------------------------------------------------------ - //
// Variation of reallocate that looks at the internal size //
// - ------------------------------------------------------------------------------------------ - //
inline void reallocate_DataBlock( DataBlock** p ) {
	reallocate_DataBlock( p, (*p)->Size );
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// Initializer capable versions of resize, reallocate, and copy //
// - ------------------------------------------------------------------------------------------ - //
// Copy one DataBlock to another, no larger than Destination Size Bytes //
inline void copy_DataBlock( DataBlock* _Src, DataBlock* _Dest, const int _InitValue ) {
	// If source is smaller than the destination //
	if ( _Dest->Size > _Src->Size ) {
		// Copy source number of bytes //
		copy_Data( _Src->Data, _Dest->Data, _Src->Size );
		// Fill the rest of the data with initializer //
		set_Data( _InitValue, &_Dest->Data[_Src->Size], _Dest->Size - _Src->Size );
	}
	else {
		// Otherwise, copy destination number of bytes //
		copy_Data( _Src->Data, _Dest->Data, _Dest->Size );
	}
}
// - ------------------------------------------------------------------------------------------ - //
inline void reallocate_DataBlock( DataBlock** p, const st32 _NewSize, const int _InitValue ) {
	// Allocate our new block //
	DataBlock* NewBlock = new_DataBlock( _NewSize );
	
	// Copy the data to our new block //
	copy_DataBlock( *p, NewBlock, _InitValue );
	
	// Delete the old block ponted to //
	delete_DataBlock( *p );
	
	// Make the pointer point to the new block //
	(*p) = NewBlock;
}
// - ------------------------------------------------------------------------------------------ - //
inline void resize_DataBlock( DataBlock** p, const st32 _NewSize, const int _InitValue ) {
	// A cheat.  We can resize the block without reallocating
	if ( _NewSize <= (*p)->Size ) {
		//st32 OldSize = (*p)->Size;
		
		// Set the size to the new size, and we're done //
		(*p)->Size = _NewSize;
		
		// Note this will never happen, since this is normally a max size test //
//		// If this grows us //
//		if ( OldSize < _NewSize ) {
//			// Fill in new values with passed value //
//			for( st idx = (_NewSize - OldSize); idx--; ) {
//				(*p)->Data[OldSize + idx] = _InitValue;
//			}
//		}
	}
	else {
		// Well, we tried.  We need to reallocate and copy the data. //
		reallocate_DataBlock( p, _NewSize, _InitValue );
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void pushback_DataBlock( DataBlock** p, const int _InitValue ) {
	resize_DataBlock( p, (*p)->Size + 1, _InitValue );
} 
// - ------------------------------------------------------------------------------------------ - //
inline int popback_DataBlock( DataBlock** p ) {
	// TODO: Assert if Size == 0 //
	(*p)->Size--;
	
	return (*p)->Data[ (*p)->Size ];
} 
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
//}; // namespace Data //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_DataBlock_Core_H__ //
// - ------------------------------------------------------------------------------------------ - //
