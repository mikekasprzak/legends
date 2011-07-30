// - ------------------------------------------------------------------------------------------ - //
#ifndef __Allocator_H__
#define __Allocator_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// TODO: Promote this to a variant of StaticArray in the Data Library. //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
class Allocator {
public:
	int _Size;
	Type* Data;
public:
//	inline Allocator() :
//		_Size( 0 )
//	{
//		Data = new Type[_MaxSize];
//	}

	inline Allocator( const int _MaxSize, const int Start = 0 ) :
		_Size( Start )
	{
		Data = new Type[_MaxSize];
	}
	
	inline ~Allocator() {
		delete [] Data;
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
#endif // __Allocator_H__ //
// - ------------------------------------------------------------------------------------------ - //
