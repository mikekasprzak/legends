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
enum {	// Package Chunk Types //
	NP_UNRELIABLE = 0x0000,
	NP_RELIABLE = 0x8000,

	NP_EOF = 0,							// Special code for no more chunks (Type=0 and Size=0) //
	NP_PING = 1,						// Ping Message (i.e. Unreliable UID) //
	NP_PONG = 2,						// Ping Response (i.e. Unreliable Receipt) //
	NP_UID = 1 | NP_RELIABLE,			// UID Chunk (also reliable) //
	NP_RECEIPT = 2 | NP_RELIABLE,		// Receipt Chunk (also reliable) //
	NP_UNRELIABLE_MESSAGE = 4,			// Unreliable Chat Messages (Unused?) //
	NP_MESSAGE = 4 | NP_RELIABLE,		// Chat Messages (TODO: Sender, Recipiant/Channel) //
	
	// TODO: File Payloads? //
	
	NP_BASE = 8,						// Base ID to use for new message codes //
	NP_RELIABLE_BASE = 8 | NP_RELIABLE,	// Base ID to use for new reliable message codes //
};
// - ------------------------------------------------------------------------------------------ - //
struct cNP_Header {
	unsigned short Type;				// One of the above enums, or custom (NP_RELIABLE_BASE+value) //
	unsigned short Size;				// In Bytes //
};
// - ------------------------------------------------------------------------------------------ - //
template< class Type = char >
struct cNP_Chunk {
	cNP_Header Header;
	Type Data[0];

	inline const size_t Size() const {	// In Types //
		return Header.Size / sizeof(Type);
	}
	inline const size_t SizeOf() const {// In Bytes //
		return Header.Size;				
	}
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// A chunked data format that is built by Clients and Servers, then sent over some transport. //
// NetPackage structures contain padding, and each chunk has an 8 byte header. //
class cNetPackage {
	static unsigned _NextUID;
	inline static const unsigned NextUID() {
		return _NextUID++;		// Thread Unsafe //
	}
	
	// TODO: Replace with cGelArray2 replacement //
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
		
		cNP_Chunk<>* Base = (cNP_Chunk<>*)Data.PushBlockBack( sizeof(cNP_Chunk<>) );
		Base->Header.Type = Type;
		Base->Header.Size = 0;
	}
	
	inline void Write( const void* Src, const unsigned short _Size ) {
		// TODO: Assert //
		cNP_Chunk<>* Base = (cNP_Chunk<>*)Data.PushBlockBack( Src, _Size );
		Base->Header.Size += _Size;
	}
	
	inline void WriteCopy( const void* Src ) {
		// TODO: Assert //
		cNP_Chunk<>* Base = (cNP_Chunk<>*)Src;
		Write( Src, Base->Header.Size + sizeof(cNP_Chunk<>) );
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

	// Add a chunk that uniquely identifies this packet //
	inline void AddUID() {
		AddChunk( NP_UID );
		WriteU32( NextUID() );
	}
	inline void AddReceipt( const unsigned UID ) {
		AddChunk( NP_RECEIPT );
		WriteU32( UID );
	}
	
	// Add a chunk that signifies the ending of the packet //
	inline void AddEnd() {
		AddChunk( NP_EOF );
	}
	
	// Populate with the necessary data to be a complete packet //
	inline void AddPing() {
		AddChunk( NP_PING );
		AddEnd();
	}
	inline void AddPong() {
		AddChunk( NP_PING );
		AddEnd();
	}
	
	// Takes an incoming NetPackage and generates a receipt plus a copy of all reliable data //
	inline void AddReceipt( cNetPackage* In ) {
		typedef cNP_Chunk<unsigned> cNP_ReceiptChunk;
		cNP_ReceiptChunk* Chunk = (cNP_ReceiptChunk*)Get();
		while( Chunk ) {
			if ( Chunk->Header.Type == NP_UID ) {
				AddReceipt( Chunk->Data[0] );		// Only because it's an <unsigned> this is legal //
			}
			Chunk = (cNP_ReceiptChunk*)Next( Chunk );
		}
	}
	
	// Copies all the reliable chunks from a NetPackage (used to resend) //
	inline void AddReliableChunks( cNetPackage* In ) {
		cNP_Chunk<>* Chunk = Get();
		while( Chunk ) {
			if ( Chunk->Header.Type & NP_RELIABLE ) {
				WriteCopy( Chunk );
			}
			Chunk = Next( Chunk );
		}
	}

public:
	inline const st32 Size() const {
		return Data.Size();
	}
	inline const st32 SizeOf() const {
		return Data.SizeOf();
	}
	
	inline cNP_Chunk<>* Get() {
		return (cNP_Chunk<>*)(*Data)->Data;
	}
	
	inline cNP_Chunk<>* Next( void* Pos ) {
		// TODO: Assert //
		cNP_Chunk<>* Base = (cNP_Chunk<>*)Pos;
		if ( Base->Header.Type == NP_EOF ) {
			return 0;
		}
		
		size_t NextPos = Base->Header.Size;
		// If misaligned, then skip over padding //
		if ( NextPos & 3 ) {
			NextPos += 4 - (NextPos & 3);
		}
		Base += sizeof(cNP_Chunk<>) + NextPos;
		return Base;
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __NET_NETPACKAGE_H__ //
// - ------------------------------------------------------------------------------------------ - //