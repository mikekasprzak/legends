// - ------------------------------------------------------------------------------------------ - //
#ifndef __Allocator_H__
#define __Allocator_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Style/Style.h>
#include <Core/DataArray.h>
// - ------------------------------------------------------------------------------------------ - //
// TODO: Promote this to a variant of StaticArray in the Data Library. //
// - ------------------------------------------------------------------------------------------ - //
//#define ALLOCATOR_DEBUG
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
class Allocator {
protected:
	int _Size;
	DataArray<Type>* Data;
	
public:
	inline Allocator() :
		_Size( 0 ),
		Data( 0 )
	{	
		#ifdef ALLOCATOR_DEBUG
			Log( "! NULL 0x%x (0x%x)", Data, this );
		#endif // ALLOCATOR_DEBUG //
	}
	
	inline Allocator( const int _MaxSize, const int Start = 0 ) :
		_Size( Start )
	{
		Data = new_DataArray<Type>( _MaxSize );
		#ifdef ALLOCATOR_DEBUG
			Log("! NEW 0x%x (0x%x)", Data, this );
			//VVVLog( "! Allocator Construct (%i -- 0x%x) (0x%x)", _MaxSize, Data, this );
		#endif // ALLOCATOR_DEBUG //
	}
	
	inline ~Allocator() {
		#ifdef ALLOCATOR_DEBUG
			Log("! ~ 0x%x (0x%x)", Data, this );
			//VVVLog( "! Allocator Destruct (%i -- 0x%x) (0x%x)", _Size, Data, this );
		#endif // ALLOCATOR_DEBUG //

		if ( Data )
			delete_DataArray<Type>( Data );
	}
	
	inline Allocator<Type>( const Allocator& Copy ) :
		_Size( Copy._Size )
	{
		#ifdef ALLOCATOR_DEBUG
			Log("! COPY 0x%x = 0x%x (0x%x)", Data, &Copy, this );
			//VVVLog( "! Allocator Copy (%i -- 0x%x <- 0x%x) (0x%x)", _Size, Data, Copy.Data, this );
		#endif // ALLOCATOR_DEBUG //

		if ( Copy.Data )
			Data = copy_DataArray<Type>( Copy.Data );
		else
			Data = 0;
	}
	
	inline Allocator& operator = ( const Allocator& Copy ) {
		#ifdef ALLOCATOR_DEBUG
			Log("! ASSIGN 0x%x = 0x%x (0x%x)", Data, &Copy, this );
			//VVVLog( "! Allocator Assignment (%i -- 0x%x <- 0x%x) (0x%x)", _Size, Data, Copy.Data, this );
		#endif // ALLOCATOR_DEBUG //
		if ( this != &Copy ) {
			_Size = Copy._Size;
			if ( Copy.Data )
				Data = copy_DataArray<Type>( Copy.Data );
			else
				Data = 0;
		}
		return *this;
	}
	
	inline Type& operator []( const int Index ) {
		return Data->Data[Index];
	}
	inline const Type& operator []( const int Index ) const {
		return Data->Data[Index];
	}
	
	inline Type* Get() {
		return &Data->Data[0];
	}
	inline const Type* Get() const {
		return &Data->Data[0];
	}
	
	inline const int Size() const {
		return _Size;
	}

	inline const int SizeOf() const {
		return Data->Size;
	}

public:
	inline Type& Add() {
		return Data->Data[_Size++];
	}

	inline Type& Add( const Type& Value ) {
		return Data->Data[_Size++] = Value;
	}

	inline const int AddMany( const int Count ) {
		int OldSize = _Size;
		_Size += Count;

		return OldSize;
	}

	inline const int AddMany( const Type* Src, const int Count ) {
		int OldSize = _Size;
		
		// TODO: Use a better copy function //
		for ( int idx = Count; idx--; ) {
			Data->Data[ _Size + idx ] = Src[idx];
		}

		_Size += Count;

		return OldSize;
	}

	inline void Clear() {
		_Size = 0;
	}
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Allocator_H__ //
// - ------------------------------------------------------------------------------------------ - //
