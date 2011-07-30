// - ------------------------------------------------------------------------------------------ - //
// Endian - Endian manipulation functions //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_Endian_Core_H__
#define __Library_Data_Endian_Core_H__
// - ------------------------------------------------------------------------------------------ - //
// TODO: Add block swapping functions //
// - ------------------------------------------------------------------------------------------ - //
//namespace Data {
// - ------------------------------------------------------------------------------------------ - //
// Putting the uEndianMunge class in it's own namespace, since it's not needed elsewhere //
// - ------------------------------------------------------------------------------------------ - //
namespace Endian {
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
union uEndianMunge {
	Type Source;
	unsigned char Byte[ sizeof(Type ) ];
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Endian //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const Type byteswap2( const Type _Src ) {
	Endian::uEndianMunge<Type> Src;
	Src.Source = _Src;
	
	Endian::uEndianMunge<Type> Copy;
	Copy.Byte[0] = Src.Byte[1];
	Copy.Byte[1] = Src.Byte[0];
	
	return Copy.Source;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const Type byteswap3( const Type _Src ) {
	Endian::uEndianMunge<Type> Src;
	Src.Source = _Src;
	
	Endian::uEndianMunge<Type> Copy;
	Copy.Byte[0] = Src.Byte[2];
	Copy.Byte[1] = Src.Byte[1];
	Copy.Byte[2] = Src.Byte[0];
	
	return Copy.Source;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const Type byteswap4( const Type _Src ) {
	Endian::uEndianMunge<Type> Src;
	Src.Source = _Src;
	
	Endian::uEndianMunge<Type> Copy;
	Copy.Byte[0] = Src.Byte[3];
	Copy.Byte[1] = Src.Byte[2];
	Copy.Byte[2] = Src.Byte[1];
	Copy.Byte[3] = Src.Byte[0];
	
	return Copy.Source;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const Type byteswap6( const Type _Src ) {
	Endian::uEndianMunge<Type> Src;
	Src.Source = _Src;
	
	Endian::uEndianMunge<Type> Copy;
	Copy.Byte[0] = Src.Byte[5];
	Copy.Byte[1] = Src.Byte[4];
	Copy.Byte[2] = Src.Byte[3];
	Copy.Byte[3] = Src.Byte[2];
	Copy.Byte[4] = Src.Byte[1];
	Copy.Byte[5] = Src.Byte[0];
	
	return Copy.Source;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const Type byteswap8( const Type _Src ) {
	Endian::uEndianMunge<Type> Src;
	Src.Source = _Src;
	
	Endian::uEndianMunge<Type> Copy;
	Copy.Byte[0] = Src.Byte[7];
	Copy.Byte[1] = Src.Byte[6];
	Copy.Byte[2] = Src.Byte[5];
	Copy.Byte[3] = Src.Byte[4];
	Copy.Byte[4] = Src.Byte[3];
	Copy.Byte[5] = Src.Byte[2];
	Copy.Byte[6] = Src.Byte[1];
	Copy.Byte[7] = Src.Byte[0];
	
	return Copy.Source;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const Type byteswap16( const Type _Src ) {
	Endian::uEndianMunge<Type> Src;
	Src.Source = _Src;
	
	Endian::uEndianMunge<Type> Copy;
	Copy.Byte[0]  = Src.Byte[15];
	Copy.Byte[1]  = Src.Byte[14];
	Copy.Byte[2]  = Src.Byte[13];
	Copy.Byte[3]  = Src.Byte[12];
	Copy.Byte[4]  = Src.Byte[11];
	Copy.Byte[5]  = Src.Byte[10];
	Copy.Byte[6]  = Src.Byte[9];
	Copy.Byte[7]  = Src.Byte[8];
	Copy.Byte[8]  = Src.Byte[7];
	Copy.Byte[9]  = Src.Byte[6];
	Copy.Byte[10] = Src.Byte[5];
	Copy.Byte[11] = Src.Byte[4];
	Copy.Byte[12] = Src.Byte[3];
	Copy.Byte[13] = Src.Byte[2];
	Copy.Byte[14] = Src.Byte[1];
	Copy.Byte[15] = Src.Byte[0];
	
	return Copy.Source;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const Type byteswap32( const Type _Src ) {
	Endian::uEndianMunge<Type> Src;
	Src.Source = _Src;
	
	Endian::uEndianMunge<Type> Copy;
	Copy.Byte[0]  = Src.Byte[31];
	Copy.Byte[1]  = Src.Byte[30];
	Copy.Byte[2]  = Src.Byte[29];
	Copy.Byte[3]  = Src.Byte[28];
	Copy.Byte[4]  = Src.Byte[27];
	Copy.Byte[5]  = Src.Byte[26];
	Copy.Byte[6]  = Src.Byte[25];
	Copy.Byte[7]  = Src.Byte[24];
	Copy.Byte[8]  = Src.Byte[23];
	Copy.Byte[9]  = Src.Byte[22];
	Copy.Byte[10] = Src.Byte[21];
	Copy.Byte[11] = Src.Byte[20];
	Copy.Byte[12] = Src.Byte[19];
	Copy.Byte[13] = Src.Byte[18];
	Copy.Byte[14] = Src.Byte[17];
	Copy.Byte[15] = Src.Byte[16];
	Copy.Byte[16] = Src.Byte[15];
	Copy.Byte[17] = Src.Byte[14];
	Copy.Byte[18] = Src.Byte[13];
	Copy.Byte[19] = Src.Byte[12];
	Copy.Byte[20] = Src.Byte[11];
	Copy.Byte[21] = Src.Byte[10];
	Copy.Byte[22] = Src.Byte[9];
	Copy.Byte[23] = Src.Byte[8];
	Copy.Byte[24] = Src.Byte[7];
	Copy.Byte[25] = Src.Byte[6];
	Copy.Byte[26] = Src.Byte[5];
	Copy.Byte[27] = Src.Byte[4];
	Copy.Byte[28] = Src.Byte[3];
	Copy.Byte[29] = Src.Byte[2];
	Copy.Byte[30] = Src.Byte[1];
	Copy.Byte[31] = Src.Byte[0];
	
	return Copy.Source;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const Type byteswap64( const Type _Src ) {
	Endian::uEndianMunge<Type> Src;
	Src.Source = _Src;
	
	Endian::uEndianMunge<Type> Copy;
	Copy.Byte[0]  = Src.Byte[63];
	Copy.Byte[1]  = Src.Byte[62];
	Copy.Byte[2]  = Src.Byte[61];
	Copy.Byte[3]  = Src.Byte[60];
	Copy.Byte[4]  = Src.Byte[59];
	Copy.Byte[5]  = Src.Byte[58];
	Copy.Byte[6]  = Src.Byte[57];
	Copy.Byte[7]  = Src.Byte[56];
	Copy.Byte[8]  = Src.Byte[55];
	Copy.Byte[9]  = Src.Byte[54];
	Copy.Byte[10] = Src.Byte[53];
	Copy.Byte[11] = Src.Byte[52];
	Copy.Byte[12] = Src.Byte[51];
	Copy.Byte[13] = Src.Byte[50];
	Copy.Byte[14] = Src.Byte[49];
	Copy.Byte[15] = Src.Byte[48];
	Copy.Byte[16] = Src.Byte[47];
	Copy.Byte[17] = Src.Byte[46];
	Copy.Byte[18] = Src.Byte[45];
	Copy.Byte[19] = Src.Byte[44];
	Copy.Byte[20] = Src.Byte[43];
	Copy.Byte[21] = Src.Byte[42];
	Copy.Byte[22] = Src.Byte[41];
	Copy.Byte[23] = Src.Byte[40];
	Copy.Byte[24] = Src.Byte[39];
	Copy.Byte[25] = Src.Byte[38];
	Copy.Byte[26] = Src.Byte[37];
	Copy.Byte[27] = Src.Byte[36];
	Copy.Byte[28] = Src.Byte[35];
	Copy.Byte[29] = Src.Byte[34];
	Copy.Byte[30] = Src.Byte[33];
	Copy.Byte[31] = Src.Byte[32];
	Copy.Byte[32] = Src.Byte[31];
	Copy.Byte[33] = Src.Byte[30];
	Copy.Byte[34] = Src.Byte[29];
	Copy.Byte[35] = Src.Byte[28];
	Copy.Byte[36] = Src.Byte[27];
	Copy.Byte[37] = Src.Byte[26];
	Copy.Byte[38] = Src.Byte[25];
	Copy.Byte[39] = Src.Byte[24];
	Copy.Byte[40] = Src.Byte[23];
	Copy.Byte[41] = Src.Byte[22];
	Copy.Byte[42] = Src.Byte[21];
	Copy.Byte[43] = Src.Byte[20];
	Copy.Byte[44] = Src.Byte[19];
	Copy.Byte[45] = Src.Byte[18];
	Copy.Byte[46] = Src.Byte[17];
	Copy.Byte[47] = Src.Byte[16];
	Copy.Byte[48] = Src.Byte[15];
	Copy.Byte[49] = Src.Byte[14];
	Copy.Byte[50] = Src.Byte[13];
	Copy.Byte[51] = Src.Byte[12];
	Copy.Byte[52] = Src.Byte[11];
	Copy.Byte[53] = Src.Byte[10];
	Copy.Byte[54] = Src.Byte[9];
	Copy.Byte[55] = Src.Byte[8];
	Copy.Byte[56] = Src.Byte[7];
	Copy.Byte[57] = Src.Byte[6];
	Copy.Byte[58] = Src.Byte[5];
	Copy.Byte[59] = Src.Byte[4];
	Copy.Byte[60] = Src.Byte[3];
	Copy.Byte[61] = Src.Byte[2];
	Copy.Byte[62] = Src.Byte[1];
	Copy.Byte[63] = Src.Byte[0];	
	return Copy.Source;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const Type byteswap( const Type Target ) {
	// Return the appropriately swapped data (inlining should eliminate the if's) //
	if ( sizeof( Target ) == 1 )
		return Target;
	else if ( sizeof(Target) == 2 )
		return byteswap2(Target);
	else if ( sizeof(Target) == 3 )
		return byteswap3(Target);
	else if ( sizeof(Target) == 4 )
		return byteswap4(Target);
	else if ( sizeof(Target) == 6 )
		return byteswap6(Target);
	else if ( sizeof(Target) == 8 )
		return byteswap8(Target);
	else if ( sizeof(Target) == 16 )
		return byteswap16(Target);
	else if ( sizeof(Target) == 32 )
		return byteswap32(Target);
	else if ( sizeof(Target) == 64 )
		return byteswap64(Target);
	
	// TODO: Assert on Swap identification failure //
	return Target;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// Process entire blocks of memory full of data that needs swapping //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void byteswap2( const Type* _Src, const size_t Count = 1 ) {
	for ( size_t idx = Count; idx--; ) {
		_Src[ idx ] = byteswap2( _Src[ idx ] );
	}
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void byteswap3( const Type* _Src, const size_t Count = 1 ) {
	for ( size_t idx = Count; idx--; ) {
		_Src[ idx ] = byteswap3( _Src[ idx ] );
	}
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void byteswap4( const Type* _Src, const size_t Count = 1 ) {
	for ( size_t idx = Count; idx--; ) {
		_Src[ idx ] = byteswap4( _Src[ idx ] );
	}
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void byteswap6( const Type* _Src, const size_t Count = 1 ) {
	for ( size_t idx = Count; idx--; ) {
		_Src[ idx ] = byteswap6( _Src[ idx ] );
	}
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void byteswap8( const Type* _Src, const size_t Count = 1 ) {
	for ( size_t idx = Count; idx--; ) {
		_Src[ idx ] = byteswap8( _Src[ idx ] );
	}
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void byteswap16( const Type* _Src, const size_t Count = 1 ) {
	for ( size_t idx = Count; idx--; ) {
		_Src[ idx ] = byteswap16( _Src[ idx ] );
	}
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void byteswap32( const Type* _Src, const size_t Count = 1 ) {
	for ( size_t idx = Count; idx--; ) {
		_Src[ idx ] = byteswap32( _Src[ idx ] );
	}
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void byteswap64( const Type* _Src, const size_t Count = 1 ) {
	for ( size_t idx = Count; idx--; ) {
		_Src[ idx ] = byteswap64( _Src[ idx ] );
	}
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void byteswap( const Type* _Src, const size_t Count = 1 ) {
	// Execute the appropriately data swap (inlining should eliminate the if's) //
	if ( sizeof(Type) == 1 )
		return;
	else if ( sizeof(Type) == 2 )
		byteswap2( _Src, Count );
	else if ( sizeof(Type) == 3 )
		byteswap3( _Src, Count );
	else if ( sizeof(Type) == 4 )
		byteswap4( _Src, Count );
	else if ( sizeof(Type) == 6 )
		byteswap6( _Src, Count );
	else if ( sizeof(Type) == 8 )
		byteswap8( _Src, Count );
	else if ( sizeof(Type) == 16 )
		byteswap16( _Src, Count );
	else if ( sizeof(Type) == 32 )
		byteswap32( _Src, Count );
	else if ( sizeof(Type) == 64 )
		byteswap64( _Src, Count );
	else {
		// TODO: Assert that an invalid byte swap was requested //
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
//}; // namespace Data //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_Endian_Core_H__ //
// - ------------------------------------------------------------------------------------------ - //
