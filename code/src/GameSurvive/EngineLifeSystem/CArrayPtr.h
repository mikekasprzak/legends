// - ------------------------------------------------------------------------------------------ - //
#ifndef __CARRAYPTR_H__
#define __CARRAYPTR_H__
// - ------------------------------------------------------------------------------------------ - //
// C Array of Pointers -- Enhanced version of a C Array, with pointer specific features //
//   T is assumed to be a pointer //
// - ------------------------------------------------------------------------------------------ - //
#include <string.h>
// - ------------------------------------------------------------------------------------------ - //
template<class T, size_t _Size>
class CArrayPtr {
	T Data[_Size];

public:
	static T ErrorPtr;
	
	enum {
		Error = -1,
		Empty = 0,
		
		FirstIndex = 0,
		LastIndex = _Size-1,
		
		// Feed these values in to NextIterator and PrevIterator //
		FrontIterator = FirstIndex-1,
		BackIterator = LastIndex+1,
	};

public:
	inline CArrayPtr() {
		Zero();
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

	// SizeOf() returns the array size, because Size() should change.
	inline static const size_t SizeOf() {
		return _Size;
	}
	
	// Size() returns elements used, for compatibility with other arrays.
	inline const size_t Size() const {
		size_t Count = 0;
		
		for ( size_t idx = _Size; idx--; ) {
			if ( Data[idx] != (T)Empty )
				Count++;
		}
		
		return Count;
	}
	
	
	inline void Remove( const size_t Index ) {
		Data[Index] = (T)Empty;
	}
	inline void Zero( const size_t Start = 0, const size_t Count = _Size ) {
		// TODO: Assert Start > _Size; Start < 0 handled by size_t
		// NOTE: This is written funny to encourage the optimizer to eliminate this check //
		size_t idx;
		if ( Start+Count > _Size )
			idx = _Size;
		else
			idx = Start+Count;

		// Index in Reverse Order //
		for ( ; idx-- > Start; ) {
			Remove(idx);
		}
	}
	
	inline void Delete( const size_t Index ) {
		if ( Data[Index] ) {
			delete Data[Index];
			Remove(Index);
		}
	}
	inline void Clear( const size_t Start = 0, const size_t Count = _Size ) {
		// TODO: Assert Start > _Size; Start < 0 handled by size_t
		// NOTE: This is written funny to encourage the optimizer to eliminate this check //
		size_t idx;
		if ( Start+Count > _Size )
			idx = _Size;
		else
			idx = Start+Count;

		// Index in Reverse Order //
		for ( ; idx-- > Start; ) {
			Delete(idx);
		}
	}
	
	// - ------------------------------------------------------------------ - //
	
	// Smart Indexing Function //
	inline T& Index( const int idx ) {
		if ( idx < 0 )
			return ErrorPtr;
		else if ( idx >= _Size )
			return ErrorPtr;
		return Data[idx];
	}
	inline const T& Index( const int idx ) const {
		if ( idx < 0 )
			return ErrorPtr;
		else if ( idx >= _Size )
			return ErrorPtr;
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
			return Data[0];
		else if ( idx >= _Size )
			return Data[_Size-1];
		return Data[idx];
	}
	inline const T& Saturate( const int idx ) const {
		if ( idx < 0 )
			return Data[0];
		else if ( idx >= _Size )
			return Data[_Size-1];
		return Data[idx];
	}
	
	// - ------------------------------------------------------------------ - //
	
	// Given a Pointer value, Find the Index that points to it ------------ - //
	inline const int FindIndex( const T Vs ) const {
		for ( size_t idx = 0; idx < _Size; idx++ ) {
			if ( Data[idx] == Vs )
				return idx;
		}
		return Error;
	}

	inline const int FindIndexBack( const T Vs ) const {
		// Index in Reverse Order //
		for ( size_t idx = _Size; idx--; ) {
			if ( Data[idx] == Vs )
				return idx;
		}
		return Error;
	}

	// NOTE: No "Find()" function because you should always verify that an //
	//       index was actually found. //
	
	// - ------------------------------------------------------------------ - //

	// Iterator Functions -- Iterator results are Indexing compatable, but -- //
	//                       you'll want to confirm the iterator is legal. -- //
	
	// HOW TO USE:
	//	int Index = Active.FrontIterator;
	//	while( !Active.IsError( Index = Active.NextIterator(Index) ) ) {
	//	}
	inline const int NextIterator( const int Index = FrontIterator ) const {
		for ( size_t idx = Index+1; idx < _Size; idx++ ) {
			if ( Data[idx] != (T)Empty )
				return idx;
		}
		return Error;
	}
	inline const int FirstIterator() const {
		return NextIterator();
	}

	// HOW TO USE:
	//	int Index = Active.BackIterator;
	//	while( !Active.IsError( Index = Active.PrevIterator(Index) ) ) {
	//	}
	inline const int PrevIterator( const int Index = BackIterator ) const {
		for ( size_t idx = Index-1; idx--; ) {
			if ( Data[idx] != (T)Empty )
				return idx;
		}
		return Error;
	}
	inline const int LastIterator() const {
		return PrevIterator();
	}

	// - ------------------------------------------------------------------ - //
	
	// Get an unused Index ------------------------------------------------ - //
	inline const int GetIndex() {
		for ( size_t idx = 0; idx < _Size; idx++ ) {
			if ( Data[idx] == (T)Empty )
				return idx;
		}
		return Error;
	}
	
	inline const int GetIndexBack() {
		// Index in Reverse Order //
		for ( size_t idx = _Size; idx--; ) {
			if ( Data[idx] == (T)Empty )
				return idx;
		}
		return Error;
	}

	// - ------------------------------------------------------------------ - //
	
	// Get a reference to an unused array element ------------------------- - //
	inline T& Get() {
		for ( size_t idx = 0; idx < _Size; idx++ ) {
			if ( Data[idx] == (T)Empty )
				return Data[idx];
		}
		return ErrorPtr;
	}
	inline const T& Get() const {
		for ( size_t idx = 0; idx < _Size; idx++ ) {
			if ( Data[idx] == (T)Empty )
				return Data[idx];
		}
		return ErrorPtr;
	}
	
	inline T& GetBack() {
		// Index in Reverse Order //
		for ( size_t idx = _Size; idx--; ) {
			if ( Data[idx] == (T)Empty )
				return Data[idx];
		}
		return ErrorPtr;
	}
	inline const T& GetBack() const {
		// Index in Reverse Order //
		for ( size_t idx = _Size; idx--; ) {
			if ( Data[idx] == (T)Empty )
				return Data[idx];
		}
		return ErrorPtr;
	}

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
		Data[Start] = (T)Empty;
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
		Data[Start+Count-1] = (T)Empty;
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
T CArrayPtr<T,_Size>::ErrorPtr = (T)CArrayPtr<T,_Size>::Empty;
// - ------------------------------------------------------------------------------------------ - //
#endif // __CARRAYPTR_H__ //
// - ------------------------------------------------------------------------------------------ - //
