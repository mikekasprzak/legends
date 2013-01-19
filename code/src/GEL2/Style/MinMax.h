// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL2_STYLE_MINMAX_H__
#define __GEL2_STYLE_MINMAX_H__
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
inline const T Min( const T a ) {
	return a;
};
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
inline const T Min( const T a, const T b ) {
	if ( a < b )
		return a;
	else
		return b;
};
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
inline const T Min( const T a, const T b, const T c ) {
	T Low = a;

	if ( b < Low ) Low = b;
	if ( c < Low ) Low = c;
		
	return Low;
};
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
inline const T Min( const T a, const T b, const T c, const T d ) {
	T Low = a;

	if ( b < Low ) Low = b;
	if ( c < Low ) Low = c;
	if ( d < Low ) Low = d;
		
	return Low;
};
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
inline const T Min( const T a, const T b, const T c, const T d, const T e ) {
	T Low = a;

	if ( b < Low ) Low = b;
	if ( c < Low ) Low = c;
	if ( d < Low ) Low = d;
	if ( e < Low ) Low = e;
		
	return Low;
};
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
inline const T Min( const T a, const T b, const T c, const T d, const T e, const T f ) {
	T Low = a;

	if ( b < Low ) Low = b;
	if ( c < Low ) Low = c;
	if ( d < Low ) Low = d;
	if ( e < Low ) Low = e;
	if ( f < Low ) Low = f;
		
	return Low;
};
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
inline const T Min( const T a, const T b, const T c, const T d, const T e, const T f, const T g ) {
	T Low = a;

	if ( b < Low ) Low = b;
	if ( c < Low ) Low = c;
	if ( d < Low ) Low = d;
	if ( e < Low ) Low = e;
	if ( f < Low ) Low = f;
	if ( g < Low ) Low = g;
		
	return Low;
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< typename T >
inline const T Max( const T a ) {
	return a;
};
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
inline const T Max( const T a, const T b ) {
	if ( a > b )
		return a;
	else
		return b;
};
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
inline const T Max( const T a, const T b, const T c ) {
	T High = a;

	if ( b > High ) High = b;
	if ( c > High ) High = c;
		
	return High;
};
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
inline const T Max( const T a, const T b, const T c, const T d ) {
	T High = a;

	if ( b > High ) High = b;
	if ( c > High ) High = c;
	if ( d > High ) High = d;
		
	return High;
};
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
inline const T Max( const T a, const T b, const T c, const T d, const T e ) {
	T High = a;

	if ( b > High ) High = b;
	if ( c > High ) High = c;
	if ( d > High ) High = d;
	if ( e > High ) High = e;
		
	return High;
};
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
inline const T Max( const T a, const T b, const T c, const T d, const T e, const T f ) {
	T High = a;

	if ( b > High ) High = b;
	if ( c > High ) High = c;
	if ( d > High ) High = d;
	if ( e > High ) High = e;
	if ( f > High ) High = f;
		
	return High;
};
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
inline const T Max( const T a, const T b, const T c, const T d, const T e, const T f, const T g ) {
	T High = a;

	if ( b > High ) High = b;
	if ( c > High ) High = c;
	if ( d > High ) High = d;
	if ( e > High ) High = e;
	if ( f > High ) High = f;
	if ( g > High ) High = g;
		
	return High;
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL2_STYLE_MINMAX_H__ //
// - ------------------------------------------------------------------------------------------ - //
