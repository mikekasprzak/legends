// - ------------------------------------------------------------------------------------------ - //
#ifndef __PLAYMORE_KEYSTORE_H__
#define __PLAYMORE_KEYSTORE_H__
// - ------------------------------------------------------------------------------------------ - //
#include <map>
#include <string>

#include "Flex.h"
// - ------------------------------------------------------------------------------------------ - //
class cKeyStore {
public: // - Class Helpers -------------------------------------------------------------------- - //
	typedef cKeyStore thistype;
	inline void* GetThis() { return this; }
public: // - Members -------------------------------------------------------------------------- - //
	std::map<std::string,flex> Data;		// Key/Value Pairs //
public: // - Constructors and Destructors ----------------------------------------------------- - //
	cKeyStore()
	{
	}

public: // - Methods -------------------------------------------------------------------------- - //
	inline flex& operator() ( const char* Name ) {
		auto Itr = Data.find( Name );
		if ( Itr != Data.end() ) {
			return Itr->second;
		}
		else {
			Log( "! ERROR: Invalid Key \"%s\" in KeyStore", Name );
			static flex Dummy;
			return Dummy;
		}		
	}
	inline flex& operator() ( const std::string Name ) {
		return operator()( Name.c_str() );
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PLAYMORE_KEYSTORE_H__ //
// - ------------------------------------------------------------------------------------------ - //