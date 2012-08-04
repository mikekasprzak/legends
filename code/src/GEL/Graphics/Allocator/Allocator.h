// - ------------------------------------------------------------------------------------------ - //
#ifndef __Allocator_H__
#define __Allocator_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Core/DataArray.h>
// - ------------------------------------------------------------------------------------------ - //
// TODO: Promote this to a variant of StaticArray in the Data Library. //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
class Allocator {
protected:
	int _Size;
	DataArray<Type>* Data;
	
public:
	inline Allocator( const int _MaxSize, const int Start = 0 ) :
		_Size( Start )
	{
		Data = new_DataArray<Type>( _MaxSize );
	}
	
	inline ~Allocator() {
		delete_DataArray<Type>( Data );
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
