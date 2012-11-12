// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_UTIL_FUNCTOR_H__
#define __GEL_UTIL_FUNCTOR_H__
// - ------------------------------------------------------------------------------------------ - //
template<class Type>
class Functor: public Type {
	static void StaticFunction( Functor* th ) {
		th->operator()( );
	}
public:
	typedef void (*FVoidPtr)(void*);
	
	inline Functor* GetThis() {
		return this;
	}
	
	inline static FVoidPtr GetFunc() {
		return (FVoidPtr)&StaticFunction;
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_UTIL_FUNCTOR_H__ //
// - ------------------------------------------------------------------------------------------ - //
