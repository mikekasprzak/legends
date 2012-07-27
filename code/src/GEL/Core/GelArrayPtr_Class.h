// - ------------------------------------------------------------------------------------------ - //
// GelArrayPtr Class - Variation of cGelArray. Includes pointer specific calls. //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_GelArrayPtr_Class_H__
#define __Library_Data_GelArrayPtr_Class_H__
// - ------------------------------------------------------------------------------------------ - //
#include "GelArray_Class.h"
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
class cGelArrayPtr: public cGelArray<Type> {
public:
	enum {
		null = 0
	};
public:
	// Constructor //
	inline cGelArrayPtr() :
		cGelArray<Type>()
	{
	}
	
	// Contrast to cGelArray, this will always initialize to null, due to uses //
	inline cGelArrayPtr( const size_t _Size ) :
		cGelArray<Type>( _Size, (Type)null )
	{
	}
	
	inline cGelArrayPtr( const size_t _Size, const Type& _InitValue ) :
		cGelArray<Type>( _Size, _InitValue )
	{
	}
	
	// Given a filename as an argument, load it //
	inline cGelArrayPtr( const char* _FileName ) :
		cGelArray<Type>( _FileName )
	{
	}
	
	// Given an GelArray, make our GelArray directly what we were given //
	// Note: I'm now in charge of freeing, so don't try sharing this data //
	inline cGelArrayPtr( GelArray<Type>* _Src ) :
		cGelArray<Type>( _Src )
	{
	}
	
	// Copy Constructor - replicates the contents of a DataBlock//
	inline cGelArrayPtr( const cGelArray<Type>& _Src ) :
		cGelArray<Type>( _Src )
	{
	}
	
	// Destructor //
	inline virtual ~cGelArrayPtr() {
		// Will not automatically delete! You must explicitly call delete! //
	}
public:	
	// Removing is nulling the pointer //
	inline void Remove( const size_t Index ) {
		cGelArray<Type>::_Data->Data[ Index ] = (Type)null;
	}
	inline void RemoveAll() {
		for ( size_t idx = cGelArray<Type>::Size(); idx--; ) {
			Remove( idx );
		}
	}
	inline void RemoveAll( const size_t Start, const size_t Count ) {
		// NOTE: size_t handles < 0
		Assert( Start >= cGelArray<Type>::Size(), "Start (%i) is out of range (>= %i)", Start, cGelArray<Type>::Size() );
		// NOTE: This is written funny to encourage the optimizer to eliminate this check //
		size_t idx;
		if ( Start+Count > cGelArray<Type>::Size() )
			idx = cGelArray<Type>::Size();
		else
			idx = Start+Count;

		// Index in Reverse Order //
		for ( ; idx-- > Start; ) {
			Remove(idx);
		}
	}

	
	// Deleting is explicitly C++ style delete, followed by nulling //
	inline void Delete( const size_t Index ) {
		if ( cGelArray<Type>::_Data->Data[ Index ] != (Type)null ) {
			delete cGelArray<Type>::_Data->Data[ Index ];
			Remove( Index ); // Null the Pointer //
		}
	}
	inline void DeleteAll() {
		for ( size_t idx = cGelArray<Type>::Size(); idx--; ) {
			Delete( idx );
		}
	}
	inline void DeleteAll( const size_t Start, const size_t Count ) {
		// NOTE: size_t handles < 0
		Assert( Start >= cGelArray<Type>::Size(), "Start (%i) is out of range (>= %i)", Start, cGelArray<Type>::Size() );
		// NOTE: This is written funny to encourage the optimizer to eliminate this check //
		size_t idx;
		if ( Start+Count > cGelArray<Type>::Size() )
			idx = cGelArray<Type>::Size();
		else
			idx = Start+Count;

		// Index in Reverse Order //
		for ( ; idx-- > Start; ) {
			Delete(idx);
		}
	}
	
	// Variation of delete that does not null. Exists only really to save a cycle. //
	inline void _Delete( const size_t Index ) {
		if ( cGelArray<Type>::_Data->Data[ Index ] != (Type)null ) {
			delete cGelArray<Type>::_Data->Data[ Index ];
		}
	}
	inline void _DeleteAll() {
		for ( size_t idx = cGelArray<Type>::Size(); idx--; ) {
			_Delete( idx );
		}
	}
	inline void _DeleteAll( const size_t Start, const size_t Count ) {
		// NOTE: size_t handles < 0
		Assert( Start >= cGelArray<Type>::Size(), "Start (%i) is out of range (>= %i)", Start, cGelArray<Type>::Size() );
		// NOTE: This is written funny to encourage the optimizer to eliminate this check //
		size_t idx;
		if ( Start+Count > cGelArray<Type>::Size() )
			idx = cGelArray<Type>::Size();
		else
			idx = Start+Count;

		// Index in Reverse Order //
		for ( ; idx-- > Start; ) {
			_Delete(idx);
		}
	}
		
	// Erasing is physically removing the data while resizing //
	// TODO: Do this inside cGelArray. //

	// DeleteErase doing a delete, followed by physically removing the data while resizing //
	// TODO: this. //
	
	// More word choices: Eradicate, Eliminate, Destroy, Kill, Expunge
	// DeleteErase, while phonetically strange, is more specific RE what is being done.
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_GelArrayPtr_Class_H__ //
// - ------------------------------------------------------------------------------------------ - //
