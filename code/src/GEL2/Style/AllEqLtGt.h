// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL2_STYLE_ALLEQLTGT_H__
#define __GEL2_STYLE_ALLEQLTGT_H__
// - ------------------------------------------------------------------------------------------ - //
// Operations AllEq, AllNeq, AllLt, AllGt, AllLte, AllGte that compare one value vs many //
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
		return Vs _op b; \
	return false; \
}; \
\
template< typename T > \
inline const bool _op_name( const T Vs, const T a, const T b, const T c ) { \
	if ( Vs _op a ) \
		if ( Vs _op b ) \
			return Vs _op c; \
	return false; \
}; \
\
template< typename T > \
inline const bool _op_name( const T Vs, const T a, const T b, const T c, const T d ) { \
	if ( Vs _op a )  \
		if ( Vs _op b )  \
			if ( Vs _op c )  \
				return Vs _op d; \
	return false; \
}; \
\
template< typename T > \
inline const bool _op_name( const T Vs, const T a, const T b, const T c, const T d, const T e ) { \
	if ( Vs _op a )  \
		if ( Vs _op b )  \
			if ( Vs _op c )  \
				if ( Vs _op d )  \
					return Vs _op e; \
	return false; \
}; \
\
template< typename T > \
inline const bool _op_name( const T Vs, const T a, const T b, const T c, const T d, const T e, const T f ) { \
	if ( Vs _op a )  \
		if ( Vs _op b )  \
			if ( Vs _op c )  \
				if ( Vs _op d )  \
					if ( Vs _op e )  \
						return Vs _op f; \
	return false; \
}; \
\
template< typename T > \
inline const bool _op_name( const T Vs, const T a, const T b, const T c, const T d, const T e, const T f, const T g ) { \
	if ( Vs _op a )  \
		if ( Vs _op b )  \
			if ( Vs _op c )  \
				if ( Vs _op d )  \
					if ( Vs _op e )  \
						if ( Vs _op f )  \
							return Vs _op g; \
	return false; \
};
// - ------------------------------------------------------------------------------------------ - //
_OP_RET_BOOL( AllEq, == );
_OP_RET_BOOL( AllNEq, != );
_OP_RET_BOOL( AllLt, < );
_OP_RET_BOOL( AllGt, > );
_OP_RET_BOOL( AllLte, <= );
_OP_RET_BOOL( AllGte, >= );
// - ------------------------------------------------------------------------------------------ - //
#undef _OP_RET_BOOL
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL2_STYLE_ALLEQLTGT_H__ //
// - ------------------------------------------------------------------------------------------ - //
