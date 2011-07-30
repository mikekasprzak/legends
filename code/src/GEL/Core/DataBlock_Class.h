// - ------------------------------------------------------------------------------------------ - //
// DataBlock Class - Class version of DataBlock. Deletes self as it goes out of scope. //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_DataBlock_Class_H__
#define __Library_Data_DataBlock_Class_H__
// - ------------------------------------------------------------------------------------------ - //
#include "DataBlock_Core.h"
#include "DataBlock_File.h"
#include "DataBlock_Hash32.h"
// - ------------------------------------------------------------------------------------------ - //
#pragma warning "DataBlock Class is depricated"
// - ------------------------------------------------------------------------------------------ - //
//namespace Data {
// - ------------------------------------------------------------------------------------------ - //
class cDataBlock {
protected:
	DataBlock* _Data;
	
public:
	// Constructor //
	inline cDataBlock() :
		_Data( 0 )
	{
	}
	
	// Since this is a "power use" class, I'm making initializing optional //
	inline cDataBlock( const size_t _Size ) :
		_Data( new_DataBlock( _Size ) )
	{
	}
	
	inline cDataBlock( const size_t _Size, const int _InitValue ) :
		_Data( new_DataBlock( _Size, _InitValue ) )
	{
	}
	
	// Given a filename as an argument, load it //
	inline cDataBlock( const char* _FileName ) :
		_Data( new_DataBlock( _FileName ) )
	{
	}
	
	// Given a DataBlock, make our DataBlock directly what we were given //
	// Note: I'm now in charge of freeing, so don't try sharing this data //
	inline cDataBlock( DataBlock* _Src ) :
		_Data( _Src )
	{
	}
	
	// Copy Constructor - replicates the contents of a DataBlock//
	inline cDataBlock( const cDataBlock& _Src ) :
		_Data( copy_DataBlock( _Src._Data ) )
	{
	}
	
	// Destructor //
	inline ~cDataBlock() {
		if (_Data)
			delete_DataBlock( _Data );
	}
public:
	inline size_t Size() const {
		if (_Data)
			return _Data->Size;
		return 0;
	}
	
	inline const char* Data() const {
		if (_Data)
			return _Data->Data;
		return 0;
	}
	
	inline char& operator [] ( const size_t Index ) {
		// TODO: Assert indexing in to valid memory, and within size? //
		return _Data->Data[ Index ];
	}
	
	inline DataBlock* operator * () {
		return _Data;	
	}
public:
	inline void Load( const char* _FileName ) {
		// Delete the file if there is one loaded //
		if (_Data)
			delete_DataBlock( _Data );
		// load the file //
		_Data = new_DataBlock( _FileName );
	}
	
	inline void Save( const char* _FileName ) {
		if (_Data)
			write_DataBlock( _Data, _FileName );
	}

public:
	inline void Resize( const size_t _Size ) {
		if (_Data)
			resize_DataBlock( &_Data, _Size );
	}
	
	inline void Set( const int _InitValue ) {
		if (_Data)
			set_DataBlock( _Data, _InitValue );
	}
	
	inline void Clear( ) {
		Set( 0 );
	}
	
	inline void PushBack( const int _InitValue ) {
		pushback_DataBlock( &_Data, _InitValue );
	}
	
	inline const int PopBack() {
		return popback_DataBlock( &_Data );
	}
public:
	// Compression //
	inline static const cDataBlock UnpackLZMA( const cDataBlock& _Src );
	inline static const cDataBlock UnpackLZMA( const DataBlock* _Src );
	
	inline static cDataBlock UnpackBZIP( cDataBlock& _Src );
	inline static cDataBlock UnpackBZIP( DataBlock* _Src );
	inline static cDataBlock PackBZIP( cDataBlock& _Src );
	inline static cDataBlock PackBZIP( DataBlock* _Src );
	
	inline static cDataBlock UnpackZLIB( cDataBlock& _Src );
	inline static cDataBlock UnpackZLIB( DataBlock* _Src );
	inline static cDataBlock PackZLIB( cDataBlock& _Src );
	inline static cDataBlock PackZLIB( DataBlock* _Src );
	
	inline static cDataBlock UnpackLZO( cDataBlock& _Src );
	inline static cDataBlock UnpackLZO( DataBlock* _Src );
	inline static cDataBlock PackLZO( cDataBlock& _Src );
	inline static cDataBlock PackLZO( DataBlock* _Src );

	// Hash //
	inline const unsigned int Hash32() const {
		return hash32_DataBlock( _Data );
	}
	//inline static const MD5Hash HashMD5( const cDataBlock& _Src  );
	//inline static const SHA1Hash HashSHA1( const cDataBlock& _Src  );
};
// - ------------------------------------------------------------------------------------------ - //
//}; // namespace Data //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_DataBlock_Class_H__ //
// - ------------------------------------------------------------------------------------------ - //
