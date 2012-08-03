// - ------------------------------------------------------------------------------------------ - //
#ifndef __StaticAllocator_H__
#define __StaticAllocator_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// TODO: Promote this to a variant of StaticArray in the Data Library. //
// - ------------------------------------------------------------------------------------------ - //
template< class Type, const int _MaxSize >
class StaticAllocator {
public:
	int _Size;
	Type Data[_MaxSize];
public:
	inline StaticAllocator() :
		_Size( 0 )
	{
	}

	inline StaticAllocator( const int Start ) :
		_Size( Start )
	{
	}
	
	inline Type& operator []( const int Index ) {
		return Data[Index];
	}
	inline const Type& operator []( const int Index ) const {
		return Data[Index];
	}
	
	inline Type* Get() {
		return Data;
	}
	inline const Type* Get() const {
		return Data;
	}
	
	inline const int Size() const {
		return _Size;
	}
	
	inline const int SizeOf() const {
		return _MaxSize;
	}

public:
	inline Type& Add() {
		return Data[_Size++];
	}

	inline Type& Add( const Type& Value ) {
		return Data[_Size++] = Value;
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
			Data[ _Size + idx ] = Src[idx];
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
#endif // __StaticAllocator_H__ //
// - ------------------------------------------------------------------------------------------ - //
