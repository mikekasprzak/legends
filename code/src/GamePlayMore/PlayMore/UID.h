// - ------------------------------------------------------------------------------------------ - //
#ifndef __PLAYMORE_UID_H__
#define __PLAYMORE_UID_H__
// - ------------------------------------------------------------------------------------------ - //
class cUID {
public: // - Class Helpers -------------------------------------------------------------------- - //
	typedef cUID thistype;
	inline void* GetThis() { return this; }
private: // - Members ------------------------------------------------------------------------- - //
	typedef unsigned int UIDType;
	static UIDType CurrentUID;

	UIDType Data;
public: // - Constructors and Destructors ----------------------------------------------------- - //
	cUID() :
		Data( Generate().Get() )
	{
	}

	cUID( const UIDType _Data ) :
		Data( _Data )
	{
	}

public: // - Static Methods ------------------------------------------------------------------- - //
	static void Init( const UIDType InitValue = 1 ) {
		CurrentUID = InitValue;
	}
	static const cUID Generate() {
		return cUID(CurrentUID++);
	}

public: // - Methods -------------------------------------------------------------------------- - //
	const unsigned int Get() const {
		return Data;
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PLAYMORE_UID_H__ //
// - ------------------------------------------------------------------------------------------ - //
