// - ------------------------------------------------------------------------------------------ - //
// A class for safely reading streams of data //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_StreamReader_H__
#define __GEL_StreamReader_H__
// - ------------------------------------------------------------------------------------------ - //
class cStreamReader {
	int StreamSize;
	const char* Start;
	const char* End;
	const char* Current;
public:
	template< class T >
	cStreamReader( T* _Ptr, int _Size = -1 ) :
		StreamSize( _Size ),
		Start( (const char*)_Ptr ),
		Current( (const char*)_Ptr )
	{
		if ( _Size == -1 ) {
			End = (const char*)-1;
		}
		else {
			End = Start+_Size;
		}
	}
	
	inline bool IsAtEnd() {
		return Current >= End;
	}
	
	// TODO: Make versions of these functions that read per-byte, for broken aligned-read systems //
	inline int GetInt() {
		int Value = *(const int*)Current;
		Current += sizeof(int);
		return Value;
	}
	
	inline int GetInt( const int Count ) {
		int Value;
		
		if ( Count >= 4 ) {
			Value = *(const int*)Current;
		}
		else if ( Count == 3 ) {
			Value = (*(const int*)Current) & 0xffffff;
			// Sign Extend //
			if ( Value > 0x7fffff )
				Value |= 0xff000000;
		}
		else if ( Count == 2 ) {
			Value = *(const short*)Current;
		}
		else if ( Count == 1 ) {
			Value = *(const char*)Current;
		}

		Current += Count;
		return Value;
	}
	
	inline const char* const GetString( const int Count ) {
		const char* Value = Current;
		
		Current += Count;
		return Value;
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_StreamReader_H__ //
// - ------------------------------------------------------------------------------------------ - //
