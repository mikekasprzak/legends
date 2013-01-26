// - ------------------------------------------------------------------------------------------ - //
// Data - Data utility/reading/writing wrapping library //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_GELCore_Data_Core_H__
#define __Library_GELCore_Data_Core_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Style/GelTypes.h>
#include "Ptr.h"				// is_aligned_Ptr() //
#include <stdio.h>				// FILE*, fopen, ftell, etc //
// - ------------------------------------------------------------------------------------------ - //
// NOTE: This code could "technically" be made in to a general purpose reader/writer for all //
//   IO Operations.  F:/Art/DataFile.img for files, M1:/MyData.img for a memory card, 
//   FTP://Urb.com/neffle.dat for a remote file, etc. //
// This is open for debate though.  Memory Card code is almost worth abstracting to a custom //
//   interface, because it's a different task than reading game data, saving editor information. //
// The ability to poll local and remote data is fascinating though, even if it's LAN data. //
// Thusly, it's probably of interest to be able to either define a source (CD, HD, LAN), and all //
//   this code pulls from that source.  Do this on a per platform basis though. //
// DS or PSP could benefit greatly from this. //
// - ------------------------------------------------------------------------------------------ - //
// NOTE: Update.  Instead of this being a general purpose reader/writer, it's a framework. //
//   What this means is you simply write functions that take the new source a source, in custom //
//   "new_Data", "read_Data" and "write_Data" functions.  Name it "Data_MySource.h", and //
//   place is in your library heiarchy.  Then to support a new source, you include it from it's //
//   library's folder.  Easy clean extendability. //
// - ------------------------------------------------------------------------------------------ - //
// TODO: Come up with a standard interface for streamable data. //
// - ------------------------------------------------------------------------------------------ - //

// For fastest loops, use 64bit numbers and SIMD types //

//#define FASTLOOP(Count) for(unsigned ___idx_ ## __COUNTER__ = (Count)+1; --___idx_ ## __COUNTER__;)

inline void u32set_Data( const unsigned _Value, void* _Data, const size_t _Size ) {
	unsigned* Data = (unsigned*)_Data;
	unsigned* DataTarget = (unsigned*)((char*)_Data+_Size);

	// I need to test the pointer if it's at the target. No way to go faster. :( //
	while ( Data != DataTarget ) {
		*Data = _Value;
		++Data;
	}

	// Fast yes, but index is unusuable //
//	FASTLOOP(_Size>>2) {
//		Data[
//	}
	// The solution to the unusable index is to change the base pointer. //
	// Then the index can simply be added to the target address before performing a store. //
}

// - ------------------------------------------------------------------------------------------ - //
//inline void aligned_copy_Data( const void* const _Src, void* const _Dest, const szt _Size ) {
//	unsigned* Src = (unsigned* const)_Src;
//	unsigned* Dest = (unsigned* const)_Dest;
//	--Src;
//	--Dest;
//
//	for ( szt Index = _Size+1; --Index; ) {
//		Dest[Index] = Src[Index];
//	}
//}
// - ------------------------------------------------------------------------------------------ - //
// You probably want this, not MemSet //
template< typename tType >
inline void fill_Data( const tType& Src, tType* Dest, const szt Count ) {
	--Dest;

	for ( szt Index = Count+1; --Index; ) {
		Dest[Index] = Src;
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// MemSET wrapper -- Only writes bytes (despite input being an int) //
inline void set_Data( const int _Value, void* _Data, const size_t _Size ) {
	memset( _Data, _Value, _Size );
}
// - ------------------------------------------------------------------------------------------ - //
// MemCPY wrapper //
inline void copy_Data( const void* _Src, void* _Dest, const size_t _Size ) {
	memcpy( _Dest, _Src, _Size );
}
// - ------------------------------------------------------------------------------------------ - //
// MemMove wrapper //
inline void move_Data( const void* _Src, void* _Dest, const size_t _Size ) {
	memmove( _Dest, _Src, _Size );
}
// - ------------------------------------------------------------------------------------------ - //
// MemCMP wrapper //
inline const int compare_Data( const void* const _Src, const void* _Dest, const size_t _Size ) {
	return memcmp( _Dest, _Src, _Size );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// copy data while applying padding //
// WARNING: SIZE SHOULD BE a multiple of Bytes*Padding!! //
inline void copyPadded_Data( void* _Src, void* _Dest, const size_t _Size, const size_t Bytes, const size_t Padding, const int PadValue ) {
	char* Src = (char*)_Src;
	char* Dest = (char*)_Dest;
	char* TargetSrc = Src + _Size;
	
	while ( Src < TargetSrc ) {
		for ( size_t Num = Bytes; Num--; ) {
			*Dest = *Src;
			Dest++;
			Src++;
		}
		for ( size_t Num = Padding; Num--; ) {
			*Dest = PadValue;
			Dest++;
		}
	};
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Zero Memory //
inline void zero_Data( void* _Data, const size_t _Size ) {
	// TODO: optimized for loop that does 32bit writes //
	set_Data( 0, _Data, _Size );
}
// - ------------------------------------------------------------------------------------------ - //
// Write a bitmask of all 1's (-1) //
inline void one_Data( void* _Data, const size_t _Size ) {
	// TODO: optimized for loop that does 32bit writes //
	set_Data( -1, _Data, _Size );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Special template variants of zeroing/oneing //
// - ------------------------------------------------------------------------------------------ - //
template< typename tType >
inline void Zero( tType& _Data ) {
	zero_Data( &_Data, sizeof(_Data) );
}
// - ------------------------------------------------------------------------------------------ - //
template< typename tType >
inline void Zero( tType* _Data, const szt Count ) {
	zero_Data( _Data, sizeof(tType)*Count );
}
// - ------------------------------------------------------------------------------------------ - //
template< typename tType >
inline void One( tType& _Data ) {
	one_Data( &_Data, sizeof(_Data) );
}
// - ------------------------------------------------------------------------------------------ - //
template< typename tType >
inline void One( tType* _Data, const szt Count ) {
	one_Data( _Data, sizeof(tType)*Count );
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
inline const size_t read_Data( const char* _FileName, void* Data, const size_t _Size ) {
	// Open File //
	FILE* fp = fopen( _FileName, "rb" );
	if ( fp == 0 ) {
		// TODO: Log file open error //
		return 0;
	}
	
	// Determine how large file is //
	fseek( fp, 0, SEEK_END );
	size_t Size = ftell( fp );
#ifdef _MSC_VER
	fseek( fp, 0L, SEEK_SET );
#else // _MSC_VER //
	rewind( fp );
#endif // _MSC_VER //

	// Read data (only as much as the smallest size) //
	size_t BytesRead = fread( Data, 1, Size > _Size ? _Size : Size, fp );
	
	// Close file //
	fclose( fp );
	
	// Return the number of bytes read //
	return BytesRead;
}
// - ------------------------------------------------------------------------------------------ - //
inline const size_t write_Data( const char* _FileName, void* Data, size_t _Size ) {
	// Open File //
	FILE* fp = fopen( _FileName, "wb" );
	if ( fp == 0 ) {
		// TODO: Log file open error //
		return 0;
	}
	
	// Write the data //
	size_t BytesWritten = fwrite( Data, 1, _Size, fp );
	// TODO: Assert on fire write error //
	
	// Close file //
	fclose( fp );
	
	// Return the number of bytes written //
	return BytesWritten;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
inline void* new_Data( const size_t _Size ) {
	return (void*)(new char[_Size]);
}
// - ------------------------------------------------------------------------------------------ - //
inline void delete_Data( void* _Data ) {
	delete [] reinterpret_cast<char*>(_Data);
}
// - ------------------------------------------------------------------------------------------ - //
inline void* new_Data( const char* _FileName ) {
	// Open File //
	FILE* fp = fopen( _FileName, "rb" );
	if ( fp == 0 ) {
		return 0;
	}
	
	// Determine how large file is //
	fseek( fp, 0, SEEK_END );
	size_t Size = ftell( fp );
#ifdef _MSC_VER
	fseek( fp, 0L, SEEK_SET );
#else // _MSC_VER //
	rewind( fp );
#endif // _MSC_VER //
	
	// Allocate space //
	void* p = new_Data( Size );
	// TODO: Assert failure allocating block //
	
	// Read data //
	fread( p, 1, Size, fp );
	
	// Close file //
	fclose( fp );
	
	// Return data //
	return p;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Copy one DataBlock to another, no larger than Destination Size Bytes //
// - ------------------------------------------------------------------------------------------ - //
inline void copy_Data( const void* _SrcData, const size_t _SrcSize, void* _DestData, const size_t _DestSize ) {
	// If source is smaller than the destination //
	if ( _DestSize > _SrcSize ) {
		// Copy source number of bytes //
		copy_Data( _SrcData, _DestData, _SrcSize );
	}
	else {
		// Otherwise, copy destination number of bytes //
		copy_Data( _SrcData, _DestData, _DestSize );
	}
}
// - ------------------------------------------------------------------------------------------ - //
// Allocate and return a duplicate of a Data //
// - ------------------------------------------------------------------------------------------ - //
inline void* copy_Data( const void* _Src, const size_t _Size ) {
	// Allocate our new block //
	void* NewData = new_Data( _Size );
	
	// Copy the data to our new block //
	copy_Data( _Src, _Size, NewData, _Size );
	
	// Return the block //
	return NewData;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// A useful accessory, resizing. //
// Reducing size can work safely, but expanding would require new allocation //
//   this is because new/delete ignore my internal size variable //
// - ------------------------------------------------------------------------------------------ - //
inline void reallocate_Data( void** p, const size_t _OldSize, const size_t _NewSize ) {
	// Allocate our new block //
	void* NewData = new_Data( _NewSize );
	
	// Copy the data to our new block //
	copy_Data( *p, _OldSize, NewData, _NewSize );
	
	// Delete the old block ponted to //
	delete_Data( *p );
	
	// Make the pointer point to the new block //
	(*p) = NewData;
}
// - ------------------------------------------------------------------------------------------ - //
inline void resize_Data( void** p, const size_t _OldSize, const size_t _NewSize ) {
	// A cheat.  We can resize the block without reallocating
	if ( _NewSize <= _OldSize ) {
		// If the size wasn't something implicit, we'd set it right now. //
		// However, Size is an implied argument, so we just asume you're going to use the new //
		//   size as the correct size from now on //
	}
	else {
		// Well, we tried.  We need to reallocate and copy the data. //
		reallocate_Data( p, _OldSize, _NewSize );
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Initializer capable versions of resize, reallocate, and copy //
// - ------------------------------------------------------------------------------------------ - //
// Copy one DataBlock to another, no larger than Destination Size Bytes //
inline void copy_Data( const void* _Src, const size_t _SrcSize, void* _Dest, const size_t _DestSize, const int _InitValue ) {
	// If source is smaller than the destination //
	if ( _DestSize > _SrcSize ) {
		// Copy source number of bytes //
		copy_Data( _Src, _Dest, _SrcSize );
		// Fill the rest of the data with initializer //
		set_Data( _InitValue, &(((char*)_Dest)[_SrcSize]), _DestSize - _SrcSize );
	}
	else {
		// Otherwise, copy destination number of bytes //
		copy_Data( _Src, _Dest, _DestSize );
	}
}
// - ------------------------------------------------------------------------------------------ - //
inline void reallocate_Data( void** p, const size_t _OldSize, const size_t _NewSize, const int _InitValue ) {
	// Allocate our new block //
	void* NewData = new_Data( _NewSize );
	
	// Copy the data to our new block //
	copy_Data( *p, _OldSize, NewData, _NewSize, _InitValue );
	
	// Delete the old block ponted to //
	delete_Data( *p );
	
	// Make the pointer point to the new block //
	(*p) = NewData;
}
// - ------------------------------------------------------------------------------------------ - //
inline void resize_Data( void** p, const size_t _OldSize, const size_t _NewSize, const int _InitValue ) {
	// A cheat.  We can resize the block without reallocating
	if ( _NewSize <= _OldSize ) {
		// If the size wasn't something implicit, we'd set it right now. //
		// However, Size is an implied argument, so we just asume you're going to use the new //
		//   size as the correct size from now on //
	}
	else {
		// Well, we tried.  We need to reallocate and copy the data. //
		reallocate_Data( p, _OldSize, _NewSize, _InitValue );
	}
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
//}; // namespace Data //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_Data_Core_H__ //
// - ------------------------------------------------------------------------------------------ - //
