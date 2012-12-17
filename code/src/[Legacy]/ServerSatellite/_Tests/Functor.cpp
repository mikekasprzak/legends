
#include <stdio.h>

// Functor Class //

typedef void (*FVoidPtr)(void*);

template<class Type>
class Functor: public Type {
	static void StaticFunc( Functor* th ) {
		th->operator()( );
	}
public:
	
	inline Functor* GetThis() {
		return this;
	}
	
	inline static FVoidPtr GetFunc() {
		return (FVoidPtr)&StaticFunc;
	}
};

// An implementation //

struct MyFunc {
	inline void operator()( ) {
		printf("Hi 0x%x\n", this);
	}
};

// Usage //

int main( int argc, char* argv[] ) {
	Functor<MyFunc> Func;
	Func();
	
	FVoidPtr FuncPtr = Func.GetFunc();
	FuncPtr( Func.GetThis() );

	return 0;
}

