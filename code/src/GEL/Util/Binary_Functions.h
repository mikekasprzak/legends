// - ------------------------------------------------------------------------------------------ - //
// Binary //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_UTIL_Binary_Functions_H__
#define __GEL_UTIL_Binary_Functions_H__
// - ------------------------------------------------------------------------------------------ - //
// TODO: Add functions for working with bitmasks.  Individual bits operations go in bits.h //
// - ------------------------------------------------------------------------------------------ - //
template< class tType >
inline tType omit_BitMask( const tType Input, const tType Mask ) {
	return Input & (~Mask);
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_UTIL_Binary_Functions_H__ //
// - ------------------------------------------------------------------------------------------ - //