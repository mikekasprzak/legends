// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL2_STYLE_EQLTGT_H__
#define __GEL2_STYLE_EQLTGT_H__
// - ------------------------------------------------------------------------------------------ - //
// Operations Eq, Neq, Lt, Gt, Lte, Gte that compare one value vs many //
// - ------------------------------------------------------------------------------------------ - //
#define _OP_RET_BOOL( _op_name, _op ) \
\
template< typename T > \
inline const bool _op_name( const T Vs, const T a ) { \
	return Vs _op a; \
}; \
\
template< typename T > \
inline const bool _op_name( const T Vs, const T a, const T b ) { \
	if ( Vs _op a ) \
		return true; \
	else \
		return Vs _op b; \
}; \
\
template< typename T > \
inline const bool _op_name( const T Vs, const T a, const T b, const T c ) { \
	if ( Vs _op a ) \
		return true; \
	else if ( Vs _op b ) \
		return true; \
	else \
		return Vs _op c; \
}; \
\
template< typename T > \
inline const bool _op_name( const T Vs, const T a, const T b, const T c, const T d ) { \
	if ( Vs _op a )  \
		return true; \
	else if ( Vs _op b )  \
		return true; \
	else if ( Vs _op c )  \
		return true; \
	else  \
		return Vs _op d; \
}; \
\
template< typename T > \
inline const bool _op_name( const T Vs, const T a, const T b, const T c, const T d, const T e ) { \
	if ( Vs _op a )  \
		return true; \
	else if ( Vs _op b )  \
		return true; \
	else if ( Vs _op c )  \
		return true; \
	else if ( Vs _op d )  \
		return true; \
	else  \
		return Vs _op e; \
}; \
\
template< typename T > \
inline const bool _op_name( const T Vs, const T a, const T b, const T c, const T d, const T e, const T f ) { \
	if ( Vs _op a )  \
		return true; \
	else if ( Vs _op b )  \
		return true; \
	else if ( Vs _op c )  \
		return true; \
	else if ( Vs _op d )  \
		return true; \
	else if ( Vs _op e )  \
		return true; \
	else  \
		return Vs _op f; \
}; \
\
template< typename T > \
inline const bool _op_name( const T Vs, const T a, const T b, const T c, const T d, const T e, const T f, const T g ) { \
	if ( Vs _op a )  \
		return true; \
	else if ( Vs _op b )  \
		return true; \
	else if ( Vs _op c )  \
		return true; \
	else if ( Vs _op d )  \
		return true; \
	else if ( Vs _op e )  \
		return true; \
	else if ( Vs _op f )  \
		return true; \
	else  \
		return Vs _op g; \
};
// - ------------------------------------------------------------------------------------------ - //
_OP_RET_BOOL( Eq, == );
_OP_RET_BOOL( NEq, != );
_OP_RET_BOOL( Lt, < );
_OP_RET_BOOL( Gt, > );
_OP_RET_BOOL( Lte, <= );
_OP_RET_BOOL( Gte, >= );
// - ------------------------------------------------------------------------------------------ - //
#undef _OP_RET_BOOL
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL2_STYLE_EQLTGT_H__ //
// - ------------------------------------------------------------------------------------------ - //
