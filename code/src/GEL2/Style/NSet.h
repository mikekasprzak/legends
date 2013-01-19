// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL2_STYLE_NSET_H__
#define __GEL2_STYLE_NSET_H__
// - ------------------------------------------------------------------------------------------ - //
// TODO: Test if template overloading (i.e. NSet<t1>, NSet<t1,t2>) works. 
// - ------------------------------------------------------------------------------------------ - //
#define _IF_INDEX_RET_VOIDPTR( _idx, _vs, _var ) \
	if ( (_idx) == (_vs) ) \
		return (void*)_var
// - ------------------------------------------------------------------------------------------ - //
#define _RET_VOIDPTR( _var ) \
	return (void*)_var
// - ------------------------------------------------------------------------------------------ - //
// NSet is a templated type that takes n template arguments, each with its own Type
// - ------------------------------------------------------------------------------------------ - //
template< typename t1 >
class NSet1 {
	typedef NSet1 TypeName;
public:
	t1 a;

	inline NSet1( const t1 _a = t1() ) :
		a(_a)
	{
	}
	
public:
	inline const void* operator[]( const size_t Index ) const {
		_IF_INDEX_RET_VOIDPTR( Index, 0, &a );
		else _RET_VOIDPTR( 0 );
	}
	inline void* operator[]( const size_t Index ) {
		_IF_INDEX_RET_VOIDPTR( Index, 0, &a );
		else _RET_VOIDPTR( 0 );
	}
};
// - ------------------------------------------------------------------------------------------ - //
template< typename t1, typename t2 >
class NSet2 {
	typedef NSet2 TypeName;
public:
	t1 a;
	t2 b;
	
	inline NSet2( const t1 _a = t1(), const t2 _b = t2() ) :
		a(_a),
		b(_b)
	{
	}
	
public:
	inline const void* operator[]( const size_t Index ) const {
		_IF_INDEX_RET_VOIDPTR( Index, 0, &a );
		else _IF_INDEX_RET_VOIDPTR( Index, 1, &b );
		else _RET_VOIDPTR( 0 );
	}
	inline void* operator[]( const size_t Index ) {
		_IF_INDEX_RET_VOIDPTR( Index, 0, &a );
		else _IF_INDEX_RET_VOIDPTR( Index, 1, &b );
		else _RET_VOIDPTR( 0 );
	}
};
// - ------------------------------------------------------------------------------------------ - //
template< typename t1, typename t2, typename t3 >
class NSet3 {
	typedef NSet3 TypeName;
public:
	t1 a;
	t2 b;
	t3 c;

	inline NSet3( const t1 _a = t1(), const t2 _b = t2(), const t3 _c = t3() ) :
		a(_a),
		b(_b),
		c(_c)
	{
	}
	
public:
	inline const void* operator[]( const size_t Index ) const {
		_IF_INDEX_RET_VOIDPTR( Index, 0, &a );
		else _IF_INDEX_RET_VOIDPTR( Index, 1, &b );
		else _IF_INDEX_RET_VOIDPTR( Index, 2, &c );
		else _RET_VOIDPTR( 0 );
	}
	inline void* operator[]( const size_t Index ) {
		_IF_INDEX_RET_VOIDPTR( Index, 0, &a );
		else _IF_INDEX_RET_VOIDPTR( Index, 1, &b );
		else _IF_INDEX_RET_VOIDPTR( Index, 2, &c );
		else _RET_VOIDPTR( 0 );
	}
};
// - ------------------------------------------------------------------------------------------ - //
template< typename t1, typename t2, typename t3, typename t4 >
class NSet4 {
	typedef NSet4 TypeName;
	t1 a;
	t2 b;
	t3 c;
	t4 d;

	inline NSet4( const t1 _a = t1(), const t2 _b = t2(), const t3 _c = t3(), const t4 _d = t4() ) :
		a(_a),
		b(_b),
		c(_c),
		d(_d)
	{
	}
	
public:
	inline const void* operator[]( const size_t Index ) const {
		_IF_INDEX_RET_VOIDPTR( Index, 0, &a );
		else _IF_INDEX_RET_VOIDPTR( Index, 1, &b );
		else _IF_INDEX_RET_VOIDPTR( Index, 2, &c );
		else _IF_INDEX_RET_VOIDPTR( Index, 3, &d );
		else _RET_VOIDPTR( 0 );
	}
	inline void* operator[]( const size_t Index ) {
		_IF_INDEX_RET_VOIDPTR( Index, 0, &a );
		else _IF_INDEX_RET_VOIDPTR( Index, 1, &b );
		else _IF_INDEX_RET_VOIDPTR( Index, 2, &c );
		else _IF_INDEX_RET_VOIDPTR( Index, 3, &d );
		else _RET_VOIDPTR( 0 );
	}
};
// - ------------------------------------------------------------------------------------------ - //
template< typename t1, typename t2, typename t3, typename t4, typename t5 >
class NSet5 {
	typedef NSet5 TypeName;
public:
	t1 a;
	t2 b;
	t3 c;
	t4 d;
	t5 e;

	inline NSet5( const t1 _a = t1(), const t2 _b = t2(), const t3 _c = t3(), const t4 _d = t4(), const t5 _e = t5() ) :
		a(_a),
		b(_b),
		c(_c),
		d(_d),
		e(_e)
	{
	}
	
public:
	inline const void* operator[]( const size_t Index ) const {
		_IF_INDEX_RET_VOIDPTR( Index, 0, &a );
		else _IF_INDEX_RET_VOIDPTR( Index, 1, &b );
		else _IF_INDEX_RET_VOIDPTR( Index, 2, &c );
		else _IF_INDEX_RET_VOIDPTR( Index, 3, &d );
		else _IF_INDEX_RET_VOIDPTR( Index, 4, &e );
		else _RET_VOIDPTR( 0 );
	}
	inline void* operator[]( const size_t Index ) {
		_IF_INDEX_RET_VOIDPTR( Index, 0, &a );
		else _IF_INDEX_RET_VOIDPTR( Index, 1, &b );
		else _IF_INDEX_RET_VOIDPTR( Index, 2, &c );
		else _IF_INDEX_RET_VOIDPTR( Index, 3, &d );
		else _IF_INDEX_RET_VOIDPTR( Index, 4, &e );
		else _RET_VOIDPTR( 0 );
	}
};
// - ------------------------------------------------------------------------------------------ - //
#undef _IF_INDEX_RET_VOIDPTR
#undef _RET_VOIDPTR
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL2_STYLE_NSET_H__ //
// - ------------------------------------------------------------------------------------------ - //
