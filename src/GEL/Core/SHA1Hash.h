// - ------------------------------------------------------------------------------------------ - //
// SHA1Hash - 
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_SHA1Hash_H__
#define __Library_Data_SHA1Hash_H__
// - ------------------------------------------------------------------------------------------ - //
#include <External/SHA1/sha1.h>
// - ------------------------------------------------------------------------------------------ - //
struct SHA1Hash {
	char Hash[SHA1_DIGEST_SIZE];
	
	inline const bool operator == ( const SHA1Hash& Vs ) const {
		return compare_Data( Hash, Vs.Hash, SHA1_DIGEST_SIZE ) == 0;
	}
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline const bool equal_SHA1Hash( const SHA1Hash& a, const SHA1Hash& b ) {
	return compare_Data( a.Hash, b.Hash, SHA1_DIGEST_SIZE ) == 0;
} 
// - ------------------------------------------------------------------------------------------ - //
inline const bool equal_SHA1Hash( const SHA1Hash* a, const SHA1Hash* b ) {
	return compare_Data( a->Hash, b->Hash, SHA1_DIGEST_SIZE ) == 0;
} 
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_SHA1Hash_H__ //
// - ------------------------------------------------------------------------------------------ - //