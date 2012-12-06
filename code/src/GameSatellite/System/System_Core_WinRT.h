// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_SYSTEM_CORE_WINRT_H__
#define __GEL_SYSTEM_CORE_WINRT_H__
// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_WINRT
// - ------------------------------------------------------------------------------------------ - //
namespace System {
// - ------------------------------------------------------------------------------------------ - //

// Unavailable in WinRT //
// http://msdn.microsoft.com/en-us/library/tehxacec%28v=vs.110%29.aspx //
// http://msdn.microsoft.com/en-us/library/tb2sfw2z.aspx //

// However, Username and other user info IS available //
// http://msdn.microsoft.com/en-us/library/windows/apps/windows.system.userprofile.userinformation.aspx //

// - ------------------------------------------------------------------------------------------ - //
inline const char* GetUserName() {
	return "User";
}
inline const char* GetComputerName() {
	return "Unknown";
}
inline const char** GetEnv() {
	static const char* Env[] = {0}; // Empty //
	return Env;
}
inline const char* GetEnv( const char* ) {
	return 0; // Null Ptr if variable doesn't exist //
}
// - ------------------------------------------------------------------------------------------ - //
};
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_WINRT //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_SYSTEM_CORE_WINRT_H__ //
// - ------------------------------------------------------------------------------------------ - //
