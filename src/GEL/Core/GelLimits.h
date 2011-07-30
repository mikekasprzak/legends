// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_Core_GelLimits_H__
#define __GEL_Core_GelLimits_H__
// - ------------------------------------------------------------------------------------------ - //
#include <limits.h>
// - ------------------------------------------------------------------------------------------ - //
template<class tType>
inline tType MaxValue();
// - ------------------------------------------------------------------------------------------ - //
template<>
inline int MaxValue<int>() {
	return INT_MAX;
}
// - ------------------------------------------------------------------------------------------ - //
template<>
inline unsigned int MaxValue<unsigned int>() {
	return UINT_MAX;
}
// - ------------------------------------------------------------------------------------------ - //
template<>
inline short MaxValue<short>() {
	return SHRT_MAX;
}
// - ------------------------------------------------------------------------------------------ - //
template<>
inline unsigned short MaxValue<unsigned short>() {
	return USHRT_MAX;
}
// - ------------------------------------------------------------------------------------------ - //
template<>
inline char MaxValue<char>() {
	return CHAR_MAX;
}
// - ------------------------------------------------------------------------------------------ - //
template<>
inline unsigned char MaxValue<unsigned char>() {
	return UCHAR_MAX;
}
// - ------------------------------------------------------------------------------------------ - //
template<>
inline const int MaxValue<const int>() {
	return INT_MAX;
}
// - ------------------------------------------------------------------------------------------ - //
template<>
inline const unsigned int MaxValue<const unsigned int>() {
	return UINT_MAX;
}
// - ------------------------------------------------------------------------------------------ - //
template<>
inline const short MaxValue<const short>() {
	return SHRT_MAX;
}
// - ------------------------------------------------------------------------------------------ - //
template<>
inline const unsigned short MaxValue<const unsigned short>() {
	return USHRT_MAX;
}
// - ------------------------------------------------------------------------------------------ - //
template<>
inline const char MaxValue<const char>() {
	return CHAR_MAX;
}
// - ------------------------------------------------------------------------------------------ - //
template<>
inline const unsigned char MaxValue<const unsigned char>() {
	return UCHAR_MAX;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template<class tType>
inline tType MinValue();
// - ------------------------------------------------------------------------------------------ - //
template<>
inline int MinValue<int>() {
	return INT_MIN;
}
// - ------------------------------------------------------------------------------------------ - //
template<>
inline unsigned int MinValue<unsigned int>() {
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
template<>
inline short MinValue<short>() {
	return SHRT_MIN;
}
// - ------------------------------------------------------------------------------------------ - //
template<>
inline unsigned short MinValue<unsigned short>() {
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
template<>
inline char MinValue<char>() {
	return CHAR_MIN;
}
// - ------------------------------------------------------------------------------------------ - //
template<>
inline unsigned char MinValue<unsigned char>() {
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
template<>
inline const int MinValue<const int>() {
	return INT_MIN;
}
// - ------------------------------------------------------------------------------------------ - //
template<>
inline const unsigned int MinValue<const unsigned int>() {
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
template<>
inline const short MinValue<const short>() {
	return SHRT_MIN;
}
// - ------------------------------------------------------------------------------------------ - //
template<>
inline const unsigned short MinValue<const unsigned short>() {
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
template<>
inline const char MinValue<const char>() {
	return CHAR_MIN;
}
// - ------------------------------------------------------------------------------------------ - //
template<>
inline const unsigned char MinValue<const unsigned char>() {
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class tType >
inline const size_t SizeOf() {
	return sizeof(tType);
}
// - ------------------------------------------------------------------------------------------ - //
template< class tType >
inline const size_t Bits() {
	return sizeof(tType) << 3;
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_Core_GelLimits_H__ //
// - ------------------------------------------------------------------------------------------ - //
