// - ------------------------------------------------------------------------------------------ - //
// A class for working with chunked files (Size+Magic+Data) //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Chunk_ChunkReader_H__
#define __Chunk_ChunkReader_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Core/DataBlock.h>
// - ------------------------------------------------------------------------------------------ - //
class cChunkReader {
	char* ChunkData;
	char* Current;

	enum {
		CHUNK_SIZE = 0,
		CHUNK_NAME = 4,
		CHUNK_HEADER_SIZE = 8
	};
public:
	cChunkReader() {
	}
	
	cChunkReader( char* _Data ) {
		Load( _Data );
	}
	
	cChunkReader( DataBlock* _Data ) {
		Load( _Data );
	}
	
	void Load( DataBlock* _Data ) {
		ChunkData = _Data->Data;
		First();
	}
	
	void Load( char* _Data ) {
		ChunkData = _Data;
		First();
	}
	
public:	
	inline bool Is( const char* Pattern ) const {
		return Name() == *(const int*)&Pattern[0];
	}

	inline const int Size() const {
		return *(int*)&Current[ CHUNK_SIZE ];
	}
	
	inline const int Name() const {
		return *(const int*)&Current[ CHUNK_NAME ];
	}

	inline const int* NamePointer() const {
		return (const int*)&Current[ CHUNK_NAME ];
	}
	
	template< class T >
	inline T* Data() {
		return (T*)&Current[ CHUNK_HEADER_SIZE ];
	}

public:
	inline void First() {
		Current = ChunkData;
	}
	
	inline void Next() {
		Current += CHUNK_HEADER_SIZE + Size();
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Chunk_ChunkReader_H__ //
// - ------------------------------------------------------------------------------------------ - //
