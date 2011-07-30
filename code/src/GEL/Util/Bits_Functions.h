// - ------------------------------------------------------------------------------------------ - //
// Bits //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_UTIL_Bits_Functions_H__
#define __GEL_UTIL_Bits_Functions_H__
// - ------------------------------------------------------------------------------------------ - //
// TODO: Add various functions for getting information about individual bits //
//    Handle "bit-mask" operations in Binary.h //
// - ------------------------------------------------------------------------------------------ - //
#define bitSet(_var, _bit)				_var = (_var) | (1<<(_bit))
#define bitReset(_var, _bit)			_var = (_var) & ~(1<<(_bit))
#define bitGet(_var, _bit)				((_var) & (1<<(_bit)))
// - ------------------------------------------------------------------------------------------ - //
template< class tType >
inline unsigned int count_Bits( const tType Value ) {
	unsigned int Count = 0;
	
	for ( unsigned int idx = (sizeof(tType)<<3)-1; idx--; ) {
		if ( (1<<idx) & Value )
			Count++;
	}
	
	return Count;
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_UTIL_Bits_Functions_H__ //
// - ------------------------------------------------------------------------------------------ - //
