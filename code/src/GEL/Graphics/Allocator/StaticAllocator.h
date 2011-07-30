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
	
	inline const int Size() const {
		return _Size;
	}

public:
	inline Type& Add() {
		// TODO: Set this to zero? //
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
		for ( int idx = Count; idx--; ) 
		{
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
