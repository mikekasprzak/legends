// - ------------------------------------------------------------------------------------------ - //
#ifndef __PLAYMORE_TAG_H__
#define __PLAYMORE_TAG_H__
// - ------------------------------------------------------------------------------------------ - //
#include "UID.h"
// - ------------------------------------------------------------------------------------------ - //
enum eTagType {
	TT_NULL = 0,

	TT_INT,
	TT_FLOAT,
	TT_UID,
	TT_STRING
};
// - ------------------------------------------------------------------------------------------ - //
class cTag {
public: // - Class Helpers -------------------------------------------------------------------- - //
	typedef cTag thistype;
	inline void* GetThis() { return this; }
public: // - Members -------------------------------------------------------------------------- - //
	st32		Size;				// 32bit -- Size in Bytes //
	eTagType	Type;				// 32bit -- The Tag Type //
	
	char Data[0];					// TBD   -- The Data //

private: // - Constructors and Destructors ---------------------------------------------------- - //
	cTag() :
		Size( 0 ),
		Type( TT_NULL )
	{
	}

	cTag( const eTagType _Type, const st32 _Size ) :
		Size( _Size ),
		Type( _Type )
	{
	}

public: // - Methods -------------------------------------------------------------------------- - //
	// Type Checking //
	inline const bool IsInt() const {
		return Type == TT_INT;
	}
	inline const bool IsFloat() const {
		return Type == TT_FLOAT;
	}
	inline const bool IsUID() const {
		return Type == TT_UID;
	}
	inline const bool IsString() const {
		return Type == TT_STRING;
	}
	
	// Data Retrieval //
	inline const int GetInt() const {
		return *((int*)Data);
	}
	inline const float GetFloat() const {
		return *((float*)Data);
	}
	inline const cUID GetUID() const {
		return *((cUID*)Data);
	}
	inline const char* GetString() const {
		return *((char**)Data);
	}
	
	// Data Access //
	inline int* GetIntPtr() {
		return (int*)Data;
	}
	inline float* GetFloatPtr() {
		return (float*)Data;
	}
	inline cUID* GetUIDPtr() {
		return (cUID*)Data;
	}
	inline char** GetStringPtr() {
		return (char**)Data;
	}
	
	// Create //
	inline static cTag* newInt( const int Value ) {
		char* Ptr = new char[ sizeof(cTag) + sizeof(int) ];
		cTag* Tag = new(Ptr) cTag( TT_INT, sizeof(int) );
		*(Tag->GetIntPtr()) = Value;
		return Tag;
	}
	inline static cTag* newFloat( const float Value ) {
		char* Ptr = new char[ sizeof(cTag) + sizeof(float) ];
		cTag* Tag = new(Ptr) cTag( TT_FLOAT, sizeof(float) );
		*(Tag->GetFloatPtr()) = Value;
		return Tag;
	}
	inline static cTag* newUID( const cUID Value ) {
		char* Ptr = new char[ sizeof(cTag) + sizeof(cUID) ];
		cTag* Tag = new(Ptr) cTag( TT_UID, sizeof(cUID) );
		*(Tag->GetUIDPtr()) = Value;
		return Tag;
	}
	inline static cTag* newString( const char* Value ) {
		st Length = strlen( Value );
		char* Ptr = new char[ sizeof(cTag) + (Length + 1) ];
		cTag* Tag = new(Ptr) cTag( TT_STRING, Length + 1 );
		memcpy( Tag->Data, Value, Length+1 );
		return Tag;
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PLAYMORE_TAG_H__ //
// - ------------------------------------------------------------------------------------------ - //
