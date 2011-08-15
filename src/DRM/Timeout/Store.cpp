// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_STORE_TIMEOUT
// - ------------------------------------------------------------------------------------------ - //
#include <Timer/GelDate.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Debug/GelDebug.h>
#include "Store.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_WINDOWS
#include <windows.h>

#define Notice(_msg) \
	Log(_msg); \
    MessageBox( \
        NULL, \
        TEXT( _msg ), \
        TEXT("Smiles - Error"), \
        MB_OK | MB_ICONINFORMATION | MB_SETFOREGROUND \
        );
#elif defined(USES_UNIX)
#define Notice(_msg) \
	printf(_msg);
#else // !USES_WINDOWS //
#define Notice(_msg) \
	Log(_msg);
#endif // USES_WINDOWS //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
bool gelStoreAuthorize() {
	GelDate TestDate = new_GelDate( GEL_MARCH, 30, 2011 );
	
	Log( "- Initializing Timeout DRM (%i)\n", TestDate );

	bool Authorized = true;
	GelDate Now = get_GelDate();

	if ( Now > TestDate ) {
		Notice( "Exhibit version of Smiles has expired.  Please contact Mike (mike@sykhronics.com) for a newer version, or if in a pinch, set the computer date backwards.\n" );
		Authorized = false;
	}
	Log("\n");
	
	return Authorized;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void gelStoreExit() {
	Log( "- Shutting down Timeout DRM...\n" );
	Log( "\n" );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
int gelStoreGetExitCode() {
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_STORE_TIMEOUT //
// - ------------------------------------------------------------------------------------------ - //

