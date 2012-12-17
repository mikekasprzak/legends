#include <stdio.h>

typedef void (*FVoidPtr)(void*);

template<class t>
class cAction: public t {
	bool Done;
public:
	cAction() :
		Done( false )
	{
	}
	
	static void stAction( cAction* th ) {
		th->Action();
		th->Done = true;
	}
	
	inline cAction* GetThis() {
		return this;
	}
	
	inline static FVoidPtr GetAction() {
		return (FVoidPtr)&stAction;
	}

	inline const bool IsDone() const {
		return Done;
	}
};


//class MyAction {
//	bool Ready;
//public:
//	MyAction() :
//		Ready( false )
//	{
//	}
//	
//	void Action() {
//		printf( "My This Addr: 0x%x\n", this );		
//		Ready = true;
//	}
//
//	inline const bool IsReady() const {
//		return Ready;
//	}
//};


#include "TinyThread/tinythread.h"

using namespace tthread;

int main( int argc, char* argv[] ) {	
	struct MyAction {
		void Action() {
			printf( "My This Addr Yo: 0x%x\n", this );
		}
	};
	
	cAction<MyAction> Me;
	Me.Action();
	
	FVoidPtr Func2 = Me.GetAction();
	Func2( Me.GetThis() );
	
	thread t( Me.GetAction(), Me.GetThis() );

	t.join(); // Wait until finished //

	return 0;
}
