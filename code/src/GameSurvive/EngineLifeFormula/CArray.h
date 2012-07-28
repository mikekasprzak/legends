// - ------------------------------------------------------------------------------------------ - //
#ifndef __CARRAY_H__
#define __CARRAY_H__
// - ------------------------------------------------------------------------------------------ - //
// C Array -- Enhanced version of a C Array //
// - ------------------------------------------------------------------------------------------ - //
#include <string.h>
// - ------------------------------------------------------------------------------------------ - //
template<class T, size_t _Size>
class CArray {
protected:
	T Data[_Size];
public:
	static T ErrorData;

	enum {
		Error = -1,
		
		FirstIndex = 0,
		LastIndex = _Size-1,		
	};

public:
	inline CArray() {
	}

	inline T& operator [] ( const size_t Index ) {
		return Data[Index];
	}
	inline const T& operator [] ( const size_t Index ) const {
		return Data[Index];
	}
	
	inline T& Front() {
		return Data[FirstIndex];
	}
	inline const T& Front() const {
		return Data[FirstIndex];
	}

	inline T& Back() {
		return Data[LastIndex];
	}
	inline const T& Back() const {
		return Data[LastIndex];
	}

public:
	// Check for Error with this handy syntax //
	inline static const bool IsError( const int Value ) {
		return Value == Error;
	}

	// SizeOf() returns the array size, for compatibility. //
	inline static const size_t SizeOf() {
		return _Size;
	}
	
	// Size() returns the array size //
	inline const size_t Size() const {
		return _Size;
	}
		
	// - ------------------------------------------------------------------ - //
	
	// Smart Indexing Function //
	inline T& Index( const int idx ) {
		if ( idx < 0 )
			return ErrorData;
		else if ( idx >= _Size )
			return ErrorData;
		return Data[idx];
	}
	inline const T& Index( const int idx ) const {
		if ( idx < 0 )
			return ErrorData;
		else if ( idx >= _Size )
			return ErrorData;
		return Data[idx];
	}
		
	// Wrapping Index Function //
	inline T& Wrap( const int idx ) {
		return Data[idx % _Size];
	}
	inline const T& Wrap( const int idx ) const {
		return Data[idx % _Size];
	}
		
	// Saturation Indexing Function //
	inline T& Saturate( const int idx ) {
		if ( idx < 0 )
			return Data[FirstIndex];
		else if ( idx >= _Size )
			return Data[LastIndex];
		return Data[idx];
	}
	inline const T& Saturate( const int idx ) const {
		if ( idx < 0 )
			return Data[FirstIndex];
		else if ( idx >= _Size )
			return Data[LastIndex];
		return Data[idx];
	}
	
	// - ------------------------------------------------------------------ - //
	
	// Given a value, Find the Index that points to it -------------------- - //
	inline const int FindNextIndex( const T& Vs, const size_t Start = FirstIndex-1 ) const {
		for ( size_t idx = Start+1; idx < _Size; idx++ ) {
			if ( Data[idx] == Vs )
				return idx;
		}
		return Error;
	}

	inline const int FindPrevIndex( const T& Vs, const size_t Start = LastIndex+1 ) const {
		// Index in Reverse Order //
		for ( size_t idx = Start; idx--; ) {
			if ( Data[idx] == Vs )
				return idx;
		}
		return Error;
	}

	// NOTE: No "Find()" function because you should always verify that an //
	//       index was actually found. //

	// - ------------------------------------------------------------------ - //

	inline void Swap( const size_t A, const size_t B ) {
		T Temp = B;
		B = A;
		A = Temp;
	}
	
	inline void _MoveForward( const size_t Start = 0, const size_t Count = _Size ) {
		// TODO: Assert Start > _Size; Start < 0 handled by size_t
		// NOTE: This is written funny to encourage the optimizer to eliminate this check //
		size_t idx;
		if ( Start+Count-1 > _Size-1 )
			idx = _Size-1;
		else
			idx = Start+Count-1;   
			
		// Index in Reverse Order //
		for ( ; idx-- > Start; ) {
			Data[idx+1] = Data[idx];
		}
	}
	inline void MoveForward( const size_t Start = 0, const size_t Count = _Size ) {
		_MoveForward( Start, Count );
		Data[Start] = T();
	}
	inline void PushFront( const T& Value ) {
		_MoveForward();
		Data[FirstIndex] = Value;
	}
	inline const T PopBack() {
		T Value = Data[LastIndex];
		MoveForward();
		return Value;
	}

	inline void _MoveBackward( const size_t Start = 0, const size_t Count = _Size ) {
		// TODO: Assert Start > _Size; Start < 0 handled by size_t
		// NOTE: This is written funny to encourage the optimizer to eliminate this check //
		size_t MaxIndex;
		if ( Start+Count-1 > _Size-1 )
			MaxIndex = _Size-1;
		else
			MaxIndex = Start+Count-1;   
			
		for ( size_t idx = Start; idx < MaxIndex; idx++ ) {
			Data[idx] = Data[idx+1];
		}
	}
	inline void MoveBackward( const size_t Start = 0, const size_t Count = _Size ) {
		_MoveBackward( Start, Count );
		Data[Start+Count-1] = T();
	}
	inline void PushBack( const T& Value ) {
		_MoveBackward();
		Data[LastIndex] = Value;
	}
	inline const T PopFront() {
		T Value = Data[FirstIndex];
		MoveBackward();
		return Value;
	}
			
//	inline void Defragment() {
//	inline void FrontAlign() {
//	inline void BackAlign() {	
		
	// - ------------------------------------------------------------------ - //
};
// - ------------------------------------------------------------------------------------------ - //
template <class T, size_t _Size> 
T CArray<T,_Size>::ErrorData = T();
// - ------------------------------------------------------------------------------------------ - //
#endif // __CARRAY_H__ //
// - ------------------------------------------------------------------------------------------ - //
