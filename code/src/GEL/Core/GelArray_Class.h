// - ------------------------------------------------------------------------------------------ - //
// GelArray Class - Class version of DataBlock. Deletes self as it goes out of scope. //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_GelArray_Class_H__
#define __Library_Data_GelArray_Class_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Debug/Log.h>

#include "DataBlock_Core.h"
#include "DataBlock_File.h"

#include "GelArray_Core.h"
#include "GelArray_File.h"
#include "GelArray_Hash32.h"
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
class cGelArray {
protected:
	GelArray<Type>* _Data;
public:
	// Constructor //
	inline cGelArray() :
		_Data( 0 )
	{
	}
	
	// Since this is a "power use" class, I'm making initializing optional //
	inline cGelArray( const size_t _Size ) :
		_Data( new_GelArray<Type>( _Size ) )
	{
	}
	
	inline cGelArray( const size_t _Size, const Type& _InitValue ) :
		_Data( new_GelArray<Type>( _Size, _InitValue ) )
	{
	}
	
	// Given a filename as an argument, load it //
	inline cGelArray( const char* _FileName ) :
		_Data( new_read_GelArray<Type>( _FileName ) )
	{
	}
	
	// Given an GelArray, make our GelArray directly what we were given //
	// Note: I'm now in charge of freeing, so don't try sharing this data //
	inline cGelArray( GelArray<Type>* _Src ) :
		_Data( _Src )
	{
	}
	
	// Copy Constructor - replicates the contents of a DataBlock//
	inline cGelArray( const cGelArray<Type>& _Src ) :
		_Data( copy_GelArray<Type>( _Src ) )
	{
	}
	
	// Assignment Operator -- for compatibility with new_GelArray, use it as is //
	inline GelArray<Type>* operator = ( GelArray<Type>* Val ) {
		if ( _Data )
			delete_GelArray<Type>( _Data );
			
		_Data = Val;
		return _Data;
	}
	
	// Destructor //
	inline ~cGelArray() {
		if ( _Data )
			delete_GelArray<Type>( _Data );
	}
public:
	inline const size_t FirstIndex() const {
		return 0;
	}
	inline const size_t LastIndex() const {
		if ( _Data == 0 )
			return 0;
		return _Data->Size - 1;
	}
	
	// Size() returns the number of elements used. //
	inline const size_t Size() const {
		if ( _Data == 0 )
			return 0;
		return _Data->Size;
	}
	
	// SizeOf() returns the maxiumum size, or rather, how much memory is used //
	inline const size_t SizeOf() const {
		if ( _Data == 0 )
			return 0;
		return _Data->MaxSize;
	}

	
	inline Type& operator [] ( const size_t Index ) {
		Warning( _Data == 0, "cGelArray w/o Data" );
		Warning( Index < 0, "Index out of bounds (%i < 0)", Index );
		Warning( Index > Size(), "Index out of bounds (%i >= %i)", Index, Size() );
		return _Data->Data[ Index ];
	}
	inline const Type& operator [] ( const size_t Index ) const {
		Warning( _Data == 0, "cGelArray w/o Data" );
		Warning( Index < 0, "Index out of bounds (%i < 0)", Index );
		Warning( Index > Size(), "Index out of bounds (%i >= %i)", Index, Size() );
		return _Data->Data[ Index ];
	}
	
	inline Type& Front() {
		Warning( _Data == 0, "cGelArray w/o Data" );
		return _Data->Data[ FirstIndex() ];
	}
	inline const Type& Front() const {
		Warning( _Data == 0, "cGelArray w/o Data" );
		return _Data->Data[ FirstIndex() ];
	}

	inline Type& Back() {
		Warning( _Data == 0, "cGelArray w/o Data" );
		return _Data->Data[ LastIndex() ];
	}
	inline const Type& Back() const {
		Warning( _Data == 0, "cGelArray w/o Data" );
		return _Data->Data[ LastIndex() ];
	}

	
	inline GelArray<Type>* operator * () {
		return _Data;	
	}
public:
	inline void Load( const char* _FileName ) {
		// Delete the file if there is one loaded //
		if ( _Data )
			delete_GelArray<Type>( _Data );
		// Load the file //
		_Data = new_GelArray<Type>( _FileName );
	}
	
	inline void Save( const char* _FileName ) {
		return_Warning( _Data == 0, "cGelArray w/o Data" );
		write_GelArray<Type>( _Data, _FileName );
	}

public:
	inline void Resize( const size_t _Size ) {
		resize_GelArray<Type>( &_Data, _Size );
	}
	
	inline void Set( const Type& _Value ) {
		return_Warning( _Data == 0, "cGelArray w/o Data" );
		set_GelArray<Type>( _Data, _Value );
	}
	
	inline void Clear( ) {
		Set( Type() );
	}
	
	inline void Reset( ) {
		Resize( 0 );
	}
	
	inline void PushBack( const Type& _Value ) {
		pushback_GelArray<Type>( &_Data, _Value );
	}
	
	inline const Type PopBack() {
		return popback_GelArray<Type>( &_Data );
	}

public:
	// Compression //
	inline void UnpackLZMA( const DataBlock* _Src );
	
	inline void UnpackBZIP( DataBlock* _Src );
	inline DataBlock* PackBZIP();
	
	inline void UnpackZLIB( DataBlock* _Src );
	inline DataBlock* PackZLIB();
	
	inline void UnpackLZO( DataBlock* _Src );
	inline DataBlock* PackLZO();
	
	// Hash //
	inline const unsigned int Hash32() const {
		return_value_Warning( 0, _Data == 0, "cGelArray w/o Data" );
		return hash32_GelArray( _Data );
	}
	//inline static const MD5Hash HashMD5( const cGelArray<Type>& _Src  );
	//inline static const SHA1Hash HashSHA1( const cGelArray<Type>& _Src  );
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_GelArray_Class_H__ //
// - ------------------------------------------------------------------------------------------ - //
