// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_NETGET_H__
#define __GEL_NETGET_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Core/GelArray.h>
// - ------------------------------------------------------------------------------------------ - //
// GelArray<char>* types have 2 members: Size and Data //
//   Ret->Data would be a char*
//   Ret->Size would be the size in bytes //
// - ------------------------------------------------------------------------------------------ - //
// Zero Terminates the return data (suitable for any text uses) //
GelArray<char>* gelNetGetText( const char* URL );
GelArray<char>* gelNetPostText( const char* URL, const char* PostData );

// Does not zero terminate the return data //
GelArray<char>* gelNetGetBinary( const char* URL );
GelArray<char>* gelNetPostBinary( const char* URL, const char* PostData );
// - ------------------------------------------------------------------------------------------ - //
void gelNetInit( const bool DoWindowsInit = true );
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_NETGET_H__ //
// - ------------------------------------------------------------------------------------------ - //
