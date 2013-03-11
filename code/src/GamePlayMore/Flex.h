// - ------------------------------------------------------------------------------------------ - //
#ifndef __PLAYMORE_FLEX_H__
#define __PLAYMORE_FLEX_H__
// - ------------------------------------------------------------------------------------------ - //
// "flex" is the notable type here. It can be assigned Integers, Floats, Strings and UIDs.
//   Output can be requested with the appropriate GetInt, GetFloat, GetUID, GetString functions.
//   Explicit conversions can be done with ToInt, ToFloat, ToBool, and ToString.
// - ------------------------------------------------------------------------------------------ - //
#include "UID.h"
// - ------------------------------------------------------------------------------------------ - //
enum eFlexType {
	FT_NULL = 0,

	FT_INT,
	FT_FLOAT,
	FT_BOOL,
	FT_UID,
	FT_STRING
};
// - ------------------------------------------------------------------------------------------ - //
// For Internal use Only:
// - ------------------------------------------------------------------------------------------ - //
// Create using the new methods. Constructor is private, so this is the only way. //
//   cRawFlex::new_Flex( 14 )		/* autodetect */
//   cRawFlex::new_Float( 10.0f );	/* explicit type */
// Then delete when done //
//   cRawFlex::delete_Flex( MyFlex );
// - ------------------------------------------------------------------------------------------ - //
class cRawFlex {
public: // - Class Helpers -------------------------------------------------------------------- - //
	typedef cRawFlex thistype;
	inline void* GetThis() { return this; }
private: // - Members -------------------------------------------------------------------------- - //
	eFlexType	Type;				// 32bit -- The Flex Type //
	st32		Size;				// 32bit -- Size in Bytes //
	
	char Data[0];					// TBD   -- The Data //
	
	friend class flex;

private: // - Constructors and Destructors ---------------------------------------------------- - //
	cRawFlex() :
		Type( FT_NULL ),
		Size( 0 )
	{
	}

	cRawFlex( const eFlexType _Type, const st32 _Size ) :
		Type( _Type ),
		Size( _Size )
	{
	}

public: // - Methods -------------------------------------------------------------------------- - //
	// Type Checking -------------------------------------------------------------------------- - //
	inline const bool IsNull() const {
		return Type == FT_NULL;
	}
	inline const bool IsInt() const {
		return Type == FT_INT;
	}
	inline const bool IsFloat() const {
		return Type == FT_FLOAT;
	}
	inline const bool IsBool() const {
		return Type == FT_BOOL;
	}
	inline const bool IsUID() const {
		return Type == FT_UID;
	}
	inline const bool IsString() const {
		return Type == FT_STRING;
	}
	
	// Data Retrieval ------------------------------------------------------------------------- - //
	inline const int GetInt() const {
		return *((int*)Data);
	}
	inline const float GetFloat() const {
		return *((float*)Data);
	}
	inline const bool GetBool() const {
		return *((bool*)Data);
	}
	inline const cUID GetUID() const {
		return *((cUID*)Data);
	}
	inline const char* GetString() const {
		return (char*)Data;
	}

	// Data Changing -------------------------------------------------------------------------- - //
	inline void SetInt( const int Value ) {
		*((int*)Data) = Value;
	}
	inline void SetFloat( const float Value ) {
		*((float*)Data) = Value;
	}
	inline void SetBool( const bool Value ) {
		*((bool*)Data) = Value;
	}
	inline void SetUID( const cUID Value ) {
		*((cUID*)Data) = Value;
	}
//	inline void SetString( const int Value ) {
//		*((int*)Data) = Value;
//	}

	// Data Access ---------------------------------------------------------------------------- - //
	inline int* GetIntPtr() {
		return (int*)Data;
	}
	inline float* GetFloatPtr() {
		return (float*)Data;
	}
	inline bool* GetBoolPtr() {
		return (bool*)Data;
	}
	inline cUID* GetUIDPtr() {
		return (cUID*)Data;
	}
	inline char** GetStringPtr() {
		return (char**)Data;
	}
	
	// Create --------------------------------------------------------------------------------- - //
	inline static cRawFlex* new_Null() {
		char* Ptr = new char[ sizeof(cRawFlex) ];
		cRawFlex* Flex = new(Ptr) cRawFlex( FT_NULL, 0 );
		return Flex;
	}
	inline static cRawFlex* new_Int( const int Value ) {
		char* Ptr = new char[ sizeof(cRawFlex) + sizeof(int) ];
		cRawFlex* Flex = new(Ptr) cRawFlex( FT_INT, sizeof(int) );
		*(Flex->GetIntPtr()) = Value;
		return Flex;
	}
	inline static cRawFlex* new_Float( const float Value ) {
		char* Ptr = new char[ sizeof(cRawFlex) + sizeof(float) ];
		cRawFlex* Flex = new(Ptr) cRawFlex( FT_FLOAT, sizeof(float) );
		*(Flex->GetFloatPtr()) = Value;
		return Flex;
	}
	inline static cRawFlex* new_Bool( const bool Value ) {
		char* Ptr = new char[ sizeof(cRawFlex) + sizeof(bool) ];
		cRawFlex* Flex = new(Ptr) cRawFlex( FT_BOOL, sizeof(bool) );
		*(Flex->GetBoolPtr()) = Value;
		return Flex;
	}
	inline static cRawFlex* new_UID( const cUID Value ) {
		char* Ptr = new char[ sizeof(cRawFlex) + sizeof(cUID) ];
		cRawFlex* Flex = new(Ptr) cRawFlex( FT_UID, sizeof(cUID) );
		*(Flex->GetUIDPtr()) = Value;
		return Flex;
	}
	inline static cRawFlex* new_String( const char* Value ) {
		st32 Length = strlen( Value );
		char* Ptr = new char[ sizeof(cRawFlex) + (Length + 1) ];
		cRawFlex* Flex = new(Ptr) cRawFlex( FT_STRING, Length + 1 );
		memcpy( Flex->GetStringPtr(), Value, Length + 1 );
		return Flex;
	}
	// Variation where we know the string length (or want to substring by offsetting the base addr) //
	inline static cRawFlex* new_String( const char* Value, const st32 Length ) {
		char* Ptr = new char[ sizeof(cRawFlex) + (Length + 1) ];
		cRawFlex* Flex = new(Ptr) cRawFlex( FT_STRING, Length + 1 );
		memcpy( Flex->GetStringPtr(), Value, Length + 1 );
		return Flex;
	}
	inline static cRawFlex* new_String2( const char* Value, const char* Value2 ) {
		st32 Length = strlen( Value );
		st32 Length2 = strlen( Value2 );
		char* Ptr = new char[ sizeof(cRawFlex) + (Length + Length2 + 1) ];
		cRawFlex* Flex = new(Ptr) cRawFlex( FT_STRING, Length + Length2 + 1 );
		memcpy( Flex->GetStringPtr(), Value, Length );
		memcpy( &(Flex->Data[Length]), Value2, Length2 + 1 );
		return Flex;
	}
	// Variation where we know 1 string length //
	inline static cRawFlex* new_String2( const char* Value, const st32 Length, const char* Value2 ) {
		st32 Length2 = strlen( Value2 );
		char* Ptr = new char[ sizeof(cRawFlex) + (Length + Length2 + 1) ];
		cRawFlex* Flex = new(Ptr) cRawFlex( FT_STRING, Length + Length2 + 1 );
		memcpy( Flex->GetStringPtr(), Value, Length );
		memcpy( &(Flex->Data[Length]), Value2, Length2 + 1 );
		return Flex;
	}
	// Variation where we know both String lengths //
	inline static cRawFlex* new_String2( const char* Value, const st32 Length, const char* Value2, const st32 Length2 ) {
		char* Ptr = new char[ sizeof(cRawFlex) + (Length + Length2 + 1) ];
		cRawFlex* Flex = new(Ptr) cRawFlex( FT_STRING, Length + Length2 + 1 );
		memcpy( Flex->GetStringPtr(), Value, Length );
		memcpy( &(Flex->Data[Length]), Value2, Length2 + 1 );
		return Flex;
	}
	
	// Autodetect Flex type based on argument //
	inline static cRawFlex* new_Flex() {
		return new_Null();
	}
	inline static cRawFlex* new_Flex( const int Value ) {
		return new_Int( Value );
	}
	inline static cRawFlex* new_Flex( const float Value ) {
		return new_Float( Value );
	}
	inline static cRawFlex* new_Flex( const double Value ) {
		// For automatic type conversion (comment out function for strict 1.0f style syntax only) //
		return new_Float( Value );
	}
	inline static cRawFlex* new_Flex( const bool Value ) {
		return new_Bool( Value );
	}
	inline static cRawFlex* new_Flex( const cUID Value ) {
		return new_UID( Value );
	}
	inline static cRawFlex* new_Flex( const char* Value ) {
		return new_String( Value );
	}
	
	
	// Destroy -------------------------------------------------------------------------------- - //
	inline static void delete_Flex( cRawFlex* Flex ) {
		Flex->~cRawFlex();
		delete [] Flex;
	}

	// Nice ----------------------------------------------------------------------------------- - //
	inline const int ToInt() {
		if ( Type == FT_INT ) {
			return GetInt();
		}
		else if ( Type == FT_FLOAT ) {
			return (int)GetFloat();
		}
		else if ( Type == FT_BOOL ) {
			return (int)GetBool();
		}
		else if ( Type == FT_UID ) {
			return (int)GetUID().Get();
		}
		else if ( Type == FT_STRING ) {
			return atoi(GetString());
		}
		else {
			return 0;
		}
	}
	
	inline const float ToFloat() {
		if ( Type == FT_INT ) {
			return (float)GetInt();
		}
		else if ( Type == FT_FLOAT ) {
			return GetFloat();
		}
		else if ( Type == FT_BOOL ) {
			return GetBool();
		}
		else if ( Type == FT_UID ) {
			return (float)GetUID().Get();
		}
		else if ( Type == FT_STRING ) {
			return atof(GetString());
		}
		else {
			return 0;
		}
	}

	inline const bool ToBool() {
		if ( Type == FT_INT ) {
			return GetInt() != 0;
		}
		else if ( Type == FT_FLOAT ) {
			return GetFloat() != 0.0f;
		}
		else if ( Type == FT_BOOL ) {
			return GetBool();
		}
		else if ( Type == FT_UID ) {
			return true;
		}
		else if ( Type == FT_STRING ) {
			// TODO: decide whether a String converted to a bool should mean something other than true. //
			return true;
		}
		else {
			return false;
		}
	}
	
	// WARNING: A limit of 64 ToString calls can be made at a time, otherwise returned values may be bad //
	inline const char* ToString() {
		static char Text[64][128];		// 64 slots, 128 chars long (8,192 bytes). An Int is 10 chars long max. //
		static int CurrentText = 0;
		CurrentText++;
		CurrentText &= 63;
		
		if ( Type == FT_STRING ) {
			return GetString();
		}
		else if ( Type == FT_INT ) {
			safe_sprintf( Text[CurrentText], sizeof(Text[CurrentText]), "%i", GetInt() );
			return Text[CurrentText];
		}
		else if ( Type == FT_FLOAT ) {
			safe_sprintf( Text[CurrentText], sizeof(Text[CurrentText]), "%f", GetFloat() );
			return Text[CurrentText];
		}
		else if ( Type == FT_BOOL ) {
			if ( GetBool() )
				return "True";
			else
				return "False";
		}
		else if ( Type == FT_UID ) {
			safe_sprintf( Text[CurrentText], sizeof(Text[CurrentText]), "%i", GetUID().Get() );
			return Text[CurrentText];
		}
		else if ( Type == FT_NULL ) {
			return "Null";
		}
		else {
			return "Unknown Flex";
		}
	}
	
	inline const char* TypeToString() {
		if ( Type == FT_INT ) {
			return "Int";
		}
		else if ( Type == FT_FLOAT ) {
			return "Float";
		}
		else if ( Type == FT_BOOL ) {
			return "Bool";
		}
		else if ( Type == FT_UID ) {
			return "UID";
		}
		else if ( Type == FT_STRING ) {
			return "String";
		}
		else if ( Type == FT_NULL ) {
			return "Null";
		}
		else {
			return "Unknown";
		}		
	}
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
class flex {
public: // - Class Helpers -------------------------------------------------------------------- - //
	typedef flex thistype;
	inline void* GetThis() { return this; }
private: // - Members -------------------------------------------------------------------------- - //
	cRawFlex* Data;
public: // - Constructors and Destructors ------------------------------------------------------ - //
	inline flex() :
		Data( 0 )
	{
	}

	// Constructor //
	inline flex( const int _Value ) :
		Data( cRawFlex::new_Int( _Value ) )
	{
	}
	inline flex( const float _Value ) :
		Data( cRawFlex::new_Float( _Value ) )
	{
	}
	inline flex( const double _Value ) :
		Data( cRawFlex::new_Float( _Value ) )
	{
		// For automatic type conversion (comment out function for strict 1.0f style syntax only) //
	}
	inline flex( const bool _Value ) :
		Data( cRawFlex::new_Bool( _Value ) )
	{
	}
	inline flex( const cUID _Value ) :
		Data( cRawFlex::new_UID( _Value ) )
	{
	}
	inline flex( const char* _Value ) :
		Data( cRawFlex::new_String( _Value ) )
	{
	}
	
	// Copy Constructor //
	inline flex( const flex& Orig )
	{
		if ( Orig.Data == 0 ) { // Undefined //
			Data = 0;
		}
		else if (Orig.Data->Type == FT_NULL) {
			Data = cRawFlex::new_Null();
		}
		else if (Orig.Data->Type == FT_INT) {
			Data = cRawFlex::new_Int( Orig.GetInt() );
		}
		else if (Orig.Data->Type == FT_FLOAT) {
			Data = cRawFlex::new_Float( Orig.GetFloat() );
		}
		else if (Orig.Data->Type == FT_BOOL) {
			Data = cRawFlex::new_Bool( Orig.GetBool() );
		}
		else if (Orig.Data->Type == FT_UID) {
			Data = cRawFlex::new_UID( Orig.GetUID() );
		}
		else if (Orig.Data->Type == FT_STRING) {
			Data = cRawFlex::new_String( Orig.GetString() );
		}
	}
	
	// Assignment //
	inline flex& operator = ( const int _Value ) {
		if ( Data ) {
			if ( Data->Type == FT_INT ) {
				Data->SetInt( _Value );
				return *this;
			}
			else
				cRawFlex::delete_Flex( Data );
		}
		Data = cRawFlex::new_Int( _Value );
		return *this;
	}
	inline flex& operator = ( const float _Value ) {
		if ( Data ) {
			if ( Data->Type == FT_FLOAT ) {
				Data->SetFloat( _Value );
				return *this;
			}
			else
				cRawFlex::delete_Flex( Data );
		}
		Data = cRawFlex::new_Float( _Value );
		return *this;
	}
	inline flex& operator = ( const double _Value ) {
		if ( Data ) {
			if ( Data->Type == FT_FLOAT ) {
				Data->SetFloat( _Value );
				return *this;
			}
			else
				cRawFlex::delete_Flex( Data );
		}
		Data = cRawFlex::new_Float( _Value );
		return *this;
	}
	inline flex& operator = ( const bool _Value ) {
		if ( Data ) {
			if ( Data->Type == FT_BOOL ) {
				Data->SetBool( _Value );
				return *this;
			}
			else
				cRawFlex::delete_Flex( Data );
		}
		Data = cRawFlex::new_Bool( _Value );
		return *this;
	}
	inline flex& operator = ( const cUID _Value ) {
		if ( Data ) {
			if ( Data->Type == FT_UID ) {
				Data->SetUID( _Value );
				return *this;
			}
			else
				cRawFlex::delete_Flex( Data );
		}
		Data = cRawFlex::new_UID( _Value );
		return *this;
	}
	inline flex& operator = ( const char* _Value ) {
		// I always assume a string needs to be recreated to be reassigned //
		if ( Data )
			cRawFlex::delete_Flex( Data );
		Data = cRawFlex::new_String( _Value );
		return *this;
	}
	inline flex& operator = ( const flex& Orig ) {
		// NOTE: This could be faster if we checked for type equality and just set //
		if ( Data ) {
			cRawFlex::delete_Flex( Data );
		}

		// Copy Constructor Start //
		if ( Orig.Data == 0 ) { // Undefined //
			Data = 0;
		}
		else if (Orig.Data->Type == FT_NULL) {
			Data = cRawFlex::new_Null();
		}
		else if (Orig.Data->Type == FT_INT) {
			Data = cRawFlex::new_Int( Orig.GetInt() );
		}
		else if (Orig.Data->Type == FT_FLOAT) {
			Data = cRawFlex::new_Float( Orig.GetFloat() );
		}
		else if (Orig.Data->Type == FT_BOOL) {
			Data = cRawFlex::new_Bool( Orig.GetBool() );
		}
		else if (Orig.Data->Type == FT_UID) {
			Data = cRawFlex::new_UID( Orig.GetUID() );
		}
		else if (Orig.Data->Type == FT_STRING) {
			Data = cRawFlex::new_String( Orig.GetString() );
		}
		// Copy Constructor End //
		
		return *this;
	}
	
	// Destructor //	
	inline ~flex() {
		if ( Data )
			cRawFlex::delete_Flex( Data );
	}
	
	// Erase the contained data //
	inline void Clear() {
		if ( Data )
			cRawFlex::delete_Flex( Data );
		Data = 0;
	}		

public: // - Methods -------------------------------------------------------------------------- - //
	inline const eFlexType GetType() const {
		if ( Data ) {
			return Data->Type;
		}
		else {
			return FT_NULL;
		}
	}

	inline const int ToInt() const {
		if ( Data ) {
			return Data->ToInt();
		}
		else {
			return 0;
		}
	}

	inline const float ToFloat() const {
		if ( Data ) {
			return Data->ToFloat();
		}
		else {
			return 0.0f;
		}
	}

	inline const bool ToBool() const {
		if ( Data ) {
			return Data->ToBool();
		}
		else {
			return false;
		}
	}

	inline const char* ToString() const {
		if ( Data ) {
			return Data->ToString();
		}
		else {
			return "Undefined";
		}
	}

	inline const char* TypeToString() const {
		if ( Data ) {
			return Data->TypeToString();
		}
		else {
			return "Undefined";
		}
	}
	
	// Type Checks //
	inline const bool IsUndefined() {
		return Data == 0;
	}
	inline const bool IsNull() {
		if ( Data )
			return Data->IsNull();
		else
			return false;
	}
	inline const bool IsInt() {
		if ( Data )
			return Data->IsInt();
		else
			return false;
	}
	inline const bool IsFloat() {
		if ( Data )
			return Data->IsFloat();
		else
			return false;
	}
	inline const bool IsBool() {
		if ( Data )
			return Data->IsBool();
		else
			return false;
	}
	inline const bool IsUID() {
		if ( Data )
			return Data->IsUID();
		else
			return false;
	}
	inline const bool IsString() {
		if ( Data )
			return Data->IsString();
		else
			return false;
	}
	
	// Gets //
	inline const int GetSize() const {
		return Data->Size;
	}
	inline const int GetInt() const {
		// TODO: Assert Data //
		return Data->GetInt();
	}
	inline const float GetFloat() const {
		// TODO: Assert Data //
		return Data->GetFloat();
	}
	inline const bool GetBool() const {
		// TODO: Assert Data //
		return Data->GetBool();
	}
	inline const cUID GetUID() const {
		// TODO: Assert Data //
		return Data->GetInt();
	}
	inline const char* GetString() const {
		// TODO: Assert Data //
		return Data->GetString();
	}
	
	// Get Ptrs //
	inline int* GetIntPtr() {
		// TODO: Assert Data //
		return Data->GetIntPtr();
	}
	inline float* GetFloatPtr() {
		// TODO: Assert Data //
		return Data->GetFloatPtr();
	}
	inline bool* GetBoolPtr() {
		// TODO: Assert Data //
		return Data->GetBoolPtr();
	}
	inline cUID* GetUIDPtr() {
		// TODO: Assert Data //
		return Data->GetUIDPtr();
	}
	inline char** GetStringPtr() {
		// TODO: Assert Data //
		return Data->GetStringPtr();
	}
	
	// Operators -- Integers //
	inline flex& operator += ( const int _Value ) {
		if ( Data ) {
			if ( Data->Type == FT_INT ) {
				*this = Data->GetInt() + (int)_Value;
			}
			else if ( Data->Type == FT_FLOAT ) {
				*this = Data->GetFloat() + (float)_Value;
			}
			else if ( Data->Type == FT_STRING ) {
				static char Text[128];
				safe_sprintf( Text, sizeof(Text), "%i", _Value );

				cRawFlex* Old = Data;
				Data = cRawFlex::new_String2( Data->GetString(), Data->Size-1, Text );
				cRawFlex::delete_Flex( Old );
			}
		}
		else {
			Data = cRawFlex::new_Int( _Value );
		}
		return *this;
	}

	inline flex& operator -= ( const int _Value ) {
		if ( Data ) {
			if ( Data->Type == FT_INT ) {
				*this = Data->GetInt() - (int)_Value;
			}
			else if ( Data->Type == FT_FLOAT ) {
				*this = Data->GetFloat() - (float)_Value;
			}
		}
		else {
			Data = cRawFlex::new_Int( _Value );
		}
		return *this;
	}

	inline flex& operator *= ( const int _Value ) {
		if ( Data ) {
			if ( Data->Type == FT_INT ) {
				*this = Data->GetInt() * (int)_Value;
			}
			else if ( Data->Type == FT_FLOAT ) {
				*this = Data->GetFloat() * (float)_Value;
			}
		}
		else {
			Data = cRawFlex::new_Int( _Value );
		}
		return *this;
	}

	inline flex& operator /= ( const int _Value ) {
		if ( Data ) {
			if ( Data->Type == FT_INT ) {
				*this = Data->GetInt() / (int)_Value;
			}
			else if ( Data->Type == FT_FLOAT ) {
				*this = Data->GetFloat() / (float)_Value;
			}
		}
		else {
			Data = cRawFlex::new_Int( _Value );
		}
		return *this;
	}

	inline flex& operator %= ( const int _Value ) {
		if ( Data ) {
			if ( Data->Type == FT_INT ) {
				*this = Data->GetInt() % (int)_Value;
			}
			else {
				// Assert //
			}
		}
		else {
			Data = cRawFlex::new_Int( _Value );
		}
		return *this;
	}

	// Operators -- Floats //
	inline flex& operator += ( const float _Value ) {
		if ( Data ) {
			if ( Data->Type == FT_INT ) {
				*this = Data->GetInt() + (int)_Value;
			}
			else if ( Data->Type == FT_FLOAT ) {
				*this = Data->GetFloat() + (float)_Value;
			}
			else if ( Data->Type == FT_STRING ) {
				static char Text[128];
				safe_sprintf( Text, sizeof(Text), "%f", _Value );
				
				cRawFlex* Old = Data;
				Data = cRawFlex::new_String2( Data->GetString(), Data->Size-1, Text );
				cRawFlex::delete_Flex( Old );
			}
		}
		else {
			Data = cRawFlex::new_Float( _Value );
		}
		return *this;
	}

	inline flex& operator -= ( const float _Value ) {
		if ( Data ) {
			if ( Data->Type == FT_INT ) {
				*this = Data->GetInt() - (int)_Value;
			}
			else if ( Data->Type == FT_FLOAT ) {
				*this = Data->GetFloat() - (float)_Value;
			}
		}
		else {
			Data = cRawFlex::new_Float( _Value );
		}
		return *this;
	}

	inline flex& operator *= ( const float _Value ) {
		if ( Data ) {
			if ( Data->Type == FT_INT ) {
				*this = Data->GetInt() * (int)_Value;
			}
			else if ( Data->Type == FT_FLOAT ) {
				*this = Data->GetFloat() * (float)_Value;
			}
		}
		else {
			Data = cRawFlex::new_Float( _Value );
		}
		return *this;
	}

	inline flex& operator /= ( const float _Value ) {
		if ( Data ) {
			if ( Data->Type == FT_INT ) {
				*this = Data->GetInt() / (int)_Value;
			}
			else if ( Data->Type == FT_FLOAT ) {
				*this = Data->GetFloat() / (float)_Value;
			}
		}
		else {
			Data = cRawFlex::new_Float( _Value );
		}
		return *this;
	}
	
	// Operators -- Doubles (proxy) //
	inline flex& operator += ( const double _Value ) {
		return operator +=( (float)_Value );
	}
	inline flex& operator -= ( const double _Value ) {
		return operator -=( (float)_Value );
	}
	inline flex& operator *= ( const double _Value ) {
		return operator *=( (float)_Value );
	}
	inline flex& operator /= ( const double _Value ) {
		return operator /=( (float)_Value );
	}

	// Operators -- Boolean //
	inline flex& operator += ( const bool _Value ) {
		if ( Data ) {
			if ( Data->Type == FT_STRING ) {
				cRawFlex* Old = Data;
				Data = cRawFlex::new_String2( Data->GetString(), Data->Size-1, _Value ? "True" : "False" );
				cRawFlex::delete_Flex( Old );
			}
		}
		else {
			Data = cRawFlex::new_Bool( _Value );
		}
		return *this;
	}
		
	// Operators -- Strings //
	inline flex& operator += ( const char* _Value ) {
		if ( Data ) {
			static char Text[128];
			if ( Data->Type == FT_INT ) {
				safe_sprintf( Text, sizeof(Text), "%i", Data->GetInt() );
				cRawFlex* Old = Data;
				Data = cRawFlex::new_String2( Text, _Value );
				cRawFlex::delete_Flex( Old );
			}
			else if ( Data->Type == FT_FLOAT ) {
				safe_sprintf( Text, sizeof(Text), "%f", Data->GetFloat() );
				cRawFlex* Old = Data;
				Data = cRawFlex::new_String2( Text, _Value );
				cRawFlex::delete_Flex( Old );
			}
			else if ( Data->Type == FT_BOOL ) {
				cRawFlex* Old = Data;
				Data = cRawFlex::new_String2( Old->GetBool() ? "True" : "False", _Value );
				cRawFlex::delete_Flex( Old );
			}
			else if ( Data->Type == FT_UID ) {
				safe_sprintf( Text, sizeof(Text), "%i", Data->GetUID().Get() );
				cRawFlex* Old = Data;
				Data = cRawFlex::new_String2( Text, _Value );
				cRawFlex::delete_Flex( Old );
			}
			else if ( Data->Type == FT_STRING ) {
				cRawFlex* Old = Data;
				Data = cRawFlex::new_String2( Old->GetString(), Old->Size-1, _Value );
				cRawFlex::delete_Flex( Old );
			}
		}
		else {
			Data = cRawFlex::new_String( _Value );
		}
		return *this;
	}
	
	// Operators -- flexes //
	inline flex& operator += ( const flex& Orig ) {		
		if ( Data == 0 ) {
			return operator = ( Orig );
		}
		else if ( Orig.Data->Type == FT_INT ) {
			return operator += ( Orig.GetInt() );
		}
		else if ( Orig.Data->Type == FT_FLOAT ) {
			return operator += ( Orig.GetFloat() );
		}
		else if ( Orig.Data->Type == FT_BOOL ) {
			return operator += ( Orig.GetBool() );
		}
		else if ( Orig.Data->Type == FT_UID ) {
			return operator += ( Orig.GetUID() );
		}
		else if ( Orig.Data->Type == FT_STRING ) {
			return operator += ( Orig.GetString() );
		}
		return *this; // i.e. Orig is nothing of interest (Undefined, Null) //
	}

};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PLAYMORE_FLEX_H__ //
// - ------------------------------------------------------------------------------------------ - //
