// - ------------------------------------------------------------------------------------------ - //
// Endian Accessory - Endian functions that rely on the prior BE or LE header //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_Endian_Accessory_H__
#define __Library_Data_Endian_Accessory_H__
// - ------------------------------------------------------------------------------------------ - //
//namespace Data {
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const Type beswap( const Type Target ) {
	// Return the appropriately swapped data (inlining should eliminate the if's) //
	if ( sizeof( Target ) == 1 )
		return Target;
	else if ( sizeof(Target) == 2 )
		return beswap2(Target);
	else if ( sizeof(Target) == 3 )
		return beswap3(Target);
	else if ( sizeof(Target) == 4 )
		return beswap4(Target);
	else if ( sizeof(Target) == 6 )
		return beswap6(Target);
	else if ( sizeof(Target) == 8 )
		return beswap8(Target);
	else if ( sizeof(Target) == 16 )
		return beswap16(Target);
	else if ( sizeof(Target) == 32 )
		return beswap32(Target);
	else if ( sizeof(Target) == 64 )
		return beswap64(Target);
	
	// TODO: Assert on Swap identification failure //
	return Target;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const Type leswap( const Type Target ) {
	// Return the appropriately swapped data (inlining should eliminate the if's) //
	if ( sizeof( Target ) == 1 )
		return Target;
	else if ( sizeof(Target) == 2 )
		return leswap2(Target);
	else if ( sizeof(Target) == 3 )
		return leswap3(Target);
	else if ( sizeof(Target) == 4 )
		return leswap4(Target);
	else if ( sizeof(Target) == 6 )
		return leswap6(Target);
	else if ( sizeof(Target) == 8 )
		return leswap8(Target);
	else if ( sizeof(Target) == 16 )
		return leswap16(Target);
	else if ( sizeof(Target) == 32 )
		return leswap32(Target);
	else if ( sizeof(Target) == 64 )
		return leswap64(Target);
	
	// TODO: Assert on Swap identification failure //
	return Target;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
//}; // namespace Data //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_Endian_Accessory_H__ //
// - ------------------------------------------------------------------------------------------ - //
