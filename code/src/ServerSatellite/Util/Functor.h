// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_UTIL_FUNCTOR_H__
#define __GEL_UTIL_FUNCTOR_H__
// - ------------------------------------------------------------------------------------------ - //
#include <TinyThread/tinythread.h>
// - ------------------------------------------------------------------------------------------ - //
template<class Type>
class Functor: public Type {
protected:
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

public: // Threading Extensions. Need to manage the thread pointers yourself. //
	// These exist because the Move operator is not available. //
	inline tthread::thread* new_thread() {
		return new tthread::thread( GetFunc(), this );
	}
	
	inline void delete_thread( tthread::thread* Me ) const {
		delete Me;
	}
};
// - ------------------------------------------------------------------------------------------ - //
// A variation that has an internal Thread and starts automatically //
// - ------------------------------------------------------------------------------------------ - //
template<class Type>
class TFunctor: public Functor<Type> {
protected:
	tthread::thread Thread;
public:
	inline TFunctor() :
		Thread( Functor<Type>::GetFunc(), this )
	{
	}
	
	inline tthread::thread& GetThread() {
		return Thread;
	}
	
	// Wait for Thread to finish //
	inline void join() {
		Thread.join();
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_UTIL_FUNCTOR_H__ //
// - ------------------------------------------------------------------------------------------ - //
