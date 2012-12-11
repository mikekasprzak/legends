// - ------------------------------------------------------------------------------------------ - //
// A NetPackage is like a Network Packet (eventually, it becomes one). //
// It's a collection of messages, and supports combining reliable and //
// unreliable messages in to a single package (of messages). //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __NET_NETPACKAGE_H__
#define __NET_NETPACKAGE_H__
// - ------------------------------------------------------------------------------------------ - //
#include <string.h>
#include <Core/GelArray.h>
// - ------------------------------------------------------------------------------------------ - //
enum {	// Package Types //
	NP_UNRELIABLE = 0x0000,
	NP_RELIABLE = 0x8000,

	NP_EOF = 0,							// Special code for no more chunks (Type=0 and Size=0) //
	NP_PING = 1,						// Ping Message //
	NP_PONG = 2,						// Ping Response //
	NP_UNRELIABLE_MESSAGE = 3,			// Unreliable Chat Messages (Unused?) //
	NP_RECEIPT = 0 | NP_RELIABLE,		// Special code for receipts (also reliable) //
	NP_MESSAGE = 3 | NP_RELIABLE,		// Chat Messages (TODO: Sender, Recipiant/Channel) //
	
	// TODO: File Payloads? //
	
	NP_BASE = 8,						// Base ID to use for new message codes //
	NP_RELIABLE_BASE = 8 | NP_RELIABLE,	// Base ID to use for new reliable message codes //
};
// - ------------------------------------------------------------------------------------------ - //
struct cNP_Header {
	unsigned short Type;				// One of the above enums, or custom (NP_RELIABLE_BASE+value) //
	unsigned short UID;					// Unique Packet ID (Just a local incrementing number) //
	st32 Size;							// In Bytes //
};
// - ------------------------------------------------------------------------------------------ - //
struct cNP_Chunk {
	cNP_Header Header;
	char Data[0];

	inline const size_t Size() const {
		return Header.Size;
	}
	inline const size_t SizeOf() const {
		return Header.Size;				// Always in Bytes //
	}
};
// - ------------------------------------------------------------------------------------------ - //
// Receipts are confirmations that a reliable packet was recieved //
struct cNP_ReceiptChunk {
	cNP_Header Header;
	unsigned short Data[0];				// UID //
	
	inline const size_t Size() const {
		return Header.Size >> 1;		// We know the correct Data Size! //
	}
	inline const size_t SizeOf() const {
		return Header.Size;				// Always in Bytes //
	}
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// A chunked data format that is built by Clients and Servers, then sent over some transport. //
// NetPackage structures contain padding, and each chunk has an 8 byte header. //
class cNetPackage {
	static unsigned short _NextUID;
	inline static const unsigned short NextUID() {
		return _NextUID++;		// Thread Unsafe //
	}
	
	cGelArray<char> Data;
public:
	cNetPackage() {
	}
	
	inline void AddChunk( const unsigned short Type ) {
		// Write Padding //
		if ( Data.Size() & 3 ) {
			int Dummy = 0;
			Write( (void*)&Dummy, 4 - (Data.Size() & 3) );
		}
		
		cNP_Chunk* Base = (cNP_Chunk*)Data.PushBlockBack( sizeof(cNP_Chunk) );
		Base->Header.Type = Type;

		if ( Type & NP_RELIABLE ) {
			Base->Header.UID = NextUID();
		}
		else {
			Base->Header.UID = 0;
		}

		Base->Header.Size = 0;
	}
	
	inline void Write( const void* Src, const unsigned short _Size ) {
		cNP_Chunk* Base = (cNP_Chunk*)Data.PushBlockBack( Src, _Size );
		Base->Header.Size += _Size;
	}

	inline void WriteU8( const u8 Value )   { Write( (void*)&Value, sizeof(Value) ); }
	inline void WriteS8( const s8 Value )   { Write( (void*)&Value, sizeof(Value) ); }
	inline void WriteU16( const u16 Value ) { Write( (void*)&Value, sizeof(Value) ); }
	inline void WriteS16( const s16 Value ) { Write( (void*)&Value, sizeof(Value) ); }
	inline void WriteU32( const u32 Value ) { Write( (void*)&Value, sizeof(Value) ); }
	inline void WriteS32( const s32 Value ) { Write( (void*)&Value, sizeof(Value) ); }
	inline void WriteU64( const u64 Value ) { Write( (void*)&Value, sizeof(Value) ); }
	inline void WriteS64( const s64 Value ) { Write( (void*)&Value, sizeof(Value) ); }
	inline void WriteF32( const f32 Value ) { Write( (void*)&Value, sizeof(Value) ); }
	inline void WriteF64( const f64 Value ) { Write( (void*)&Value, sizeof(Value) ); }
	
	inline const st32 Size() const {
		return Data.Size();
	}
	inline const st32 SizeOf() const {
		return Data.SizeOf();
	}
	
	inline char* Front() {
		return (*Data)->Data;
	}
	
	inline char* Next( const char* Pos ) {
		// TODO: Assert //

		cNP_Chunk* Base = (cNP_Chunk*)Pos;
		if ( Base->Header.Type == NP_EOF ) {
			return 0;
		}
		
		size_t NextPos = Base->Header.Size;
		if ( NextPos & 3 ) {
			NextPos += 4 - (NextPos & 3);
		}
		Base += sizeof(cNP_Chunk) + NextPos;
		return (char*)Base;
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __NET_NETPACKAGE_H__ //
// - ------------------------------------------------------------------------------------------ - //
