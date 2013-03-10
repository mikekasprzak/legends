// - ------------------------------------------------------------------------------------------ - //
#ifndef __PLAYMORE_TAG_H__
#define __PLAYMORE_TAG_H__
// - ------------------------------------------------------------------------------------------ - //
// Create using the new methods. Constructor is private, so this is the only way. //
//   cTag::new_Tag( 14 )		/* autodetect */
//   cTag::new_Float( 10.0f );	/* explicit type */
// Then delete when done //
//   cTag::delete_Tag( MyTag );
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
private: // - Members -------------------------------------------------------------------------- - //
	eTagType	Type;				// 32bit -- The Tag Type //
	st32		Size;				// 32bit -- Size in Bytes //
	
	char Data[0];					// TBD   -- The Data //

private: // - Constructors and Destructors ---------------------------------------------------- - //
	cTag() :
		Type( TT_NULL ),
		Size( 0 )
	{
	}

	cTag( const eTagType _Type, const st32 _Size ) :
		Type( _Type ),
		Size( _Size )
	{
	}

public: // - Methods -------------------------------------------------------------------------- - //
	// Type Checking -------------------------------------------------------------------------- - //
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
	
	// Data Retrieval ------------------------------------------------------------------------- - //
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
		return (char*)Data;
	}
	
	// Data Access ---------------------------------------------------------------------------- - //
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
	
	// Create --------------------------------------------------------------------------------- - //
	inline static cTag* new_Int( const int Value ) {
		char* Ptr = new char[ sizeof(cTag) + sizeof(int) ];
		cTag* Tag = new(Ptr) cTag( TT_INT, sizeof(int) );
		*(Tag->GetIntPtr()) = Value;
		return Tag;
	}
	inline static cTag* new_Float( const float Value ) {
		char* Ptr = new char[ sizeof(cTag) + sizeof(float) ];
		cTag* Tag = new(Ptr) cTag( TT_FLOAT, sizeof(float) );
		*(Tag->GetFloatPtr()) = Value;
		return Tag;
	}
	inline static cTag* new_UID( const cUID Value ) {
		char* Ptr = new char[ sizeof(cTag) + sizeof(cUID) ];
		cTag* Tag = new(Ptr) cTag( TT_UID, sizeof(cUID) );
		*(Tag->GetUIDPtr()) = Value;
		return Tag;
	}
	inline static cTag* new_String( const char* Value ) {
		st32 Length = strlen( Value );
		Log("**");
		char* Ptr = new char[ sizeof(cTag) + (Length + 1) ];
		Log("**");
		cTag* Tag = new(Ptr) cTag( TT_STRING, Length + 1 );
		Log("**");
		memcpy( Tag->GetStringPtr(), Value, Length + 1 );
		Log("**");
		return Tag;
	}
	
	// Autodetect tag type based on argument //
	inline static cTag* new_Tag( const int Value ) {
		return new_Int( Value );
	}
	inline static cTag* new_Tag( const float Value ) {
		return new_Float( Value );
	}
	inline static cTag* new_Tag( const double Value ) {
		// For automatic type conversion (comment out function for strict 1.0f style syntax only) //
		return new_Float( Value );
	}
	inline static cTag* new_Tag( const cUID Value ) {
		return new_UID( Value );
	}
	inline static cTag* new_Tag( const char* Value ) {
		return new_String( Value );
	}
	
	
	// Destroy -------------------------------------------------------------------------------- - //
	inline static void delete_Tag( cTag* Tag ) {
		Tag->~cTag();
		delete [] Tag;
	}

	// Nice ----------------------------------------------------------------------------------- - //
	// WARNING: A limit of 1 ToString call can be made at a time, otherwise returned values may be bad //
	inline const char* ToString() {
		static char Text[2048];
		if ( Type == TT_STRING ) {
			return GetString();
		}
		else if ( Type == TT_INT ) {
			sprintf( Text, "%i", GetInt() );
			return Text;
		}
		else if ( Type == TT_FLOAT ) {
			sprintf( Text, "%f", GetFloat() );
			return Text;
		}
		else if ( Type == TT_UID ) {
			sprintf( Text, "%i", GetUID().Get() );
			return Text;
		}
		else {
			return "Unknown Tag";
		}
	}
	
	inline const char* TypeToString() {
		if ( Type == TT_INT ) {
			return "Int";
		}
		else if ( Type == TT_FLOAT ) {
			return "Float";
		}
		else if ( Type == TT_UID ) {
			return "UID";
		}
		else if ( Type == TT_STRING ) {
			return "String";
		}
		else {
			return "Unknown";
		}		
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PLAYMORE_TAG_H__ //
// - ------------------------------------------------------------------------------------------ - //
