#include <stdio.h>

//class TheClass {
//public:
//	void MemberFunc() {
//		printf( "My This Addr: 0x%x\n", this );
//	}
//
//	typedef TheClass thisclass;
//	
//	static void stMemberFunc( thisclass* th ) {
//	static void stMemberFunc( TheClass* th ) {
//		th->MemberFunc();
//	}
//	
//	inline void* GetThis() {
//		return (void*)this;
//	}
//};

#define DEFINE_thistype( __name ) \
	typedef __name thistype

#define DEFINE_GetThis() \
	inline thistype* GetThis() { \
		return this; \
	}

#define DEFINE_STATIC_MEMBER_FUNC( __name ) \
	static void st ## __name( thistype* th ) { \
		th->__name(); \
	}


class TheClass {
public:
	DEFINE_thistype( TheClass );
	DEFINE_GetThis();

	void MemberFunc() {
		printf( "My This Addr: 0x%x\n", this );
	}	
	DEFINE_STATIC_MEMBER_FUNC( MemberFunc );
};


typedef void (*FVoidPtr)(void*);

struct TheAction {
	void Action() {
		printf( "My This Addr: 0x%x\n", this );		
	}
};

template<class t>
class SMF: public t {
public:
	static void stAction( t* th ) {
		th->Action();
	}
	
	inline SMF* GetThis() {
		return this;
	}
	
	inline static FVoidPtr GetAction() {
		return (FVoidPtr)&stAction;
	}
};


int main( int argc, char* argv[] ) {
	TheClass Instance;
	Instance.MemberFunc();
	
	FVoidPtr Func = (FVoidPtr)&TheClass::stMemberFunc;
	
	Func( Instance.GetThis() );
	
	SMF<TheAction> MyAction;
	MyAction.Action();
	
	FVoidPtr Func2 = MyAction.GetAction();
	Func2( MyAction.GetThis() );

	return 0;
}
